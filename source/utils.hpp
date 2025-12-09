#pragma once

#include <string>

#include "Position.hpp"


//=====[PRINTERS]=====
void printTitle(std::string title);
void printSubtitle(std::string subtitle);
void printMessage(std::string message);
void printInputMessage();
void printLine(int size = 100, char character = '-');
void printSectionDivider();
void printEndMessage();

void breakLine(int number = 1);


//=====[TIME]=====
void sleepFPS(int fps);


//=====[RANDOM]=====
int random(int begin_range, int end_range);


//=====[MATH]=====
int manhattanDistance(Position position1, Position position2);

