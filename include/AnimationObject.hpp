#ifndef ANIMATIONOBJECT_HPP
#define ANIMATIONOBJECT_HPP

#include <vector>
#include <string>

#include "Util/Animation.hpp"
#include "Util/GameObject.hpp"

class AnimationObject : public Util::GameObject {
public:
    explicit AnimationObject(const std::vector<std::string>& AnimationPaths) {
        m_Drawable = std::make_shared<Util::Animation>(AnimationPaths, false, 500, true, 0);
    }

    AnimationObject(const std::vector<std::string>& AnimationPaths, bool Play, std::size_t Interval) {
        m_Drawable = std::make_shared<Util::Animation>(AnimationPaths, Play, Interval, true, 0);
    }

    [[nodiscard]] bool IsLooping() const {
        return std::dynamic_pointer_cast<Util::Animation>(m_Drawable)->GetLooping();
    }

    [[nodiscard]] bool IsPlaying() const {
        return std::dynamic_pointer_cast<Util::Animation>(m_Drawable)->GetState() == Util::Animation::State::PLAY;
    }

    void SetLooping(bool looping) const {
        auto temp = std::dynamic_pointer_cast<Util::Animation>(m_Drawable);
        temp->SetLooping(looping);
    }

    void SetPlaying() const {
        auto temp = std::dynamic_pointer_cast<Util::Animation>(m_Drawable);
        temp->Play();
    }

    void SetPause() const {
        auto temp = std::dynamic_pointer_cast<Util::Animation>(m_Drawable);
        temp->Pause();
    }

    void SetImage(const std::vector<std::string> &AnimationPaths, bool Play, std::size_t Interval) {
        m_Drawable = std::make_shared<Util::Animation>(AnimationPaths, Play, Interval, true, 0);
    }

    void SetCurrentFrameIndex(int index) const {
        auto temp = std::dynamic_pointer_cast<Util::Animation>(m_Drawable);
        temp->SetCurrentFrame(index);
    }

    [[nodiscard]] std::size_t GetCurrentFrameIndex() const {
        auto temp = std::dynamic_pointer_cast<Util::Animation>(m_Drawable);
        return temp->GetCurrentFrameIndex();
    }

    [[nodiscard]] bool IfAnimationEnds() const;
};

#endif
