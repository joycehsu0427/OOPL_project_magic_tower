#ifndef ENEMYDATA_HPP
#define ENEMYDATA_HPP

#include "ImageObject.hpp"
#include "TextObject.hpp"
#include "Player.hpp"

class EnemyData {
public:
    EnemyData(int num);

    void SetEnemy(int num) const;
    void SetPlayer(const std::shared_ptr<Player> &player);
    void SetVisible(bool visible) {
        m_Visible = visible;
        for (auto& child : m_Children) {
            child->SetVisible(visible);
        }
    }

    [[nodiscard]] std::vector<std::shared_ptr<Util::GameObject>> GetChildren() const {
        return m_Children;
    }

private:
    bool m_Visible = false;
    std::shared_ptr<ImageObject> m_BackGround;
    std::shared_ptr<ImageObject> m_ImageFrame;
    std::shared_ptr<ImageObject> m_Image;
    std::shared_ptr<TextObject> m_Name_Title;
    std::shared_ptr<TextObject> m_Name;
    std::shared_ptr<TextObject> m_Special_Title;
    std::shared_ptr<TextObject> m_Special;
    std::shared_ptr<TextObject> m_HP_Title;
    std::shared_ptr<TextObject> m_HP;
    std::shared_ptr<TextObject> m_ATK_Title;
    std::shared_ptr<TextObject> m_ATK;
    std::shared_ptr<TextObject> m_DEF_Title;
    std::shared_ptr<TextObject> m_DEF;
    std::shared_ptr<TextObject> m_AGI_Title;
    std::shared_ptr<TextObject> m_AGI;
    std::shared_ptr<TextObject> m_ATKTime_Title;
    std::shared_ptr<TextObject> m_ATKTime;
    std::shared_ptr<TextObject> m_Hurt_Title;
    std::shared_ptr<TextObject> m_Hurt;
    std::shared_ptr<TextObject> m_EXP_Title;
    std::shared_ptr<TextObject> m_EXP;
    std::shared_ptr<TextObject> m_Coin_Title;
    std::shared_ptr<TextObject> m_Coin;

    std::vector<std::shared_ptr<Util::GameObject>> m_Children;

    std::shared_ptr<Player> m_Player = nullptr;
};

#endif
