//! @file docktests
//! @authors Юрков П.А.
//! @note Ответственный: Полевой Д.В.#pragma once
#include <string>
#include <vector>


// File Work
namespace fw
{
	// Operations With Strings
	namespace ows
	{
		//! @brief Разделяет строку по символу
		//! @param[in] in -- входная строка, которую надо разделить
		//! @param[in] c -- символ, по которому делится строка
		std::vector<std::string> Split(const std::string& in, const char c);

		//! @brief Разделяет строку по другой строке
		//! @param[in] in -- входная строка, которую надо разделить
		//! @param[in] c -- строка, по которой делится другая строка
		std::vector<std::string> Split(const std::string& in, const std::string c);

		//! @brief Разделяет строку на вектор по 2 символа в элементе
		//! @param[in] in -- строка, которую надо раздеить
		std::vector<std::string> ByteSplit(std::string in);

		//! @brief Переворачивает строку
		//! @param[in] s -- строка, которую надо перевернуть
		std::string Reverse(std::string s);

	}
}