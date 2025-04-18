#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <vector>
#include <string>

#include "Util/GameObject.hpp"

class ScenesManager;

class Player : public Util::GameObject {
public:
     Player(int x, int y, int positionX, int positionY);

    void SetSceneManager(const std::shared_ptr<ScenesManager> &scenesManager);

    void SetPosition(int x, int y) {
         m_position_x = x;
         m_position_y = y;
    }

    [[nodiscard]] int GetPositionX() const { return m_position_x; }
    [[nodiscard]] int GetPositionY() const { return m_position_y; }

    // 取得基本資料
    [[nodiscard]] bool GetWeak() const;
    [[nodiscard]] bool GetPoison() const;
    [[nodiscard]] int GetLevel() const;
    [[nodiscard]] int GetHP() const;
    [[nodiscard]] int GetATK() const;
    [[nodiscard]] int GetDEF() const;
    [[nodiscard]] int GetAGI() const;
    [[nodiscard]] int GetEXP() const;
    [[nodiscard]] std::vector <int> GetKeys() const;
    [[nodiscard]] int GetYellowKey() const;
    [[nodiscard]] int GetBlueKey() const;
    [[nodiscard]] int GetRedKey() const;
    [[nodiscard]] int GetCoins() const;

    [[nodiscard]] std::string GetStatus() const;

    [[nodiscard]] std::vector<std::string> GetCurrentdaData1() const;

    [[nodiscard]] std::vector<std::string> GetCurrentdaData2() const;

    // 改變資料
    void SetWeak(bool weak);
    void SetPoison(bool poison);
    void LevelUp(int level);
    void SetHP(int hp);
    void ChangeHP(int hp);
    void ChangeATK(int atk);
    void ChangeDEF(int def);
    void ChangeAGI(int agi);
    void ChangeEXP(int exp);
    void ChangeYellowKey(int key);
    void ChangeBlueKey(int key);
    void ChangeRedKey(int key);
    void ChangeCoins(int coin);
    void SetHeartMirror(bool heartMirror);



private:
    int m_position_x;
    int m_position_y;
    // 基礎能力及所擁有的物品
    bool m_Weak = false;
    bool m_Poison = false;
    int m_Level = 1;                        // 等級
    int m_HP = 1000;                        // 血量
    int m_ATK = 10;                         // 攻擊力
    int m_DEF = 10;                         // 防禦力
    int m_AGI = 1;                          // 敏捷
    int m_EXP = 0;                          // 經驗值
    std::vector <int> m_Keys = { 1, 1, 1 }; // 黃 / 藍 / 紅鑰匙
    int m_Coins = 0;                        // 金幣
    bool m_HeartMirror = false;

    // 角色圖片
    // 前0 後1 左2 右3 (各有4張照片)
    std::vector <std::vector <std::string>> m_Image;

    std::shared_ptr<ScenesManager> m_ScenesManager;

};

#endif
