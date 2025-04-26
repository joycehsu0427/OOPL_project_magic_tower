#include "Fly.hpp"
#include "MapManager.hpp"

Fly::Fly() {
    float scale = 0.732f;
    m_BackGround = std::make_shared<ImageObject>(RESOURCE_DIR"/bmp/Special/Fly.bmp", 30);
    m_BackGround->SetPivot({-194, 0});
    m_BackGround->SetVisible(false);
    m_BackGround->SetScale(scale);
    m_Children.push_back(m_BackGround);

    m_FloorText = std::make_shared<TextObject>(100, "0", 35);
    m_FloorText->SetPivot({-100, 0});
    m_FloorText->SetVisible(false);
    m_Children.push_back(m_FloorText);

    int arrow_y = 250;
    m_UpArrow = std::make_shared<ImageObject>(RESOURCE_DIR"/bmp/Special/up_arrow_white.png", 35);
    m_UpArrow->SetPivot({-194, -arrow_y});
    m_UpArrow->SetVisible(false);
    m_UpArrow->SetScale(scale);
    m_Children.push_back(m_UpArrow);

    m_DownArrow = std::make_shared<ImageObject>(RESOURCE_DIR"/bmp/Special/down_arrow_white.png", 35);
    m_DownArrow->SetPivot({-194, arrow_y});
    m_DownArrow->SetVisible(false);
    m_DownArrow->SetScale(scale);
    m_Children.push_back(m_DownArrow);

    m_ConfirmText = std::make_shared<TextObject>(25, "-Space-", 35);
    m_ConfirmText->SetPivot({-300, 170});
    m_ConfirmText->SetVisible(false);
    m_Children.push_back(m_ConfirmText);

    m_QuitText = std::make_shared<TextObject>(25, "-Quit-(F)", 35);
    m_QuitText->SetPivot({-360, 275});
    m_QuitText->SetVisible(false);
    m_Children.push_back(m_QuitText);
}

void Fly::StartFly() {
    if (m_CurrentFloor == m_MinFloor)
        m_DownArrow->SetImage(RESOURCE_DIR"/bmp/Special/down_arrow_gray.png");
    else
        m_DownArrow->SetImage(RESOURCE_DIR"/bmp/Special/down_arrow_white.png");
    if (m_CurrentFloor == m_MaxFloor)
        m_UpArrow->SetImage(RESOURCE_DIR"/bmp/Special/up_arrow_gray.png");
    else
        m_UpArrow->SetImage(RESOURCE_DIR"/bmp/Special/up_arrow_white.png");
    m_FloorText->SetText(std::to_string(m_CurrentFloor));
    SetVisible(true);
}

void Fly::Up() {
    if (m_CurrentFloor < m_MaxFloor) {
        if (m_CurrentFloor == m_MinFloor) {
            m_DownArrow->SetImage(RESOURCE_DIR"/bmp/Special/down_arrow_white.png");
        }
        m_CurrentFloor++;
        if (m_CurrentFloor == m_MaxFloor) {
            m_UpArrow->SetImage(RESOURCE_DIR"/bmp/Special/up_arrow_gray.png");
        }
        m_FloorText->SetText(std::to_string(m_CurrentFloor));
    }
}

void Fly::Down() {
    if (m_CurrentFloor > m_MinFloor) {
        if (m_CurrentFloor == m_MaxFloor) {
            m_UpArrow->SetImage(RESOURCE_DIR"/bmp/Special/up_arrow_white.png");
        }
        m_CurrentFloor--;
        if (m_CurrentFloor == m_MinFloor)
            m_DownArrow->SetImage(RESOURCE_DIR"/bmp/Special/down_arrow_gray.png");
        m_FloorText->SetText(std::to_string(m_CurrentFloor));
    }
}

void Fly::Confirm() {
    m_MapManager->SpecificFloor(m_CurrentFloor);
    SetVisible(false);
}

void Fly::SetVisible(bool visible) {
    m_Visible = visible;
    for (auto& child : m_Children) {
        child->SetVisible(m_Visible);
    }
}

void Fly::SetFloor(int floor) {
    m_CurrentFloor = floor;
    m_FloorText->SetText(std::to_string(m_CurrentFloor));

    if (m_CurrentFloor > m_MaxFloor) {
        m_MaxFloor = m_CurrentFloor;
    }
}

void Fly::SetMapManager(const std::shared_ptr<MapManager> &manager) {
    m_MapManager = manager;
}

[[nodiscard]] int Fly::GetCurrentFloor() const {
    return m_CurrentFloor;
}
