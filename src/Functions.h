#ifndef FUNCTIONS_H
#define FUNCTIONS_H


#include <string>
#include <sstream>
#include <iostream>

template <class T>
bool FromString( const std::string& s, T& t, std::ios_base& (*f)(std::ios_base&) = std::dec )
{
	std::istringstream iss( s );
	return !(iss >> f >> t).fail();
}

#define StringToInt( str, num ) FromString<int>( str, num )
#define StringToFloat( str, num ) FromString<float>( str, num )

#endif // FUNCTIONS_H
