#ifndef BINARY_SAVE_H
#define BINARY_SAVE_H

#include <vector>
#include <string>

#include "BinaryFile.h"

//	TODO: would help to merge this with BinaryFile.h so there's just the one file (similar to TextFile.h)

//	Explicit implementations	//

//std::string
template <>
void BinaryFile::Write<std::string>( std::string s );
template <>
std::string BinaryFile::Read<std::string>();

//bool
template <>
void BinaryFile::Write<bool>( bool b );
template <>
bool BinaryFile::Read<bool>();

#endif