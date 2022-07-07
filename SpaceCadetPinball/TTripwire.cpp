#include "pch.h"
#include "TTripwire.h"

#include "control.h"
#include "loader.h"
#include "TBall.h"
#include "TPinballTable.h"

TTripwire::TTripwire(TPinballTable* table, int groupIndex) : TRollover(table, groupIndex, true)
{
}

void TTripwire::Collision(TBall* ball, vector2* nextPosition, vector2* direction, float coef,
                          TEdgeSegment* edge)
{
	ball->Position.X = nextPosition->X;
	ball->Position.Y = nextPosition->Y;
	ball->RayMaxDistance -= coef;
	ball->not_again(edge);
	if (!PinballTable->TiltLockFlag)
	{
		loader::play_sound(SoftHitSoundId);
		control::handler(63, this);
	}
}
