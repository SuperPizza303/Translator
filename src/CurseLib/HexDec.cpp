#pragma once
#include <iostream>
#include <string>
#include "HexDec.h"


std::string fw::hd::HexTranslate(std::string s)
{
	if (s == "10") return "A";
	else if (s == "11") return "B";
	else if (s == "12") return "C";
	else if (s == "13") return "D";
	else if (s == "14") return "E";
	else if (s == "15") return "F";
	return s;
}

std::string fw::hd::DecTranslate(char s)
		{
			if (s == 'A') return "10";
			else if (s == 'B') return "11";
			else if (s == 'C') return "12";
			else if (s == 'D') return "13";
			else if (s == 'E') return "14";
			else if (s == 'F') return "15";
			std::string z = "";
			z += s;
			return z;
		}


		unsigned long fw::hd::Degree(unsigned long num, unsigned long ind)
		{
			int an = 1;
			for (int i = 0; i < ind; ++i)
				an *= num;
			return an;
		}

		std::string fw::hd::ToHex(unsigned long n)
		{
			std::string nh = "";
			unsigned long num;
			if (n == 0)
				return "00";
			while (n != 0)
			{
				num = n % 16;
				nh = HexTranslate(std::to_string(num)) + nh;
				n /= 16;
			}
			if (nh.size() & 1)
				nh.insert(nh.begin(), '0');
			return nh;
		}

		size_t fw::hd::ToDec(std::string nh)
		{
			size_t ind = 0;
			size_t n = 0;
			size_t some;
			for (int i = nh.size() - 1; i > -1; --i)
			{
				some = stoi(DecTranslate(nh[i]));
				n += some * Degree(16, ind);
				++ind;
			}

			return n;
		}
