#include <SDL2/SDL.h>

#include <EventTriggers.hpp>
// #include "../text/text.cpp"
#include "Position.hpp"
#include "particles/ParticleStatic.hpp"

// Есть 2 реализации:
#include <cstddef>
#include <cstdio>
#include <iostream>


using namespace std::chrono;


class GameLoop;


class EventHandler : public EventTriggers {
public:

  GameLoop & game_loop;
  Position   pointer_pos;

  EventHandler( WindowConfig &window_config, GameLoop& game_loop ) 
    : EventTriggers(window_config), game_loop(game_loop) {}


  void on_mouse_motion( Position pos )          override;
  void on_mouse_button_down( Uint8 btn_number ) override;
  void on_mouse_button_up( Uint8 btn_number )   override;
  void on_key_down(int btn_number)              override;
  void on_key_up(int btn_number)                override;
};


class GameLoop { 
private:
  static inline bool start_off = false;
  static inline bool start     = true;
  static inline Position cursor_cur_pos;
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
  };

  ~GameLoop() { 

    // if ( event_handler ) delete event_handler; //  — динамически выделенная память освобождается вручную.
    // if (drawler)         delete drawler;      //! — эта команда НЕ нужна, так как используется "умный" указатель.
    
    SDL_Quit();
  };
  
  void set_start(bool flag) {
    start = flag;
  };

  bool get_start() {
    return start;
  };

  void set_start_off(bool flag) {
    start_off = flag;
  };

  bool get_start_off() {
    return start_off;
  };

  void set_cursor_pos(Position& new_pos) {
    cursor_cur_pos = new_pos;
  };

  Position& get_cursor_pos() {
    return cursor_cur_pos;
  };

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
      } 
      // else if (control.get_particle_code() == 3) {
      //   drawler->draw_pixel( pix_pos, { .r = 255, .g = 255 });
      // }
    };
  };
  
  static void interpolateController(Position& target_pos, int mode=0) {
   
    Position cur_pos = cursor_cur_pos;
    do {
      Position new_pos = Position::interpolate(cur_pos, target_pos);
      if (
          std::abs(cur_pos.x - new_pos.x) > 1 ||
          std::abs(cur_pos.y - new_pos.y) > 1
      ) {
          std::cerr << "out of range :: line 134\n"; 
          break;
      };
      cur_pos = new_pos;

      if ( mode == 0 ) {
        if (Particle::create_new( cur_pos, 0 )) {
          auto c = Color::random();
          std::cout << static_cast<int>(c.r) << " | " << static_cast<int>(c.g) << " | " << static_cast<int>(c.b) << std::endl;
          GameLoop::drawler->draw_pixel(target_pos, c);
        };
      } else if ( mode == 1 ) {
        create_type(cur_pos);
      } else if ( mode == 2 ) {
        auto hash = window_config.pos_to_hash(cur_pos);
        auto res = clear_particle(hash);
        drawler->clear_pixel(hash);
      }
    } while (cur_pos.x != target_pos.x && cur_pos.y != target_pos.y);
    cursor_cur_pos = target_pos;
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

    // if ( start_off == true && start == true ) {
    //   for (auto it = Particle::_all.begin(); it != Particle::_all.end(); ++it) {
    //     it->second.set_type(1);
    //     it->second.upd_beh();
    //     Particle::_dynPart.emplace_back(it->first);
    //     it->second.behaviour(it);
    //   }
    // } else 
    if ( control.get_lmb() ) {
      if ( control.get_lctrl() ) {
        auto res_clear = clear_particle(hash);
        if (res_clear.first != 0) {
          control.set_particle_code((control.get_particle_code() + 1) % PART_TYPES_AMOUNT);
          // print("particle_code", (control.get_particle_code() + 1) % (PART_TYPES_AMOUNT - 1));
        };
      };
      // create_type();
      GameLoop::interpolateController(event_handler->pointer_pos, 1);
    } else if ( control.get_rmb() ) {
      // print("clear");
      
      // auto res = clear_particle(hash);
      // drawler->clear_pixel(hash);
      GameLoop::interpolateController(event_handler->pointer_pos, 2);
    } else if ( control.get_r() ) {
      if ( control.get_shift() ) {
        Particle::clear();
      };
      std::srand(std::time(0));
      Uint32 count = static_cast<Uint32>(std::rand() % 300);
      while (count == 0 || count <= 70) {
        count = static_cast<Uint32>(std::rand() % 300);
      };
      for (Uint32 _ = 0; _ <= count; ++_) {
        std::srand(std::time(0));
        Position new_pos {std::rand() % window_config.res_w, std::rand() % window_config.res_h};
        int c = Particle::_all.count(window_config.pos_to_hash(new_pos));
        std::srand(std::time(0));
        while (c != 0) {
          if (Particle::_all.size() == window_config.get_res_area()) {
            print("field is full!");
            return;
          };
          new_pos = Position(std::rand() % window_config.res_w, std::rand() % window_config.res_h);
          c = Particle::_all.count(window_config.pos_to_hash(new_pos));
        };
        std::srand(std::time(0));
        if (Particle::create_new( new_pos, 0 )) {
          auto c = Color::random();
          drawler->draw_pixel(new_pos, c);
        };
      };
    };

    // Обновление частиц:
    Particle::update_all();
  }

  static void fixed_update() { // — 60 кадров в секунду.

    // Торможение частиц:
    Particle::frame_step();
  }

  static void render() {
    cursor_cur_pos = event_handler->pointer_pos;
    GameLoop::fixed_update();

    GameLoop::drawler->render();
  }
  
  void run() {
    
    TimeManager ev_h = TimeManager(0ns,  [] () { event_handler->handle_events(); });
    TimeManager upd  = TimeManager(0ns,  [] () { update(); });
    TimeManager ren  = TimeManager(16ms, [] () { render(); });
    
    // //todo информационный текст пикселями
    // GameLoop::start_off = false;
    // auto text = Text::get_text();
    // for (int i_ = 0; i_ < 3; i_++) {
    //   for (auto i = text[0].begin(); i != text[0].end(); ++i) {
    //     Position pos {
    //       .x=30 + i[i_][0][0],
    //       .y=70 + i[i_][1][0]
    //     };
    //     if (Particle::create_new(pos, 1)) {
    //       drawler->draw_pixel( pos, { .r = i[i_][2][0], .g = i[i_][2][1], .b = i[i_][2][2] });
    //     }
    //   }
    // }

    while (control.get_run()) {
      ev_h.tick();
      upd. tick();
      ren. tick();
    };
    
    // timer.start_ticking();
    
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
    //todo интерполяция не распростряняется на этот режим
    int hash = window_config.pos_to_hash(pointer_pos);
    auto res = GameLoop::clear_particle(hash);
    if (res.first != 0) {
      game_loop.drawler->clear_pixel(hash);
    };
    GameLoop::interpolateController(pointer_pos, 0);
  };
}

void EventHandler::on_mouse_button_down(Uint8 btn_number) {
  // if (game_loop.get_start_off() == false && game_loop.get_start() == true) game_loop.set_start_off(true);

  switch (btn_number) {

    case SDL_BUTTON_LEFT:
      control.set_lmb(true);
      break;

    case SDL_BUTTON_RIGHT:
      control.set_rmb(true);
      break;
  };
};

void EventHandler::on_mouse_button_up(Uint8 btn_number) {

  switch (btn_number) {

    case SDL_BUTTON_LEFT:
      control.set_lmb(false);
      break;

    case SDL_BUTTON_RIGHT:
      control.set_rmb(false);
      break;
  };
};

void EventHandler::on_key_down(int btn_munber) {
  switch (btn_munber) {
    case SDLK_r:
      control.set_r(true);
      break;
  };
};

void EventHandler::on_key_up(int btn_munber) {
  switch (btn_munber) {
    case SDLK_r:
      control.set_r(false);
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