# Expression Evaluator

A simple C++17-based expression evaluator that supports basic arithmetic operations (`+`, `-`, `*`, `/`) and function calls with flexible data types such as `int`, `float`, `double`, and `std::string`. It also supports extracting variables from expressions and evaluating expressions using those variables.

## Features

- **Arithmetic Operations**: Supports addition, subtraction, multiplication, and division of numeric values.
- **Flexible Data Types**: Can evaluate expressions with mixed data types such as `int`, `float`, `double`, and `std::string`.
- **Variable Extraction**: Ability to extract variables from expressions without evaluating them.
- **Function Call Support**: Built-in support for calling custom functions within expressions.
- **String Concatenation**: Automatically converts operands to strings if one of the operands is a `std::string`.

## Getting Started

### Prerequisites

Ensure you have a C++17-compatible compiler such as:

- GCC 7.2+
- Clang 6.0+
- Microsoft Visual Studio 2019 or later

### Installing

1. Clone the repository:

   ```bash
   git clone https://github.com/your-username/expression-evaluator.git
   cd expression-evaluator```

2. Build the project using CMake:

   ```bash
   Copy code
   mkdir build
   cd build
   cmake ..
   make```