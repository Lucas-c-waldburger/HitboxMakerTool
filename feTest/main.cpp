#include <iostream>
#include "Sounds.h"
#include "Sprites.h"
#include "Controller.h"
#include "HitboxManager.h"
#include "Widgets.h"
#include "RhythmAnimation.h"

using namespace Sprites;

int main(int argc, char* args[])
{
	App::App app{};
	Sounds::Init();

	App::Window window{ "F.E. Testing" };
	App::Renderer renderer{ window };

	//cursors.set(App::AppCursors::ArrowType::NE_SW);

	//Controller* controller;

	//try
	//{
	//	controller = new Controller{};
	//}

	//catch (std::runtime_error& ex)
	//{
	//	SDL_Log(SDL_GetError());
	//	return 1;
	//}


	//Texture tex{};
	//tex.load(renderer, "C:\\Users\\Lucas\\Documents\\steam_assist\\logs\\cuts\\bby8.png");
	//ExOptions exop{};
	//exop.scale = { 50, 50 };

	
	//widgets::TextTexture txt;
	//txt.setX(100); 
	//txt.setY(100);

	//if (!txt.open_font("fonts/LinLibertine_DR.ttf", 18));
	//std::cout << SDL_GetError() << '\n';

	//txt.load(renderer, "hello");
	
	SDL_Event ev;
	HitboxManager hitbox_manager;


	//hbm::EventHandler hbm_handler(cursors);
	//double music_pos = 0.0;

	//Mix_PlayMusic(Sounds::gMusic, -1);
	//double music_duration = (Mix_MusicDuration(Sounds::gMusic));
	//Mix_HaltMusic();
	//bool need_reset_timer = false;
	//bool need_update_timer = false;

	//int i = 0;
	//double total_time_diff = 0.0;

	while (1)
	{
		//timer.update();
		//std::cout << "TIMER: " << timer.count << '\n';
		//if (Mix_PlayingMusic())
		//{
		//	double temp_music_pos = Mix_GetMusicPosition(Sounds::gMusic) * 1000;
		//	//std::cout << "MUSIC POS: " << music_pos << '\n';
		//	if (music_pos == 0.0)
		//	{
		//		if (need_reset_timer)
		//		{
		//			timer.reset();
		//			need_reset_timer = false;
		//		}
		//	}
		//	else
		//	{
		//		need_reset_timer = true;
		//	}

		//	if (music_pos != temp_music_pos)
		//	{
		//		music_pos = temp_music_pos;

		//		double current_diff = music_pos - timer.count;
		//		if (current_diff > 0.0)
		//		{
		//			total_time_diff += current_diff;
		//			++i;

		//			double avg_diff = total_time_diff / i;

		//			//std::cout << "AVERAGE DIFFERENCE: " << avg_diff << '\n';

		//			//timer.count += static_cast<Uint64>(avg_diff);

		//			//std::cout << "CURRENT DIFFERENCE: " << timer.count << '\n';
		//		}
		//		//std::cout << "DIFFERENCE (MUSIC - TIMER)" << music_pos - timer.count << '\n';

		//	}


		//}

		while (SDL_PollEvent(&ev))
		{
			if (ev.type == SDL_QUIT)
				goto gameExit;


			//Sounds::event_loop(&ev);

			/*std::cout << "MOUSE COORDS CURRENT: { " << mouse_coords.current().x << ", " << mouse_coords.current().y << " }\n" 
					  << "MOUSE COORDS LAST_FRAME: { " << mouse_coords.last_frame().x << ", " << mouse_coords.last_frame().y << " }\n\n";*/

			hitbox_manager.event_loop(&ev);
		}

		renderer.clear();

		//rhythm_display::draw_display(renderer);

		//if (Mix_PlayingMusic())
		//{
		//	rhythm_anim::move_anim_rect(timer.count, timer.duration);
		//}

		//rhythm_anim::draw_anim_rects(renderer);

		SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);

		hitbox_manager.draw_rects(renderer);

		//txt.draw_all(renderer);
		//tex.draw(renderer, &exop);

		renderer.present();
	}



gameExit:
	Sounds::Close();
	return 0;
};