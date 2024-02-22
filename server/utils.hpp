#include <fstream>
#include <sstream>
#include <filesystem>
#include <sys/stat.h>
#include <iostream>

namespace utils
{
    std::string get_file(const std::string& dir, const std::string& filename)
    {
        std::ifstream file((std::filesystem::current_path().string() + "/" + dir + "/" + filename), std::ios::binary);
        if (!file.is_open()) 
        {
            return "missing";
        }

        std::ostringstream oss;
        oss << file.rdbuf();

        file.close();

        return oss.str();
    }

    std::string list_files(const std::string& dir)
    {
        std::string res = "";
        try 
        {
            std::filesystem::path fp = std::filesystem::current_path().string() + "/" + dir;

            if (!std::filesystem::exists(fp))
            {
                std::filesystem::create_directory(fp);
            }

            for (const auto& entry : std::filesystem::directory_iterator(fp)) 
            {
                if (entry.is_regular_file() && entry.path().extension() == ".txt") 
                {
                    res += entry.path().filename().string() + "\n";
                }
            }
        }
        catch(...) 
        {
            res = "error with directory";
        }

        return res;
    }

    int create_file(const std::string& dir, const std::string& filename)
    {
        std::ofstream file((std::filesystem::current_path().string() + "/" + dir + "/" + filename), std::ios::binary);
        if (!file.is_open())
        {
            return -1;
        }

        file << "created file";
        file.close();
        
        return 1;
    }

    int delete_file(const std::string& dir, const std::string& filename)
    {
        try
        {
            std::filesystem::path fp = std::filesystem::current_path().string() + "/" + dir + "/" + filename;
            std::filesystem::remove(fp);
            return 1;
        }
        catch(const std::filesystem::filesystem_error& e)
        {
            std::cout << e.what();
            return -1;
        }
    }

    std::string get_file_info(const std::string& dir, const std::string& filename)
    {
        struct stat fileStat;
        if (stat((std::filesystem::current_path().string() + "/" + dir + "/" + filename).c_str(), &fileStat) == 0) 
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