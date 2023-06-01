#pragma once
#include <vector>
#include <string>
#include <map>

namespace fw
{
	namespace bin
	{

		class OffsetTable
		{
		public:
			OffsetTable() = default;

			OffsetTable(const OffsetTable& ot);

			OffsetTable(const std::string dict_path);

			~OffsetTable() = default;
 
			// ���������� �������� ������� � �������
			char operator[](const size_t i);


			// ���������� ������
			size_t size() const;

			// ���������� ����� �����
			size_t end() const;

			// ���������� �������� ������� � ������� �� ���� 16-������ ������
			char get_byte_h(const  std::string i, const std::string j);

			// ���������� �������� ������� � ������� �� ���� 10-������ ������
			char get_byte_d(const size_t i, const size_t j);

			// �������� ������ � �������
			void add(const unsigned char& symbol);

			// ������ �������
			void start(const std::string dict_path);

			// ��������� ���������
			void add_stop_byte(const std::string sb);

			// �������� ������� � �������
			unsigned long get_pos() const;

			// ���������� ������� � �������
			void set_pos(const size_t new_pos);

			// ��������� ������� ���������
			void padding(const size_t start, const size_t end, const char symbol=0, bool rewrite=true);

			// ���������� offset_table, ��� ������
			std::string get_string() const;

			// ��������� �������� � ������ �����
			void insert(const size_t pos, std::string value);

		private:

			// ��������� �����
			void TranslateText(const std::string& input_path);

			// ��������� �������, �� �������� ����� ������������ �������
			void FillDict(const std::string& path);

			// ���� ����-���� � ������
			bool FindStopByte(const std::string& sb);
			

		public:
			std::vector<size_t> pointers;
		private:
			size_t pos;
			std::string offset_table;
			std::vector<std::string> stop_bytes;
			std::map<std::string, std::string> dict;

		};

		std::ostream& operator<<(std::ostream& ostrm, const OffsetTable& ot);
	}
}

