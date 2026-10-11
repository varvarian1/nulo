#include "core/viewport.hpp"
#include "core/cursor.hpp"

namespace nulo::core {

void Viewport::follow(const Cursor& cur, int screenHeight) {
    if (cur.row < top_) {
        top_ = cur.row;
    } else if (cur.row >= top_ + screenHeight) {
        top_ = cur.row - screenHeight + 1;
    }
}

}