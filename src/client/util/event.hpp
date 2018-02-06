//
// Created by Igor on 2/6/2018.
//

#ifndef TCP_CHAT_EVENT_HPP
#define TCP_CHAT_EVENT_HPP


#include <mapinls.h>

class Event {
public:
	explicit Event(WORD id) : id(id), handled_(false) { };

	inline void consume() { handled_ = true; }
	inline void handled(bool handled) { handled_ = handled; }

	inline bool isHandled() const { return handled_; }
	inline WORD getId() const { return id; }

private:
	WORD id;
	bool handled_;
};


#endif //TCP_CHAT_EVENT_HPP
