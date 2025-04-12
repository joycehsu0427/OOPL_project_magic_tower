#include "ShopDialog.hpp"
#include "Util/Logger.hpp"

ShopDialog::ShopDialog() : Dialog(RESOURCE_DIR"/bmp/Shop/ShopDialog.bmp") {
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

    m_DialogText->SetPivot({-192.5f, -135});
    m_DialogText->SetVisible(false);
    m_Children.push_back(m_DialogText);

    float position_x = -150;
    float position_y = -10;
    for (int i = 0; i < 4; i++) {
        Optionposition_y[i] = position_y + i * 55;
        m_Options[i] = std::make_shared<TextObject>(30, "Option" + std::to_string(i), 35);
        m_Options[i]->SetPivot({position_x, Optionposition_y[i]});
        m_Options[i]->SetVisible(false);
        m_Children.push_back(m_Options[i]);
    }

    m_CurrentOption = 0;
    m_OptionNumber = 4;

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
    LOG_DEBUG("UP " + std::to_string(m_CurrentOption));
}

void ShopDialog::OptionDown() {
    if (m_CurrentOption < m_OptionNumber - 1) {
        m_CurrentOption++;
        m_Tag->SetPivot({0, Optionposition_y[m_CurrentOption]});
    }
    LOG_DEBUG("Down " + std::to_string(m_CurrentOption));
}

void ShopDialog::Fixed() {

}
