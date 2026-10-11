#pragma once

#include "input/key.hpp"

namespace nulo::input {

// blocking read with the termios timeout (VMIN=0, VTIME=1)
// returns Key{KeyCode::None} if nothing was typed within ~100ms
Key read_key();

}