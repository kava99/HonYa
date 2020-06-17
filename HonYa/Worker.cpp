#include "Worker.h"


Worker::Worker()
{
	mPosition = { 0, 0 };
	mTaskType = TaskType::IDLE;
	bball = al_load_bitmap("ball.png");
}

Worker::~Worker()
{
}

void Worker::draw()
{
	al_draw_bitmap(bball, mPosition.x, mPosition.y, 0);
}

