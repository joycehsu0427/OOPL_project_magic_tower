#ifndef TEXTOBJECT_HPP
#define TEXTOBJECT_HPP

#include "Util/GameObject.hpp"
#include "Util/Text.hpp"

class TextObject : public Util::GameObject{
public:
    TextObject(const int &size, const std::string &text );
    TextObject(const int &size, const std::string &text, const float &zindex);
    TextObject(const int &size, const std::string &text, const Util::Color &color, const float &zindex);
    void SetText(const std::string &text) const;
private:

};

#endif
