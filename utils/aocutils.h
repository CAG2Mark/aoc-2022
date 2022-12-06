#include <deque>
#include <fstream>
#include <map>
#include <string>
#include <tuple>
#include <unordered_map>
#include <vector>

std::vector<std::string> get_lines(std::string filename = "input");
std::string strip_str(std::string str);
bool string_is_whitespace(std::string str);
std::vector<std::string> split_str(
    std::string inp, std::string delim, bool ignore_empty = false);

// debug tools
template <typename T>
std::ostream &operator<<(std::ostream &os, const std::vector<T> &container) {
    typename std::vector<T>::const_iterator begin = container.begin();
    typename std::vector<T>::const_iterator end = container.end();
    os << '[';
    for (typename std::vector<T>::const_iterator i = begin; i != end; ++i) {
        if (i != begin)
            os << ", ";
        os << *begin;
    }
    os << ']';
    return os;
}

template <typename T>
std::ostream &operator<<(std::ostream &os, const std::deque<T> &container) {
    typename std::deque<T>::const_iterator begin = container.begin();
    typename std::deque<T>::const_iterator end = container.end();
    os << '[';
    for (typename std::deque<T>::const_iterator i = begin; i != end; ++i) {
        if (i != begin)
            os << ", ";
        os << *begin;
    }
    os << ']';
    return os;
}

// Source: https://geo-ant.github.io/blog/2020/stream-insertion-for-tuples/
template <typename... Ts, size_t... Is>
std::ostream &println_tuple_impl(
    std::ostream &os, std::tuple<Ts...> tuple, std::index_sequence<Is...>) {

    static_assert(sizeof...(Is) == sizeof...(Ts),
        "Indices must have same number of elements as tuple types!");

    static_assert(sizeof...(Ts) > 0, "Cannot insert empty tuple into stream.");

    unsigned long last = sizeof...(Ts);

    return ((os << std::get<Is>(tuple) << (Is != last - 1 ? ", " : "")), ...);
}

template <typename... Ts>
std::ostream &operator<<(std::ostream &os, const std::tuple<Ts...> &container) {
    os << '(';
    println_tuple_impl(os, container, std::index_sequence_for<Ts...> {});
    return os << ')';
}

template <typename K, typename V>
std::ostream &operator<<(std::ostream &os, const std::map<K, V> &container) {
    os << '{';
    auto begin = container.begin();
    auto end = container.end();
    for (auto i = begin; i != end; ++i) {
        if (i != begin)
            os << ", ";
        auto a = *i;
        os << std::get<0>(a) << ": " << std::get<1>(a);
    }
    os << '}';
    return os;
}

template <typename K, typename V>
std::ostream &operator<<(std::ostream &os, const std::unordered_map<K, V> &container) {
    os << '{';
    auto begin = container.begin();
    auto end = container.end();
    for (auto i = begin; i != end; ++i) {
        if (i != begin)
            os << ", ";
        auto a = *i;
        os << std::get<0>(a) << ": " << std::get<1>(a);
    }
    os << '}';
    return os;
}