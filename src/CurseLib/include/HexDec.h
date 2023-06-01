#pragma once
#include <iostream>
#include <string>

// File Work
namespace fw 
{
	// HecDec
	namespace hd
	{

		// Переводит hex-символ в десятичную систему
		std::string HexTranslate(std::string s);

		// Переводит число в hex-символ
		std::string DecTranslate(char s);

		// Возводит в степень
		unsigned long Degree(unsigned long num, unsigned long ind);

		// Переводит десятичный байт в hex-строку
		std::string ToHex(unsigned long n);

		// Переводит hex-строку в десятичную систему
		size_t ToDec(std::string nh);
	}
}
