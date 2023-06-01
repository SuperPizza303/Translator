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

		// Заполняет массив чаров нулями, для доведения указателя до нужных размеров
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


		// Преобразует указатель из целочисленного числа в массив символов
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


		// Читает указатель с массива символов
		size_t ReadPointer(std::string bank)
		{
			size_t value = 0;
			for (int i = bank.size() - 1; i >= 0; --i)
				value += hd::Degree(256, bank.size() - 1 - i) * (unsigned char)bank[i];

			return value;
		}


		// Создаёт указатель по заданным параметрам
		std::string CreatePointer(size_t ptr, size_t size=4, bool reverse=false)
		{
			return CompletePointer(PreparePointer(ptr, reverse), size, reverse);
		}

		// Сохраняет хекс, записанный в строке, в файл
		void SaveHexString(std::string s, FILE* f)
		{
			std::string input;
			char* c = new char[2];
			for (size_t i = 0; i < s.size(); i += 2)
			{
				input = "";
				input += s[i];
				input += s[i + 1];
				input = strtol(input.c_str(), &c, 16);
				fwrite(input.c_str(), 1, 1, f);
			}
		}

		// Устанавливает позицию в файле без ограничений
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
