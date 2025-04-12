#include "TextObject.hpp"
#include "Util/Logger.hpp"

TextObject::TextObject(const int &size, const std::string &text ) {
    m_Drawable = std::make_unique<Util::Text>(RESOURCE_DIR"/Font/Cubic_11.ttf", size, text,
                                     Util::Color::FromName(Util::Colors::WHITE));
    m_ZIndex = 5;

}

TextObject::TextObject(const int &size, const std::string &text, const float &zindex) {
    m_Drawable = std::make_unique<Util::Text>(RESOURCE_DIR"/Font/Cubic_11.ttf", size, text,
                                     Util::Color::FromName(Util::Colors::WHITE));
    m_ZIndex = zindex;
}

TextObject::TextObject(const int &size, const std::string &text, const Util::Color &color, const float &zindex) {
    m_Drawable = std::make_unique<Util::Text>(RESOURCE_DIR"/Font/Cubic_11.ttf", size, text, color);
    m_ZIndex = zindex;
}


void TextObject::SetText(const std::string &text) const {
    auto temp = std::dynamic_pointer_cast<Util::Text>(m_Drawable);
    temp->SetText(text);
}
