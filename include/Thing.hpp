#ifndef THING_HPP
#define THING_HPP

#include "Util/GameObject.hpp"
#include "Util/Image.hpp"

class Thing : public Util::GameObject {
public:
    Thing(const std::string &path, bool traversable, const int &x, const int &y, const int &index) : m_Path(path), m_Traversable(traversable), m_Index(index) {
        m_Drawable = std::make_shared<Util::Image>( RESOURCE_DIR"/bmp/" + m_Path + ".bmp" );
        m_ZIndex = 10;
        m_Transform.scale = {0.732f, 0.732f};
        m_Pivot = {x, y};
        m_Visible = false;
    }

    [[nodiscard]] bool IsTraversable() const { return m_Traversable; }

    [[nodiscard]] bool IsVisible() const { return m_Visible; }

    [[nodiscard]] int GetIndex() const { return m_Index; }

    virtual void Touched() = 0;

protected:
    std::string m_Path;
    bool m_Traversable;
    int m_Index;


};

#endif //THING_HPP
