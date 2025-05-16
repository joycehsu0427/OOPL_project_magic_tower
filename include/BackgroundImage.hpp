#ifndef BACKGROUND_IMAGE_HPP
#define BACKGROUND_IMAGE_HPP

#include "Util/GameObject.hpp"
#include "Util/Image.hpp"

class BackgroundImage : public Util::GameObject {

public:
    BackgroundImage() : GameObject(
            std::make_unique<Util::Image>(RESOURCE_DIR"/bmp/Scene/scene0.BMP"), -10) {
    }

    void SetScene(const int scene) {
        auto temp = std::dynamic_pointer_cast<Util::Image>(m_Drawable);
        temp->SetImage(ImagePath(scene));
    }

private:
    inline std::string ImagePath(const int scene) const {
        return RESOURCE_DIR"/bmp/Scene/scene" + std::to_string(scene) + ".BMP";
    }
};

#endif
