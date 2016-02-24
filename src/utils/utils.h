#ifndef UTILS_H
#define UTILS_H

#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <stdlib.h>
#include <math.h>

template<typename T>
std::string toString( const T& value );
std::vector<std::string> splitString(std::string path, char delimeter);

#endif // UTILS_H
