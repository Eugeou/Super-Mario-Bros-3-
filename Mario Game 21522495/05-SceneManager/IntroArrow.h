#pragma once
#define ID_ANI_ARROW_INTRO 400010
#define ID_ANI_ARROW_INTRO_CHANGE_SCENE 400020

#define ARROW_NOT_RENDER 0
#define ARROW_UP 1
#define ARROW_DOWN 2

//nút mũi tên để chọn chế độ trong intro scene
class CIntroArrow
{
private:
	float x, y;

public:
	CIntroArrow() {
		x = 0;
		y = 0;
	}
	void Render(float x, float y);
	void RenderChangeScene(float x, float y);
	float GetY() { return y; }
	void SetY(float y) {
		this->y = y;
	}
};

