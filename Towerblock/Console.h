#ifndef CONSOLE_H
#define CONSOLE_H
//	TODO: move to framework folders
#include <vector>
#include "SFML\Graphics.hpp"
#include "Framework\IO\BinarySave.h"
#include <iostream>
#include "TextFile.h"

#define ConsoleBackgroundColour sf::Color(0, 0, 0, 155)
#define ConsoleTextSize 16
#define ConsoleLineLimit 20
#define ConsoleMarginHeight 10
#define Log(X) Console::C()->AddLine(X)

class Console
{
public:

	~Console();

	static Console* C();

	static void Draw(sf::RenderWindow* rw);
	static void DumpLog(std::string filename);
	static void Clear();
	static void AddLine(std::string line);
	static void Init(sf::Font font, int text_size, int line_limit);

protected:

	static int CountLines();

	std::vector<std::string> _TextLog;
	sf::Font _Font;
	int _TextSize;
	int _LineLimit;	//	Lines on screen at once

private:

	Console();
	static Console* _Instance;
};

#endif