#include "Player.hpp"
#include "ScenesManager.hpp"
#include "Util/Image.hpp"

Player::Player(int x, int y, int positionX, int positionY) {
    // 圖片設置
    std::string image_path = RESOURCE_DIR"/bmp/Player/player_forward.png";
    m_Drawable = std::make_shared<Util::Image>(image_path);
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
[[nodiscard]] bool Player::GetWin() const { return m_Win; }

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
void Player::SetForward() {
    auto temp = std::dynamic_pointer_cast<Util::Image>(m_Drawable);
    temp->SetImage(RESOURCE_DIR"/bmp/Player/player_forward.png");
}

void Player::SetBackward() {
    auto temp = std::dynamic_pointer_cast<Util::Image>(m_Drawable);
    temp->SetImage(RESOURCE_DIR"/bmp/Player/player_backward.png");
}

void Player::SetLeft() {
    auto temp = std::dynamic_pointer_cast<Util::Image>(m_Drawable);
    temp->SetImage(RESOURCE_DIR"/bmp/Player/player_left.png");
}

void Player::SetRight() {
    auto temp = std::dynamic_pointer_cast<Util::Image>(m_Drawable);
    temp->SetImage(RESOURCE_DIR"/bmp/Player/player_right.png");
}

void Player::ResetData() {
    m_Weak = false;
    m_Poison = false;
    m_Level = 1;
    m_HP = 1000;
    m_ATK = 10;
    m_DEF = 10;
    m_AGI = 1;
    m_EXP = 0;
    m_Keys[0] = 1;
    m_Keys[1] = 1;
    m_Keys[2] = 1;
    m_Coins = 0;
    m_SeeEnemyData = false;
    m_Fly = false;
    m_Win = false;
    m_ScenesManager->ResetPlayerData();
}

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
        m_ScenesManager->ResetPlayerHP();
        m_ScenesManager->ResetPlayerATK();
        m_ScenesManager->ResetPlayerDEF();
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

void Player::SetWin(bool win) {
    m_Win = win;
}
