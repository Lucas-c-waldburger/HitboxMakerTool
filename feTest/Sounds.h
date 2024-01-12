#pragma once
#include "App.h"
#include <iostream>
#include <string_view>
#include "Timing.h"

using namespace Timing;


namespace Sounds
{
	// filepaths
	static constexpr std::string_view BEAT_MUSIC = "sfx_music/beat.wav";
	static constexpr std::string_view SCRATCH_SFX = "sfx_music/scratch.wav";
	static constexpr std::string_view HIGH_SFX = "sfx_music/high.wav";
	static constexpr std::string_view MED_SFX = "sfx_music/medium.wav";
	static constexpr std::string_view LOW_SFX = "sfx_music/low.wav";

	// music
	inline static Mix_Music* gMusic = nullptr;

	// sfx
	inline static Mix_Chunk* gScratch = nullptr;
	inline static Mix_Chunk* gHigh = nullptr;
	inline static Mix_Chunk* gMedium = nullptr;
	inline static Mix_Chunk* gLow = nullptr;

	bool Init();
	bool init_err_ret(const std::string_view file_name);
	void Close();

	void event_loop(SDL_Event* ev);


	// successful hit windows

	struct HitWindow
	{
		HitWindow(Mix_Music* music);

		static constexpr Uint64 AWESOME_RANGE = 40;
		static constexpr Uint64 GOOD_RANGE = 70;
		static constexpr Uint64 OK_RANGE = 110;
		static constexpr Uint64 DETECTION_RANGE = 150;

		static bool hit_in_range(Uint64 window, Uint64 music_len_ms, Uint64 target_pos, Uint64 current_pos);

		double music_len_ms;
	};

	inline static std::unique_ptr<HitWindow> hit_window = nullptr;
	inline static Uint64 HIT_TARGET_MS = 100;

	inline static int HIT_TARGETS[] = { 100, 1100 };

	void report_hit(Uint64 current_pos, Uint64 target);
};

