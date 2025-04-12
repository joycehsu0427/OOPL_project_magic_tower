#include "NPCDialog.hpp"
#include "NPC.hpp"

void NPCDialog::SetNPCDialog(const std::string &imagePath, const std::vector <std::pair <std::string, std::string>> &dialog) {
    m_ImagePath = imagePath;
    m_DialogData = dialog;
    m_DialogTime = dialog.size();
    m_CurrentDialogTime = 0;
    ChangeNPCDialog();
}

void NPCDialog::NextDialog() {
    m_CurrentDialogTime++;
    if (m_CurrentDialogTime == m_DialogTime) {
        SetVisible(false);
        return;
    }
    ChangeNPCDialog();
}

void NPCDialog::SetPeopleAndPosition(const std::string &name) {
    if (name == "勇者") {
        m_People->SetImage(RESOURCE_DIR"/bmp/NPC/player.bmp");
        if (!is_Player) {
            m_Background->SetPivot({-192.5f, y_position});
            m_People->SetPivot({38.5f, y_position - 77});
            m_Name->SetPivot({-192.5f, 60});
            m_DialogText->SetPivot({-192.5f, 150});
            m_RemindText->SetPivot({-315, 230});
        }
        is_Player = true;
    }
    else {
        m_People->SetImage(m_ImagePath);
        if (is_Player) {
            m_Background->SetPivot({-192.5f, -y_position});
            m_People->SetPivot({38.5f, -y_position - 77});
            m_Name->SetPivot({-192.5f, -220});
            m_DialogText->SetPivot({-192.5f, -135});
            m_RemindText->SetPivot({-315, -50});
        }
        is_Player = false;
    }
}

void NPCDialog::ChangeNPCDialog() {
    SetPeopleAndPosition(m_DialogData[m_CurrentDialogTime].first);
    m_Name->SetText(m_DialogData[m_CurrentDialogTime].first);
    m_DialogText->SetText(m_DialogData[m_CurrentDialogTime].second);
}