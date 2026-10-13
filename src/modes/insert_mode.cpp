#include "modes/insert_mode.hpp"
#include "modes/normal_mode.hpp"
#include "app/editor.hpp"

namespace nulo::modes {

void InsertMode::handle(const input::Key& k, Editor& ed) {
    if (k.code == input::KeyCode::Escape) {
        ed.set_mode(std::make_unique<NormalMode>());
        return;
    }

    switch (k.code) {
        case input::KeyCode::ArrowUp: {
            ed.move_cursor(-1, 0); return;
        }
        case input::KeyCode::ArrowDown: {
            ed.move_cursor(1, 0); return;
        }
        case input::KeyCode::ArrowLeft: {
            ed.move_cursor(0, -1); return;
        }
        case input::KeyCode::ArrowRight: {
            ed.move_cursor(0, 1); return;
        }
        case input::KeyCode::Home: { 
            ed.move_to_line_start(); return;
        }
        case input::KeyCode::End: {
            ed.move_to_line_end(); return;
        }
        case input::KeyCode::Delete: { 
            ed.delete_char(); return;
        }
        default: break;
    }

    if (k.code == input::KeyCode::Enter) {
        ed.insert_newline();
        return;
    }
    if (k.code == input::KeyCode::Backspace) {
        ed.backspace();
        return;
    }
    if (k.code == input::KeyCode::Tab) {
        ed.insert_char('\t');
        return;
    }
    if (k.code == input::KeyCode::Char && !k.ctrl && !k.alt) {
        ed.insert_char(k.ch);
        return;
    }
}

}