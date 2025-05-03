#ifndef ENEMYDATAMANAGER_HPP
#define ENEMYDATAMANAGER_HPP

#include "Enemy.hpp"
#include "EnemyData.hpp"
#include "ImageObject.hpp"
#include "Player.hpp"
#include "Thing.hpp"

class EnemyDataManager {
public:
    EnemyDataManager();

    void NextPage();
    void PrePage();

    void SetPlayer(const std::shared_ptr<Player> &player) const;
    void SetEnemyDataManager(const std::vector<std::vector<std::shared_ptr<Thing>>> &currentMap);
    void SetVisible(bool visible) {
        m_Visible = visible;
        for (auto &child: m_Children) {
            child->SetVisible(m_Visible);
        }
        for (int i = 0; i < 3; i++) {
            m_EnemyData[i]->SetVisible(m_Visible);
        }
    }

    [[nodiscard]] std::vector<std::shared_ptr<Util::GameObject>> GetChildren() const {
        std::vector<std::shared_ptr<Util::GameObject>> children = m_Children;
        for (int i = 0; i < 3; i++) {
            std::vector<std::shared_ptr<Util::GameObject>> enemyData = m_EnemyData[i]->GetChildren();
            children.insert(children.end(), enemyData.begin(), enemyData.end());
        }
        return children;
    }

private:
    bool m_Visible = false;
    std::shared_ptr<ImageObject> m_BackGround;
    std::shared_ptr<EnemyData> m_EnemyData[3];
    std::shared_ptr<ImageObject> m_LeftArrow;
    std::shared_ptr<ImageObject> m_RightArrow;
    std::shared_ptr<TextObject> m_RemindText;
    std::vector<std::shared_ptr<Enemy>> m_Enemy_List = std::vector<std::shared_ptr<Enemy>>();
    unsigned long long int m_Page = 0;
    unsigned long long int m_CurrentPage = 0;

    std::vector<std::shared_ptr<Util::GameObject>> m_Children;

    void SetEnemies() const;
};
#endif
