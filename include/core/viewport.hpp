#pragma once

namespace nulo::core {

class Cursor;

class Viewport {
public:
    void follow(const Cursor& cur, int screenHeight);
    int top_row() const { return top_; }

private:
    int top_ = 0;
};
}