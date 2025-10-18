#include "../include/Position.hpp"
#include "DrawInterface.hpp"
#include "SDL2/SDL_stdinc.h"
#include <WindowConfig.hpp>

#include <iostream>
#include <exception>
#include <sys/stat.h>
#include <unordered_map>
#include <array>
#include <vector>
#include <algorithm>

#define DEBUG 0

#if DEBUG
  #include <stdexcept>
#endif

#pragma once


class Particle {

protected:
  
  // Объявление сокращённых типов (2 способа):
  // 1. using:
  using ParticleMap    = std::unordered_map<Uint32, Particle>; // — тип карты частиц.
  using MapIterator    = ParticleMap::iterator;                // — тип итератора по карте.
  using ParticleVector = std::vector<Uint32>;
  // typedef ParticleMap::iterator MapIterator;
  // 2. typedef:
  typedef void (* Behaviour )(MapIterator&);                // — тип поведения частиц.
  
  Uint8 _type         = 0;

public:

  // Поведение частиц 1 вида:

  static void beh_monolit(MapIterator& iterator) {
    /* Ничего не происходит. Статичное поведение. */
  }

  // Поведение частиц 2 вида:

  static void beh_falling(MapIterator& iterator) {
    
    // Замедление обновления частиц:
    if ( iterator->second.freq_upd_count > 0 ) {
      return;
    }
    
    iterator->second.freq_upd_count = FREQ_UPD_LIMIT;
    //* Падение частиц:
    
    // Нахождение позиции:
    Uint32 pos_hash = iterator->first;
    
    Position pos = drawler->window_config.hash_to_pos(pos_hash);
    
    Position new_pos = {
      .x = pos.x,
      .y = pos.y + 1, // — ось y перевёрнута. 
    };

    // print(_all);
    // print(_dynPart);
    const Uint32 entry_color = drawler->get_pixel(pos_hash);

    if (not drawler->window_config.pos_in_res(drawler->window_config.pos_to_hash(new_pos))) {
      // print(_all.size());
      
      drawler->clear_pixel(pos_hash);
      _all.extract(iterator); 

      // print(_all.size());
      // print("=====");
      return;
    } else {
      // print(8);
      int pos_new_hash = drawler->window_config.pos_to_hash(new_pos);
      
      MapIterator other_iterator = _all.find(pos_new_hash);
      
      // Если новая позиция НЕ занята:
      if ( other_iterator == _all.end() ) {
        // print(9);
        drawler->draw_pixel(pos_new_hash, entry_color);
        drawler->clear_pixel(pos_hash);
        
        // Отключаем узел карты от карты
        // (ячейка памяти становится самостоятельной):
  
        auto node = _all.extract(iterator);
  
        node.key()           = pos_new_hash;
        
        auto result          = _all.insert(std::move(node));
  
        // _dynPart.push_back(node);
        // if (result.inserted) { 
        //   iterator = result.position; // * — идём к только что добавленной сущности.
        // }
      }
    };
    

  } // beh_falling.


  // Свойства частицы:
  Behaviour behaviour      = beh_monolit;    //! — поведение.
  Uint8     freq_upd_count = FREQ_UPD_LIMIT; //  — счётчик обновления.
  Uint32    id             = 0;              //  — id для сравнения частиц.


  // Статические поля:
  inline static ParticleMap    _all{}; // — карта всех частиц.
  inline static ParticleVector _dynPart{};

  // inline static WindowConfig  * window_config = nullptr;
  inline static DrawInterface * drawler       = nullptr;
  
  const inline static Uint8  FREQ_UPD_LIMIT = 1; // — кол-во пропускаемых между обновлениями кадров.
        inline static Uint32 id_counter     = 0; // — счётчик id.

public:


//region Конструкторы копирования:
  Particle(const Particle&)            = delete;
  Particle& operator=(const Particle&) = delete;
  
  // Конструкторы перемещения:
  Particle(Particle&&)            = default;
  Particle& operator=(Particle&&) = default;
  
  // Стандартный конструктор:
  Particle() = default;

  // Деструктор:
  ~Particle() {
    // Для отладки:
    print("PARTICLE DESTROY"); 
  }
//endregion 


  static void frame_step() {

    for ( MapIterator it = _all.begin(); it != _all.end(); ++it ) {

      if ( it->second.freq_upd_count ) {

        it->second.freq_upd_count --;
        
      }
    }
  }

  static bool create_new(
    Position pos, 
    Uint8 type = 0
  ) {
    
    #if DEBUG
      if ( not is_inited() ) throw std::runtime_error("`Particle` НЕ инициализирован."); 
    #endif

    int  pos_hash    = drawler->window_config.pos_to_hash(pos);
    bool is_positive = pos_hash > -1;

    if ( is_positive && _all.find(pos_hash) == _all.end()) {

      auto [ it, inserted ] = _all.try_emplace(pos_hash);

      // Назначение типа
      it->second._type = type; //<-
      
      // Назначение id:
      it->second.id = id_counter++;
      
      // Поведение сущности:
      switch (type) {

        case 1:
          it->second.behaviour = beh_falling;
          _dynPart.emplace_back(pos_hash); //<-
          // print(90);
          return inserted;
        default:
          it->second.behaviour = beh_monolit;
          return inserted;
          // TODO
      };
    };

    return is_positive;
  }


  static void update_all() {

    #if DEBUG
      if ( not is_inited() ) throw std::runtime_error("`Particle` НЕ инициализирован."); 
    #endif
    
    auto it = std::remove_if(
      _dynPart.begin(),
      _dynPart. end(),
      [] (Uint32 & e) {
        auto it_ = _all.find(e);
        if (it_ != _all.end()) {
          // print("00");
          it_->second.behaviour(it_);
          e = it_->first;
          return false;
        };
        return true;
      }
    );

    _dynPart.erase(it, _dynPart.end());

  }
  
  static void clear() {
    //TODO 
    for (auto it = _all.begin(); it != _all.end(); ++it) {
      drawler->clear_pixel(it->first);
      // it->second.behaviour = beh_falling;
    };
    print("clear");
    _dynPart.clear();
    _all.clear();
  }

  static bool is_inited() { return drawler != nullptr; }


  static void init(WindowConfig * wind_config, DrawInterface * drawler) {
    
    #if DEBUG
      if ( not wind_config ) throw std::invalid_argument("Particle :: init :: nullptr WindowConfig");
    #endif

    // Particle::window_config = wind_config;
    Particle::drawler       = drawler;

    // _all.reserve(window_config->get_res_area() / 2);
  };

};

// std::unordered_map<Uint32, Particle> Particle::_all{};

