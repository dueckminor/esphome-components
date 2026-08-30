# Local Development Setup

## Setup Virtual Environment (Recommended)

Create a virtual environment with all dependencies:

```bash
# Create virtual environment
python3 -m venv .venv

# Activate it
source .venv/bin/activate

# Install the project with dev dependencies
pip install -e ".[dev]"

# Install C++ formatter (macOS)
brew install clang-format

# Or on Linux
# sudo apt-get install clang-format
```

## Prerequisites (Alternative: Manual Install)

If you prefer not to use a virtual environment:

```bash
# Install Python dependencies
pip install esphome ruff

# Install pre-commit (optional, for automatic checks)
pip install pre-commit

# Install C++ formatter (macOS)
brew install clang-format

# Or on Linux
# sudo apt-get install clang-format
```

## Quick Start

### Check code (same as CI)
```bash
./scripts/lint.sh
```

### Auto-fix formatting
```bash
./scripts/format.sh
```

### Individual tools

**Python:**
```bash
# Check for issues
ruff check esphome/

# Auto-fix issues
ruff check --fix esphome/

# Check formatting
ruff format --check esphome/

# Auto-format
ruff format esphome/
```

**C++:**
```bash
# Check formatting
find esphome/components -name '*.cpp' -o -name '*.h' -exec clang-format --dry-run --Werror {} \;

# Auto-format
find esphome/components -name '*.cpp' -o -name '*.h' -exec clang-format -i {} \;
```

## Pre-commit Hooks (Recommended)

Automatically run checks before each commit:

```bash
# Install the hooks
pre-commit install

# Run manually on all files
pre-commit run --all-files
```

Once installed, the checks run automatically on `git commit`. If they fail, the commit is blocked until you fix the issues (or use `git commit --no-verify` to skip).
