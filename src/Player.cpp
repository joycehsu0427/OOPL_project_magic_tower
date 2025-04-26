#include "Player.hpp"
#include "ScenesManager.hpp"
#include "Util/Animation.hpp"

Player::Player(int x, int y, int positionX, int positionY) {
    // 圖片設置
    std::vector<std::string> image;
    image.emplace_back(RESOURCE_DIR"/bmp/Player/player.png");
    image.emplace_back(RESOURCE_DIR"/bmp/Player/player.png");
    for (int i = 1; i <= 4; i++) {
        std::vector <std::string> temp;
        for (int j = 1; j <= 4; j++) {
            temp.push_back(RESOURCE_DIR"/bmp/Player/player_" + std::to_string(i * 10 + j) + ".BMP");
        }
        m_Image.push_back(temp);
    }
    m_Drawable = std::make_shared<Util::Animation>(image, false, 500, false, 0);
    m_ZIndex = 20;
    m_Transform.scale = {0.73f, 0.73f};
    m_Pivot = {x, y};
    m_position_x = positionX;
    m_position_y = positionY;
}

void Player::SetSceneManager(const std::shared_ptr<ScenesManager> &scenesManager) {
    m_ScenesManager = scenesManager;
}


// 取得基本資料
[[nodiscard]] bool Player::GetWeak() const {return m_Weak;}
[[nodiscard]] bool Player::GetPoison() const {return m_Poison;}
[[nodiscard]] int Player::GetLevel() const { return m_Level; }
[[nodiscard]] int Player::GetHP() const { return m_HP; }
[[nodiscard]] int Player::GetATK() const { return m_ATK; }
[[nodiscard]] int Player::GetDEF() const { return m_DEF; }
[[nodiscard]] int Player::GetAGI() const { return m_AGI; }
[[nodiscard]] int Player::GetEXP() const { return m_EXP; }
[[nodiscard]] std::vector <int> Player::GetKeys() const { return m_Keys; }
[[nodiscard]] int Player::GetYellowKey() const { return m_Keys[0]; }
[[nodiscard]] int Player::GetBlueKey() const { return m_Keys[1]; }
[[nodiscard]] int Player::GetRedKey() const { return m_Keys[2]; }
[[nodiscard]] int Player::GetCoins() const { return m_Coins; }
[[nodiscard]] bool Player::CanSeeEnemyData() const { return m_SeeEnemyData; }
[[nodiscard]] bool Player::CanFly() const { return m_Fly; }

// 取得ScenceManager需要的文字資料
[[nodiscard]] std::string Player::GetStatus() const {
    if (!m_Weak && !m_Poison)
        return "正常";
    if (m_Weak && m_Poison)
        return "衰弱 & 中毒";
    if (m_Weak)
        return "衰弱";
    // 剩下只有 m_Poison == true的情況
    return "中毒";
}

[[nodiscard]] std::vector<std::string> Player::GetCurrentdaData1() const {
    return {std::to_string(m_Level), std::to_string(m_HP), std::to_string(m_ATK),
        std::to_string(m_DEF), std::to_string(m_AGI), std::to_string(m_EXP)};
}

[[nodiscard]] std::vector<std::string> Player::GetCurrentdaData2() const {
    return {std::to_string(m_Keys[0]), std::to_string(m_Keys[1]), std::to_string(m_Keys[2]), std::to_string(m_Coins)};
}

// 改變資料
void Player::SetWeak(bool weak) {
    m_Weak = weak;
    m_ScenesManager->ResetPlayerStatus();
}
void Player::SetPoison(bool poison) {
    m_Poison = poison;
    m_ScenesManager->ResetPlayerStatus();
}
void Player::LevelUp(int level) {
    if (level > 0) {
        m_Level += level;
        m_HP += 500;
        m_ATK += 5;
        m_DEF += 5;
        m_ScenesManager->ResetPlayerLevel();
    }
}
void Player::SetHP(int hp) {
    m_HP = hp;
    m_ScenesManager->ResetPlayerHP();
}
void Player::ChangeHP(int hp) {
    m_HP += hp;
    m_ScenesManager->ResetPlayerHP();
}
void Player::ChangeATK(int atk) {
    if (atk > 0) {
        m_ATK += atk;
        m_ScenesManager->ResetPlayerATK();
    }
}
void Player::ChangeDEF(int def) {
    if (def > 0) {
        m_DEF += def;
        m_ScenesManager->ResetPlayerDEF();
    }
}
void Player::ChangeAGI(int agi) {
    if (agi > 0) {
        m_AGI += agi;
        m_ScenesManager->ResetPlayerAGI();
    }
}
void Player::ChangeEXP(int exp) {
    m_EXP += exp;
    m_ScenesManager->ResetPlayerEXP();
}
void Player::ChangeYellowKey(int key) {
    m_Keys[0] += key;
    m_ScenesManager->ResetPlayerYellowKey();
}
void Player::ChangeBlueKey(int key) {
    m_Keys[1] += key;
    m_ScenesManager->ResetPlayerBlueKey();
}
void Player::ChangeRedKey(int key) {
    m_Keys[2] += key;
    m_ScenesManager->ResetPlayerRedKey();
}
void Player::ChangeCoins(int coin) {
    m_Coins += coin;
    m_ScenesManager->ResetPlayerCoins();
}
void Player::SetSeeEnemyData(bool see_enemy_data) {
    m_SeeEnemyData = see_enemy_data;
}
void Player::SetFly(bool fly) {
    m_Fly = fly;
}

