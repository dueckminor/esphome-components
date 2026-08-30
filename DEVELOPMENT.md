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

## VS Code Setup

The repository includes VS Code configuration for the best development experience:

**Recommended Extensions** (VS Code will prompt you to install):
- **Ruff** - Python linting and formatting
- **Clang-Format** - C++ formatting
- **Python** - Python language support
- **C/C++** - C++ IntelliSense and debugging

**Features:**
- ✅ Auto-format on save (Python and C++)
- ✅ C++ IntelliSense with ESPHome headers (autocomplete, go-to-definition)
- ✅ Auto-fix lint issues on save
- ✅ Import organization

**C++ IntelliSense Notes:**
- Requires virtual environment (`.venv`) to find ESPHome headers
- Arduino framework headers (ArduinoJson.h, Esp.h, etc.) are not available in the dev environment
- IntelliSense error checking is disabled to avoid false positives from missing framework headers
- You'll still get **autocomplete, go-to-definition, and hover documentation** for ESPHome code
- **Use ESPHome compile** to catch syntax errors: `esphome compile tests/components/*/test.yaml`
- The linting workflow will catch errors in CI

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
