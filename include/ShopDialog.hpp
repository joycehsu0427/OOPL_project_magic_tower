#ifndef SHOPDIALOG_HPP
#define SHOPDIALOG_HPP

#include <Dialog.hpp>

class ShopDialog : public Dialog {
public:
    ShopDialog();

    void OptionUp();
    void OptionDown();
    void Fixed();

    void SetVisible(bool visible) override {
        m_Visible = visible;
        for (auto& child : m_Children) {
            child->SetVisible(m_Visible);
        }
    }

    [[nodiscard]] std::vector<std::shared_ptr<Util::GameObject>> GetChildren() const override {
        return m_Children;
    }

private:
    std::shared_ptr<TextObject> m_Name;
    std::shared_ptr<ImageObject> m_People;
    std::shared_ptr<TextObject> m_Options[4];
    std::shared_ptr<TextObject> m_Tag;

    int m_CurrentOption;
    int m_OptionNumber;
    float Optionposition_y[4] = {0};
    std::vector<std::shared_ptr<Util::GameObject>> m_Children;
};

#endif
