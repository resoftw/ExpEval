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
```

2. Build the project using CMake:

```bash
mkdir build
cd build
cmake ..
make
```

### Example Usage

Here's a basic example to get started with the Expression Evaluator:

```cpp
#include "ExpressionEvaluator.h"
#include <iostream>

int main() {
    ExpressionEvaluator evaluator;

    // Define an expression
    std::string expression = "x + y * 5";

    // Step 1: Extract variables
    auto variables = evaluator.extractVariables(expression);
    for (const auto& var : variables) {
        std::cout << "Variable found: " << var << std::endl;
    }

    // Step 2: Set variables with values
    evaluator.setVariable("x", 10);
    evaluator.setVariable("y", 2);

    // Step 3: Evaluate the expression
    Value result = evaluator.evaluate(expression);
    std::cout << "Result: " << std::visit([](auto&& arg) { return std::to_string(arg); }, result) << std::endl;

    return 0;
}
```

### Output

```yaml
Variable found: x
Variable found: y
Result: 20
```

### API Reference

setVariable(const std::string& name, const Value& value)
Assigns a value to a variable used in expressions.

name: The name of the variable.
value: The value to be assigned to the variable (can be int, float, double, or std::string).
evaluate(const std::string& expression)
Evaluates the given expression based on the current set of variables.

expression: A string representing the arithmetic or functional expression.
Returns the result of the evaluation as a Value (variant type).
extractVariables(const std::string& expression)
Extracts the variable names used in the expression without evaluating it.

expression: A string containing the expression.
Returns a std::set<std::string> containing the variable names.