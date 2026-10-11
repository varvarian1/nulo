#include <cstdlib>
#include <stdexcept>
#include <system_error>
#include <cerrno>
#include "app/terminal.hpp"

namespace nulo {

void Terminal::enable_raw_mode() {
    if (rawEnabled_) throw std::logic_error("enable_raw_mode: raw mode already enabled");

    // tcgetattr: "get attributes" - read current terminal settings
    if (tcgetattr(STDIN_FILENO, &original_) == -1) {
        throw std::system_error(errno, std::generic_category(), "tcgetattr");
    }

    termios raw = original_;

    // lflag: local (line-discipline) flags
    // ECHO   - don't print typed characters back to the screen
    // ICANON - disable line buffering; read byte-by-byte, no Enter needed
    // ISIG   - disable Ctrl+C / Ctrl+Z signals
    // IEXTEN - disable extended input processing (e.g. Ctrl+V)
    raw.c_lflag &= ~(ECHO | ICANON | ISIG | IEXTEN);
    
    // IXON   - disable Ctrl+S / Ctrl+Q software flow control
    // ICRNL  - don't translate CR (\r) to NL (\n) on input
    // BRKINT - don't send SIGINT on a break condition
    // INPCK  - disable input parity checking
    // ISTRIP - don't strip the 8th bit; keep full 8-bit input
    raw.c_iflag &= ~(IXON | ICRNL | BRKINT | INPCK | ISTRIP);
    
    // oflag: output flags
    // OPOST - disable output post-processing (\n -> \r\n etc.)
    raw.c_oflag &= ~(OPOST);
    
    // cflag: output flags
    // CS8 - use 8 bits per character
    raw.c_cflag |= CS8;

    // c_cc: control characters
    raw.c_cc[VMIN] = 0; // read() returns even if 0 bytes are available
    raw.c_cc[VTIME] = 1; // ...but wait at most 0.1s (1 decisecond) for input

    /* tcsetattr: "set attributes" - apply the new settings to the terminal.
     * TCSAFLUSH discards pending input before switching, so keys pressed
     * before entering raw mode don't leak into the editor. */
    if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw) == -1) {
        throw std::system_error(errno, std::generic_category(), "tcsetattr");
    }
    rawEnabled_ = true;
}

void Terminal::disable_raw_mode() {
    if (!rawEnabled_) throw std::logic_error("disable_raw_mode: raw mode not enabled");

    // restore the original terminal settings saved in enable_raw_mode()
    // TCSAFLUSH discards anything typed but not yet read
    if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &original_) == -1) {
        throw std::system_error(errno, std::generic_category(), "tcsetattr");
    }
    rawEnabled_ = false;
}

}