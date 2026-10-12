#pragma once

#include "modes/mode.hpp"

namespace nulo::modes {

class TildeMode : public Mode {
public:
    void handle(const input::Key& k, Editor& ed) override;
    std::string name() const override { return "TILDE"; }
    std::string command_line() const override { return buffer_; }

private:
    void execute(Editor& ed);
    std::string buffer_;
};

}
