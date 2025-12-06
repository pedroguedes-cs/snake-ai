#include <iostream>

#include "utils.hpp"

void printTitle(std::string title)
{
    printLine(100, '-');
    std::cout << "\n";

    printLine(10, '=');
    std::cout << "[" << title << "]\n";

    printLine(100, '-');
    std::cout << "\n\n\n";
}

void printSubtitle(std::string subtitle)
{
    std::cout << "\n";
    printLine(5, '=');
    std::cout << "[" << subtitle << "]\n";
}

void printMessage(std::string message)
{
    std::cout << "\n" << message << "\n";
}

void printInputMessage()
{
    std::cout << "\n>>> Press enter to continue: ";
}

void printLine(int size, char character)
{
    size = std::max(0, size);

    for (int i = 0; i < size; i++)
    {
        std::cout << character;
    }
}