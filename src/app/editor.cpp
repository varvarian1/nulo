#include <unistd.h>
#include "app/editor.hpp"
#include "app/terminal.hpp"
#include "core/document.hpp"
#include "modes/normal_mode.hpp"
#include "ui/renderer.hpp"
#include "input/key_reader.hpp"
#include "input/key_name.hpp"

namespace nulo {

Editor::Editor(Terminal& term, std::string filepath)
    : term_(term),
      doc_(core::Document::open(filepath)),
      mode_(std::make_unique<modes::NormalMode>()) {}

void Editor::render() {
    std::string status = "-- " + mode_->name() + " --";
    if (!last_key_desc_.empty()) {
        status += "   Last key: " + last_key_desc_;
    }
    renderer_.draw(doc_, cursor_, viewport_, status);
}

void Editor::move_cursor(int drow, int dcol) {
    cursor_.row += drow;
    cursor_.col += dcol;
    cursor_.clamp(doc_);

    // content area = terminal height minus the status line
    int contentHeight = renderer_.height() - 1;
    if (contentHeight < 1) contentHeight = 1;
    viewport_.follow(cursor_, contentHeight);
}

void Editor::insert_char(char c) {
    doc_.insert(cursor_.row, cursor_.col, c);
    cursor_.col += 1;
}

void Editor::insert_newline() {
    doc_.insert_newline(cursor_.row, cursor_.col);
    cursor_.row += 1;
    cursor_.col = 0;
}

void Editor::delete_char() {
    doc_.erase(cursor_.row, cursor_.col);
    cursor_.clamp(doc_);
}

void Editor::backspace() {
    if (cursor_.col == 0 && cursor_.row == 0) return;
    if (cursor_.col > 0) {
        doc_.erase_before(cursor_.row, cursor_.col);
        cursor_.col -= 1;
    } else {
        int prev_len = static_cast<int>(doc_.line(cursor_.row - 1).size());
        doc_.erase_before(cursor_.row, cursor_.col);
        cursor_.row -= 1;
        cursor_.col = prev_len;
    }
}

void Editor::set_mode(std::unique_ptr<modes::Mode> m) {
    mode_ = std::move(m);
}

void Editor::run() {
    while (running_) {
        render();
        input::Key k = input::read_key();
        if (k.code != input::KeyCode::None) {
            last_key_desc_ = key_to_string(k);
            mode_->handle(k, *this);
        }
    }
    // clear screen on exit
    static constexpr char kCleanup[] = "\x1b[2J\x1b[H";
    ::write(STDOUT_FILENO, kCleanup, sizeof(kCleanup) - 1);
}

void Editor::quit() {
    running_ = false;
}

}