#include "ShopDialog.hpp"

#include <Shop.hpp>

#include "Util/Logger.hpp"

ShopDialog::ShopDialog() : Dialog(RESOURCE_DIR"/bmp/Shop/ShopDialog.bmp", 23) {
    m_Background->SetPivot({-192.5f, -38.5f});
    m_Background->SetVisible(false);
    m_Children.push_back(m_Background);

    m_People = std::make_shared<ImageObject>(RESOURCE_DIR"/bmp/Shop/elder.bmp", 35);
    m_People->SetPivot({-38.5f, -231});
    m_People->SetVisible(false);
    m_People->SetScale(0.73f);
    m_Children.push_back(m_People);

    m_Name = std::make_shared<TextObject>(30, "老人", 35);
    m_Name->SetPivot({-192.5f, -220});
    m_Name->SetVisible(false);
    m_Children.push_back(m_Name);

    m_DialogText->SetPivot({-207, -135});
    m_DialogText->SetVisible(false);
    m_Children.push_back(m_DialogText);

    m_Money = 20;
    m_MoneyText = std::make_shared<TextObject>(22, std::to_string(m_Money), 35);
    m_MoneyText->SetPivot({-165, -135});
    m_MoneyText->SetVisible(false);
    m_Children.push_back(m_MoneyText);

    float position_x = -150;
    float position_y = -10;
    for (int i = 0; i < 4; i++) {
        Optionposition_y[i] = position_y + i * 55;
        m_Options[i] = std::make_shared<TextObject>(25, "Option" + std::to_string(i), 35);
        m_Options[i]->SetPivot({position_x, Optionposition_y[i]});
        m_Options[i]->SetVisible(false);
        m_Children.push_back(m_Options[i]);
    }

    m_CurrentOption = 0;
    m_OptionNumber = 3;

    m_Tag = std::make_shared<TextObject>(30, "→", 35);
    m_Tag->SetPivot({0, Optionposition_y[0]});
    m_Tag->SetVisible(false);
    m_Children.push_back(m_Tag);
}

void ShopDialog::OptionUp() {
    if (m_CurrentOption > 0) {
        m_CurrentOption--;
        m_Tag->SetPivot({0, Optionposition_y[m_CurrentOption]});
    }
}

void ShopDialog::OptionDown() {
    if (m_CurrentOption < m_OptionNumber) {
        m_CurrentOption++;
        m_Tag->SetPivot({0, Optionposition_y[m_CurrentOption]});
    }
}

void ShopDialog::Fixed() {
    if (m_CurrentOption == m_OptionNumber) {
        SetVisible(false);
    }
    else {
        Buy();
    }
}

void ShopDialog::ResetShopDialog() {
    m_Money = 20;
    m_MoneyText->SetText(std::to_string(m_Money));
}


void ShopDialog::SetShopDialog(const std::string &imagePath, const std::pair <std::string, std::string> &dialog,
    bool spendmoney, const std::vector<std::vector<std::string>> &optiondata, bool hide, Shop* shop) {
    m_People->SetImage(imagePath);
    m_Name->SetText(dialog.first);
    m_DialogText->SetText(dialog.second);
    SetVisible(true);

    m_SpendMoney = spendmoney;
    m_MoneyText->SetVisible(m_SpendMoney);
    m_OptionData = optiondata;
    m_OptionNumber = m_OptionData.size() - 1;
    for (int i = 0; i < m_OptionNumber; i++) {
        m_Options[i]->SetText(m_OptionData[i + 1][0]);
    }
    m_Options[m_OptionNumber]->SetText("離開");
    for (int i = m_OptionNumber + 1; i < 4; i++) {
        m_Options[i]->SetVisible(false);
    }
    m_CurrentOption = 0;
    m_Tag->SetPivot({0, Optionposition_y[m_CurrentOption]});

    m_Hide = hide;
    m_Shop = shop;
}

void ShopDialog::Buy() {
    bool can_buy = false;
    int data[9];
    for (int i = 0; i < 9; i++) {
        // LOG_DEBUG(m_OptionData[0][i+1] + "-" + m_OptionData[m_CurrentOption + 1][i+1]);
        data[i] = std::stoi(m_OptionData[m_CurrentOption + 1][i+1]);
    }
    if (m_SpendMoney) {
        if (m_Player->GetCoins() >= m_Money) {
            can_buy = true;
            m_Player->ChangeCoins(-m_Money);
            m_Money ++;
            m_MoneyText->SetText(std::to_string(m_Money));
        }
    }
    else {
        if (data[EXP] < 0) {
            if (abs(data[EXP]) <= m_Player->GetEXP()) {
                can_buy = true;
                m_Player->ChangeEXP(data[EXP]);
            }
        }
        else if (data[COIN] < 0) {
            if (abs(data[COIN]) <= m_Player->GetCoins()) {
                can_buy = true;
                m_Player->ChangeCoins(data[COIN]);
            }
        }
        else if (data[COIN] > 0) {
            if (m_Player->GetYellowKey() >= abs(data[YELLOW_KEY]) || m_Player->GetBlueKey() >= abs(data[BLUE_KEY]) || m_Player->GetRedKey() >= abs(data[RED_KEY])) {
                can_buy = true;
                m_Player->ChangeYellowKey(data[YELLOW_KEY]);
                m_Player->ChangeBlueKey(data[BLUE_KEY]);
                m_Player->ChangeRedKey(data[RED_KEY]);
            }
        }
    }
    if (can_buy) {
        if (data[LEVEL] > 0)
            m_Player->LevelUp(data[LEVEL]);
        else if (data[HP] > 0)
            m_Player->ChangeHP(data[HP]);
        else if (data[ATK] > 0)
            m_Player->ChangeATK(data[ATK]);
        else if (data[DEF] > 0)
            m_Player->ChangeDEF(data[DEF]);
        else if (data[EXP] > 0)
            m_Player->ChangeEXP(data[EXP]);
        else if (data[YELLOW_KEY] > 0)
            m_Player->ChangeYellowKey(data[YELLOW_KEY]);
        else if (data[BLUE_KEY] > 0)
            m_Player->ChangeBlueKey(data[BLUE_KEY]);
        else if (data[RED_KEY] > 0)
            m_Player->ChangeRedKey(data[RED_KEY]);
        else if (data[COIN] > 0)
            m_Player->ChangeCoins(data[COIN]);
        if (m_Hide) {
            SetVisible(false);
            m_Shop->SetVisible(false);
        }
    }
}
