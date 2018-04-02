#include "TextFile.h"

TextFile::TextFile()
{

};

TextFile::TextFile(std::string filename, int open_mode, bool overwrite)
{
	if (filename != "")
		Open(filename, open_mode, overwrite);
};
TextFile::~TextFile()
{
	if (_Stream.is_open())
		_Stream.close();
};

bool TextFile::Open(std::string filename, int open_mode, bool overwrite)
{
	if (_Stream.is_open())
		_Stream.close();

	if (filename.compare(filename.length() - 4, 4, ".txt") != 0)
		filename += ".txt";

	_Stream.open(filename, ((open_mode == IOS_IN) ? std::ios::in : std::ios::out) | (overwrite ? std::ios::trunc : std::ios::app | std::ios::ate));

	return _Stream.is_open();
};

void TextFile::Write(std::string line)
{
	if (!_Stream.is_open())
		return;
	_Stream << line.c_str() << std::endl;
};

void TextFile::Close()
{
	_Stream.close();
};