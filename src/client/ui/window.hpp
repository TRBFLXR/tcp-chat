//
// Created by Igor on 2/6/2018.
//

#ifndef TCP_CHAT_WINDOW_HPP
#define TCP_CHAT_WINDOW_HPP


#include <string>
#include <windows.h>

#include "components/components.hpp"

namespace ui {

	class Window final {
	public:
		explicit Window(const std::wstring_view &title, HINSTANCE app, unsigned width, unsigned height, int cmd);
		~Window();

		inline const HWND &getHwnd() const { return hwnd; }
		inline const std::wstring &getTitle() const { return title; }

		void setTitle(const std::wstring_view &title);

	private:
		static LRESULT CALLBACK inputProcessor(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

	private:
		static Window *windowPtr;

		HWND hwnd;
		WNDCLASSEXW wc;

		Components *components;

		std::wstring title;
	};

}


#endif //TCP_CHAT_WINDOW_HPP
