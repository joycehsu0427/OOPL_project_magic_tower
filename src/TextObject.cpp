#include "TextObject.hpp"

TextObject::TextObject(int size, std::string text) {
    m_Drawable =std::make_unique<Util::Text>(RESOURCE_DIR"/Font/Cubic_11.ttf", size, text,
                                     Util::Color::FromName(Util::Colors::WHITE));
    m_ZIndex = 5;
}