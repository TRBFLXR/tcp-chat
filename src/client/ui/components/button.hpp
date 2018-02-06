//
// Created by Igor on 2/6/2018.
//

#ifndef TCP_CHAT_BUTTON_HPP
#define TCP_CHAT_BUTTON_HPP


#include <string>
#include <functional>

#include "component.hpp"
#include "../../util/types.hpp"

namespace ui {

	class Button : public Component {
	public:
		explicit Button(std::function<void(void)> function,
		                const std::wstring_view &caption,
		                const vec2u &pos, const vec2u &size,
		                const HWND &parent, WORD id);

		void handleEvent(Event &event) override;

	private:
		std::wstring caption;

		std::function<void(void)> function;
	};

}

#endif //TCP_CHAT_BUTTON_HPP
