#include <iostream>
#include <filesystem>
#include <vector>
#include "OffsetTable.h"
#include "bin.h"
#include "OWS.h"

void Write(std::string s, FILE* f)
{
	for (auto i : s)
		fputc(i, f);
}

void translate_file(std::string& file_path, std::string& file_outpath, fw::bin::OffsetTable& ot)
{
	size_t save = 0, point = 0;
	ot.start(file_path);
	FILE* f = fopen(file_outpath.c_str(), "wb");

	Write("MES", f);

	fseek(f, 5, SEEK_CUR);

	// Количество указателей
	Write(fw::bin::CreatePointer(ot.pointers.size(), 4, true), f);

	// Начальная позиция
	Write(fw::bin::CreatePointer(ot.get_start_position(), 4, true), f);

	for (auto i : ot.pointers)
	{
		Write(fw::bin::CreatePointer(save, 4, true), f);
		Write(fw::bin::CreatePointer(i, 4, true), f);
		save += 0x64;
	}

	for (size_t i = 0; i < ot.size(); ++i)
	{
		fputc(ot[i], f);
	}
	fclose(f);
}

/*
int work_with_explorer(std::string table, std::string in, std::string out)
{
	setlocale(LC_ALL, "");
	/*std::string table, in, out;
	std::cout << "Введите путь к таблице:\n";
	std::cin >> table; 
	std::cout << "Введите путь к папке с входными данными:\n";
	std::cin >> in;
	std::cout << "Введите путь к выходными данными:\n";
	std::cin >> out;

	fw::bin::OffsetTable ot(table);
	for (auto dir : std::filesystem::directory_iterator{ in })
	{
		std::string infile_name = dir.path().string();
		std::string outfile_name;

		std::vector split_path = fw::ows::Split(infile_name, '\\');
		infile_name = split_path[split_path.size() - 1];

		outfile_name = fw::ows::Split(infile_name, '.')[0];
		outfile_name = out + "\\" + outfile_name;
		infile_name = dir.path().string();

		translate_file(infile_name, outfile_name, ot);
	}


	/* 
	C:\Users\1\Desktop\Curse\Tests\Test_Table.tbl
	C:\Users\1\Desktop\Curse\Tests\Input
	C:\Users\1\Desktop\Curse\Tests\Output

	

}*/