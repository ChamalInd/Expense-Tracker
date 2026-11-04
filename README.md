# Expense-Tracker

A simple expense tracker that lives in your terminal, written in C++. Record what you spend, list your expenses, filter them by year, month or day, and see the total for any period. Expenses are stored in a plain text file in the directory you run the program from, so every project folder can have its own expense log.

## Table of Contents

- [Features](#features)
- [Requirements](#requirements)
- [Installation](#installation)
- [Usage](#usage)
- [Examples](#examples)
- [Project Structure](#project-structure)
- [Development](#development)

## Features

- Add expenses with a description and an amount
- The date is recorded automatically (today's date)
- List all expenses in an aligned table
- Filter by `--year`, `--month` and `--day`, alone or combined
- Print the total for all expenses or for a filtered period
- Delete an expense by its ID (other IDs stay the same)
- Per-directory expense logs (stored in a local `.records` file)
- Changes are saved to disk immediately
- No dependencies beyond the C++ standard library
- Object-oriented design with a separate `Expense` and `ExpenseManager`
- Makefile with incremental builds, `install` and `uninstall` targets

## Requirements

- A C++17 compatible compiler (GCC 9+, Clang 10+)
- `make`

On Debian/Ubuntu, `sudo apt install build-essential` provides both. On macOS, run `xcode-select --install`. On Windows, use WSL.

## Installation

### 1. Clone the repository

```bash
git clone https://github.com/ChamalInd/Expense-Tracker.git
cd Expense-Tracker
```

### 2. Build

```bash
make
```

This compiles the sources into `build/` and produces an executable named `exptrc` in the project root.

You can override the compiler or flags if needed:

```bash
make CXX=clang++
make CXXFLAGS="-std=c++17 -O0 -g"
```

**Without make:**

```bash
g++ -std=c++17 -Wall -Wextra -o exptrc src/*.cpp
```

### 3. Run

```bash
./exptrc help
```

### 4. (Optional) Install system-wide

```bash
sudo make install      # installs to /usr/local/bin
exptrc help            # now usable from anywhere
```

Install somewhere else with `make install PREFIX=$HOME/.local`. To remove it later, run `sudo make uninstall` (or `make uninstall PREFIX=$HOME/.local` to match).

## Usage

```
exptrc <command> [arguments]
```

| Command | Description |
| --- | --- |
| `add "<expense>" <amount>` | Add a new expense dated today. |
| `delete <expense-id>` | Delete an expense. |
| `list` | List all expenses. |
| `list --year <year>` | List expenses from a certain year. |
| `list --month <month>` | List expenses from a certain month (1-12). |
| `list --day <day>` | List expenses from a certain day of the month (1-31). |
| `summary` | Print the total of all expenses. |
| `summary --year <year>` | Print the total for a certain year. |
| `summary --month <month>` | Print the total for a certain month. |
| `summary --day <day>` | Print the total for a certain day. |
| `help` | Print the help message. |

The `--year`, `--month` and `--day` filters work with both `list` and `summary`, and can be combined. For example, `list --year 2026 --month 11` shows only expenses from November 2026.

Running `exptrc` with no arguments prints a short hint to use `help`.

**Notes**

- Wrap the description in quotes so the shell treats it as a single argument.
- Expense IDs are shown when you add an expense and in the `list` output.
- Deleting an expense does not renumber the others, so the remaining IDs stay valid.
- Amounts are displayed with two decimal places and a `$` sign.
- Avoid using the `|` character in descriptions, since it is used as the field separator in the data file.

## Examples

### Add some expenses

```console
$ exptrc add "Groceries" 45.50
Expense added successfully [ID: 1]

$ exptrc add "Bus pass" 30
Expense added successfully [ID: 2]

$ exptrc add "Dinner with friends" 62.75
Expense added successfully [ID: 3]
```

### List expenses

```console
$ exptrc list
ID  Date        Description           Amount ($)
------------------------------------------------
1   2026-11-04  Groceries                45.50
2   2026-11-04  Bus pass                 30.00
3   2026-11-04  Dinner with friends      62.75
```

### Filter by date

```console
$ exptrc list --year 2026 --month 11
ID  Date        Description           Amount ($)
------------------------------------------------
1   2026-11-04  Groceries                45.50
2   2026-11-04  Bus pass                 30.00
3   2026-11-04  Dinner with friends      62.75
```

If nothing matches the filter, you get a message instead of an empty table:

```console
$ exptrc list --year 1999
No expense records found for given period.
```

### Summarise expenses

```console
$ exptrc summary
Total expenses for given period: $ 138.25

$ exptrc summary --month 11
Total expenses for given period: $ 138.25
```

### Delete an expense

```console
$ exptrc delete 2
Expense removed successfully [ID: 2]

$ exptrc list
ID  Date        Description           Amount ($)
------------------------------------------------
1   2026-11-04  Groceries                45.50
3   2026-11-04  Dinner with friends      62.75
```


## Project Structure

```
Expense-Tracker/
├── Makefile                      # Build rules
├── README.md
├── .gitignore
├── includes/
│   └── includes.h                # Shared includes, Expense and ExpenseManager declarations
└── src/
    ├── main.cpp                  # Entry point and command dispatch
    ├── expense.cpp               # Expense implementation (get/set, file line conversion)
    ├── expense-manager.cpp       # ExpenseManager implementation (add, delete, list, summary, file I/O)
    └── helper.cpp                # Argument parsing, date and currency helpers, error messages
```

## Development

### Build targets

| Command | What it does |
| --- | --- |
| `make` | Build the `exptrc` executable |
| `make clean` | Remove the `build/` directory and the executable |
| `make install` | Install to `/usr/local/bin` (override with `PREFIX=...`) |
| `make uninstall` | Remove the installed binary |

The Makefile generates dependency files (`.d`) next to each object file, so editing a header only rebuilds the files that include it.

### Data file

Expenses are saved to a file named `.records` in the **current working directory**, one expense per line:

```
<id>|<year>-<month>-<day>|<description>|<amount>
```

For example:

```
1|2026-11-4|Groceries|45.500000
3|2026-11-4|Dinner with friends|62.750000
```

The file is created automatically the first time you run the program, and it is listed in `.gitignore` so your personal expenses don't get committed by accident.

### Debug build with sanitizers

Sanitizers catch out-of-range accesses and undefined behaviour early:

```bash
make clean
make CXXFLAGS="-std=c++17 -g -Wall -Wextra -fsanitize=address,undefined"
```

### Resetting your data

To start fresh, delete the `.records` file in your working directory:

```bash
rm .records
```
