#pragma once

namespace nulo::input {

enum class KeyCode {
    None,       // no key (read timeout)
    Char,       // printable character, see `ch`
    Enter,
    Escape,
    Backspace,
    Tab,
    ArrowUp,
    ArrowDown,
    ArrowLeft,
    ArrowRight,
    Home,
    End,
    Delete
};

struct Key {
    KeyCode code = KeyCode::None;
    char ch = 0; // valid only when code == Char
    bool ctrl = false; // Ctrl held (for Ctrl+A etc.)
    bool alt = false; // Alt held
};

}