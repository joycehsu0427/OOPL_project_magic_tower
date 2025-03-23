#ifndef THING_HPP
#define THING_HPP

#include "Util/GameObject.hpp"
#include "Util/Image.hpp"

class Thing : public Util::GameObject {
public:
    Thing(std::string path, bool traversable, int x, int y) : m_Path(path), m_Traversable(traversable) {
        m_Drawable = std::make_shared<Util::Image>( RESOURCE_DIR"/bmp/" + m_Path + ".bmp" );
        m_ZIndex = 10;
        m_Transform.scale = {0.732f, 0.732f};
        m_Pivot = {x, y};
    }

    bool IsTraversable() { return m_Traversable; }

    bool IsVisible() { return m_Visible; }

    virtual void Touched() = 0;

protected:
    std::string m_Path;

    bool m_Traversable;


};

#endif //THING_HPP
