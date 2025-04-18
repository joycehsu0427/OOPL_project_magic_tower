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
    m_ImagePath(RESOURCE_DIR"/bmp/NPC/" + data[0] + ".bmp"), m_DialogPath(RESOURCE_DIR"/Text/" + std::to_string(floor) + "_" + data[0] + ".csv"),
    m_Name(data[1]), m_NPCDialog(npcDialog) {
        // 設定要傳送的Dialog資料
        std::vector<std::vector<std::string>> dialogdata = Read::open_csv(m_DialogPath);
        int currentdialogSize = -1;
        for (int i = 0; i < int(dialogdata.size()); i++) {
            if (dialogdata[i][0] != "0") {
                if (dialogdata[i][0] == "item") {
                    m_HaveItem = true;
                    m_Item.first = dialogdata[i][1];
                    m_Item.second = dialogdata[i][2];
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
        m_NPCDialog->SetNPCDialog(m_ImagePath, m_Dialog, m_HaveItem, m_Item, m_Hide, this);
        if (m_Traversable)
            m_Visible = false;
    }

private:
    std::string m_ImagePath;
    std::string m_DialogPath;
    std::string m_Name;
    std::vector <std::pair<std::string, std::string>> m_Dialog;
    bool m_HaveItem = false;
    std::pair<std::string, std::string> m_Item = std::make_pair("", "");
    bool m_Hide = false;
    std::shared_ptr<NPCDialog> m_NPCDialog;
};

#endif
