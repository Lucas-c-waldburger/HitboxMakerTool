#include "Sounds.h"

bool Sounds::Init()
{
	gMusic = Mix_LoadMUS(BEAT_MUSIC.data());
	if (!gMusic)
		return init_err_ret(BEAT_MUSIC);

	gScratch = Mix_LoadWAV(SCRATCH_SFX.data());
	if (!gScratch)
		return init_err_ret(SCRATCH_SFX);

	gHigh = Mix_LoadWAV(HIGH_SFX.data());
	if (!gHigh)
		return init_err_ret(HIGH_SFX);

	gMedium = Mix_LoadWAV(MED_SFX.data());
	if (!gMedium)
		return init_err_ret(MED_SFX);

	gLow = Mix_LoadWAV(LOW_SFX.data());
	if (!gLow)
		return init_err_ret(LOW_SFX);

	hit_window = std::make_unique<HitWindow>(gMusic);
	return true;
}

void Sounds::Close()
{
	Mix_FreeChunk(gScratch);
	Mix_FreeChunk(gHigh);
	Mix_FreeChunk(gMedium);
	Mix_FreeChunk(gLow);
	gScratch = nullptr;
	gHigh = nullptr;
	gMedium = nullptr;
	gLow = nullptr;

	Mix_FreeMusic(gMusic);
	gMusic = nullptr;

	Mix_Quit();
}

bool Sounds::init_err_ret(const std::string_view file_name)
{
	std::cout << "Failed to load " <<  file_name << ": " << Mix_GetError() << '\n';
	return false;
}


void Sounds::event_loop(SDL_Event* ev)
{

	if (ev->type == SDL_KEYDOWN)
	{
		switch (ev->key.keysym.sym)
		{
		case SDLK_1:
			Mix_PlayChannel(-1, gHigh, 0); break;

		case SDLK_2:
			Mix_PlayChannel(-1, gMedium, 0); break;

		case SDLK_3:
			Mix_PlayChannel(-1, gLow, 0); break;

		case SDLK_4:
			Mix_PlayChannel(-1, gScratch, 0); break;

		case SDLK_6:
		{
			if (Mix_PlayingMusic())
			{
				for (int i = 0; i < sizeof(HIT_TARGETS) / sizeof(Uint64); i++)
				{
					if (HitWindow::hit_in_range(HitWindow::DETECTION_RANGE, hit_window->music_len_ms, HIT_TARGETS[i], timer.count))
						report_hit(timer.count, HIT_TARGETS[i]);
				}

			}

			break;
		}
		case SDLK_7:
			if (!Mix_PlayingMusic())
				Mix_FadeInMusic(gMusic, -1, 1000);

			break;

		case SDLK_8:
			if (Mix_PlayingMusic())
				Mix_FadeOutMusic(1000);

			break;

		case SDLK_9:
			if (!Mix_PlayingMusic())
			{
				Mix_PlayMusic(gMusic, -1);
				timer.start_timing(Mix_MusicDuration(gMusic) * 1000.0);
			}


			else
			{
				if (Mix_PausedMusic())
					Mix_ResumeMusic();

				else
					Mix_PauseMusic();
			}

			break;

		case SDLK_0:
			Mix_HaltMusic(); 
			break;
		}		
	}
}


void Sounds::report_hit(Uint64 current_pos, Uint64 target)
{
	//double current_pos = Mix_GetMusicPosition(gMusic) * 1000.0;

	//double testing_range = HitWindow::AWESOME_RANGE
	std::cout << "CURRENT POSITION: " << current_pos << " ----- ";

	if (HitWindow::hit_in_range(HitWindow::AWESOME_RANGE, hit_window->music_len_ms, target, current_pos))
	{
		std::cout << "AWESOME!!!\n";
		return;
	}

	if (HitWindow::hit_in_range(HitWindow::GOOD_RANGE, hit_window->music_len_ms, target, current_pos))
	{
		std::cout << "GOOD!\n";
		return;
	}

	if (HitWindow::hit_in_range(HitWindow::OK_RANGE, hit_window->music_len_ms, target, current_pos))
	{
		std::cout << "OK\n";
		return;
	}

	std::cout << "MISS...\n";
}



Sounds::HitWindow::HitWindow(Mix_Music* music)
{
	if (!music)
		throw std::invalid_argument("Mix_Music is null");

	music_len_ms = Mix_MusicDuration(music) * 1000.0;
}

bool Sounds::HitWindow::hit_in_range(Uint64 window, Uint64 music_len_ms, Uint64 target_pos, Uint64 current_pos)
{
	auto between = [&current_pos](int lo, int hi)
	{
		//std::cout << "LOOKING FOR BETWEEN (" << low << ", " << hi << ")...\n";
		return current_pos >= lo && current_pos <= hi;
	};

	int low = target_pos - window, high = target_pos + window;

	/*std::cout << "LOOKING FOR LOW...\n";
	std::cout << "LO RANGE ADJUSTED: " << (music_len_ms + low) << " - " << music_len_ms << '\n'
			  << "HI RANGE ADJUSTED: " << 0 << " - " << target_pos << '\n'
			  << "BETWEEN ?: " << std::boolalpha << between(music_len_ms + low, music_len_ms) && between(0.0, target_pos) << '\n';*/

	//std::cout << "LOOKING FOR HI...\n";
	//std::cout << "LO RANGE ADJUSTED: " << (music_len_ms + low) << " - " << music_len_ms << '\n'
	//		  << "HI RANGE ADJUSTED: " << 0 << " - " << target_pos << '\n';

	bool in_range_low = (low < 0.0) ? between(music_len_ms + low, music_len_ms) || between(0.0, target_pos) :
		between(low, target_pos);

	if (in_range_low)
		return true;

	bool in_range_high = (high > music_len_ms) ? between(target_pos, music_len_ms) || between(0, high - music_len_ms) :
		between(target_pos, high);

	//std::cout << std::boolalpha << "HIGH-> BETWEEN?: " << between(target_pos, high);

	//std::cout << "RANGE ( LOW = " << low << ", " << "HIGH = " << high << " )\n";

	return in_range_high;
}


