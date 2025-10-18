# c.exe - Cross-Architecture C Compiler/Linker/Runner/Package Manager

An opensource, cross-architecture (x86, x86_64, arm, arm64) C language compiler, linker, runner, and package manager.

## Features

- **Cross-Architecture Support**: Built to work on x86, x86_64, arm, and arm64 architectures
- **Multi-Mode Operation**:
  - **Compiler Mode**: Compile C source files to object files
  - **Linker Mode**: Link object files into executables
  - **Runner Mode**: Compile and immediately execute C programs
  - **Package Manager**: Manage C libraries and dependencies (coming soon)
- **Wrapper Around GCC**: Leverages the power of GCC with simplified interface
- **Portable**: Single executable that works across different architectures

## Building

```bash
make
```

This will create the `c.exe` executable for your current architecture.

## Installation

```bash
sudo make install
```

This installs `c.exe` to `/usr/local/bin`.

## Usage

### Basic Compilation

Compile a C program:
```bash
./c.exe program.c
```

This creates an executable named `a.out`.

### Compile with Output Name

```bash
./c.exe -o myprogram program.c
```

### Compile Only (Create Object File)

```bash
./c.exe -c module.c
```

This creates `module.o`.

### Link Object Files

```bash
./c.exe -l main.o module.o -o myprogram
```

### Run Mode (Compile and Execute)

```bash
./c.exe -r program.c
```

Compiles and immediately runs the program.

### With Compiler Flags

```bash
./c.exe -Wall -O2 -g program.c
```

### Target Specific Architecture

```bash
./c.exe --arch=arm64 program.c
```

### Version Information

```bash
./c.exe --version
```

### Help

```bash
./c.exe --help
```

## Command Line Options

### Modes
- `-c` - Compile only (produce object file)
- `-l` - Link mode (link object files)
- `-r` - Run mode (compile and execute)
- `-p` - Package manager mode
- `-v, --version` - Show version information
- `-h, --help` - Show help message

### Compiler Options
- `-o <file>` - Specify output file
- `-O<level>` - Optimization level (0-3)
- `-g` - Include debug information
- `-Wall` - Enable all warnings
- `-I<dir>` - Add include directory
- `-L<dir>` - Add library directory
- `-l<lib>` - Link with library
- `--arch=<arch>` - Target architecture (x86|x86_64|arm|arm64)

## Examples

### Simple Hello World

Create `hello.c`:
```c
#include <stdio.h>

int main() {
    printf("Hello, World!\n");
    return 0;
}
```

Compile and run:
```bash
./c.exe hello.c
./a.out
```

Or use run mode:
```bash
./c.exe -r hello.c
```

### Multi-File Project

Compile modules separately:
```bash
./c.exe -c main.c
./c.exe -c utils.c
./c.exe -l main.o utils.o -o myapp
```

### With Libraries

```bash
./c.exe -o server server.c -lpthread -lm
```

## Architecture Support

c.exe automatically detects and supports the following architectures:
- **x86** - 32-bit Intel/AMD processors
- **x86_64** - 64-bit Intel/AMD processors (amd64)
- **arm** - 32-bit ARM processors
- **arm64** - 64-bit ARM processors (aarch64)

The tool will display the detected architecture when you run:
```bash
./c.exe --version
```

## Package Manager (Coming Soon)

The package manager mode will support:
- Installing C libraries and headers
- Managing dependencies
- Cross-architecture package support

## Development

### Building from Source

```bash
git clone https://github.com/partnernetsoftware/c
cd c
make
```

### Running Tests

```bash
make test
```

### Clean Build

```bash
make clean
make
```

## License

This project is opensource. Please check the LICENSE file for details.

## Contributing

Contributions are welcome! Please feel free to submit pull requests or open issues for bugs and feature requests.

## Architecture

c.exe is built as a wrapper around GCC, providing a simplified and unified interface for common C development tasks across different architectures. It detects the host architecture at runtime and can target different architectures through the `--arch` flag.

The tool is designed to be:
- **Simple**: Easy to use interface for common tasks
- **Portable**: Single binary works across architectures
- **Extensible**: Easy to add new features and modes
- **Fast**: Minimal overhead over direct GCC usage

## Roadmap

- [x] Cross-architecture support
- [x] Compiler mode
- [x] Linker mode  
- [x] Runner mode
- [ ] Package manager implementation
- [ ] Cross-compilation support
- [ ] Build system integration
- [ ] Plugin system
- [ ] Optimization profiles
