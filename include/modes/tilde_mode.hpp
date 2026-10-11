#pragma once

#include "modes/mode.hpp"

namespace nulo::modes {

class TildeMode : public Mode {
public:
    void handle(const input::Key& k, Editor& ed) override;
    std::string name() const override { return "TILDE"; }
};

}