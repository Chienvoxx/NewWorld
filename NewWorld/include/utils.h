#pragma once
#ifndef _UTILS_H
#define _UTILS_H

//#include <string>
//#include <fstream>
//#include <iostream>
//#include <vector>

#include <mesh.h>

std::string readTextFile(const char *filename);
std::vector<std::string> readTextFileLines(const char *file);
//std::vector<std::string> readTextFileLines(std::string const &path);
std::string findFileOrThrow(const std::string &strBasename);


#endif // !_UTILS_H
