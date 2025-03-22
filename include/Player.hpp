#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <vector>
#include <string>

#include "Util/Animation.hpp"
#include "Util/GameObject.hpp"

class Player : public Util::GameObject {
public:
     Player(int x, int y, int positionX, int positionY) {
         // 圖片設置
         for (int i = 1; i <= 4; i++) {
             std::vector <std::string> temp;
             for (int j = 1; j <= 4; j++) {
                 temp.push_back(RESOURCE_DIR"/bmp/Player/player_" + std::to_string(i * 10 + j) + ".BMP");
             }
             m_Image.push_back(temp);
         }
         m_Drawable = std::make_shared<Util::Animation>(m_Image[0], false, 500, false, 0);
         m_ZIndex = 20;
         m_Transform.scale = {0.73f, 0.73f};
         m_Pivot = {x, y};
         m_position_x = positionX;
         m_position_y = positionY;
     }

    [[nodiscard]] int GetPositionX() { return m_position_x; }
    [[nodiscard]] int GetPositionY() { return m_position_y; }

    void SetPosition(int x, int y) {
         m_position_x = x;
         m_position_y = y;
    }

    // 取得基本資料
    [[nodiscard]] int GetLevel() const { return m_Level; }
    [[nodiscard]] int GetHP() const { return m_HP; }
    [[nodiscard]] int GetATK() const { return m_ATK; }
    [[nodiscard]] int GetDEF() const { return m_DEF; }
    [[nodiscard]] int GetAGI() const { return m_AGI; }
    [[nodiscard]] std::vector <int> GetKeys() const { return m_Keys; }
    [[nodiscard]] int GetYellowKey() const { return m_Keys[0]; }
    [[nodiscard]] int GetBlueKey() const { return m_Keys[1]; }
    [[nodiscard]] int GetRedKey() const { return m_Keys[2]; }
    [[nodiscard]] int GetCoins() const { return m_Coins; }

    //改變資料
    void LevelUp(int level) { m_Level += level; }
    void ChangeHP(int hp) { m_HP += hp; }
    void ChangeATK(int atk) { m_ATK += atk; }
    void ChangeDEF(int def) { m_DEF += def; }
    void ChangeAGI(int agi) { m_AGI += agi; }
    void ChangeYellowKey(int key) { m_Keys[0] += key; }
    void ChangeBlueKey(int key) { m_Keys[1] += key; }
    void ChangeRedKey(int key) { m_Keys[2] += key; }
    void ChangeCoins(int coin) { m_Coins += coin; }



private:
    int m_position_x;
    int m_position_y;
    // 基礎能力及所擁有的物品
    int m_Level = 1;                        // 等級
    int m_HP = 1000;                        // 血量
    int m_ATK = 10;                         // 攻擊力
    int m_DEF = 10;                         // 防禦力
    int m_AGI = 1;                          // 敏捷
    int m_EXP = 0;                          // 經驗值
    std::vector <int> m_Keys = { 1, 1, 1 }; // 黃 / 藍 / 紅鑰匙
    int m_Coins = 0;                        // 金幣

    // 角色圖片
    // 前0 後1 左2 右3 (各有4張照片)
    std::vector <std::vector <std::string>> m_Image;

};

#endif
