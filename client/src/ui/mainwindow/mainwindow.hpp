//
// Created by Igor on 2/9/2018.
//

#ifndef TCP_CHAT_MAINWINDOW_HPP
#define TCP_CHAT_MAINWINDOW_HPP


#include "../window.hpp"

namespace ui {

	class MainWindow : public Window {
	public:
		explicit MainWindow(Application *application, const std::wstring_view &title,
		                    HINSTANCE app, unsigned width, unsigned height, int cmd);

		~MainWindow() override;

		void setupComponents() override;

	private:
		static LRESULT inputProcessor(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

	private:
		static MainWindow *windowPtr;
	};

}


#endif //TCP_CHAT_MAINWINDOW_HPP
