#pragma once
#include "GameObject.h"
#include "Animation.h"
#include "Animations.h"

#define ID_ANI_TRANSPARENTBLOCK 12000
#define TRANSPARENTBLOCK_WIDTH 16
#define TRANSPARENTBLOCK_BBOX_WIDTH 16
#define TRANSPARENTBLOCK_BBOX_HEIGHT 16

class CTransparentBlock : public CGameObject {
public:
	CTransparentBlock(float x, float y) : CGameObject(x, y) {}
	void Render();
	void Update(DWORD dt) {}
	void GetBoundingBox(float& l, float& t, float& r, float& b);
};