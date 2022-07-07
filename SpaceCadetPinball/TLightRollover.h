#pragma once
#include "TRollover.h"

class TLightRollover :
	public TRollover
{
public:
	TLightRollover(TPinballTable* table, int groupIndex);
	~TLightRollover() override = default;
	int Message(int code, float value) override;
	void Collision(TBall* ball, vector2* nextPosition, vector2* direction, float coef,
		TEdgeSegment* edge) override;

	static void delay_expired(int timerId, void* caller);

	float FloatArr;
	int Timer;
};
