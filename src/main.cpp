#include <iostream>
#include "calculator/calculator.h"
#include <fstream>

int main() {
    bool run = true;
    while (run) {
        std::string s;
        std::getline(std::cin, s);
        if (s == "exit") {
            run = false;
        } else {
            try {
                auto result = calculate_expression(s);
                std::cout << "=" << result << "\n";
            } catch (const CalcException & e) {
                std::cout << e.name() << std::endl;
                std::cout << e.what() << std::endl;
            }
        }
    }
}