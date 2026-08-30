#!/usr/bin/env bash
# Auto-fix formatting issues

set -e

echo "=== Auto-fixing Python code with ruff ==="
ruff check --fix esphome/
ruff format esphome/
echo "✓ Python code formatted"

echo ""
echo "=== Auto-fixing C++ code with clang-format ==="
if ! command -v clang-format &> /dev/null; then
    echo "⚠️  clang-format not found, skipping C++ formatting"
    echo "   Install with: brew install clang-format"
else
    find esphome/components -name '*.cpp' -o -name '*.h' -exec clang-format -i {} \;
    echo "✓ C++ code formatted"
fi

echo ""
echo "🎉 All code formatted!"
