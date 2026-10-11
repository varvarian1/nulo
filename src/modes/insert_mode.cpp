#include "modes/insert_mode.hpp"
#include "modes/normal_mode.hpp"
#include "app/editor.hpp"

namespace nulo::modes {

void InsertMode::handle(const input::Key& k, Editor& ed) {
    if (k.code == input::KeyCode::Escape) {
        ed.set_mode(std::make_unique<NormalMode>());
        return;
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