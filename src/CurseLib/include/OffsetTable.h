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
 
			// Возвращает значение позиции в таблице
			char operator[](const size_t i);


			// Возвращает размер
			size_t size() const;

			// Возвращает конец файла
			size_t end() const;

			// Возвращает значение позиции в таблице по двум 16-ричным числам
			char get_byte_h(const  std::string i, const std::string j);

			// Возвращает значение позиции в таблице по двум 10-ричным числам
			char get_byte_d(const size_t i, const size_t j);

			// Добавить символ в таблицу
			void add(const unsigned char& symbol);

			// Начать перевод
			void start(const std::string dict_path);

			// Добавляет стопбайты
			void add_stop_byte(const std::string sb);

			// Получить позицию в таблице
			unsigned long get_pos() const;

			// Установить позицию в таблице
			void set_pos(const size_t new_pos);

			// Заполняет область значением
			void padding(const size_t start, const size_t end, const char symbol=0, bool rewrite=true);

			// Возвращает offset_table, как строку
			std::string get_string() const;

			// Вставляет значение в нужное место
			void insert(const size_t pos, std::string value);

		private:

			// Переводит текст
			void TranslateText(const std::string& input_path);

			// Заполняет словарь, по которому потом производится перевод
			void FillDict(const std::string& path);

			// Ищет стоп-байт в списке
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

