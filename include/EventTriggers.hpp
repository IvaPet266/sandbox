#include "SDL2/SDL_keycode.h"
#include "SDL2/SDL_stdinc.h"
#include <SDL2/SDL_events.h>

#include <Position.hpp>
#include <WindowConfig.hpp>
#include "particles/ParticleStatic.hpp"
#include <control.hpp>
#include <windows.h>
// #include <iostream>

#pragma once


class EventTriggers {

public:

  void handle_events() {
    
    SDL_Event event;

    while (SDL_PollEvent(&event)) {
      switch(event.type) {
        
        case SDL_QUIT:
          control.set_run(false);
          // break;
          return;

        case SDL_KEYDOWN:
          print(event.key.keysym.sym);
          on_key_down(event.key.keysym.sym);
          switch (event.key.keysym.sym) {
            case SDLK_ESCAPE: //27="esc"
              Particle::clear();
              print("escape");
              break;
            case SDLK_SPACE: //32=" "  
              if (not control.get_space()) control.set_space(true); //режим рисования
              break;
            case SDLK_q: //113="q"
              control.set_run(false);
              // break;
              return;
            // case SDLK_RCTRL:
            case SDLK_LCTRL:
              //todo при нажатии ctrl меняется тип частицы по нажатию
              if (not control.get_ctrl()) control.set_ctrl(true);
              break;
            case SDLK_i:
              print("particles amount", Particle::_all.size());
              break;
            case SDLK_0:
              control.set_particle_code(0); //beh_monolit
              print("code", control.get_particle_code());
              break;
            case SDLK_1:
              control.set_particle_code(1); //beh_falling
              print("code", control.get_particle_code());
              break;
            case SDLK_2:
              control.set_particle_code(2); //beh_levitating
              print("code", control.get_particle_code());
              break;
          };
          break;

        case SDL_KEYUP:
          on_key_up(event.key.keysym.sym);
          switch(event.key.keysym.sym) {
            case SDLK_ESCAPE:
              print("escape отжат");
              break;
            case SDLK_SPACE:
              control.set_space(false);
              break;
            // case SDLK_RCTRL:
            case SDLK_LCTRL:
              control.set_ctrl(false);
              break;
            
          };
          break;

        case SDL_MOUSEMOTION:
          on_mouse_motion({
              .x = (event.motion.x * window_config.res_w) / window_config.window_w,
              .y = (event.motion.y * window_config.res_h) / window_config.window_h
            }
          );
          break;

        case SDL_MOUSEBUTTONDOWN:
          on_mouse_button_down(event.button.button);
          break;

        case SDL_MOUSEBUTTONUP:
          on_mouse_button_up(event.button.button);
          break;
      };
    };
  };


  WindowConfig& window_config;


  EventTriggers(WindowConfig& window_config) 
    : window_config(window_config) {}


  virtual void on_key_down(SDL_Keycode keycode) {}
  virtual void on_key_up  (SDL_Keycode keycode) {}

  virtual void on_mouse_button_down(Uint8 btn_number) {}
  virtual void on_mouse_button_up  (Uint8 btn_number) {}
    
  virtual void on_mouse_motion(Position pos) {}
};
