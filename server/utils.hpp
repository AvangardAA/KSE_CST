#include <fstream>
#include <sstream>

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
}