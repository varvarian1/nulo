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

    if (k.code != input::KeyCode::Char) return;

    switch (k.ch) {
        case 's':
            ed.save();
            return;  // stay in TildeMode

        case 'q':
            ed.quit();
            return;
 
        default:
            // unknown tilde command - cancel
            ed.set_mode(std::make_unique<NormalMode>());
            return;
    }
}

}