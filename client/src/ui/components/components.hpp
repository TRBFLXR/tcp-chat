//
// Created by Igor on 2/6/2018.
//

#ifndef TCP_CHAT_COMPONENTS_HPP
#define TCP_CHAT_COMPONENTS_HPP


#include "button.hpp"
#include "textfield.hpp"
#include "textarea.hpp"

class Application;

namespace ui {

	struct Components {
		explicit Components(Application * app);
		~Components();

		void input(WORD id);

		Button *button1;
		Button *button2;
		Button *button3;

		TextArea *textArea;

		TextField *textField;

	private:
		Application * app;
	};

}


#endif //TCP_CHAT_COMPONENTS_HPP
