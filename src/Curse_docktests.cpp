//! @file main
//! @authors Юрков П.А.
//! @note Ответственный: Полевой Д.В.
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


std::vector<std::string> get_args(int argc, char* argv[])
{
    // i, o, t
    //  input=C:
    //  -i path ☺
    // --input ☺
    //  path
    std::vector<std::string> rtn = std::vector<std::string>(3, "");
    int j = 0;

    for (int i = 1; i < argc; ++i)
    {
        //std::cout << argv[i] << std::endl;
        if (_stricmp(argv[i], "-i") == 0 || _stricmp(argv[i], "--input") == 0)
        {
            ++i;
            rtn[0] = argv[i];
            continue;
        }
        else if (_stricmp(argv[i], "-o") == 0 || _stricmp(argv[i], "--output") == 0)
        {
            ++i;
            rtn[1] = argv[i];
            continue;
        }
        else if (_stricmp(argv[i], "-t") == 0 || _stricmp(argv[i], "--table") == 0)
        {
            ++i;
            rtn[2] = argv[i];
            continue;
        }
        
        std::vector<std::string> tmp;
        std::string str = argv[i];

        if (std::find(str.begin(), str.end(), '=') != str.end())
        {
            tmp = fw::ows::Split(str, '=');
            if (tmp[0] == "input")
            {
                rtn[0] = tmp[1];
                continue;
            }
            if (tmp[0] == "output")
            {
                rtn[1] = tmp[1];
                continue;
            }
            if (tmp[0] == "table")
            {
                rtn[2] = tmp[1];
                continue;
            }
        }

        rtn[j] = argv[i];
        ++j;

    }
    return rtn;
}


int main(int argc, char* argv[])
{
    setlocale(LC_ALL, "");
    std::vector<std::string> args;
    std::string table, 
                in, 
                out, 
                answers;

    args = get_args(argc, argv);

    fs::path currentPath = fs::current_path(); //!< Путь до .exe файла

    if (args[0] == "")
        in = currentPath.string() + "\\Input"; //!< Путь до входных данных
    else
        in = args[0];
    if (args[1] == "")
        out = currentPath.string() + "\\Output"; //!<  Путь до папки, в которую надо сохранить выходные файлы
    else
        out = args[1];
    if (args[2] == "")
        table = currentPath.string() + "\\Test_Table.tbl"; //!< Путь до таблицы перевода
    else
        table = args[2];

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
    }

}