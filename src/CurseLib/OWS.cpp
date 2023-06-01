#pragma once
#include <iostream>
#include <string>
#include <vector>
#include "OWS.h"

// Splits string with symbol
std::vector<std::string> fw::ows::Split(const std::string& in, const char c)
{
	std::vector<std::string> v;
	std::string s = "";
	for (ptrdiff_t i = 0; i < in.size(); ++i)
	{
		if (in[i] == c)
		{
			v.push_back(s);
			s = "";
			continue;
		}

		s += in[i];
	}
	v.push_back(s);
	return v;
}

std::vector<std::string> fw::ows::Split(const std::string& in, const std::string c)
{
	std::vector<std::string> v;
	std::string s;
	ptrdiff_t ppos = 0, npos = -1;

	while (true)
	{
		s = "";
		npos = in.find(c, npos + 1);
		if (npos == std::string::npos)
			break;
		for (size_t i = ppos; ppos < npos; ++i)
			s += in[i];
		v.push_back(s);
		ppos = npos;
	}

	v.push_back(s);
	return v;
}

// Splits String by vector with two symbols
std::vector<std::string> fw::ows::ByteSplit(std::string in)
{
	std::vector<std::string> v;
	std::string s;
	for (ptrdiff_t i = 0; i < in.size(); i += 2)
	{
		s = "";
		s += in[i];
		s += in[i + 1];
		v.push_back(s);
	}
	return v;
}

std::string fw::ows::Reverse(std::string s)
{
	for (int i = 0; i < s.size() / 2; ++i)
		std::swap(s[i], s[s.size() - 1 - i]);
	return s;
}