#pragma once
#include <string>
#include <vector>


// File Work
namespace fw
{
	// Operations With Strings
	namespace ows
	{
		// Splits string with symbol
		std::vector<std::string> Split(const std::string& in, const char c);

		// Splits string with string
		std::vector<std::string> Split(const std::string& in, const std::string c);

		// Splits String by vector with two symbols
		std::vector<std::string> ByteSplit(std::string in);

		std::string Reverse(std::string s);

	}
}
