#include "Worker.h"


Worker::Worker()
{
	mPosition = { 0, 0 };
	mDestination = { 0, 0 };
	mSpeed = 300.0f;
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

void Worker::update(float ticks)
{

	if (mDestination.x > mPosition.x)
		mPosition.x += (mSpeed * ticks);
	if (mDestination.x < mPosition.x)
		mPosition.x -= (mSpeed * ticks);
	if (mDestination.y < mPosition.y)
		mPosition.y -= (mSpeed * ticks);
	if (mDestination.y > mPosition.y)
		mPosition.y += (mSpeed * ticks);

	if (mDestination.x - mPosition.x >= -2.0f && mDestination.x - mPosition.x <= 2.0f)
		mPosition.x = mDestination.x;
	if (mDestination.y - mPosition.y >= -2.0f && mDestination.y - mPosition.y <= 2.0f)
		mPosition.y = mDestination.y;


}

