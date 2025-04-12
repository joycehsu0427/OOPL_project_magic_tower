#ifndef ITEMDIALOG_HPP
#define ITEMDIALOG_HPP

#include "Dialog.hpp"

class ItemDialog : public Dialog {
public:
    ItemDialog() : Dialog(RESOURCE_DIR"/bmp/Item/ItemDialog.bmp") {
        m_Background->SetPivot({-175, 0});
        m_Background->SetVisible(false);

        m_GetText = std::make_shared<TextObject>(25, "取得", 35);
        m_GetText->SetPivot({190, 0});
        m_GetText->SetVisible(false);

        m_DialogText->SetPivot({-130, 0});
        m_DialogText->SetVisible(false);

        m_RemindText = std::make_shared<TextObject>(25, "-Space-", 35);
        m_RemindText->SetPivot({-450, 0});
        m_RemindText->SetVisible(false);

        m_Visible = false;
    }

    void SetVisible(bool visible) override {
        m_Visible = visible;
        m_Background->SetVisible(m_Visible);
        m_GetText->SetVisible(m_Visible);
        m_DialogText->SetVisible(m_Visible);
        m_RemindText->SetVisible(m_Visible);
    }

    [[nodiscard]] std::vector<std::shared_ptr<Util::GameObject>> GetChildren() const override {
        return {m_Background, m_GetText, m_DialogText, m_RemindText};
    }
private:
    std::shared_ptr<TextObject> m_GetText;
    std::shared_ptr<TextObject> m_RemindText;
};


#endif
