#include <iostream>
#include <optional>
#include <string>
#include <type_traits>

#pragma once


// Проверка на std::pair:
template <typename T>
struct is_pair : std::false_type {};


template <typename T1, typename T2>
struct is_pair<std::pair<T1, T2>> : std::true_type {};

template<class T>
concept string_like = std::is_convertible_v<T, std::string_view>;


// Проверка на контейнер (имеет begin()/end()):
template <typename T>
concept container = ! string_like<T> && requires(T t) {
  { t.begin() } -> std::input_iterator;
  { t.end()   } -> std::sentinel_for<decltype(t.begin())>;
};


// Проверка на priority_queue:
template <typename T>
concept is_priority_queue = requires {
    
  typename T::container_type;
  typename T::value_compare;
};

// Вывод [[очереди приоритета][очередь приоритета]]:
template <is_priority_queue Q>
std::ostream& operator<<(std::ostream& os, Q pq) {
//!                                        ^
//!                                        здесь нельзя использовать ссылку,
//!                                        так как очередь будет будет изменяться в коде ниже.
//*                                        Так что очередь передаётся через копирование,
//*                                        и меняется только локальная копия
    os << "[";
    while (!pq.empty()) {
      os << pq.top();
      pq.pop(); // — извлечение элемента очереди.
      if (!pq.empty()) os << ", ";
    }
    os << "]";
    return os;
}


// Перегрузка для `std::pair`:
template <typename T1, typename T2>
std::ostream& operator<<(std::ostream& os, const std::pair<T1, T2>& p) {
  
  os << "{" << p.first << ": " << p.second << "}";
  return os;
}


// Перегрузка для `std::optional`:
template <typename T>
std::ostream& operator<<(std::ostream& os, const std::optional<T>& opt) {
  
  if (opt.has_value()) os << opt.value();
  else                 os << "nullopt_t";

  return os;
}


// Основной шаблон для контейнеров:
template <container C>
std::ostream& operator<<(std::ostream& os, const C& cont) {
  if (cont.empty()) {
    os << (is_pair<typename C::value_type>::value ? "{}" : "[]");
    return os;
  }

  // Для map'ов используем фигурные скобки,
  // а для упорядоченных структур — квадратные:
  os << (is_pair<typename C::value_type>::value ? "{" : "[");
  
  for (auto it = cont.begin(); it != cont.end(); ++it) {
    os << *it;
    if (std::next(it) != cont.end()) os << ", ";
  }
  
  os << (is_pair<typename C::value_type>::value ? "}" : "]");
  return os;
}


class Particle;
std::ostream& operator << (std::ostream& os, const Particle& cont) {
  os << &cont;
  return os;
}