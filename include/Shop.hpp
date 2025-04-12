#ifndef SHOP_HPP
#define SHOP_HPP

#include "Thing.hpp"
#include "ShopDialog.hpp"

class Shop : public Thing {
public:
    Shop(std::vector<std::string> data, int x, int y, const std::shared_ptr<ShopDialog> &shopDialog) : Thing ("Shop/" + data[0], false, x, y),
    m_Name(data[1]), m_ShopDialog(shopDialog){}

    void Touched() override {
        m_ShopDialog->SetVisible(true);
    }

private:
    std::string m_Name;
    std::shared_ptr<ShopDialog> m_ShopDialog;
};

#endif //SHOP_HPP
