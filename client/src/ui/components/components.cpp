//
// Created by Igor on 2/6/2018.
//

#include "../../application.hpp"
#include "components.hpp"

ui::Components::Components(Application *app) :
		app(app) {

	HWND parent = app->getWindow().getHwnd();

	button1 = new Button(L"button1", {20, 20}, {100, 20}, parent, 1);
	button2 = new Button(L"button2", {20, 50}, {100, 20}, parent, 2);
	button3 = new Button(L"button3", {20, 80}, {100, 20}, parent, 3);
	textArea = new TextArea(L"", {0, 120}, {500, 320}, parent, 0);
	textField = new TextField(L"", {130, 20}, {100, 20}, parent, 0);
}

ui::Components::~Components() {
	delete button1;
	delete button2;
	delete button3;

	delete textArea;
	delete textField;
}

void ui::Components::input(WORD id) {
	switch (id) {
		case 1:
			textField->setText(L"Test жопа");
			break;
		case 2:
			app->getClient().sendString(textField->getText());
			break;
		case 3:
//			textArea.append(textField.getText() + L"\n");
			break;
		default:
			break;
	}
}