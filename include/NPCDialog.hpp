#ifndef NPCDIALOG_HPP
#define NPCDIALOG_HPP

#include "Dialog.hpp"
#include "ItemDialog.hpp"

class NPC;

class NPCDialog : public Dialog {
public:
    NPCDialog(const std::shared_ptr<ItemDialog> &item_dialog) :
	Dialog(RESOURCE_DIR"/bmp/NPC/NPCDialog.bmp"), m_ItemDialog(item_dialog) {
        m_Background->SetPivot({-192.5f, -192.5f});
        m_Background->SetVisible(false);

    	m_ImagePath = RESOURCE_DIR"/bmp/NPC/elder.bmp";

    	m_People = std::make_shared<ImageObject>(m_ImagePath, 35);
		m_People->SetPivot({38.5f, -269.5f});
    	m_People->SetVisible(false);
    	m_People->SetScale(0.73f);

    	m_Name = std::make_shared<TextObject>(30, "老人", 35);
    	m_Name->SetPivot({-192.5f, -220});
    	m_Name->SetVisible(false);

    	m_DialogText->SetPivot({-192.5f, -135});
    	m_DialogText->SetVisible(false);

    	m_RemindText = std::make_shared<TextObject>(25, "-Space-", 35);
    	m_RemindText->SetPivot({-315, -50});
    	m_RemindText->SetVisible(false);

    	m_DialogTime = 0;
    	m_CurrentDialogTime = 0;
    	is_Player = false;
    }

	void SetVisible(bool visible) override {
	    m_Visible = visible;
    	m_Background->SetVisible(m_Visible);
    	m_People->SetVisible(m_Visible);
    	m_Name->SetVisible(m_Visible);
    	m_DialogText->SetVisible(m_Visible);
    	m_RemindText->SetVisible(m_Visible);
    }

	void SetNPCDialog(const std::string &imagePath, const std::vector <std::pair <std::string, std::string>> &dialog) ;

	void NextDialog();

    [[nodiscard]] std::vector<std::shared_ptr<Util::GameObject>> GetChildren() const override {
      return { m_Background, m_People, m_Name, m_DialogText, m_RemindText };
    }

private:
	std::string m_ImagePath;
    std::shared_ptr<ImageObject> m_People;
	std::shared_ptr<TextObject> m_Name;
    std::shared_ptr<TextObject> m_RemindText;
	std::vector<std::pair<std::string, std::string>> m_DialogData;
	unsigned long long m_DialogTime;
	unsigned long long m_CurrentDialogTime;

	std::shared_ptr<ItemDialog> m_ItemDialog;

	bool is_Player;
	float y_position = 192.5f;

	void SetPeopleAndPosition(const std::string &name);

	void ChangeNPCDialog();

};

#endif
