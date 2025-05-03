#include "EnemyData.hpp"
#include "Read.hpp"

EnemyData::EnemyData(int num){
    float shift_y = 180 * num;
    float scale = 0.732f;
    m_BackGround = std::make_shared<ImageObject>(RESOURCE_DIR"/bmp/Special/Black.bmp", 30);
    m_BackGround->SetPivot({-194, 0});
    m_BackGround->SetVisible(false);
    m_BackGround->SetScale(scale);
    m_Children.push_back(m_BackGround);

    float image_x = 154;
    float image_y = -269.5f + shift_y / scale;
    m_ImageFrame = std::make_shared<ImageObject>(RESOURCE_DIR"/bmp/Special/EnemyFrame.bmp", 35);
    m_ImageFrame->SetPivot({image_x, image_y});
    m_ImageFrame->SetVisible(false);
    m_ImageFrame->SetScale(scale);
    m_Children.push_back(m_ImageFrame);

    m_Image = std::make_shared<ImageObject>(RESOURCE_DIR"/bmp/Enemy/bat.bmp", 40);
    m_Image->SetPivot({image_x, image_y});
    m_Image->SetVisible(false);
    m_Image->SetScale(scale);
    m_Children.push_back(m_Image);

    int title_size = 25;
    int data_size = 20;
    float name_y = -255 + shift_y;
    m_Name_Title = std::make_shared<TextObject>(title_size, "名稱:", 35);
    m_Name_Title->SetPivot({100, name_y});
    m_Name_Title->SetVisible(false);
    m_Children.push_back(m_Name_Title);

    m_Name = std::make_shared<TextObject>(data_size, "綠色史萊姆", Util::Color::FromName(Util::Colors::LIGHT_GREEN), 35);
    m_Name->SetPivot({-30, name_y});
    m_Name->SetVisible(false);
    m_Children.push_back(m_Name);

    m_Special_Title = std::make_shared<TextObject>(title_size, "特殊:", 35);
    m_Special_Title->SetPivot({-180, name_y});
    m_Special_Title->SetVisible(false);
    m_Children.push_back(m_Special_Title);

    m_Special = std::make_shared<TextObject>(data_size, "被擊殺後再生靈骷髏", Util::Color::FromName(Util::Colors::PINK), 35);
    m_Special->SetPivot({-330, name_y});
    m_Special->SetVisible(false);
    m_Children.push_back(m_Special);

    float position_y[4] = {-220 + shift_y, -190 + shift_y, -160 + shift_y, -130 + shift_y};
    float position_x[2][4] = {{20, -80, -200, -310}, {0, -140, -250, -330}};

    m_HP_Title = std::make_shared<TextObject>(title_size, "體力:", 35);
    m_HP_Title->SetPivot({position_x[0][0], position_y[0]});
    m_HP_Title->SetVisible(false);
    m_Children.push_back(m_HP_Title);

    m_HP = std::make_shared<TextObject>(data_size, "65", Util::Color::FromName(Util::Colors::GREEN_YELLOW), 35);
    m_HP->SetPivot({position_x[0][0], position_y[1]});
    m_HP->SetVisible(false);
    m_Children.push_back(m_HP);

    m_ATK_Title = std::make_shared<TextObject>(title_size, "攻擊力:", 35);
    m_ATK_Title->SetPivot({position_x[0][1], position_y[0]});
    m_ATK_Title->SetVisible(false);
    m_Children.push_back(m_ATK_Title);

    m_ATK = std::make_shared<TextObject>(data_size, "10", Util::Color::FromName(Util::Colors::MEDIUM_PURPLE), 35);
    m_ATK->SetPivot({position_x[0][1], position_y[1]});
    m_ATK->SetVisible(false);
    m_Children.push_back(m_ATK);

    m_DEF_Title = std::make_shared<TextObject>(title_size, "防禦力:", 35);
    m_DEF_Title->SetPivot({position_x[0][2], position_y[0]});
    m_DEF_Title->SetVisible(false);
    m_Children.push_back(m_DEF_Title);

    m_DEF = std::make_shared<TextObject>(data_size, "20", Util::Color::FromName(Util::Colors::ORANGE), 35);
    m_DEF->SetPivot({position_x[0][2], position_y[1]});
    m_DEF->SetVisible(false);
    m_Children.push_back(m_DEF);

    m_AGI_Title = std::make_shared<TextObject>(title_size, "敏捷:", 35);
    m_AGI_Title->SetPivot({position_x[0][3], position_y[0]});
    m_AGI_Title->SetVisible(false);
    m_Children.push_back(m_AGI_Title);

    m_AGI = std::make_shared<TextObject>(data_size, "30", Util::Color::FromName(Util::Colors::GREEN), 35);
    m_AGI->SetPivot({position_x[0][3], position_y[1]});
    m_AGI->SetVisible(false);
    m_Children.push_back(m_AGI);

    m_ATKTime_Title = std::make_shared<TextObject>(title_size, "攻擊次數:", 35);
    m_ATKTime_Title->SetPivot({position_x[1][0], position_y[2]});
    m_ATKTime_Title->SetVisible(false);
    m_Children.push_back(m_ATKTime_Title);

    m_ATKTime = std::make_shared<TextObject>(data_size, "40", Util::Color::FromName(Util::Colors::LIGHT_SKY_BLUE), 35);
    m_ATKTime->SetPivot({position_x[1][0], position_y[3]});
    m_ATKTime->SetVisible(false);
    m_Children.push_back(m_ATKTime);

    m_Hurt_Title = std::make_shared<TextObject>(title_size, "估計傷害:",35);
    m_Hurt_Title->SetPivot({position_x[1][1], position_y[2]});
    m_Hurt_Title->SetVisible(false);
    m_Children.push_back(m_Hurt_Title);

    m_Hurt = std::make_shared<TextObject>(data_size, "50", Util::Color::FromName(Util::Colors::RED), 35);
    m_Hurt->SetPivot({position_x[1][1], position_y[3]});
    m_Hurt->SetVisible(false);
    m_Children.push_back(m_Hurt);

    m_EXP_Title = std::make_shared<TextObject>(title_size, "Exp:", 35);
    m_EXP_Title->SetPivot({position_x[1][2], position_y[2]});
    m_EXP_Title->SetVisible(false);
    m_Children.push_back(m_EXP_Title);

    m_EXP = std::make_shared<TextObject>(data_size, "50", Util::Color::FromName(Util::Colors::LIGHT_BLUE), 35);
    m_EXP->SetPivot({position_x[1][2], position_y[3]});
    m_EXP->SetVisible(false);
    m_Children.push_back(m_EXP);

    m_Coin_Title = std::make_shared<TextObject>(title_size, "Coin:", 35);
    m_Coin_Title->SetPivot({position_x[1][3], position_y[2]});
    m_Coin_Title->SetVisible(false);
    m_Children.push_back(m_Coin_Title);

    m_Coin = std::make_shared<TextObject>(data_size, "50", Util::Color::FromName(Util::Colors::YELLOW), 35);
    m_Coin->SetPivot({position_x[1][3], position_y[3]});
    m_Coin->SetVisible(false);
    m_Children.push_back(m_Coin);
}

void EnemyData::SetEnemy(int num) const {
    std::vector<std::vector<std::string>> enemydata = Read::open_csv(RESOURCE_DIR"/Data/Enemy.csv");
    m_Image->SetImage(RESOURCE_DIR"/bmp/Enemy/" + enemydata[num][0] + ".bmp");
    m_Name->SetText(enemydata[num][1]);
    m_Special->SetText(enemydata[num][14]);
    m_HP->SetText(enemydata[num][2]);
    m_ATK->SetText(enemydata[num][3]);
    m_DEF->SetText(enemydata[num][4]);
    m_AGI->SetText(enemydata[num][5]);
    m_ATKTime->SetText(enemydata[num][10]);

    int enemy_hp = std::stoi(enemydata[num][2]);
    int enemy_atk = std::stoi(enemydata[num][3]);
    int enemy_def = std::stoi(enemydata[num][4]);
    int enemy_atktime = std::stoi(enemydata[num][10]);
    bool enemy_ignoredef = std::stoi(enemydata[num][11]);
    int atk = m_Player->GetATK() - enemy_def;
    if (atk <= 0)
        atk = 1;
    int atktime = (enemy_hp - 1) / atk;
    int atkhp = enemy_atk;
    if (!enemy_ignoredef) {
        atkhp -= m_Player->GetDEF();
    }
    if (atkhp <= 0)
        atkhp = 1;
    atkhp *= enemy_atktime;
    int hurt = atktime * atkhp;
    m_Hurt->SetText(std::to_string(hurt));
    m_EXP->SetText(enemydata[num][6]);
    m_Coin->SetText(enemydata[num][7]);
}

void EnemyData::SetEnemy(const std::shared_ptr<Enemy> &enemy) const{
    m_Image->SetImage(enemy->GetImage_Path());
    m_Name->SetText(enemy->GetName());
    m_Special->SetText(enemy->GetSpecial());
    m_HP->SetText(std::to_string(enemy->GetHP()));
    m_ATK->SetText(std::to_string(enemy->GetATK()));
    m_DEF->SetText(std::to_string(enemy->GetDEF()));
    m_AGI->SetText(std::to_string(enemy->GetAGI()));
    m_ATKTime->SetText(std::to_string(enemy->GetATK_Time()));

    int enemy_hp = enemy->GetHP();
    int enemy_atk = enemy->GetATK();
    int enemy_def = enemy->GetDEF();
    int enemy_atktime = enemy->GetATK_Time();
    bool enemy_ignoredef = enemy->GetIgnore_DEF();
    int atk = m_Player->GetATK() - enemy_def;
    if (atk <= 0)
        atk = 1;
    int atktime = (enemy_hp - 1) / atk;
    int atkhp = enemy_atk;
    if (!enemy_ignoredef) {
        atkhp -= m_Player->GetDEF();
    }
    if (atkhp <= 0)
        atkhp = 1;
    atkhp *= enemy_atktime;
    int hurt = atktime * atkhp;
    m_Hurt->SetText(std::to_string(hurt));
    m_EXP->SetText(std::to_string(enemy->GetEXP()));
    m_Coin->SetText(std::to_string(enemy->GetCoin()));
}


void EnemyData::SetPlayer(const std::shared_ptr<Player> &player) {
    m_Player = player;
}

