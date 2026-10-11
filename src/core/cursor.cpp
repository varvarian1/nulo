#include "core/cursor.hpp"
#include "core/document.hpp"

namespace nulo::core {

void Cursor::clamp(const Document& doc) {
    if (row < 0) row = 0;
    if (row >= doc.line_count()) row = doc.line_count() - 1;
    if (row < 0) row = 0;

    int len = static_cast<int>(doc.line(row).size());
    if (col < 0) col = 0;
    if (col > len) col = len;
}

}