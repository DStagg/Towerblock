#ifndef TEXT_FILE_H
#define TEXT_FILE_H

#include <fstream>

//	TODO: add common base class/interface/methodology to BinaryFile and TextFile.
//	TODO: move to framework folders
enum TextFileMode
{
	IOS_IN = 0,
	IOS_OUT
};

class TextFile
{
public:

	TextFile();
	TextFile(std::string filename, int open_mode, bool overwrite);
	~TextFile();

	bool Open(std::string filename, int open_mode, bool overwrite);
	void Write(std::string line);
	void Close();

private:

	std::ofstream _Stream;

};

#endif