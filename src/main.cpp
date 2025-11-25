
#include "Position.hpp"
#include "SDL2/SDL_mouse.h"
#include "SDL2/SDL_stdinc.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_render.h>

#include <Color.hpp>
#include <WindowConfig.hpp>
#include <EventTriggers.hpp>
#include <DrawInterface.hpp>
// #include "../text/text.cpp"
#include <Timer.hpp>

// Есть 2 реализации:
#include <cstddef>
#include <particles/ParticleStatic.hpp>

#include <iomanip>
#include <clocale>
#include <cstdlib>
#include <iostream>
#include <stdexcept>
#include <memory>
#include <chrono>
#include <functional>
#include <utility>

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
  bool run_flag = true;
public:

  static inline WindowConfig  window_config {
    .window_h = 800,
    .window_w = 1100,
    .res_h    = 200,
    .res_w    = 250,
  };

  // Для примера 2 указателя:
  // static EventHandler  *event_handler = nullptr; // — "сырой" указатель.
  static inline std::unique_ptr<EventHandler> event_handler; // — "умный" указатель.
  static inline std::unique_ptr<DrawInterface> drawler; // — "умный" указатель.

  std::chrono::steady_clock SteadyClock = std::chrono::steady_clock();

  GameLoop() {
    if ( SDL_Init( SDL_INIT_VIDEO ) != 0 ) { // — `SDL_INIT_VIDEO` уже включает `SDL_INIT_EVENTS`.
      throw std::runtime_error( SDL_GetError() );
    }
    
    
    // event_handler = EventHandler(window_config, *this); // — "сырой" указатель.
    event_handler = std::make_unique<EventHandler>(window_config, *this); // — "умный" указатель.
    drawler       = std::make_unique<DrawInterface>(window_config);     // — "умный" указатель.
    
    Particle::init(&window_config, drawler.get());
  }

  ~GameLoop() { 

    // if ( event_handler ) delete event_handler; //  — динамически выделенная память освобождается вручную.
    // if (drawler)         delete drawler;      //! — эта команда НЕ нужна, так как используется "умный" указатель.
    
    SDL_Quit();
}

  static void create_type(Position pos = Position{-1, -1}) {
    Position pix_pos;
    if (pos.x != -1 && pos.y != -1) {
      pix_pos = pos;
    } else {
      pix_pos = event_handler->pointer_pos;
    }
    if ( Particle::create_new( pix_pos, control.get_particle_code() ) ) {
      if (control.get_particle_code() == 0) {
        drawler->draw_pixel( pix_pos, { .b = 255 });
      } else if (control.get_particle_code() == 1) {
        drawler->draw_pixel( pix_pos, { .r = 255 });
      } else if (control.get_particle_code() == 2) {
        drawler->draw_pixel( pix_pos, { .g = 255 });
      };
    };
  };

  static std::pair<Uint32, Uint8> clear_particle(int hash) {
    Uint8  type      = 0;
    Uint32 del_count = 0;
    auto dyn_it = std::find(
      Particle::_dynPart.begin(), 
      Particle::_dynPart.end(), 
      hash
    );
    if (dyn_it != Particle::_dynPart.end()) { 
      Particle::_dynPart.erase(dyn_it);
    };

    for (auto it = Particle::_all.begin(); it != Particle::_all.end(); ) {
      if (it->first == hash) {
        type = it->second.get_type();
        it = Particle::_all.erase(it);
        del_count++;
      } else {
        ++it;
      };
    };
    return std::pair<Uint32, Uint8> {del_count, type};
  }

  static void update() { // — максимум кадров в секунду.
    // Рисование частиц:
    int hash = window_config.pos_to_hash(event_handler->pointer_pos);
    if ( event_handler->is_left_down ) {
      if (control.get_ctrl()) {
        auto res_clear = clear_particle(hash);
        if (res_clear.first != 0) {
          control.set_particle_code((control.get_particle_code() + 1) % PART_TYPES_AMOUNT);
          // print("particle_code", (control.get_particle_code() + 1) % (PART_TYPES_AMOUNT - 1));
        };
      };
      create_type();
    } else if ( event_handler->is_right_down ) {
      // print("clear");
      auto res = clear_particle(hash);
      drawler->clear_pixel(hash);
    }


    // Обновление частиц:
    Particle::update_all();
  }

  static void fixed_update() { // — 60 кадров в секунду.

    // Торможение частиц:
    Particle::frame_step();
  }

  static void render() {
    GameLoop::fixed_update();

    GameLoop::drawler->render();
  }
  
  void run() {
    
    TimeManager ev_h = TimeManager(0ns,  [] () { event_handler->handle_events(); });
    TimeManager upd  = TimeManager(0ns,  [] () { update(); });
    TimeManager ren  = TimeManager(16ms, [] () { render(); });
    
    while (control.get_run()) {
      ev_h.tick();
      upd. tick();
      ren. tick();
    };
    
    // timer.start_ticking();
    
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
    return;
  }
};


//* Пример рисования:
// void EventHandler::on_mouse_motion(Position pos) {

//   game_loop.drawler->draw_pixel(pos, Color::random());
// }


//* Пример создания частиц:
void EventHandler::on_mouse_motion(Position pos) {
  
  pointer_pos = pos;
  if (control.get_space()) {
    int hash = window_config.pos_to_hash(pointer_pos);
    auto res = GameLoop::clear_particle(hash);
    if (res.first != 0) {
      game_loop.drawler->clear_pixel(hash);
    };
    if (Particle::create_new( pointer_pos, 0 )) {
      game_loop.drawler->draw_pixel(pos, Color::random());
    };
  };
}

void EventHandler::on_mouse_button_down(Uint8 btn_number) {
  
  switch (btn_number) {

    case SDL_BUTTON_LEFT:
      is_left_down  = true;
      break;

    case SDL_BUTTON_RIGHT:
      is_right_down = true;
      break;
  };
};

void EventHandler::on_mouse_button_up(Uint8 btn_number) {

  switch (btn_number) {

    case SDL_BUTTON_LEFT:
      is_left_down  = false;
      break;

    case SDL_BUTTON_RIGHT:
      is_right_down = false;
      break;
  };
};



// SDL2 требует именно такую сигнатуру `main`:
int main( int argc, char *argv[] ) {
      
  setlocale(LC_ALL, "UTF8");
  std::cout << std::setprecision(17) << std::fixed;

  int exit_code = EXIT_SUCCESS;
      
  try {
    auto time_st = steady_clock::now();
    GameLoop game_loop;
    game_loop.run();
      
  } catch (const std::exception& exc) { 
    
    std::cerr << exc.what()     // — описание фактической ошибки, привёдшей в `catch`.
              << "\n" 
              << SDL_GetError() // — сообщение об ошибке, сгенерированное SDL, если есть.
              << "\n"; 

    exit_code = EXIT_FAILURE;
  };

  return exit_code;
}