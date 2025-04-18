#ifndef SHOPDIALOG_HPP
#define SHOPDIALOG_HPP

#include <Dialog.hpp>
#include <Player.hpp>

class Shop;

class ShopDialog : public Dialog {
public:
    ShopDialog();

    void OptionUp();
    void OptionDown();
    void Fixed();

    void SetVisible(bool visible) override {
        m_Visible = visible;
        for (auto& child : m_Children) {
            child->SetVisible(m_Visible);
        }
    }
    void SetShopDialog(const std::string &imagePath, const std::pair <std::string, std::string> &dialog,
        bool spendmoney, const std::vector<std::vector<std::string>> &optiondata, bool hide, Shop* shop);
    void SetPlayer(const std::shared_ptr<Player> &player) {
        m_Player = player;
    }

    [[nodiscard]] std::vector<std::shared_ptr<Util::GameObject>> GetChildren() const override {
        return m_Children;
    }

private:
    enum OptionType {
        LEVEL = 0,
        HP,
        ATK,
        DEF,
        EXP,
        YELLOW_KEY,
        BLUE_KEY,
        RED_KEY,
        COIN
    };
    std::shared_ptr<ImageObject> m_People;
    std::shared_ptr<TextObject> m_Name;
    std::shared_ptr<TextObject> m_MoneyText;
    std::shared_ptr<TextObject> m_Options[4];
    std::shared_ptr<TextObject> m_Tag;

    int m_CurrentOption;
    int m_OptionNumber;
    int m_Money;
    bool m_SpendMoney = false;
    float Optionposition_y[4] = {0};
    bool m_Hide = false;
    std::vector<std::vector<std::string>> m_OptionData;
    Shop* m_Shop = nullptr;

    std::vector<std::shared_ptr<Util::GameObject>> m_Children;

    std::shared_ptr<Player> m_Player;

    void Buy();
};

#endif
