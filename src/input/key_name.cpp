#include "input/key_name.hpp"

namespace nulo::input {

std::string key_to_string(const Key& k) {
    switch (k.code) {
        case KeyCode::None:         return "None";
        case KeyCode::Enter:        return "Enter";
        case KeyCode::Escape:       return "Esc";
        case KeyCode::Backspace:    return "Backspace";
        case KeyCode::Tab:          return "Tab";
        case KeyCode::ArrowUp:      return "Up";
        case KeyCode::ArrowDown:    return "Down";
        case KeyCode::ArrowLeft:    return "Left";
        case KeyCode::ArrowRight:   return "Right";

        case KeyCode::Char: {
            std::string s;
            if (k.ctrl) s += "Ctrl+";
            if (k.alt)  s += "Alt+";
            s += k.ch;
            return s;
        }
    }

    return "?";
}

}