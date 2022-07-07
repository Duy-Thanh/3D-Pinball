#pragma once
#include "maths.h"
#include "TCollisionComponent.h"

class TSink :
	public TCollisionComponent
{
public:
	TSink(TPinballTable* table, int groupIndex);
	int Message(int code, float value) override;
	void put_scoring(int index, int score) override;
	int get_scoring(int index) override;
	void Collision(TBall* ball, vector2* nextPosition, vector2* direction, float coef,
	               TEdgeSegment* edge) override;

	static void TimerExpired(int timerId, void* caller);

	int Timer;
	float TimerTime;
	vector2 BallPosition{};
	vector3 BallAcceleration{};
	float ThrowAngleMult;
	float ThrowSpeedMult1;
	float ThrowSpeedMult2;
	int SoundIndex4;
	int SoundIndex3;
	int Scores[3]{};
	int PlayerMessagefieldBackup[4]{};
};
