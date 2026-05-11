#include <iostream>
#include <optional>
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
std::ostream& operator<<(std::ostream& os, Q pq);


// Перегрузка для `std::pair`:
template <typename T1, typename T2>
std::ostream& operator<<(std::ostream& os, const std::pair<T1, T2>& p);


// Перегрузка для `std::optional`:
template <typename T>
std::ostream& operator<<(std::ostream& os, const std::optional<T>& opt);

// Основной шаблон для контейнеров:
template <container C>
std::ostream& operator<<(std::ostream& os, const C& cont);


class Particle;
std::ostream& operator << (std::ostream& os, const Particle& cont);