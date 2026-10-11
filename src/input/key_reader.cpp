#include <unistd.h>
#include <string>
#include "input/key_reader.hpp"

namespace nulo::input {

namespace {

// reads one byte. Returns false on timeout or error
bool read_byte(unsigned char& out) {
    unsigned char c;
    if (::read(STDIN_FILENO, &c, 1) != 1) return false;
    out = c;
    return true;
}

}

Key read_key() {
    unsigned char c; // first byte read
    if (!read_byte(c)) return {};

    // Ctrl+letter: terminal sends 0x01..0x1A for Ctrl+A..Ctrl+Z
    if (c >= 1 && c <= 26) {
        switch (c) {
            case 9:  return {KeyCode::Tab};
            case 10: return {KeyCode::Enter};
            case 13: return {KeyCode::Enter};
            default: return {KeyCode::Char, static_cast<char>('a' + c - 1), true, false};
        }
    }
    if (c == 127) return {KeyCode::Backspace};

    // escape sequence: either bare Escape, or a multi-byte sequence
    if (c == 0x1b) {
        unsigned char second;
        // if no byte arrives within VTIME, this was a bare Escape
        if (!read_byte(second)) {
            return {KeyCode::Escape};
        }

        // CSI (ESC [) and SS3 (ESC O) both introduce key sequences
        if (second == '[' || second == 'O') {
            std::string seq;
            seq += second;

            while (true) {
                unsigned char b;
                if (!read_byte(b)) return {KeyCode::None};
                seq += static_cast<char>(b);

                // letters terminate (CSI), and '~' terminates
                if ((b >= 'A' && b <= 'Z') || (b >= 'a' && b <= 'z') || b == '~') {
                    break;
                }
            }
            
            // normalize SS3 to CSI so both prefixes share the same match table
            if (seq[0] == 'O') seq[0] = '[';
            
            // now match full sequence
            if (seq == "[A") return {KeyCode::ArrowUp};
            if (seq == "[B") return {KeyCode::ArrowDown};
            if (seq == "[C") return {KeyCode::ArrowRight};
            if (seq == "[D") return {KeyCode::ArrowLeft};

            return {KeyCode::None};
        }

        // ESC + something: Alt+<key> on most terminals
        return {KeyCode::Char, static_cast<char>(second), false, true};
    }

    return {KeyCode::Char, static_cast<char>(c), false, false};
}

}