#pragma once

#include <termios.h>
#include <unistd.h>

namespace nulo {

class Terminal {
    termios original_;
    bool rawEnabled_ = false;

public:
    Terminal() = default;
    ~Terminal() { disable_raw_mode(); }

    Terminal(const Terminal&) = delete;
    Terminal& operator=(const Terminal&) = delete;

    void enable_raw_mode();
    void disable_raw_mode();
};

}