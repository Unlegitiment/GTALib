#pragma once
#include <ModCore/math/Color.h>
#include <ModCore/math/Vector2.h>
#include <ModCore/thirdparty/ScriptHook/include/natives.h>
class CFader {
public:
	enum eFaderState {
		EFS_PERFORM_FADE_OUT,
		EFS_FULLY_FADED_OUT,
		EFS_PERFORM_FADE_IN,
		EFS_FULLY_FADED_IN,
	} static inline State = EFS_FULLY_FADED_IN;
	static void Init() {

	}
	static void FadeScreenOut(int Duration) {
		sm_iBeginning = MISC::GET_GAME_TIMER();
		sm_iTarget = MISC::GET_GAME_TIMER() + Duration;
		gtaInfof("[Fade]: FadeScreenOut: sm_iBeginning - %d, sm_iTarget - %d\n", sm_iBeginning, sm_iTarget);
		State = EFS_PERFORM_FADE_OUT;
	}
	static void FadeScreenIn(int Duration) {
		sm_iBeginning = MISC::GET_GAME_TIMER();
		sm_iTarget = MISC::GET_GAME_TIMER() + Duration;
		State = EFS_PERFORM_FADE_IN;
	}
	static void SetFadeColor(legit::Colorf Color) {
		sm_colFadeColor = Color;
	}
	static void Update() {
		legit::Color<int> Color = sm_colFadeColor;
		switch (State) {
			case EFS_PERFORM_FADE_OUT:
				{
					float t = float(MISC::GET_GAME_TIMER() - sm_iBeginning) /
						float(sm_iTarget - sm_iBeginning);

					if (t > 1.0f) {
						t = 1.0f;
						State = EFS_FULLY_FADED_OUT;
					}

					Color.a = int(t * sm_colFadeColor.a);
					DrawRect({0.5,0.5}, {1,1}, Color);
					break;
				}

			case EFS_FULLY_FADED_OUT:
				{
					Color.a = sm_colFadeColor.a;
					DrawRect({0.5,0.5}, {1,1}, Color);
					break;
				}

			case EFS_PERFORM_FADE_IN:
				{
					float t = float(MISC::GET_GAME_TIMER() - sm_iBeginning) /
						float(sm_iTarget - sm_iBeginning);

					if (t > 1.0f) {
						t = 1.0f;
						State = EFS_FULLY_FADED_IN;
					}

					Color.a = int((1.0f - t) * sm_colFadeColor.a);
					DrawRect({0.5,0.5}, {1,1}, Color);
					break;
				}

			case EFS_FULLY_FADED_IN:
				{
					// do nothing (screen is clear)
					break;
				}
		}
	}
	static bool DrawRect(legit::Vec2f Position, legit::Vec2f Scale, legit::Color<int> Color) {
		GRAPHICS::DRAW_RECT(Position.x, Position.y, Scale.x, Scale.y, Color.r, Color.g, Color.b, Color.a, 1);
	}
	static void Shutdown() {

	}
private:
	static inline legit::Colorf sm_colFadeColor = {0,0,0,255.f};
	static inline int sm_iBeginning = 0;
	static inline int sm_iTarget = 0;
	static inline bool sm_bShouldFadeOut = false;
	static inline bool sm_bShouldFadeIn = false;
};
class CHudManager {
public:

private:

};