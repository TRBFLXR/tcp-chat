//
// Created by Igor on 2/6/2018.
//

#ifndef TCP_CHAT_WINDOW_HPP
#define TCP_CHAT_WINDOW_HPP


#include <string>
#include <windows.h>
#include "components/component.hpp"
#include "components.hpp"

namespace ui {

	class Window {
	public:
		explicit Window(Application *application, const std::wstring_view &title);

		virtual ~Window();

		virtual void setupComponents() = 0;

		inline const HWND &getHwnd() const { return hwnd; }
		inline const std::wstring &getTitle() const { return title; }
		Component &get(const std::string_view &componentName) { return components->get(componentName); }

		void setTitle(const std::wstring_view &title);
		void setShowCommand(int cmd) const;

	protected:
		Application *application;
		Components *components;

		HWND hwnd;
		WNDCLASSEXW wc;

		std::wstring title;
	};

}


#endif //TCP_CHAT_WINDOW_HPP
