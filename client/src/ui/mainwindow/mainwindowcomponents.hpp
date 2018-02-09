//
// Created by Igor on 2/9/2018.
//

#ifndef TCP_CHAT_MAINWINDOWCOMPONENTS_HPP
#define TCP_CHAT_MAINWINDOWCOMPONENTS_HPP


#include "../components.hpp"
#include "../components/button.hpp"
#include "../components/textarea.hpp"
#include "../components/textfield.hpp"

namespace ui {

	struct MainWindowComponents : public Components {
		explicit MainWindowComponents(Application *app);

		void input(WORD id) override;
	};

}


#endif //TCP_CHAT_MAINWINDOWCOMPONENTS_HPP
