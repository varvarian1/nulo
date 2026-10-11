#include <iostream>
#include <string>
#include <stdexcept>
#include "app/terminal.hpp"
#include "app/editor.hpp"

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "usage: nulo <file>\n";
        return 1;
    }

    std::string filepath = (argc >= 2) ? argv[1] : "";

    try {
        nulo::Terminal term;
        term.enable_raw_mode();

        nulo::Editor ed(term, filepath);
        ed.run();
    } catch (const std::exception& e) {
        std::cerr << "error: " << e.what() << '\n';
        return 1;
    }

    return 0;
}