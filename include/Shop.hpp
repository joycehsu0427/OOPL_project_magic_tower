#ifndef SHOP_HPP
#define SHOP_HPP

#include "Thing.hpp"

class Shop : public Thing {
public:
    Shop(std::vector<std::string> data, int x, int y) : Thing("Shop/" + data[0], false, x, y),
    m_Name(data[1]){}

    void Touched() override {

    }

private:
    std::string m_Name;

};

#endif //SHOP_HPP
