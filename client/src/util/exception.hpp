//
// Created by Igor on 2/10/2018.
//

#ifndef TCP_CHAT_EXCEPTION_HPP
#define TCP_CHAT_EXCEPTION_HPP

#include <exception>
#include <string>

class connection_error : public std::exception {
public:
	explicit connection_error(const std::string_view &message) : message(message) { }

	virtual const char *what() const throw() override {
		return message.c_str();
	}

private:
	std::string message;
};

class packet_error : public std::exception {
public:
	explicit packet_error(const std::string_view &message) : message(message) { }

	virtual const char *what() const throw() override {
		return message.c_str();
	}

private:
	std::string message;
};

#endif //TCP_CHAT_EXCEPTION_HPP
