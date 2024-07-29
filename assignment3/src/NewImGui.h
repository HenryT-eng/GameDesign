#pragma once

#include "AftrConfig.h"
#ifdef AFTR_CONFIG_USE_IMGUI

#include "WOImGuiAbstract.h"
#include <functional>

namespace Aftr
{
	class NewImGui : public WOImGuiAbstract {

	public:

		static NewImGui* New(WOGUI* parentWOGUI = nullptr, float width = 1.0f, float height = 1.0f);
		virtual ~NewImGui();

		virtual void drawImGui_for_this_frame();
		virtual void onUpdateWO() override;

		//static void draw_AftrImGui_Demo(NewImGui* gui);

		/*float GetRelativeRotateX();
		float GetRelativeRotateY();
		float GetRelativeX();

		float GetGlobalRotateX();
		float GetGlobalRotateY();
		float GetGlobalRotateZ();

		float GetTranslateX();
		float GetTranslateY();
		float GetTranslateZ();*/

	protected:

		virtual void onCreate(float width, float height) override;
		NewImGui(WOGUI* parentWOGUI);
	};

}

#endif