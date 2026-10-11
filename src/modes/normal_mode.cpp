#include "modes/normal_mode.hpp"
#include "modes/insert_mode.hpp"
#include "app/editor.hpp"

namespace nulo::modes {

void NormalMode::handle(const input::Key& k, Editor& ed) {
    if (k.code == input::KeyCode::Char) {
        switch (k.ch) {
            case 'q': ed.quit(); return;
            case 'i': ed.set_mode(std::make_unique<InsertMode>()); return;
        }
    }

    switch (k.code) {
        case input::KeyCode::ArrowUp:       ed.move_cursor(-1, 0); break;
        case input::KeyCode::ArrowDown:     ed.move_cursor(1, 0);  break;
        case input::KeyCode::ArrowLeft:     ed.move_cursor(0, -1); break;
        case input::KeyCode::ArrowRight:    ed.move_cursor(0, 1);  break;
        default: break;
    }
}

}