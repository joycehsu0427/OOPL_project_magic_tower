#ifndef READ_HPP
#define READ_HPP

#include <string>
#include <vector>

namespace Read {
    // csv讀取
    std::vector<std::string> split_csv(const std::string &line);
    std::vector<std::vector<std::string>> open_csv(const std::string &filepath);

    //txt讀取
    std::string open_txt(const std::string &filepath);
}
#endif
