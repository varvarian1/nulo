#include <fstream>
#include "core/document.hpp"

namespace nulo::core {

Document Document::open(const std::string& path) {
    Document doc;
    doc.path_ = path;

    std::ifstream in(path);
    if (!in) return doc;

    doc.lines_.clear();
    std::string line;
    while (std::getline(in, line)) {
        doc.lines_.push_back(line);
    }
    if (doc.lines_.empty()) doc.lines_.push_back("");
    return doc;
}

void Document::insert(int row, int col, char c) {
    lines_[row].insert(lines_[row].begin() + col, c);
}

void Document::insert_newline(int row, int col) {
    auto& cur = lines_[row];
    std::string tail = cur.substr(col);
    cur.erase(col);
    lines_.insert(lines_.begin() + row + 1, tail);
}

void Document::erase(int row, int col) {
    auto& cur = lines_[row];
    if (col < static_cast<int>(cur.size())) {
        cur.erase(col, 1);
    } else if (row + 1 < line_count()) {
        cur += lines_[row + 1];
        lines_.erase(lines_.begin() + row + 1);
    }
}

void Document::erase_before(int row, int col) {
    if (col > 0) {
        lines_[row].erase(col - 1, 1);
    } else if (row > 0) {
        lines_[row - 1] += lines_[row];
        lines_.erase(lines_.begin() + row);
    }
}

bool Document::save() {
    std::ofstream out(path_);
    if (!out) return false;
    for (size_t i = 0; i < lines_.size(); ++i) {
        out << lines_[i];
        if (i + 1 < lines_.size()) out << '\n';
    }
    return true;
}

}