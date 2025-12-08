#include <iostream>
#include <chrono>
#include <thread>
#include <random>

#include "utils.hpp"

void printTitle(std::string title)
{
    breakLine(3);
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

void printSectionDivider()
{
    breakLine(3);
    printLine(100, 'x');
    breakLine(2);
}

void printEndMessage()
{
    printTitle("THE END - SNAKE GAME - PEDRO GUEDES");
}

void breakLine(int number)
{
    number = std::max(0, number);

    for (int i = 0; i < number; i++)
    {
        std::cout << "\n";
    }
}

void sleepFPS(int fps)
{
    int milliseconds = 1000 / fps;
    std::this_thread::sleep_for(std::chrono::milliseconds(milliseconds));
}

int random(int begin_range, int end_range)
{
    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_int_distribution<> distrib(begin_range, end_range);
    return distrib(gen);
}