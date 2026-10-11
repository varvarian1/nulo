#pragma once

#include <string>
#include <string_view>

namespace nulo {

namespace core {
class Document;
struct Cursor;
class Viewport;
}

namespace ui {

class Renderer {
public:
    Renderer();

    int width() const { return width_; }
    int height() const { return height_; }

    // draws a full frame: content, status line, cursor position
    void draw(const core::Document& doc,
              const core::Cursor& cursor,
              const core::Viewport& viewport,
              std::string_view status);

private:
    void refresh_size();
    void move_to(int row, int col);
    void write(std::string_view s);
    void flush();

    std::string buf_;
    int width_ = 80;
    int height_ = 24;
};

}
}