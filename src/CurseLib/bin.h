//! @file bin.h
//! @authors Юрков П.А.
//! @note Ответственный: Полевой Д.В.
#pragma once
#include <string>
#include <vector>
#include "OWS.h"
#include "HexDec.h"

// File Work
namespace fw
{
	// Binary
	namespace bin
	{		

		//! @brief Заполняет массив символов нулями, для доведения указателя до нужных размеров
		//! @param[in] pts -- массив символов
		//! @param[in] size -- размер, до которого надо довести
		//! @param[in] place_back -- заполнить нулями сзади или спереди
		std::string CompletePointer(std::string pts, size_t size=4, bool place_back=false)
		{
			if (!place_back)
				while (pts.size() != size)
					pts.insert(pts.begin(), 0);
			else
				while (pts.size() != size)
					pts.insert(pts.end(), 0);
			return pts;
		}


		//! @brief Преобразует указатель из целочисленного числа в массив символов
		//! @param[in] ptr -- числовое значение указателя
		//! @param[in] reverse -- сделать ли указатель обратным
		std::string PreparePointer(size_t ptr, bool reverse=false)
		{
			std::string rtn = "";
			while (ptr != 0)
			{
				rtn.push_back(ptr % 256);
				ptr /= 256;
			}
			if (!reverse)
				ows::Reverse(rtn);
			return rtn;
		}


		//! @brief Читает указатель с массива символов
		//!  @param[in] bank -- указаель, записанный в массиве символов
		size_t ReadPointer(std::string bank)
		{
			size_t value = 0;
			for (int i = bank.size() - 1; i >= 0; --i)
				value += hd::Degree(256, bank.size() - 1 - i) * (unsigned char)bank[i];

			return value;
		}


		//! @brief Создаёт указатель по заданным параметрам
		//! @param[in] ptr -- числовое значение указателя
		//! @param[in] size -- размер указателя в байтах
		//!  @param[in] reverse -- сделать ли указатель обратным
		std::string CreatePointer(size_t ptr, size_t size=4, bool reverse=false)
		{
			return CompletePointer(PreparePointer(ptr, reverse), size, reverse);
		}

		//! @brief Устанавливает позицию в файле без ограничений
		//! @param[in] pos -- позиция, на которую надо переместить указатель в файле
		//! @param[in] f -- файл, в котором надо поменять положение указателя
		void fsetpos(size_t pos, FILE* f)
		{
			size_t a_point = pos / 2147454976;
			fseek(f, 0, SEEK_SET);

			for (size_t i = 0; i < a_point; ++i)
			{
				fseek(f, 2147454976, SEEK_CUR);
				pos -= 2147454976;
			}
			fseek(f, pos % 2147454976, SEEK_CUR);
		}

	}
}