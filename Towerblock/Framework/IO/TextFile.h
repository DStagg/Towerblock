#ifndef TEXT_FILE_H
#define TEXT_FILE_H

#include "BaseFile.h"

class TextFile : public BaseFile
{
public:

	TextFile(std::string filename = "", int mode = 0, bool over = false);
	~TextFile();

	virtual bool Open(std::string filename, int mode, bool overwrite);
	virtual void Close();
	virtual bool IsOpen();

	std::string Read();
	void Write(std::string line);
};

#endif