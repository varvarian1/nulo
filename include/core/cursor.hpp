#pragma once

namespace nulo::core {

class Document;

struct Cursor {
    int row = 0;
    int col = 0;

    void clamp(const Document& doc);
};
}