#include <sys/ioctl.h>
#include <unistd.h>
#include <cstdio>
#include "ui/renderer.hpp"
#include "core/document.hpp"
#include "core/cursor.hpp"
#include "core/viewport.hpp"

namespace nulo::ui {

namespace {

// ANSI escape sequences used by the renderer
// All CSI sequences start with ESC [ - see ECMA-48
constexpr std::string_view kClearScreen = "\x1b[2J";
constexpr std::string_view kCursorHome  = "\x1b[H";
constexpr std::string_view kResetAttrs  = "\x1b[0m";
constexpr std::string_view kInvert      = "\x1b[7m"; // reverse video
constexpr std::string_view kEraseLine   = "\x1b[K"; // clear to end of line

}

Renderer::Renderer() {
    refresh_size();
}

void Renderer::refresh_size() {
    winsize ws{};
    if (ioctl(STDOUT_FILENO, TIOCGWINSZ, &ws) == 0) {
        if (ws.ws_col > 0) width_ = ws.ws_col;
        if (ws.ws_row > 0) height_ = ws.ws_row;
    }
}

void Renderer::move_to(int row, int col) {
    // ANSI coordinates are 1-based
    char seq[32];
    int n = std::snprintf(seq, sizeof(seq), "\x1b[%d;%dH", row + 1, col + 1);
    buf_.append(seq, n);
}

void Renderer::write(std::string_view s) {
    buf_.append(s);
}

void Renderer::flush() {
    ::write(STDOUT_FILENO, buf_.data(), buf_.size());
    buf_.clear();
}

void Renderer::draw(const core::Document& doc,
                    const core::Cursor& cursor,
                    const core::Viewport& viewport,
                    std::string_view status) {
    refresh_size();

    const int contentHeight = height_ - 1; // last row is the status line
    const int top = viewport.top_row();

    buf_.clear();

    write(kCursorHome);
    write(kClearScreen);

    for (int screenRow = 0; screenRow < contentHeight; ++screenRow) {
        move_to(screenRow, 0);

        int docRow = top + screenRow;

        if (docRow < doc.line_count()) {
            const std::string& line = doc.line(docRow);
            // truncate to terminal width to avoid wrapping
            int len = static_cast<int>(line.size());
            if (len > width_) len = width_;
            buf_.append(line.data(), len);
        } else {
            // padding marker for lines past EOF
            write(".");
        }

        write(kEraseLine);
    }

    // status line at the bottom, in reverse video, padded to full width
    move_to(contentHeight, 0);
    write(kInvert);
    buf_.append(status);
    for (int i = static_cast<int>(status.size()); i < width_; ++i) {
        buf_.push_back(' ');
    }
    write(kResetAttrs);

    // only position the terminal cursor if it's visible in the viewport
    int screenCursorRow = cursor.row - top;
    int screenCursorCol = cursor.col;
    if (screenCursorRow >= 0 && screenCursorRow < contentHeight) {
        move_to(screenCursorRow, screenCursorCol);
    }

    flush();
}

}