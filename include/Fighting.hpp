#ifndef FIGHTING_HPP
#define FIGHTING_HPP

#include "Player.hpp"
#include "ImageObject.hpp"
#include "TextObject.hpp"

class Enemy;

class Fighting {
public:
    Fighting();

    void StartFighting(Enemy* enemy);
    void PlayerATK();
    void EnemyATK();
    void QuitFighting();
    void EndFighting();
    void ClearEffect();

    void SetVisible(const bool &visible);
    void SetPlayer(const std::shared_ptr<Player> &player);

    [[nodiscard]] bool IsVisible() const { return m_Visible; }
    [[nodiscard]] bool IsFighting() const { return m_IsFighting; }
    [[nodiscard]] bool IsEnemyATKEnd() const;
    [[nodiscard]] bool IsEnd() const { return m_EndFighting; }
    [[nodiscard]] std::vector<std::shared_ptr<Util::GameObject>> GetChildren() const {
        std::vector<std::shared_ptr<Util::GameObject>> children;
        children.insert(children.end(), m_Effect_Children.begin(), m_Effect_Children.end());
        children.insert(children.end(), m_Fighting_Children.begin(), m_Fighting_Children.end());
        children.insert(children.end(), m_Reward_Children.begin(), m_Reward_Children.end());
        return children;
    }

private:
    // 基礎配備
    std::shared_ptr<ImageObject> m_Background;
    std::shared_ptr<TextObject> m_RemindText;
    std::shared_ptr<TextObject> m_VS;
    bool m_Visible;
    bool m_IsFighting = false;
    bool m_EndFighting = false;
    // Player, Enemy 顯示資料
    std::shared_ptr<Player> m_Player;
    Enemy* m_Enemy = nullptr;
    std::shared_ptr<ImageObject> m_Effect[2];
    std::shared_ptr<TextObject> m_Minus_HP[2];
    std::shared_ptr<TextObject> m_SpecialATK;
    std::shared_ptr<ImageObject> m_Image[2];
    std::shared_ptr<TextObject> m_Name[2];
    std::shared_ptr<TextObject> m_HP_Text[2];
    std::shared_ptr<TextObject> m_HP_Title[2];
    std::shared_ptr<TextObject> m_ATK_Text[2];
    std::shared_ptr<TextObject> m_ATK_Title[2];
    std::shared_ptr<TextObject> m_DEF_Text[2];
    std::shared_ptr<TextObject> m_DEF_Title[2];
    std::shared_ptr<TextObject> m_AGI_Text[2];
    std::shared_ptr<TextObject> m_AGI_Title[2];
    int m_HP[2] = {0, 0};
    int m_ATK[2] = {0, 0};
    int m_DEF[2] = {0, 0};
    int m_AGI[2] = {0, 0};
    bool m_EnemyIgnoreDEF = false;
    int m_EnemyATKTime = 0;
    std::vector<std::shared_ptr<Util::GameObject>> m_Fighting_Children;
    std::vector<std::shared_ptr<Util::GameObject>> m_Effect_Children;

    // Reward相關顯示
    std::shared_ptr<ImageObject> m_Reward_Image;
    std::shared_ptr<TextObject> m_Win_Text;
    std::shared_ptr<TextObject> m_Reward_Text;
    std::shared_ptr<TextObject> m_EXP_Title;
    std::shared_ptr<TextObject> m_EXP_Text;
    std::shared_ptr<TextObject> m_Coin_Title;
    std::shared_ptr<TextObject> m_Coin_Text;
    std::vector<std::shared_ptr<Util::GameObject>> m_Reward_Children;

    void PlayerHPMinus(int atk);
    void EnemyHPMinus(int atk);
    void EnemyDie();
    void Reward();
    void SetStartFighting();
};

#endif
