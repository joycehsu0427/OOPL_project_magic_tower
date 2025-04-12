#ifndef IMAGEOBJECT_HPP
#define IMAGEOBJECT_HPP

#include "Util/GameObject.hpp"
#include "Util/Image.hpp"

class ImageObject : public Util::GameObject {
public:
    ImageObject(const std::string &imagePath, const float zindex) {
        m_Drawable = std::make_shared<Util::Image>(imagePath);
        m_ZIndex = zindex;
    }

    void SetScale(const float scale) {
        m_Transform.scale = {scale, scale};
    }

    void SetImage(const std::string &imagePath) const {
        auto temp = std::dynamic_pointer_cast<Util::Image>(m_Drawable);
        temp->SetImage(imagePath);
    }
};

#endif
