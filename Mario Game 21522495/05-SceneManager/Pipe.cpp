#include "Pipe.h"
#include "VenusPlant.h"
#include "PlayScene.h"

CPipe::CPipe(float x, float y, int model) : CGameObject(x, y) {
	this->x = x;
	this->y = y;
	this->model = model;
	CPlayScene* scene = (CPlayScene*)CGame::GetInstance()->GetCurrentScene();

		CVenusPlant* plant = new CVenusPlant(x, y - VENUSPLANT_BBOX_HEIGHT / 12 + 1);
		scene->AddObject(plant);

}

void CPipe::Render()
{
	CAnimations* animations = CAnimations::GetInstance();
	int aniId = -1;
	if (model == PIPE_SHORT_MODEL) aniId = ID_ANI_PIPE_SHORT;
	if (model == PIPE_LONG_MODEL) aniId = ID_ANI_PIPE_LONG;

	animations->Get(aniId)->Render(x, y);
	//RenderBoundingBox();
}

void CPipe::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	if (model == PIPE_SHORT_MODEL) {
		l = x - PIPE_BBOX_WIDTH / 2;
		t = y - PIPE_BBOX_HEIGHT_SHORT / 2;
		r = l + PIPE_BBOX_WIDTH;
		b = t + PIPE_BBOX_HEIGHT_SHORT;
	}
	else {
		l = x - PIPE_BBOX_WIDTH / 2;
		t = y - PIPE_BBOX_HEIGHT_LONG / 2;
		r = l + PIPE_BBOX_WIDTH;
		b = t + PIPE_BBOX_HEIGHT_LONG;
	}
}