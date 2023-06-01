//! @file docktests
//! @authors Юрков П.А.
//! @note Ответственный: Полевой Д.В.
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest.h>
#include <filesystem>
#include <CurseLib/Translation.cpp>

namespace fs = std::filesystem;

//! @brief Перемещение позиции указателя в файлах file1 и file2 вперёд на pos байтов
//! @param[in] file1 -- первый передаваемый файл
//! @param[in] file2 -- второй передаваемый файл
//! @param[in] pos -- количество байтов, на которое надо передвинуть указатель
void change_positions(FILE* file1, FILE* file2, size_t pos)
{
    fseek(file1, pos, SEEK_CUR);
    fseek(file2, pos, SEEK_CUR);
}

TEST_CASE("Tests")
{
    setlocale(LC_ALL, "");

    fs::path currentPath = fs::current_path(); //!< Путь до .exe файла

    std::string table, in, out, answers;
    table = currentPath.string() + "\\Test_Table.tbl"; //!< Путь до таблицы перевода
    in = currentPath.string() + "\\Input"; //!< Путь до входных данных
    answers = currentPath.string() + "\\Right_answers"; //!< Путь до правильных ответов для проверки
    out = currentPath.string() + "\\Output"; //!<  Путь до папки, в которую надо сохранить выходные файлы

    fw::bin::OffsetTable ot(table); //!< Путь до таблицы оффсетов
    
    ot.add_stop_byte("[END]");
    for (auto dir : std::filesystem::directory_iterator{ in })
    {
        std::string infile_name = dir.path().string(); //!< Наименование входного файла
        std::string outfile_name; //!< Наименование выходного файла
        std::string outfile_path; //!< Путь до выходного файла
        std::string result_bytes = ""; //!< Контрольные байты в результирующем файле 
        std::string check_bytes = ""; //!< Контрольные байты в файле ответов
        size_t ctrl_byte = 0; //!< Байт для проверки достижения конца файла

        std::vector split_path = fw::ows::Split(infile_name, '\\');
        infile_name = split_path[split_path.size() - 1];

        outfile_name = fw::ows::Split(infile_name, '.')[0];
        outfile_path = out + "\\" + outfile_name;
        infile_name = dir.path().string();

        translate_file(infile_name, outfile_path, ot);

        FILE* result = fopen(outfile_path.c_str(), "rb");
        FILE* check = fopen((answers + "\\" + outfile_name + "_check").c_str(), "rb");

        SUBCASE("HEADER")
        {
            for (short i = 0; i < 8; ++i)
            {
                result_bytes += fgetc(result);
                check_bytes += fgetc(check);
            }
            CHECK(check_bytes == result_bytes);
        }

        change_positions(check, result, 8);

        SUBCASE("AMOUNT OF POINTERS")
        {
            result_bytes = "";
            check_bytes = "";
            for (short i = 0; i < 8; ++i)
            {
                result_bytes += fgetc(result);
                check_bytes += fgetc(check);
            }
            CHECK(check_bytes == result_bytes);
        }

        change_positions(check, result, 8);

        SUBCASE("START POSITION")
        {
            result_bytes = "";
            check_bytes = "";
            for (short i = 0; i < 8; ++i)
            {
                result_bytes += fgetc(result);
                check_bytes += fgetc(check);
            }
            CHECK(check_bytes == result_bytes);
        }

        change_positions(check, result, 8);

        SUBCASE("POINTERS CHECK")
        {
            result_bytes = "";
            check_bytes = "";
            for (size_t i = 0; i < ot.get_start_position() - 16; ++i)
            {
                result_bytes += fgetc(result);
                check_bytes += fgetc(check);
            }
            CHECK(check_bytes == result_bytes);
        }

        change_positions(check, result, ot.get_start_position() - 16);

        SUBCASE("TRANSLATION CHECK")
        {
            result_bytes = "";
            check_bytes = "";
            while (ctrl_byte != EOF)
            {
                ctrl_byte = fgetc(result);
                result_bytes += ctrl_byte;
                check_bytes += fgetc(check);
            }
            CHECK(check_bytes == result_bytes);
        }

        fclose(result);
        fclose(check);
    }
}