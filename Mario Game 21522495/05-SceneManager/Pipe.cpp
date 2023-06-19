#include "Pipe.h"
#include "VenusPlant.h"
#include "PlayScene.h"

CPipe::CPipe(float x, float y, int model, int typePlant) : CGameObject(x, y) {
	this->x = x;
	this->y = y;
	this->model = model;
	this->typePlant = typePlant;
	CPlayScene* scene = (CPlayScene*)CGame::GetInstance()->GetCurrentScene();
	if (typePlant != PLANT_NOTHING) {

		if (typePlant == VENUSPLANT_SHOOT_RED) {
			CVenusPlant* plant = new CVenusPlant(x, y - VENUSPLANT_BBOX_HEIGHT / 4 + 1, VENUSPLANT_SHOOT_RED);
			scene->AddObject(plant);
		}
		else if (typePlant == VENUSPLANT_SHOOT_GREEN) {
			CVenusPlant* plant = new CVenusPlant(x, y - VENUSPLANT_BBOX_HEIGHT_SMALL / 4 + 1, VENUSPLANT_SHOOT_GREEN);
			scene->AddObject(plant);
		}
		else if (typePlant == VENUSPLANT_NOT_SHOOT) {
			CVenusPlant* plant = new CVenusPlant(x, y - VENUSPLANT_BBOX_HEIGHT_SMALL / 4 + (PIPE_BBOX_HEIGHT_LONG - PIPE_BBOX_HEIGHT_SHORT) / 2 + 1, VENUSPLANT_NOT_SHOOT);
			scene->AddObject(plant);
		}

	}

}

void CPipe::Render()
{
	if (!checkObjectInCamera(this)) return;

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