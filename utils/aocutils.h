#include <deque>
#include <fstream>
#include <map>
#include <string>
#include <tuple>
#include <unordered_map>
#include <vector>
#include <numeric>

std::vector<std::string> get_lines(std::string filename = "input");
std::string strip_str(std::string str);
bool string_is_whitespace(std::string str);
std::vector<std::string> split_str(
    std::string inp, std::string delim, bool ignore_empty = false);

template <typename T>
T exp(T x, unsigned int p) {
    T prod = 1;
    while (p) {
        if (p & 1)
            prod = (prod * x);
        x = x * x;
        p >>= 1;
    }
    return prod;
}

template <typename T>
T exp_mod(T x, unsigned int p, T m) {
    T prod = 1;
    T prev = x % m;
    while (p) {
        if (p & 1)
            prod = (prod * prev) % m;
        prev = (prev * prev) % m;
        p >>= 1;
    }
    return prod;
}

template <>
unsigned long long exp_mod(unsigned long long x, unsigned int p, unsigned long long m) {
    unsigned __int128 prod = 1;
    unsigned __int128 prev = x % m;
    while (p) {
        if (p & 1)
            prod = (prod * prev) % m;
        prev = (prev * prev) % m;
        p >>= 1;
    }
    return prod;
}

template <typename T>
T gcd(T a, T b) {
    while (b) {
        T temp = a % b;
        a = b;
        b = temp;
    }
    return a;
}

// prevx * a + prevy * b = gcd(a, b)
template <typename T>
std::tuple<T, T, T> egcd(T a, T b) {
    T prevx = 1;
    T x = 0;
    T prevy = 0;
    T y = 1;
    while (b) {
        T q = a / b;

        T temp = prevx - q * x;
        prevx = x;
        x = temp;

        temp = prevy - q * y;
        prevy = y;
        y = temp;

        temp = a % b;
        a = b;
        b = temp;
    }

    return {a, prevx, prevy};
}

// a * RET = 1 (mod p)
template <typename T>
T modular_inverse(T a, T p) {
    auto [g, q, r] = egcd(a, p);
    return q;
}


// debug tools
template <typename T>
std::ostream &operator<<(std::ostream &os, const std::vector<T> &container) {
    typename std::vector<T>::const_iterator begin = container.begin();
    typename std::vector<T>::const_iterator end = container.end();
    os << '[';
    for (typename std::vector<T>::const_iterator i = begin; i != end; ++i) {
        if (i != begin)
            os << ", ";
        os << *i;
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
        os << *i;
    }
    os << ']';
    return os;
}

template <typename T, std::size_t N>
std::ostream &operator<<(std::ostream &os, const std::array<T, N> &container) {
    os << '[';
    for (int i = 0; i < N; ++i) {
        if (i != 0)
            os << ", ";
        os << container[i];
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
std::ostream &operator<<(
    std::ostream &os, const std::unordered_map<K, V> &container) {
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
