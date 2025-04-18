#ifndef FLY_HPP
#define FLY_HPP

#include "ImageObject.hpp"
#include "TextObject.hpp"
#include <memory>

class Fly {
public:
    Fly();

private:
    std::shared_ptr<ImageObject> m_BackGround;
	std::shared_ptr<TextObject> m_Text;
	std::shared_ptr<ImageObject> m_UpArrow;
	std::shared_ptr<ImageObject> m_DownArrow;

};
#endif
