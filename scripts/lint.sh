#!/usr/bin/env bash
# Local linting script - runs the same checks as CI

set -e

echo "=== Running Python linting with ruff ==="
ruff check esphome/
echo "✓ Ruff linting passed"

echo ""
echo "=== Checking Python formatting with ruff ==="
ruff format --check esphome/
echo "✓ Ruff formatting check passed"

echo ""
echo "=== Checking C++ formatting with clang-format ==="
if ! command -v clang-format &> /dev/null; then
    echo "⚠️  clang-format not found, skipping C++ checks"
    echo "   Install with: brew install clang-format"
else
    find esphome/components -name '*.cpp' -o -name '*.h' | while read file; do
        clang-format --dry-run --Werror "$file" 2>&1 || {
            echo "✗ Formatting issues in $file"
            exit 1
        }
    done
    echo "✓ C++ formatting check passed"
fi

echo ""
echo "🎉 All checks passed!"
