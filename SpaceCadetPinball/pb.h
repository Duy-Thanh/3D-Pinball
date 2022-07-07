#pragma once
#include "high_score.h"

struct GameInput;
class TPinballTable;
class DatFile;
class TBall;

enum class GameModes
{
	InGame = 1,
	GameOver = 2,
};

class UsingSdlHint
{
public:
	explicit UsingSdlHint(const char* name, const char* value)
		: HintName(name)
	{
		auto originalValue = SDL_GetHint(name);
		if (originalValue)
			strncpy(OriginalValue, originalValue, sizeof OriginalValue - 1);

		SDL_SetHint(name, value);
	}

	~UsingSdlHint()
	{
		if (OriginalValue[0])
			SDL_SetHint(HintName, OriginalValue);
	}

private:
	char OriginalValue[40]{};
	const char* HintName;
};

class pb
{
public:
	static int time_ticks;
	static float ball_speed_limit, time_now, time_next, time_ticks_remainder;
	static GameModes game_mode;
	static bool cheat_mode;
	static DatFile* record_table;
	static TPinballTable* MainTable;
	static high_score_struct highscore_table[5];
	static bool FullTiltMode;

	static int init();
	static int uninit();
	static void reset_table();
	static void firsttime_setup();
	static void mode_change(GameModes mode);
	static void toggle_demo();
	static void replay_level(bool demoMode);
	static void ballset(float dx, float dy);
	static void frame(float dtMilliSec);
	static void timed_frame(float timeNow, float timeDelta, bool drawBalls);
	static void window_size(int* width, int* height);
	static void pause_continue();
	static void loose_focus();
	static void InputUp(GameInput input);
	static void InputDown(GameInput input);
	static void launch_ball();
	static void end_game();
	static void high_scores();
	static void tilt_no_more();
	static bool chk_highscore();
	static float collide(float timeNow, float timeDelta, TBall* ball);
	static void PushCheat(const std::string& cheat);
private:
	static bool demo_mode;

	static bool AnyBindingMatchesInput(GameInput (&options)[3], GameInput key);
};
