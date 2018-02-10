//
// Created by Igor on 2/9/2018.
//

#ifndef TCP_CHAT_CONFIGWINDOWCOMPONENTS_HPP
#define TCP_CHAT_CONFIGWINDOWCOMPONENTS_HPP


#include "../components.hpp"

namespace ui {

	class ConfigWindowComponents : public Components {
	public:
		explicit ConfigWindowComponents(Application *app, Window *parent);

		void input(WPARAM wParam) override;

		void onCreate() override;
	};

}

#endif //TCP_CHAT_CONFIGWINDOWCOMPONENTS_HPP
