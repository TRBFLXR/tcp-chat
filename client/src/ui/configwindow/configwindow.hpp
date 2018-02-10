//
// Created by Igor on 2/9/2018.
//

#ifndef TCP_CHAT_CONFIGWINDOW_HPP
#define TCP_CHAT_CONFIGWINDOW_HPP


#include "../window.hpp"

namespace ui {

	class ConfigWindow : public Window {
	public:
		explicit ConfigWindow(Application *application, const std::wstring_view &title,
		                      HINSTANCE app, unsigned width, unsigned height, int cmd);

		~ConfigWindow() override;

		void setupComponents() override;


	private:
		static LRESULT inputProcessor(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

	private:
		friend class ConfigWindowComponents;

		static ConfigWindow *windowPtr;
	};

}


#endif //TCP_CHAT_CONFIGWINDOW_HPP
