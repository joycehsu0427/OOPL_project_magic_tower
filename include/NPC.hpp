#ifndef NPC_HPP
#define NPC_HPP

#include <string>
#include <utility>

#include "Thing.hpp"
#include "NPCDialog.hpp"
#include "Read.hpp"


class NPC : public Thing {
public:
    NPC(const std::vector<std::string> &data, const int &floor, const int &x, const int &y, const std::shared_ptr<NPCDialog> &npcDialog) :
    Thing("NPC/" + data[0], std::stoi(data[2]), x, y),
    m_ImagePath(RESOURCE_DIR"/bmp/NPC/" + data[0] + ".bmp"), m_Name(data[1]),
    m_DialogPath( std::to_string(floor) + "_" + data[0] + ".csv"), m_NPCDialog(npcDialog) {
        // 設定要傳送的Dialog資料
        std::vector<std::vector<std::string>> dialogdata = Read::open_csv(RESOURCE_DIR"/Text/" + m_DialogPath);
        int currentdialogSize = -1;
        for (int i = 0; i < int(dialogdata.size()); i++) {
            if (dialogdata[i][0] != "0") {
                if (dialogdata[i][0] == "item") {
                    m_ItemText = dialogdata[i][1];
                }
                else if (dialogdata[i][0] == "hide") {
                    m_Hide = true;
                    break;
                }
                else {
                    m_Dialog.push_back(std::make_pair(dialogdata[i][0], dialogdata[i][1]));
                    currentdialogSize++;
                }
            }
            else
                m_Dialog[currentdialogSize].second += '\n' + dialogdata[i][1];
        }
    }

    void Touched() override {
        if (m_Visible) {
            m_NPCDialog->SetNPCDialog(m_ImagePath, m_Dialog);
            m_NPCDialog->SetVisible(true);
            if (m_Traversable)
                m_Visible = false;
        }
    }

private:
    std::string m_ImagePath;
    std::string m_Name;
    std::string m_DialogPath;
    std::vector <std::pair<std::string, std::string>> m_Dialog;
    std::string m_ItemText = std::string();
    bool m_Hide = false;
    std::shared_ptr<NPCDialog> m_NPCDialog;
};

#endif
