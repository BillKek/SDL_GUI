﻿#include <memory>
#include <string>
#include <regex>
#include <assert.h>

#include "GameApp.h"
#include "GameState.h"


#include "GUIWidget.h"
#include "GUIWindow.h"
#include "GUIRootWidget.h"
#include "GUIButton.h"
#include "GUITextBox.h"
#include "GUILayout.h"
#include "GUILabel.h"

// SGUI::Point GetFontTextSize(FontTTF& font, std::string str1, std::string str2)
// {
// 	int width, height;
// 
// 	std::string joint = str1 + str2;
// 	TTF_SizeUTF8(font.GetFontPtr(), joint.c_str(), &width, &height);
// 	return SGUI::Point{ width, height};
// }

class GUIState : public GameState
{
public:
	GUIState() {}
	~GUIState() { }

	bool Initialise() override
	{
		// Tell root Widget the screen / physical window size
		mGUI.setSize(SGUI::Point{ m_pWnd->GetWidth(), m_pWnd->GetHeight() });

		SGUI::Point winPos{ m_pWnd->GetWidth() / 3, m_pWnd->GetHeight() / 3 };
		SGUI::Point winSize{ m_pWnd->GetWidth() / 3, m_pWnd->GetHeight() / 3 };
		auto pWin = new SGUI::Window(&mGUI, winPos, winSize);
		assert(pWin);
		pWin->setLayout(new SGUI::GroupLayout());

		new SGUI::Label(pWin, "Push buttons");

		SGUI::Button* pButton{ new SGUI::Button(pWin, "World") };
		assert(pButton);
		pButton->setTooltip("Tooltip");

		SGUI::Button* pButton2{ new SGUI::Button(pWin, "HelloHelloHelloHelloEnd") };
		assert(pButton2);

		std::function<void()> f = std::bind(&GUIState::ButtonCallback, this);
		pButton2->setCallback(f);

		SGUI::TextBox* textBox{ new SGUI::TextBox(pWin, u8"みんなのにほんご") };
		textBox->setAlignment(SGUI::TextBox::Alignment::Left);
		textBox->setEditable(true);
		std::function<bool(const std::string& str)> fedit = [this](const std::string& str) { return EditCallBack(str); };
		textBox->setCallback(fedit);

		textBox= new SGUI::TextBox(pWin, "Text");
		textBox->setAlignment(SGUI::TextBox::Alignment::Center);
		textBox->setEditable(true);

		textBox= new SGUI::TextBox(pWin, "Text");
		textBox->setAlignment(SGUI::TextBox::Alignment::Right);
		textBox->setEditable(true);

		textBox = new SGUI::TextBox(pWin, "VeryVeryVeryVeryVeryLongText");
		textBox->setAlignment(SGUI::TextBox::Alignment::Right);
		textBox->setEditable(true);

		// Sets default theme and performs the layout
		mGUI.performLayout(m_pWnd->GetRenderer());

		return true; 
	};
	void Update(double dt)			override {}

	void ButtonCallback() 
	{
		
	}

	bool EditCallBack(const std::string& str)
	{
		return true;
	}

	void Render(Renderer& renderer)	override
	{
		mGUI.Render(renderer, SGUI::Point{ 0,0 });
	}

	void CleanUp() override {}

	bool OnUTFCharacter(const std::string& codepoint) override
	{
		return mGUI.keyboardCharacterEvent(codepoint);
	}

	bool OnKeyDown(SDL_Scancode scan, SDL_Keycode key) override
	{ 
		return mGUI.keyboardEvent(scan, key, true, SDL_GetModState());
	}

	bool OnKeyUp(SDL_Scancode scan, SDL_Keycode key) override
	{ 
		return mGUI.keyboardEvent(scan, key, false, SDL_GetModState());
	}

	bool OnLButtonDown(int mX, int mY) override
	{ 
		return mGUI.mouseButtonEvent(SGUI::Point(mX, mY), SGUI::MouseBut::LEFT, true, SDL_GetModState());
	}
	bool OnLButtonUp(int mX, int mY) override 
	{ 
		return mGUI.mouseButtonEvent(SGUI::Point(mX, mY), SGUI::MouseBut::LEFT, false, SDL_GetModState());
	}
	bool OnMouseMove(int mX, int mY, int relX, int relY, bool Left, bool Right, bool Middle) override 
	{ 
		return mGUI.mouseMotionEvent(SGUI::Point(mX, mY), SGUI::Point(relX, relY), SGUI::MouseButStatus(Left, Middle, Right), SDL_GetModState());
	}

private:
	SGUI::RootWidget mGUI; // Root widget that stores the whole of this scenes GUI
};



int main(int argc, char *argv[])
{
	WindowCreationParams createParam;

	GameApp app("GUI Dev App");
	app.Register<GUIState>("GUISTATE");

	return app.Execute(createParam, "GUISTATE");
}
