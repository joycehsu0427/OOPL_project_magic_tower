#include <fstream>
#include <sstream>

#include "Read.hpp"
namespace Read {
    std::vector<std::string> split_csv(const std::string &line) {
        std::vector<std::string> arr;
        std::istringstream delim(line);
        std::string token;
        int c = 0;
        while (getline(delim, token, ','))
        {
            arr.push_back(token);
            c++;
        }
        return  arr;
    }

    std::vector<std::vector<std::string>> open_csv(const std::string &filepath) {
        std::vector<std::vector<std::string>> data;
        std::ifstream inFile(filepath, std::ios::in);
        if (!inFile) {
            exit(1);
        }
        std::string line;
        while (getline(inFile, line)) {
            data.push_back(split_csv(line));
        }
        inFile.close();
        return data;
    }

    std::string open_txt(const std::string &filepath) {
        std::string str = std::string();
        std::ifstream inFile(filepath, std::ios::in);
        std::string s;
        while (std::getline(inFile, s)) {
            str += s + "\n";
        }
        inFile.close();
        return str;
    }

}