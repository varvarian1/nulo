#pragma once

#include <string>

#include "input/key.hpp"

namespace nulo::input {

// human-readable representation of a key, for debugging/status line
std::string key_to_string(const Key& k);

}