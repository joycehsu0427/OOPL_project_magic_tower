#ifndef NPC_HPP
#define NPC_HPP

#include <string>
#include <utility>

#include "Thing.hpp"
#include "NPCDialog.hpp"
#include "Read.hpp"


class NPC : public Thing {
public:
    NPC(const std::vector<std::string> &data, const int &floor, const int &x, const int &y, const int &index,
        const std::shared_ptr<NPCDialog> &npcDialog) :
    Thing({RESOURCE_DIR"/bmp/NPC/" + data[IMAGE] + ".bmp"}, false, 400,
        std::stoi(data[TRAVERSABLE]), x, y, index),
    m_ImagePath(RESOURCE_DIR"/bmp/NPC/" + data[IMAGE] + ".bmp"),
    m_DialogPath(RESOURCE_DIR"/Text/" + std::to_string(floor) + "_" + data[IMAGE] + ".csv"),
    m_Name(data[NAME]), m_NPCDialog(npcDialog){
        constructor();
    }

    NPC(const std::vector<std::string> &data, const bool &play, const int &floor, const int &x, const int &y, const int &index,
        const std::shared_ptr<NPCDialog> &npcDialog) :
    Thing({RESOURCE_DIR"/bmp/NPC/" + data[IMAGE] + ".bmp",
        RESOURCE_DIR"/bmp/NPC/" + data[IMAGE] + "2.bmp"}, play, 400,     std::stoi(data[TRAVERSABLE]), x, y, index),
    m_ImagePath(RESOURCE_DIR"/bmp/NPC/" + data[IMAGE] + ".bmp"),
    m_DialogPath(RESOURCE_DIR"/Text/" + std::to_string(floor) + "_" + data[IMAGE] + ".csv"),
    m_Name(data[NAME]), m_NPCDialog(npcDialog){
        constructor();
    }

    void Touched() override {
        m_NPCDialog->SetNPCDialog(m_ImagePath, m_Dialog, m_HaveItem, m_Item, m_Hide, m_Win, this);
        if (m_Traversable)
            m_Visible = false;
    }

private:
    enum DATA {
        IMAGE = 0,
        NAME,
        TRAVERSABLE
    };
    std::string m_ImagePath;
    std::string m_DialogPath;
    std::string m_Name;
    std::vector <std::pair<std::string, std::string>> m_Dialog;
    bool m_HaveItem = false;
    std::pair<std::string, std::string> m_Item = std::make_pair("", "");
    bool m_Hide = false;
    bool m_ChangeRoadMap = false;
    std::string m_RoadMapPath = std::string();
    bool m_ChangeThingMap = false;
    std::string m_ThingMapPath = std::string();
    bool m_Win = false;
    std::shared_ptr<NPCDialog> m_NPCDialog;

    void constructor() {
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
                else if (dialogdata[i][0] == "change_road_map") {
                    m_ChangeRoadMap = true;
                    m_RoadMapPath = dialogdata[i][1];
                }
                else if (dialogdata[i][0] == "change_thing_map") {
                    m_ChangeThingMap = true;
                    m_ThingMapPath = dialogdata[i][1];
                }
                else if (dialogdata[i][0] == "win") {
                    m_Win = true;
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
};

#endif
