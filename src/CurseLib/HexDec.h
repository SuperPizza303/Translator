//! @file docktests
//! @authors Юрков П.А.
//! @note Ответственный: Полевой Д.В.
#pragma once
#include <iostream>
#include <string>

// File Work
namespace fw 
{
	// HecDec
	namespace hd
	{

		//! @brief Переводит hex-символ в десятичную систему
		//! @param[in] s -- hex-символ, который надо перевести
		std::string HexTranslate(std::string s);

		//! @brief Переводит число в hex-символ
		//! @param[in] s -- число, которое надо перевести в hex-символ
		std::string DecTranslate(char s);

		//! @brief Возводит в степень
		//! @param[in] num -- число, которое надо возвести степель
		//! @param[in] ind -- показатель степени
		unsigned long Degree(unsigned long num, unsigned long ind);

		//! @brief Переводит десятичное число в hex-строку
		//! @param[in] n -- десятичное число
		std::string ToHex(unsigned long n);

		//! @brief Переводит hex-строку в десятичную систему
		//! @param[in] nh -- hex-строка
		size_t ToDec(std::string nh);
	}
}