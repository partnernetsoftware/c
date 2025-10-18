# Makefile for c.exe - Cross-Architecture C Compiler/Linker/Runner/Package Manager

CC = gcc
CFLAGS = -Wall -Wextra -O2
TARGET = c.exe
SRC = c.c

# Detect current architecture
ARCH := $(shell uname -m)

.PHONY: all clean install test help

all: $(TARGET)
	@echo "Build complete for architecture: $(ARCH)"
	@echo "Run './$(TARGET) --version' to verify installation"

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) -o $(TARGET) $(SRC)

clean:
	rm -f $(TARGET) *.o a.out /tmp/c_exe_temp_output

install: $(TARGET)
	@echo "Installing $(TARGET) to /usr/local/bin (requires sudo)"
	@sudo cp $(TARGET) /usr/local/bin/$(TARGET)
	@sudo chmod 755 /usr/local/bin/$(TARGET)
	@echo "Installation complete"

test: $(TARGET)
	@echo "Running basic tests..."
	./$(TARGET) --version
	./$(TARGET) --help
	@echo "Tests complete"

test-full: $(TARGET)
	@echo "Running comprehensive test suite..."
	@chmod +x test_suite.sh
	@./test_suite.sh

help:
	@echo "Makefile for c.exe"
	@echo ""
	@echo "Targets:"
	@echo "  all       - Build c.exe (default)"
	@echo "  clean     - Remove built files"
	@echo "  install   - Install c.exe to /usr/local/bin"
	@echo "  test      - Run basic tests"
	@echo "  test-full - Run comprehensive test suite"
	@echo "  help      - Show this help message"
	@echo ""
	@echo "Current architecture: $(ARCH)"
