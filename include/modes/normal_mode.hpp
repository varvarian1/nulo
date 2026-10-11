#pragma once

#include "modes/mode.hpp"

namespace nulo {

class Editor;

namespace modes {

class NormalMode : public Mode {
public:
    void handle(const input::Key& k, Editor& ed) override;
    std::string name() const override { return "NORMAL"; }
};

}
}