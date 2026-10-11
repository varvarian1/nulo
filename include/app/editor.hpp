#pragma once

#include <string>
#include <string_view>
#include <memory>
#include "core/document.hpp"
#include "core/cursor.hpp"
#include "core/viewport.hpp"
#include "input/key.hpp"
#include "modes/mode.hpp"
#include "ui/renderer.hpp"

namespace nulo {

class Terminal;

using namespace core;
using namespace input;
using namespace ui;
using modes::Mode;

class Editor {
public:
    Editor(Terminal& term, std::string filepath);
    ~Editor() = default;

    Editor(const Editor&) = delete;
    Editor& operator=(const Editor&) = delete;

    void run();

    const Document& document() const { return doc_; }
    const Cursor&   cursor()   const { return cursor_; }
    const Viewport& viewport() const { return viewport_; }
    Mode&           mode()           { return *mode_; }

    void quit();
    bool is_running() const { return running_; }

    void move_cursor(int drow, int dcol);
    void move_cursor_to(int row, int col);

    void insert_char(char c);
    void insert_newline();
    void delete_char();
    void backspace();

    void save();
    void set_status(std::string_view msg);

    void set_mode(std::unique_ptr<Mode> m);

private:
    void handle_key(const Key& k);
    void render();

    Terminal&   term_;
    Document    doc_;
    Cursor      cursor_;
    Viewport    viewport_;
    Renderer    renderer_;
    std::unique_ptr<modes::Mode> mode_;

    std::string last_key_desc_;

    std::string status_message_;
    bool running_ = true;
};

}