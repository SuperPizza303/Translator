#pragma once
#include "OffsetTable.h"
#include <fstream>
#include "HexDec.h"
#include "OWS.h"

/*
	C:\Users\1\Desktop\player\SciAdv.tbl
	C:\Users\1\Desktop\player\may01.txt
	C:\Users\1\Desktop\opt

	C:\Users\1\Desktop\player\SciAdv.tbl
	C:\\Users\\1\\Desktop\\inpt\\Check.txt
	C:\\Users\\1\\Desktop\\opt\\opt

*/

fw::bin::OffsetTable::OffsetTable(const OffsetTable& ot)
{
	setlocale(LC_ALL, "");
	pos = ot.pos;
	offset_table = ot.offset_table;
	pointers = ot.pointers;
	dict = ot.dict;
}

// Создание экземпляра, инициализация словаря
fw::bin::OffsetTable::OffsetTable(const std::string dict_path)
{
	setlocale(LC_ALL, "");
	FillDict(dict_path);
}

// Начать
void fw::bin::OffsetTable::start(const std::string inpt_path)
{
	pos = 0;
	offset_table = "";
	pointers.clear();
	pointers.push_back(0);
	TranslateText(inpt_path);
}

char fw::bin::OffsetTable::operator[](const size_t i)
{
	return offset_table[i];
}


size_t fw::bin::OffsetTable::size() const
{
	return offset_table.size();
}

size_t fw::bin::OffsetTable::end() const
{
	return fw::bin::OffsetTable::size() - 1;
}

inline char fw::bin::OffsetTable::get_byte_h(const std::string i, const std::string j)
{
	return get_byte_d(fw::hd::ToDec(i), fw::hd::ToDec(i));
}

inline char fw::bin::OffsetTable::get_byte_d(const size_t i, const size_t j)
{
	return offset_table[i * 16 + j];
}


void fw::bin::OffsetTable::add(const unsigned char& symbol)
{
	if (offset_table.size() > pos)
		offset_table[pos] = symbol;
	else
		offset_table.push_back(symbol);
	++pos;
}

void fw::bin::OffsetTable::add_stop_byte(const std::string sb)
{
	stop_bytes.push_back(sb);
}

inline unsigned long fw::bin::OffsetTable::get_pos() const
{
	return pos;
}

void fw::bin::OffsetTable::set_pos(const size_t new_pos)
{
	pos = new_pos;
}


void fw::bin::OffsetTable::TranslateText(const std::string& input_path)
{
	std::string str, symbol;
	std::ifstream in(input_path);


	while (getline(in, str))
	{
		for (size_t i = 0; i < str.size(); ++i)
		{
			symbol = str[i];
			if (symbol == "[")
			{
				++i;
				while (str[i] != ']')
				{
					symbol = symbol;
					symbol += str[i];
					++i;
				}
				symbol += str[i];
				pos += dict[symbol].size();
				if (FindStopByte(symbol))
					pointers.push_back(pos);
				offset_table += dict[symbol];
			}
			else if (symbol == "{")
			{
				std::string var = "";
				++i;
				while (str[i] != '}')
				{
					var += str[i];
					++i;
				}
				offset_table += fw::hd::ToDec(var);
				++pos;
			}
			else if (symbol == "\\")
			{
				++i;
				symbol += str[i];
				offset_table += dict[symbol];
				pos += dict[symbol].size();
			}
			else
			{
				offset_table += dict[symbol];
				pos += dict[symbol].size();
			}
		}
	}

	in.close();
}

// Добавить bool rewrite
void fw::bin::OffsetTable::padding(const size_t start, const size_t end, const char symbol, bool rewrite)
{
	const unsigned long _pos = pos;
	pos = start;

	if (rewrite)
		for (size_t i = 0; i < end - start; ++i)
				add(symbol);
	else
	{
		std::string s(end - start, symbol);
		insert(start, s);
	}
		
	pos = _pos;
}

std::string fw::bin::OffsetTable::get_string() const
{
	return offset_table;
}

void fw::bin::OffsetTable::insert(size_t pos, std::string value)
{
	offset_table.insert(pos, value);
}

size_t fw::bin::OffsetTable::get_start_position()
{
	return (pointers.size() / 2 * 16 + pointers.size() % 2 * 8 + 16);
}




void fw::bin::OffsetTable::FillDict(const std::string& path)
{
	using namespace fw::ows;
	using namespace fw::hd;

	std::ifstream in(path);
	std::string temp;
	std::vector<std::string> key, items;


	while (getline(in, temp))
	{
		key = Split(temp, '=');
		dict[key[1]] = "";
		items = ByteSplit(key[0]);
		for (size_t i = 0; i < items.size(); ++i)
			dict[key[1]].push_back(ToDec(items[i]));

	}
	in.close();
}

bool fw::bin::OffsetTable::FindStopByte(const std::string& sb)
{
	for (auto i : stop_bytes)
		if (i == sb)
			return true;
	return false;
}

std::ostream& fw::bin::operator<<(std::ostream& ostrm, const OffsetTable& ot)
{
	ostrm << ot.get_string();
	return ostrm;
}
