#ifndef SHOP_HPP
#define SHOP_HPP

#include "Thing.hpp"
#include "Read.hpp"
#include "ShopDialog.hpp"

class Shop : public Thing {
public:
    Shop(const std::vector<std::string> &data, const int &floor, const int &x, const int &y, const int &index,
        const std::shared_ptr<ShopDialog> &shopDialog) :
    Thing (std::vector<std::string>{RESOURCE_DIR"/bmp/Shop/" + data[IMAGE] + ".bmp",
        RESOURCE_DIR"/bmp/Shop/" + data[IMAGE] + "2.bmp"}, true, 400, false, x, y, index),
    m_ImagePath(RESOURCE_DIR"/bmp/Shop/" + data[IMAGE] + ".bmp"),
    m_DialogPath(RESOURCE_DIR"/Text/" + std::to_string(floor) + "_" + data[IMAGE] + ".csv"),
    m_OptionPath(RESOURCE_DIR"/Text/" + std::to_string(floor) + "_" + data[IMAGE] + "_option.csv"),
    m_Name(data[NAME]), m_CanTouched(std::stoi(data[CANTOUCHED])), m_Money(std::stoi(data[MONEY])), m_ShopDialog(shopDialog) {
        if (m_CanTouched) {
            // 設定要傳送的Dialog資料
            std::vector<std::vector<std::string>> dialogdata = Read::open_csv(m_DialogPath);
            int currentdialogSize = -1;
            for (int i = 0; i < int(dialogdata.size()); i++) {
                if (dialogdata[i][0] != "0") {
                    if (dialogdata[i][0] == "hide")
                        m_Hide = true;
                    else {
                        m_Dialog.first = dialogdata[i][0];
                        m_Dialog.second = dialogdata[i][1];
                        currentdialogSize++;
                    }
                }
                else
                    m_Dialog.second += '\n' + dialogdata[i][1];
            }
            m_Option = Read::open_csv(m_OptionPath);
        }
    }

    void Touched() override {
        if (m_CanTouched) {
            m_ShopDialog->SetShopDialog(m_ImagePath, m_Dialog, m_Money, m_Option, m_Hide, this);
        }
    }

private:
    enum DATA {
        IMAGE = 0,
        NAME,
        CANTOUCHED,
        MONEY
    };
    std::string m_ImagePath;
    std::string m_DialogPath;
    std::string m_OptionPath;
    std::string m_Name;
    bool m_CanTouched;
    bool m_Money;
    std::pair<std::string, std::string> m_Dialog;
    std::vector<std::vector<std::string>> m_Option;
    bool m_Hide = false;

    std::shared_ptr<ShopDialog> m_ShopDialog;
};

#endif
