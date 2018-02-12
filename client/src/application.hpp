//
// Created by Igor on 2/7/2018.
//

#ifndef TCP_CHAT_APPLICATION_HPP
#define TCP_CHAT_APPLICATION_HPP

#include <packetstructure.hpp>
#include "client.hpp"
#include "ui/mainwindow/mainwindow.hpp"
#include "ui/configwindow/configwindow.hpp"
#include "config.hpp"

class Application {
public:
	explicit Application(const std::wstring_view &title, HINSTANCE app, unsigned width, unsigned height, int cmd);
	~Application();

	int run();

	void showConfigWindow();

	inline bool shouldClose() const { return shouldExit; }
	inline void shouldClose(bool close) { shouldExit = close; }

	inline void showLostConnection(bool show) { showLostConnectionMsg = show; }

	inline const ui::MainWindow &getMainWindow() const { return window; }
	inline Client *getClient() { return client; }

	inline const HINSTANCE &getHinstance() const { return hInstance; }

	static void handleUserConnect(const std::wstring &name);
	static void handleUserDisconnect(const std::wstring &name);
	static void handleChatMessage(const std::wstring &sender, const std::wstring &message);
	static void handleClientException(const std::exception &ex);
	static void handleLostConnection();

private:
	static Application *appPtr;

	MSG msg;
	HINSTANCE hInstance;

	bool shouldExit;
	bool showLostConnectionMsg;

	Config config;
	Client *client;
	ui::MainWindow window;
	ui::ConfigWindow configWindow;
};


#endif //TCP_CHAT_APPLICATION_HPP
