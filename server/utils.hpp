#include <fstream>
#include <sstream>
#include <filesystem>

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
        std::cout << oss.str();

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
}