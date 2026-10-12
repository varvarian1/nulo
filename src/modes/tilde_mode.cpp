#include "modes/tilde_mode.hpp"
#include "modes/normal_mode.hpp"
#include "app/editor.hpp"

namespace nulo::modes {

void TildeMode::handle(const input::Key& k, Editor& ed) {
    // Esc cancels and returns to Normal
    if (k.code == input::KeyCode::Escape) {
        ed.set_mode(std::make_unique<NormalMode>());
        return;
    }

    // backspace: remove last char from buffer
    if (k.code == input::KeyCode::Backspace) {
        if (!buffer_.empty()) buffer_.pop_back();
        return;
    }

    // enter: execute the command
    if (k.code == input::KeyCode::Enter) {
        execute(ed);
        return;
    }

    // regular character: append to buffer
    if (k.code == input::KeyCode::Char && !k.ctrl && !k.alt) {
        buffer_ += k.ch;
        return;
    }
}

void TildeMode::execute(Editor& ed) {
    const std::string cmd = buffer_;

    ed.set_mode(std::make_unique<NormalMode>());

    if (cmd == "s") {
        ed.save();
    } else if (cmd == "q") {
        ed.quit();
    } else if (cmd == "sq" || cmd == "qs") {
        ed.save();
        ed.quit();
    } else {
        ed.set_status("unknown command: " + cmd);
    }
}

}
