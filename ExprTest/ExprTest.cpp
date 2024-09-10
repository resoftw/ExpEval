#include <iostream>
#include "ExpEval.hpp"

int main() {
    ExpressionEvaluator evaluator;

    std::string expr = "$x + $y.a_z * 1.412312 + z + 'aaa'";

    try {
        // Extracting variables
        auto variables = evaluator.extractVariables(expr);
        std::cout << "Variables: ";
        for (const auto& var : variables) {
            std::cout << var << " ";
        }
        std::cout << std::endl;

        evaluator.setVariable("$x", 42.5);
        evaluator.setVariable("$y.a_z", 1000.0);
        evaluator.setVariable("z", std::string(" Hello"));

        // Evaluating expression
        auto result = evaluator.evaluate(expr);
        std::visit([](auto&& val) { std::cout << "Result: " << val << std::endl; }, result);


    }
    catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    return 0;
}
