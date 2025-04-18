#ifndef SCENESMANAGER_HPP
#define SCENESMANAGER_HPP

#include <MapManager.hpp>
#include <memory>
#include <vector>

#include "BackgroundImage.hpp"
#include "AnimationObject.hpp"
#include "ImageObject.hpp"
#include "TextObject.hpp"
#include "Player.hpp"


#include "Util/Logger.hpp"
#include "Util/GameObject.hpp"

class ScenesManager {
public:
    ScenesManager(std::shared_ptr<MapManager> &mapManager, std::shared_ptr<Player> &player);

    [[nodiscard]] std::vector<std::shared_ptr<Util::GameObject>> GetChildren() const {
        return {m_BackGround, m_Loading, m_Story, m_Remind, m_Floor, m_PlayerImage,
            m_PlayerStatus, m_PlayerLevel, m_PlayerHP, m_PlayerATK, m_PlayerDEF,
            m_PlayerAGI, m_PlayerEXP,m_PlayerYellowKey, m_PlayerBlueKey, m_PlayerRedKey,
            m_PlayerCoins, m_EndScene, m_EndText};
    }

    // Loading
    [[nodiscard]] std::shared_ptr<AnimationObject> GetLoading() const { return m_Loading; }

    //Story相關函數
    void StartStory () const {
        m_Story->SetVisible(true);
        m_Remind->SetVisible(true);
    }

    void EndStory () const {
        m_Story->SetVisible(false);
        m_Remind->SetVisible(false);
        m_Floor->SetVisible(true);
        m_PlayerImage->SetVisible(true);
        m_PlayerStatus->SetVisible(true);
        m_PlayerLevel->SetVisible(true);
        m_PlayerHP->SetVisible(true);
        m_PlayerATK->SetVisible(true);
        m_PlayerDEF->SetVisible(true);
        m_PlayerAGI->SetVisible(true);
        m_PlayerEXP->SetVisible(true);
        m_PlayerYellowKey->SetVisible(true);
        m_PlayerBlueKey->SetVisible(true);
        m_PlayerRedKey->SetVisible(true);
        m_PlayerCoins->SetVisible(true);
    }

    // ResetText
    void ResetFloor (int courrentfloor) const;
    void ResetPlayerStatus()  const;
    void ResetPlayerLevel() const;
    void ResetPlayerHP() const;
    void ResetPlayerATK() const;
    void ResetPlayerDEF() const;
    void ResetPlayerAGI() const;
    void ResetPlayerEXP() const;
    void ResetPlayerYellowKey() const;
    void ResetPlayerBlueKey() const;
    void ResetPlayerRedKey() const;
    void ResetPlayerCoins() const;

    void NextScene();
    void EndScene(const bool is_win);

private:
    std::shared_ptr<BackgroundImage> m_BackGround;
    std::shared_ptr<AnimationObject> m_Loading;
    std::shared_ptr<TextObject> m_Story;
    std::shared_ptr<TextObject> m_Remind;

    // 樓層顯示
    std::vector<std::string> m_Floortext;
    std::shared_ptr<TextObject> m_Floor;
    std::shared_ptr<ImageObject> m_PlayerImage;
    std::shared_ptr<TextObject> m_PlayerStatus;
    std::shared_ptr<TextObject> m_PlayerLevel;
    std::shared_ptr<TextObject> m_PlayerHP;
    std::shared_ptr<TextObject> m_PlayerATK;
    std::shared_ptr<TextObject> m_PlayerDEF;
    std::shared_ptr<TextObject> m_PlayerAGI;
    std::shared_ptr<TextObject> m_PlayerEXP;
    std::shared_ptr<TextObject> m_PlayerYellowKey;
    std::shared_ptr<TextObject> m_PlayerBlueKey;
    std::shared_ptr<TextObject> m_PlayerRedKey;
    std::shared_ptr<TextObject> m_PlayerCoins;

    std::shared_ptr<ImageObject> m_EndScene;
    std::shared_ptr<TextObject> m_EndText;

    std::shared_ptr<MapManager> m_MapManager;
    std::shared_ptr<Player> m_Player;

    int m_scene = 0;
};

#endif
