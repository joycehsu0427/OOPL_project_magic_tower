#ifndef FLY_HPP
#define FLY_HPP

#include "ImageObject.hpp"
#include "TextObject.hpp"

class MapManager;

class Fly {
public:
    Fly();

	void StartFly();
	void Up();
	void Down();
	void Confirm();

	void SetVisible(bool visible);
	void SetFloor(int floor);
	void SetMapManager(const std::shared_ptr<MapManager> &manager);

	[[nodiscard]] int GetCurrentFloor() const;
	[[nodiscard]] std::vector<std::shared_ptr<Util::GameObject>> GetChildren() const {
        return m_Children;
    }

private:
	bool m_Visible = false;
    std::shared_ptr<ImageObject> m_BackGround;
	std::shared_ptr<TextObject> m_FloorText;
	std::shared_ptr<ImageObject> m_UpArrow;
	std::shared_ptr<ImageObject> m_DownArrow;
	std::shared_ptr<TextObject> m_ConfirmText;
	std::shared_ptr<TextObject> m_QuitText;

	int m_CurrentFloor = 0;
	int m_MaxFloor = 0;
	int m_MinFloor = 0;

	std::shared_ptr<MapManager> m_MapManager;

	std::vector<std::shared_ptr<Util::GameObject>> m_Children;
};

#endif
