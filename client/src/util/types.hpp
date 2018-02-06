//
// Created by Igor on 2/6/2018.
//

#ifndef TCP_CHAT_TYPES_HPP
#define TCP_CHAT_TYPES_HPP

template<typename T>
struct vec2_t {
	vec2_t(T x, T y) : x(x), y(y) { }

	T x;
	T y;
};

typedef vec2_t<unsigned> vec2u;

#endif //TCP_CHAT_TYPES_HPP
