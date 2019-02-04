#include <iostream>

int main() {
    std::cout << "Hello, World!" << std::endl;
    std::string inputString;
    while (std::cin >> inputString) {
        std::cout << inputString << std::endl;
    }
    return 0;
}