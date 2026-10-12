# nulo

A minimal modal text editor for the terminal, written in C++ from scratch.

## Features

- Modal editing (Normal, Insert)
- Vim-style keybindings
- Command line with `~` prefix
- ANSI-based terminal rendering

## Building 

Requires:
- CMake 3.16+
- A C++20 compiler (GCC 10+, Clang 11+)
- A POSIX-compatible system (Linux)

```bash
git clone https://github.com/varvarian1/nulo.git
cd nulo
cmake -B build
cmake --build build
```

## Usage 

```bash
./output/nulo <file>
```

### Normal mode

| Keys | Action |
|---|---|
| `Arrow keys` | Move cursor (left, down, up, right) |
| `i` | Enter Insert mode |
| `~` | Enter command mode |
| `q` | Quit |

### Insert mode

| Keys | Action |
|---|---|
| `Esc` | Return to Normal mode |
| Any character | Insert at cursor |
| `Enter` | New line |
| `Backspace` | Delete before cursor |
| `Tab` | Insert tab |

### Command mode (`~` prefix)

| Command | Action |
|---|---|
| `~s` | Save file |
| `~q` | Quit |
| `~sq` or `~qs` | Save and quit |
| `Esc` | Cancel |

## Architecture

```
src/
├── app/      Editor, Terminal
├── core/     Document, Cursor, Viewport
├── input/    key reading, escape sequence parsing
├── modes/    Mode interface + Normal, Insert, Tilde
└── ui/       Renderer
```

## License

This project is licensed under the MIT License.
MIT - see [LICENSE](LICENSE) for details.