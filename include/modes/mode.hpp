#pragma once

#include <string>
#include "input/key.hpp"

namespace nulo {

class Editor;

namespace modes {

class Mode {
public:
    virtual ~Mode() = default;
    virtual void handle(const input::Key& k, Editor& ed) = 0;
    virtual std::string name() const = 0;
};

}
}