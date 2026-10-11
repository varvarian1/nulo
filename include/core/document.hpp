#pragma once

#include <string>
#include <vector>
#include <cstddef>

namespace nulo::core {

class Document {
public:
    static Document open(const std::string& path);

    int line_count() const { return static_cast<int>(lines_.size()); }
    const std::string& line(int row) const { return lines_[row]; }

    void insert(int row, int col, char c);
    void insert_newline(int row, int col);
    void erase(int row, int col);
    void erase_before(int row, int col);

    bool save();

private:
    std::vector<std::string> lines_{""};
    std::string path_;
};

}