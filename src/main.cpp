
#include "Position.hpp"
#include "SDL2/SDL_mouse.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_render.h>

#include <Color.hpp>
#include <WindowConfig.hpp>
#include <EventTriggers.hpp>
#include <DrawInterface.hpp>
#include "../text/text.cpp"
#include <Timer.hpp>

// Есть 2 реализации:
#include <particles/ParticleStatic.hpp>

#include <iomanip>
#include <clocale>
#include <cstdlib>
#include <iostream>
#include <stdexcept>
#include <memory>
#include <chrono>

using namespace std::chrono;


class GameLoop;


class EventHandler : public EventTriggers {
public:

  GameLoop & game_loop;
  Position   pointer_pos;
  bool       is_left_down  = false;
  bool       is_right_down = false;


  EventHandler( WindowConfig &window_config, GameLoop& game_loop ) 
    : EventTriggers(window_config), game_loop(game_loop) {}


  void on_mouse_motion( Position pos )          override;
  void on_mouse_button_down( Uint8 btn_number ) override;
  void on_mouse_button_up( Uint8 btn_number )   override;
};


class GameLoop { 
private:
  bool start = true;

public:

  WindowConfig  window_config {
    .window_h = 800,
    .window_w = 1100,
    .res_h    = 200,
    .res_w    = 250,
  };

  // Для примера 2 указателя:
  EventHandler  *event_handler = nullptr; // — "сырой" указатель.
  std::unique_ptr<DrawInterface> drawler; // — "умный" указатель.


  GameLoop() {
    if ( SDL_Init( SDL_INIT_VIDEO ) != 0 ) { // — `SDL_INIT_VIDEO` уже включает `SDL_INIT_EVENTS`.
      throw std::runtime_error( SDL_GetError() );
    }
    
    
    event_handler = new EventHandler(window_config, *this); // — "сырой" указатель.
    drawler       = std::make_unique<DrawInterface>(window_config);     // — "умный" указатель.
    
    Particle::init(&window_config, drawler.get());
  }


  ~GameLoop() { 

    if ( event_handler ) delete event_handler; //  — динамически выделенная память освобождается вручную.
    // if (drawler)         delete drawler;      //! — эта команда НЕ нужна, так как используется "умный" указатель.
    
    SDL_Quit();
}


  void update() { // — максимум кадров в секунду.
    // Рисование частиц:
    if ( event_handler->is_left_down ) {

      if ( Particle::create_new( event_handler->pointer_pos, 1 ) ) {
        
        drawler->draw_pixel( event_handler->pointer_pos, { .r = 255 });
      }

    } else if ( event_handler->is_right_down ) {

      if ( Particle::create_new( event_handler->pointer_pos ) ) {
        
        drawler->draw_pixel( event_handler->pointer_pos, { .b = 255 });
      }
    }

    // Обновление частиц:
    // Particle::update_all();
  }


  void fixed_update() { // — 60 кадров в секунду.
    
    // Торможение частиц:
    Particle::frame_step();
  }


  void run() {

    Uint32 last_render_time = 0;  // — время последнего рендера.
    Uint32 frame_count      = 0;  // — счётчик кадров для FPS.
    Uint32 fps_timer        = 0;  // — таймер для вывода FPS.

    while( event_handler->flag_run ) {
      frame_count ++;
      event_handler->handle_events();
      if (event_handler->quit) return;

      

      // if (start) { //todo информационный текст пикселями
      //   Text t;
      //   auto text = t.get_text();
      //   for (auto i = text[0].begin(); i != text[0].end(); ++i) {
      //     Position pos {
      //       .x=30 + i[0][0],
      //       .y=70 + i[1][0]
      //     };
      //     Particle::create_new(pos, 1);
      //     drawler->draw_pixel( pos, { .r = i[2][0], .g = i[2][1], .b = i[2][2] });
      //   }
      // }


      const Uint32 current_time = SDL_GetTicks();
      const Uint32 elapsed_time = current_time - last_render_time;

      
      // Рендер с фиксированным интервалом 60 FPS:
      if(elapsed_time >= 16) {
//                       ^
//                       1000ms / 60 ~ 16.666ms
        
        fixed_update();

        drawler->render();

        last_render_time = current_time;
        frame_count++;

        if ( current_time - fps_timer >= 1000 ) {

            print("FPS: ", frame_count ); // * — вывод FPS в консоль.

            frame_count = 0;
            fps_timer = current_time;
            
        }
      }

      SDL_Delay(1); // — снижение нагрузки на CPU.
    }
  }
};



//* Пример рисования:
// void EventHandler::on_mouse_motion(Position pos) {

//   game_loop.drawler->draw_pixel(pos, Color::random());
// }



//* Пример создания частиц:
void EventHandler::on_mouse_motion(Position pos) {

  pointer_pos = pos;
}

void EventHandler::on_mouse_button_down(Uint8 btn_number) {
  
  switch (btn_number) {

    case SDL_BUTTON_LEFT:
      is_left_down  = true;
      break;

    case SDL_BUTTON_RIGHT:
      is_right_down = true;
      break;
  }
}

void EventHandler::on_mouse_button_up(Uint8 btn_number) {

  switch (btn_number) {

    case SDL_BUTTON_LEFT:
      is_left_down  = false;
      break;

    case SDL_BUTTON_RIGHT:
      is_right_down = false;
      break;
  }
}



// SDL2 требует именно такую сигнатуру `main`:
int main( int argc, char *argv[] ) {
      
  setlocale(LC_ALL, "UTF8");
  std::cout << std::setprecision(17) << std::fixed;

  int exit_code = EXIT_SUCCESS;
      
  try {
    auto time_st = steady_clock::now();
    GameLoop game_loop;
    game_loop.run();

    if (game_loop.event_handler->quit) return exit_code;
      
  } catch (const std::exception& exc) { 
    
    std::cerr << exc.what()     // — описание фактической ошибки, привёдшей в `catch`.
              << "\n" 
              << SDL_GetError() // — сообщение об ошибке, сгенерированное SDL, если есть.
              << "\n"; 

    exit_code = EXIT_FAILURE;
  }

  return exit_code;
}