#include "Console.h"

Console* Console::_Instance = 0;

Console::Console()
{

};

Console::~Console()
{

};

Console* Console::C()
{
	if (_Instance == 0)
		_Instance = new Console();
	return _Instance;
};

void Console::Draw(sf::RenderWindow* rw)
{
	sf::RectangleShape background;
	background.setPosition(0.f, 0.f);
	//background.setSize(sf::Vector2f((float)rw->getSize().x,(float)rw->getSize().y / 2.f));

	int linesToShow = Console::C()->CountLines();
	if (linesToShow == 0) linesToShow = 1;

	if (Console::C()->CountLines() >= Console::C()->_LineLimit)
		background.setSize(sf::Vector2f((float)rw->getSize().x, (float)(Console::C()->_TextSize * Console::C()->_LineLimit) + (float)(ConsoleMarginHeight * 0.5f * Console::C()->_LineLimit) + (float)(ConsoleMarginHeight * 2)));
	else
		background.setSize(sf::Vector2f((float)rw->getSize().x, (float)(Console::C()->_TextSize * linesToShow) + (float)((linesToShow-1) * ConsoleMarginHeight * 0.5f) + (float)(ConsoleMarginHeight * 2)));
	background.setFillColor(ConsoleBackgroundColour);
	rw->draw(background);
	
	int start_line = Console::C()->CountLines() - Console::C()->_LineLimit;	
	if (start_line < 0) start_line = 0;

	sf::Text text;
	text.setFont(Console::C()->_Font);
	text.setCharacterSize(Console::C()->_TextSize);

	for (int i = 0; i < Console::C()->_LineLimit; i++)
	{
		if (start_line + i >= Console::C()->CountLines())
			break;
		text.setString(Console::C()->_TextLog[start_line + i]);
		text.setPosition(0.f, (float)(i * Console::C()->_TextSize)+(float)(i * ConsoleMarginHeight * 0.5f) + (float)ConsoleMarginHeight);
		rw->draw(text);
	}

};

void Console::DumpLog(std::string filename)
{
	if (filename.length() < 5)
		Log("Invalid filename.");

	TextFile output;
	
	if (!output.Open(filename, IO_OUT, true))
		Log("Ouput file failed to open.");

	Log("Log dumped to: " + filename);

	for (int i = 0; i < C()->CountLines(); i++)
		output.Write(C()->_TextLog[i]);

	output.Close();
	Log("Log dumped.");
};

void Console::Clear()
{
	C()->_TextLog.clear();
};

void Console::AddLine(std::string line)
{
	C()->_TextLog.push_back(line);
};

void Console::Init(sf::Font font, int text_size, int line_limit)
{
	C()->_Font = font;
	C()->_TextSize = text_size;
	C()->_LineLimit = line_limit;
};

int Console::CountLines()
{
	return (int)(C()->_TextLog.size());
};