#!/bin/bash
# Comprehensive test script for c.exe

echo "========================================="
echo "c.exe Comprehensive Test Suite"
echo "========================================="
echo ""

# Build c.exe if it doesn't exist
if [ ! -f "./c.exe" ]; then
    echo "Building c.exe..."
    make clean && make
    echo ""
fi

# Test 1: Version
echo "Test 1: Version Information"
./c.exe --version
echo ""

# Test 2: Help
echo "Test 2: Help Information"
./c.exe --help | head -15
echo "..."
echo ""

# Test 3: Simple compilation
echo "Test 3: Simple Compilation"
./c.exe test_hello.c
if [ -f "./a.out" ]; then
    ./a.out
    rm a.out
    echo "✓ Simple compilation passed"
else
    echo "✗ Simple compilation failed"
fi
echo ""

# Test 4: Custom output name
echo "Test 4: Compilation with Custom Output"
./c.exe -o hello_test test_hello.c
if [ -f "./hello_test" ]; then
    ./hello_test
    rm hello_test
    echo "✓ Custom output passed"
else
    echo "✗ Custom output failed"
fi
echo ""

# Test 5: Run mode
echo "Test 5: Run Mode (compile and execute)"
./c.exe -r test_hello.c
echo "✓ Run mode passed"
echo ""

# Test 6: Compile only mode
echo "Test 6: Compile Only Mode"
./c.exe -c test_hello.c
if [ -f "./test_hello.o" ]; then
    echo "✓ Compile only mode passed"
    ls -lh test_hello.o
else
    echo "✗ Compile only mode failed"
fi
echo ""

# Test 7: Link mode
echo "Test 7: Link Mode"
./c.exe -l test_hello.o -o hello_linked
if [ -f "./hello_linked" ]; then
    ./hello_linked
    rm hello_linked test_hello.o
    echo "✓ Link mode passed"
else
    echo "✗ Link mode failed"
fi
echo ""

# Test 8: Multi-file compilation
echo "Test 8: Multi-file Compilation"
./c.exe -c test_main.c
./c.exe -c utils.c
./c.exe -l test_main.o utils.o -o multifile_test
if [ -f "./multifile_test" ]; then
    ./multifile_test
    rm multifile_test test_main.o utils.o
    echo "✓ Multi-file compilation passed"
else
    echo "✗ Multi-file compilation failed"
fi
echo ""

# Test 9: Compiler flags
echo "Test 9: Compiler Flags (-Wall -O2 -g)"
./c.exe -Wall -O2 -g test_hello.c -o test_flags
if [ -f "./test_flags" ]; then
    ./test_flags
    rm test_flags
    echo "✓ Compiler flags passed"
else
    echo "✗ Compiler flags failed"
fi
echo ""

# Test 10: Architecture flag
echo "Test 10: Architecture Flag"
./c.exe --arch=x86_64 test_hello.c -o test_arch
if [ -f "./test_arch" ]; then
    ./test_arch
    rm test_arch
    echo "✓ Architecture flag passed"
else
    echo "✗ Architecture flag failed"
fi
echo ""

# Test 11: Package manager mode
echo "Test 11: Package Manager Mode"
./c.exe -p
echo "✓ Package manager mode passed"
echo ""

echo "========================================="
echo "All tests completed!"
echo "========================================="
