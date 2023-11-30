//! @file docktests
//! @authors Юрков П.А.
//! @note Ответственный: Полевой Д.В.
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

			//! @brief Конструктор класса для таблицы оффсетов
			OffsetTable() = default;

			//! @brief Конструктор класса для таблицы оффсетов
			OffsetTable(const OffsetTable& ot);

			//! @brief Конструктор класса для таблицы оффсетов
			OffsetTable(const std::string dict_path);

			//! @brief Деструктор класса для таблицы оффсетов
			~OffsetTable() = default;
 
			//! @brief Перегрузка оператора []
			char operator[](const size_t i);


			//! @brief Возвращает размер
			size_t size() const;

			//! @brief Возвращает конец файла
			size_t end() const;

			//! @brief Возвращает значение позиции в таблице по двум 16-ричным числам
			//! @param[in] i -- строка в 16-ричной системе
			//! @param[in] j -- столбец в 16-ричной системе
			char get_byte_h(const  std::string i, const std::string j);

			//! @brief Возвращает значение позиции в таблице по двум 10-ричным числам
			//! @param[in] i -- строка в 10-ричной системе
			//! @param[in] j -- столбец в 10-ричной системе
			char get_byte_d(const size_t i, const size_t j);

			//! @brief Добавить символ в таблицу
			//! @param[in] symbol -- символ, который надо занести
			void add(const unsigned char& symbol);

			//! @brief Начать перевод
			//! @param[in] dict_path -- путь к таблице перевода
			void start(const std::string dict_path);

			//! @brief Добавляет стопбайты
			//! @param[in] sb -- стопбайт, который надо добавить
			void add_stop_byte(const std::string sb);

			//! @brief Получить позицию в таблице
			unsigned long get_pos() const;

			//! @brief Установить указатель на новую позицию в таблице
			//! @param[in] new_pos -- позиция, на которую надо установить указатель
			void set_pos(const size_t new_pos);

			//! @brief Заполняет область значением
			//! @param[in] start -- начало позиции для паддинга
			//! @param[in] end -- конец позиции для паддинга
			//! @param[in] symbol -- значение, которым надо заполнить область
			//! @param[in] rewrite -- переписать старые байты или сдвинуть старые значения
			void padding(const size_t start, const size_t end, const char symbol=0, bool rewrite=true);

			//! @brief Возвращает offset_table, как строку
			std::string get_string() const;

			//! @brief Вставляет значение в нужную позицию
			//! @param[in] pos -- позиция, на которую надо установить значение
			//! @param[in] value -- значение, которое надо вставить
			void insert(const size_t pos, std::string value);

			size_t get_start_position();

		private:

			//! @brief Переводит текст из файла
			//! @param[in] input_path -- путь к файлу с входными данными
			void TranslateText(const std::string& input_path);

			//! @brief Заполняет словарь, по которому потом производится перевод
			//! @param[in] path -- путь к таблице перевода
			void FillDict(const std::string& path);

			//! @brief Ищет стоп-байт в списке
			//! @param[in] sb -- стопбайт, который надо найти
			bool FindStopByte(const std::string& sb);
			

		public:
			std::vector<size_t> pointers; //!< вектор со всеми указателями
		private:
			size_t pos; //!< позиция в таблице оффсетов
			std::string offset_table; //!< таблица оффсетов
			std::vector<std::string> stop_bytes; //!< вектор со стопбайтами
			std::map<std::string, std::string> dict; //!< словарь с таблицей перевода

		};

		std::ostream& operator<<(std::ostream& ostrm, const OffsetTable& ot);
	}
}