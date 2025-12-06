#pragma once

#include <string>


//=====[PRINTERS]=====
void printTitle(std::string title);
void printSubtitle(std::string subtitle);
void printMessage(std::string message);
void printInputMessage();
void printLine(int size = 100, char character = '-');


//=====[TIME]=====
void pause(int fps);
