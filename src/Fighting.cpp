#include "Fighting.hpp"
#include "Enemy.hpp"
#include "Random.hpp"
#include "Util/Logger.hpp"

Fighting::Fighting() {
    int mid_position_x = -145;
    int padding[2] = {70, 160};
    int image_position_x[2] = {-539, 154};
    std::string image_path[2] = { RESOURCE_DIR"/bmp/Player/player_11.bmp", RESOURCE_DIR"/bmp/Enemy/green_slime.bmp" };
    int name_position_x[2] = {-400, 100};
    std::string name[2] = {"勇者", "綠色史萊姆"};
    int data_position_x[2][2] = {{ mid_position_x - padding[0], mid_position_x - padding[1] },
                                { mid_position_x + padding[0], mid_position_x + padding[1] }};
    int data_position_y[4] = { -60, -20, 20, 60 };
    int data_text_size = 22;
    std::string data_title_basic[4] = {"體　力", "攻擊力", "防禦力", "敏　捷"};

    m_Background = std::make_shared<ImageObject>(RESOURCE_DIR"/bmp/Enemy/Fighting.bmp", 30);
    m_Background->SetPivot({-192.5f, -38.5f});
    m_Background->SetVisible(false);
    m_Background->SetScale(0.73f);
    m_Fighting_Children.push_back(m_Background);

    m_RemindText = std::make_shared<TextObject>(25, "-Space-", Util::Color::FromName(Util::Colors::YELLOW), 35);
    m_RemindText->SetPivot({-425, 60});
    m_RemindText->SetVisible(false);
    m_Fighting_Children.push_back(m_RemindText);

    m_VS = std::make_shared<TextObject>(30, "VS", 35);
    m_VS->SetPivot({mid_position_x, -110});
    m_VS->SetVisible(false);
    m_Fighting_Children.push_back(m_VS);

    m_Visible = false;

    m_SpecialATK = std::make_shared<TextObject>(20, "中毒", Util::Color::FromName(Util::Colors::RED), 35);
    m_SpecialATK->SetPivot({name_position_x[0], 30});
    m_SpecialATK->SetVisible(false);
    m_Effect_Children.push_back(m_SpecialATK);

    for (int i = 0; i < 2; i++) {
        std::string data_title[4];
        for (int j = 0; j < 4; j++) {
            data_title[j] = data_title_basic[j];
            if (i == 0)
                data_title[j] = "：" + data_title[j];
            else data_title[j] = data_title[j] + "：";
        }

        m_Effect[i] = std::make_shared<ImageObject>(RESOURCE_DIR"/bmp/Effect/Fighting.png", 40);
        m_Effect[i]->SetPivot({image_position_x[i], -77});
        m_Effect[i]->SetVisible(false);
        m_Effect[i]->SetScale(0.725f);
        m_Effect_Children.push_back(m_Effect[i]);

        m_Minus_HP[i] = std::make_shared<TextObject>(30, "10", Util::Color::FromName(Util::Colors::RED), 35);
        m_Minus_HP[i]->SetPivot({name_position_x[i], 0});
        m_Minus_HP[i]->SetVisible(false);
        m_Effect_Children.push_back(m_Minus_HP[i]);

        m_Image[i] = std::make_shared<ImageObject>(image_path[i], 35);
        m_Image[i]->SetPivot({image_position_x[i], -77});
        m_Image[i]->SetVisible(false);
        m_Image[i]->SetScale(0.725f);
        m_Fighting_Children.push_back(m_Image[i]);

        m_Name[i] = std::make_shared<TextObject>(25, name[i], 35);
        m_Name[i]->SetPivot({name_position_x[i], -110});
        m_Name[i]->SetVisible(false);
        m_Fighting_Children.push_back(m_Name[i]);

        m_HP_Text[i] = std::make_shared<TextObject>(data_text_size, "1000", 35);
        m_HP_Text[i]->SetPivot({data_position_x[i][0], data_position_y[0]});
        m_HP_Text[i]->SetVisible(false);
        m_Fighting_Children.push_back(m_HP_Text[i]);

        m_HP_Title[i] = std::make_shared<TextObject>(data_text_size,  data_title[0], 35);
        m_HP_Title[i]->SetPivot({data_position_x[i][1], data_position_y[0]});
        m_HP_Title[i]->SetVisible(false);
        m_Fighting_Children.push_back(m_HP_Title[i]);

        m_ATK_Text[i] = std::make_shared<TextObject>(data_text_size, "10", 35);
        m_ATK_Text[i]->SetPivot({data_position_x[i][0], data_position_y[1]});
        m_ATK_Text[i]->SetVisible(false);
        m_Fighting_Children.push_back(m_ATK_Text[i]);

        m_ATK_Title[i] = std::make_shared<TextObject>(data_text_size, data_title[1], 35);
        m_ATK_Title[i]->SetPivot({data_position_x[i][1], data_position_y[1]});
        m_ATK_Title[i]->SetVisible(false);
        m_Fighting_Children.push_back(m_ATK_Title[i]);

        m_DEF_Text[i] = std::make_shared<TextObject>(data_text_size, "10", 35);
        m_DEF_Text[i]->SetPivot({data_position_x[i][0], data_position_y[2]});
        m_DEF_Text[i]->SetVisible(false);
        m_Fighting_Children.push_back(m_DEF_Text[i]);

        m_DEF_Title[i] = std::make_shared<TextObject>(data_text_size, data_title[2], 35);
        m_DEF_Title[i]->SetPivot({data_position_x[i][1], data_position_y[2]});
        m_DEF_Title[i]->SetVisible(false);
        m_Fighting_Children.push_back(m_DEF_Title[i]);

        m_AGI_Text[i] = std::make_shared<TextObject>(data_text_size, "2", 35);
        m_AGI_Text[i]->SetPivot({data_position_x[i][0], data_position_y[3]});
        m_AGI_Text[i]->SetVisible(false);
        m_Fighting_Children.push_back(m_AGI_Text[i]);

        m_AGI_Title[i] = std::make_shared<TextObject>(data_text_size, data_title[3], 35);
        m_AGI_Title[i]->SetPivot({data_position_x[i][1], data_position_y[3]});
        m_AGI_Title[i]->SetVisible(false);
        m_Fighting_Children.push_back(m_AGI_Title[i]);
    }

    // Reward設置
    int text_position_y = 115;

    m_Reward_Image = std::make_shared<ImageObject>(RESOURCE_DIR"/bmp/Enemy/Reward.bmp", 30);
    m_Reward_Image->SetPivot({-192.5f, 154});
    m_Reward_Image->SetVisible(false);
    m_Reward_Image->SetScale(0.73f);
    m_Reward_Children.push_back(m_Reward_Image);

    m_Win_Text = std::make_shared<TextObject>(30, "勝利!!", 35);
    m_Win_Text->SetPivot({130, text_position_y});
    m_Win_Text->SetVisible(false);
    m_Reward_Children.push_back(m_Win_Text);

    m_EXP_Title = std::make_shared<TextObject>(25, "經驗值：", 35);
    m_EXP_Title->SetPivot({0, text_position_y});
    m_EXP_Title->SetVisible(false);
    m_Reward_Children.push_back(m_EXP_Title);

    m_EXP_Text = std::make_shared<TextObject>(25, "1", 35);
    m_EXP_Text->SetPivot({-75, text_position_y});
    m_EXP_Text->SetVisible(false);
    m_Reward_Children.push_back(m_EXP_Text);

    m_Coin_Title = std::make_shared<TextObject>(25, "金幣：", 35);
    m_Coin_Title->SetPivot({-250, text_position_y});
    m_Coin_Title->SetVisible(false);
    m_Reward_Children.push_back(m_Coin_Title);

    m_Coin_Text = std::make_shared<TextObject>(25, "2", 35);
    m_Coin_Text->SetPivot({-325, text_position_y});
    m_Coin_Text->SetVisible(false);
    m_Reward_Children.push_back(m_Coin_Text);
}

void Fighting::SetStartFighting() {
    m_IsFighting = true;
    m_EndFighting = false;
    // 數值設定
    m_HP[0] = m_Player->GetHP();
    m_ATK[0] = m_Player->GetATK();
    m_DEF[0] = m_Player->GetDEF();
    m_AGI[0] = m_Player->GetAGI();
    m_HP[1] = m_Enemy->GetHP();
    m_ATK[1] = m_Enemy->GetATK();
    m_DEF[1] = m_Enemy->GetDEF();
    m_AGI[1] = m_Enemy->GetAGI();
    m_EnemyIgnoreDEF = m_Enemy->GetIgnore_DEF();
    // 視窗設定
    m_RemindText->SetText("退出(Q)");
    m_Image[1]->SetImage(m_Enemy->GetImage_Path());
    m_Name[1]->SetText(m_Enemy->GetName());
    for (int i = 0; i < 2; i++) {
        m_HP_Text[i]->SetText(std::to_string(m_HP[i]));
        m_ATK_Text[i]->SetText(std::to_string(m_ATK[i]));
        m_DEF_Text[i]->SetText(std::to_string(m_DEF[i]));
        m_AGI_Text[i]->SetText(std::to_string(m_AGI[i]));
    }
    m_Visible = true;
    for (auto& child : m_Fighting_Children)
        child->SetVisible(m_Visible);
}

void Fighting::StartFighting(Enemy *enemy) {
    m_Enemy = enemy;
    SetStartFighting();
}

void Fighting::PlayerATK() {
    int atk = m_ATK[0] - m_DEF[1];
    if (atk <= 0)
        atk = 1;
    if (m_AGI[1] != 0) {
        int miss = Random::random(100);
        // LOG_DEBUG("player atk " + std::to_string(miss));
        if (miss < m_AGI[1])
            m_Minus_HP[1]->SetText("Miss");
        else
            EnemyHPMinus(atk);
    }
    else
        EnemyHPMinus(atk);
    m_Minus_HP[1]->SetVisible(true);
    if (m_HP[1] <= 0) {
        m_HP_Text[1]->SetText("0");
        m_EndFighting = true;
    }
    else
        m_HP_Text[1]->SetText(std::to_string(m_HP[1]));
    m_EnemyATKTime = 0;
}

void Fighting::EnemyATK() {
    int atk = m_ATK[1];
    if (!m_EnemyIgnoreDEF)
        atk -= m_DEF[0];
    if (atk <= 0)
        atk = 1;
    // 普通攻擊
    if (m_AGI[0] != 0) {
        int miss = Random::random(100);
        // LOG_DEBUG("enemy atk  " + std::to_string(miss));
        if (miss < m_AGI[0]) {
            m_Minus_HP[0]->SetText("Miss");
            atk = 0;
        }
        else
            PlayerHPMinus(atk);
    }
    else
        PlayerHPMinus(atk);
    if (atk != 0) {
        // 必殺攻擊
        if (m_Enemy->GetKilling_ATK() != 0) {
            int kill = Random::random(100);
            if (kill < m_Enemy->GetKilling_ATK()) {
                m_Minus_HP[0]->SetText("Kill");
                m_HP[0] = 0;
                m_Effect[0]->SetVisible(true);
            }
        }
        // 虛弱
        if (m_Enemy->GetWeak() != 0) {
            int weak = Random::random(100);
            if (weak < 1) {
                m_SpecialATK->SetText("衰弱");
                m_SpecialATK->SetVisible(true);
                m_Player->SetWeak(true);
            }
        }
        // 中毒
        if (m_Enemy->GetPoison() != 0) {
            int poison = Random::random(100);
            if (poison < 1) {
                m_SpecialATK->SetText("中毒");
                m_SpecialATK->SetVisible(true);
                m_Player->SetPoison(true);
            }
        }
    }
    m_Minus_HP[0]->SetVisible(true);
    if (m_HP[0] <= 0) {
        m_HP_Text[0]->SetText("0");
        m_Player->SetHP(0);
        m_EndFighting = true;
    }
    else
        m_HP_Text[0]->SetText(std::to_string(m_HP[0]));
    m_EnemyATKTime++;
}

void Fighting::PlayerHPMinus(int atk) {
    m_HP[0] -= atk;
    m_Effect[0]->SetVisible(true);
    m_Minus_HP[0]->SetText(std::to_string(atk));
}

void Fighting::EnemyHPMinus(int atk) {
    m_HP[1] -= atk;
    m_Effect[1]->SetVisible(true);
    m_Minus_HP[1]->SetText(std::to_string(atk));
}


void Fighting::QuitFighting() {
    m_Player->SetHP(m_HP[0]);
    SetVisible(false);
}

void Fighting::EndFighting() {
    for (int i = 0; i < 2; i++) {
        m_Effect[i]->SetVisible(false);
        m_Minus_HP[i]->SetVisible(false);
    }
    m_IsFighting = false;
    if (m_HP[1] <= 0)
        EnemyDie();
}

void Fighting::ClearEffect() {
    for (auto& effect : m_Effect_Children) {
        effect->SetVisible(false);
    }
}


void Fighting::SetVisible(const bool &visible) {
    m_Visible = visible;
    for (auto& child : m_Fighting_Children)
        child->SetVisible(m_Visible);
    for (auto& child : m_Effect_Children)
        child->SetVisible(m_Visible);
    for (auto& child : m_Reward_Children)
        child->SetVisible(m_Visible);
}

void Fighting::SetPlayer(const std::shared_ptr<Player> &player) {
    m_Player = player;
}

[[nodiscard]] bool Fighting::IsEnemyATKEnd() const {
    return  m_Enemy->GetATK_Time() == m_EnemyATKTime;
}

void Fighting::EnemyDie() {
    m_Effect[1]->SetVisible(false);
    m_Player->SetHP(m_HP[0]);
    m_Enemy->Die();
    Reward();
    m_RemindText->SetText("-Space-");
}

void Fighting::Reward() {
    for (auto& child : m_Reward_Children)
        child->SetVisible(true);
    m_Player->ChangeEXP(m_Enemy->GetEXP());
    m_Player->ChangeCoins(m_Enemy->GetCoin());
    m_EXP_Text->SetText(std::to_string(m_Enemy->GetEXP()));
    m_Coin_Text->SetText(std::to_string(m_Enemy->GetCoin()));
}
