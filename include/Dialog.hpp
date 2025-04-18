#ifndef DIALOG_HPP
#define DIALOG_HPP

#include "ImageObject.hpp"
#include "TextObject.hpp"

class Dialog {
public:
    Dialog(const std::string &imgpath) {
        m_Background = std::make_shared<ImageObject>(imgpath, 30);
        m_Background->SetScale(0.73f);
        m_DialogText = std::make_shared<TextObject>(25, "dialog", 35);
    }
    Dialog(const std::string &imgpath, const int textsize) {
        m_Background = std::make_shared<ImageObject>(imgpath, 30);
        m_Background->SetScale(0.73f);
        m_DialogText = std::make_shared<TextObject>(textsize, "dialog", 35);
    }
    virtual ~Dialog() = default;

    [[nodiscard]] bool IsVisible() const { return m_Visible; }

    virtual void SetVisible(bool visible) {
        m_Visible = visible;
        m_Background->SetVisible(visible);
        m_DialogText->SetVisible(visible);
    }

    void SetDialog(const std::string &dialog) const {
        m_DialogText->SetText(dialog);
    }

    [[nodiscard]] virtual std::vector<std::shared_ptr<Util::GameObject>> GetChildren() const {
        return {m_Background, m_DialogText};
    }

protected:
    std::shared_ptr<ImageObject> m_Background;
    std::shared_ptr<TextObject> m_DialogText;
    bool m_Visible = false;
};

#endif
