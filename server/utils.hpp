#include <fstream>
#include <sstream>
#include <filesystem>
#include <sys/stat.h>

namespace utils
{
    std::string get_file(const std::string& filename)
    {
        std::ifstream file(filename, std::ios::binary);
        if (!file.is_open()) 
        {
            return "missing";
        }

        std::ostringstream oss;
        oss << file.rdbuf();
        //std::cout << oss.str();

        file.close();

        return oss.str();
    }

    std::string list_files()
    {
        std::string res = "";
        for (const auto& entry : std::filesystem::directory_iterator(std::filesystem::current_path()))
        {
            if (entry.is_regular_file() && entry.path().extension() == ".txt") 
            {
                res += entry.path().filename().string() + "\n";
            }
        }

        return res;
    }

    int create_file(const std::string& filename)
    {
        std::ofstream file(filename, std::ios::binary);
        if (!file.is_open())
        {
            return -1;
        }

        file << "created file";
        file.close();
        
        return 1;
    }

    int delete_file(const std::string& filename)
    {
        try
        {
            std::filesystem::remove(filename);
            return 1;
        }
        catch(const std::filesystem::filesystem_error& e)
        {
            return -1;
        }
    }

    std::string get_file_info(const std::string& filename)
    {
        struct stat fileStat;
        if (stat(filename.c_str(), &fileStat) == 0) 
        {
            std::stringstream info;
            info << "File found: " << filename << "\n";
            return info.str();
        } 
        else 
        {
            return "error loading info";
        }
    }
}