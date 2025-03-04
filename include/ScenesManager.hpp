#ifndef SCENESMANAGER_HPP
#define SCENESMANAGER_HPP
#include <memory>

#include "BackgroundImage.hpp"
#include "Util/GameObject.hpp"

class ScenesManager {
public:
    ScenesManager();

    [[nodiscard]] std::shared_ptr<Util::GameObject> GetBackGround() const {
        return m_BackGround;
    }

    void NextScene();
private:
    std::shared_ptr<BackgroundImage> m_BackGround;

    int m_scene = 0;
};

#endif
