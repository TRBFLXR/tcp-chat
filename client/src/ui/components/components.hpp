//
// Created by Igor on 2/6/2018.
//

#ifndef TCP_CHAT_COMPONENTS_HPP
#define TCP_CHAT_COMPONENTS_HPP


#include "button.hpp"
#include "textfield.hpp"
#include "textarea.hpp"

namespace ui {

	struct Components {
		explicit Components(const HWND &parent);

		void input(WORD id);

		Button button1;
		Button button2;
		Button button3;

		TextArea textArea;

		TextField textField;

	private:
		HWND parent;
	};

}


#endif //TCP_CHAT_COMPONENTS_HPP
