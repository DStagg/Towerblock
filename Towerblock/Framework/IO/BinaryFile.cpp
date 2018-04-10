#include "BinaryFile.h"

BinaryFile::BinaryFile(std::string filename, int mode, bool overwrite)
{
	if (filename != "")
		Open(filename, mode, overwrite);
};

BinaryFile::~BinaryFile()
{
	if (IsOpen())
		Close();
};

bool BinaryFile::Open(std::string filename, int mode, bool overwrite)
{
	if (filename == "")
		return false;

	if (IsOpen())
		Close();

	SetFilename(filename);
	SetMode(mode);
	SetOverwrite(overwrite);

	if (GetMode() == BinaryFile::IOMode::IO_In)
		_Stream.open(GetFilename().c_str(), std::ios::binary | std::ios::in);									//	In
	else if (GetOverwrite())
		_Stream.open(GetFilename().c_str(), std::ios::binary | std::ios::out | std::ios::trunc);				//	Out, Append
	else
		_Stream.open(GetFilename().c_str(), std::ios::binary | std::ios::out | std::ios::app | std::ios::ate);	//	Out, Overwrite

	return IsOpen();
};

void BinaryFile::Close()
{
	_Stream.close();
};

bool BinaryFile::IsOpen()
{
	return _Stream.is_open();
};