#include "DrawInterface.hpp"
#include "SDL2/SDL_stdinc.h"
#include "WindowConfig.hpp"

// #include <chrono>
#include <unordered_map>


#define DEBUG 0

#if DEBUG
  #include <stdexcept>
#endif

#pragma once


class Particle {

protected:
  
  // Объявление сокращённых типов (2 способа):
  // 1. using:
  using ParticleMap    = std::unordered_map<int, Particle>; // — тип карты частиц.
  using MapIterator    = ParticleMap::iterator;                // — тип итератора по карте.
  using ParticleVector = std::vector<int>;
  // typedef ParticleMap::iterator MapIterator;
  // 2. typedef:
  typedef void (* Behaviour )(MapIterator&);                // — тип поведения частиц.
  
  int _type = 0;

protected:

  // Поведение частиц 1 вида:

  static void beh_monolit(MapIterator& iterator) {
    /* Ничего не происходит. Статичное поведение. */
  }

  // Поведение частиц 2, 3 вида:

  static void beh_falling(MapIterator& iterator) { //todo
    // // Замедление обновления частиц:
    if ( iterator->second.freq_upd_count > 0 ) {
      return;
    }
    
    iterator->second.freq_upd_count = FREQ_UPD_LIMIT;
    //* Падение частиц:
    
    // Нахождение позиции:
    Uint32 pos_hash = iterator->first;
    
    Position pos = drawler->window_config.hash_to_pos(pos_hash);
    Position new_pos = {
      .x = pos.x + iterator->second.inst_x * control.get_speed(),
      .y = pos.y + iterator->second.inst_y * control.get_speed(), // — ось y перевёрнута. 
    };

    const Uint32 entry_color = drawler->get_pixel(pos_hash);

    if (not drawler->window_config.pos_in_res(drawler->window_config.pos_to_hash(new_pos))) {
      drawler->clear_pixel(pos_hash);
      _all.extract(iterator); 

      return;
    } else {
      int pos_new_hash = drawler->window_config.pos_to_hash(new_pos);
      
      MapIterator other_iterator = _all.find(pos_new_hash);
      
      // Если новая позиция НЕ занята:
      if ( other_iterator == _all.end() ) {
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
    
  }

public:

  // Свойства частицы:
  Behaviour behaviour      = beh_monolit;    //! — поведение.
  Uint8     freq_upd_count = FREQ_UPD_LIMIT; //  — счётчик обновления.
  Uint32    id             = 0;              //  — id для сравнения частиц.
  int inst_y               = 1;
  int inst_x               = 0;


  // Статические поля:
  inline static ParticleMap    _all{}; // — карта всех частиц.
  inline static ParticleVector _dynPart{};

  // inline static WindowConfig  * window_config = nullptr;
  inline static DrawInterface * drawler       = nullptr;
  
  const inline static Uint8  FREQ_UPD_LIMIT = 1; // — кол-во пропускаемых между обновлениями кадров.
        inline static Uint32 id_counter     = 0; // — счётчик id.


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

  int get_type() {
    return _type;
  };
  
  void set_type(int new_type) {
    _type = new_type;
  };
  static void frame_step() {

    for ( MapIterator it = _all.begin(); it != _all.end(); ++it ) {

      if ( it->second.freq_upd_count ) {

        it->second.freq_upd_count --;
        
      };
    };
  };

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
      it->second.set_type(type); //<-
      
      // Назначение id:
      it->second.id = id_counter++;
      
      // Поведение сущности:
      switch (type) {

        case 1:
          it->second.inst_y = 1;
          it->second.behaviour = beh_falling;
          _dynPart.emplace_back(pos_hash); //<-
          break;
        case 2:
          // case 3:
          it->second.inst_y = -1;
          it->second.behaviour = beh_falling;
          _dynPart.emplace_back(pos_hash); //<-
          break;
        default: //0
          it->second.behaviour = beh_monolit;
          // TODO
          break;
        };
      return inserted;
    };

    return is_positive;
  };


  static void update_all() {

    #if DEBUG
      if ( not is_inited() ) throw std::runtime_error("`Particle` НЕ инициализирован."); 
    #endif
    
    auto it = std::remove_if(
      _dynPart.begin(),
      _dynPart. end(),
      [] (int & e) {
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

  };
  
  static void clear() {
    //TODO 
    Uint16 s = _all.size();
    auto st_time = std::chrono::high_resolution_clock().now();
    _dynPart.clear();
    _all.clear();
    drawler->clear_buffer();

    print("clear");
    auto end_time = std::chrono::high_resolution_clock().now();
    auto dur = end_time- st_time; //std::chrono::duration_cast<std::chrono::microseconds>(end_time - st_time);
    print("clear time", dur);
    print("particles cleared", s);
  };

  static bool is_inited() { return drawler != nullptr; };


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

