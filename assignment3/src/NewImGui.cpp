#include "AftrConfig.h"
#ifdef AFTR_CONFIG_USE_IMGUI

#include <filesystem>
#include "AftrImGuiIncludes.h"
#include "NewImGui.h"

#include <iostream>

using namespace Aftr;

//float GetRelativeRotateX(){}
//
//float GetRelativeRotateY(){}
//
//float GetRelativeX(){}
//
//
//float GetGlobalRotateX(){}
//
//float GetGlobalRotateY(){}
//
//float GetGlobalRotateZ(){}
//
//
//float GetTranslateX(){}
//
//float GetTranslateY(){}
//
//float GetTranslateZ(){}


NewImGui* NewImGui::New(WOGUI* parentWOGUI, float width, float height) {
	NewImGui* imgui = new NewImGui(parentWOGUI);
	imgui->onCreate(width, height);
	return imgui;
}


NewImGui::NewImGui(WOGUI* parentWOGUI) : IFace(this), WOImGuiAbstract(parentWOGUI){

}

void NewImGui::onCreate(float width, float height) {
	WOImGuiAbstract::onCreate(width, height);
}

NewImGui::~NewImGui() {}

void NewImGui::onUpdateWO() {}

void NewImGui::drawImGui_for_this_frame() {
	ImGui::Begin("Hello, world!"); 
	ImGui::Text("This is some useful text.");
	ImGui::End();
	
	this->fileDialog_update_after_ImGui_end_is_called();
}

//void NewImGui::draw_AftrImGui_Demo(NewImGui* gui) {
//	ImGui::Begin("Hello, world!");
//	ImGui::Text("This is some useful text.");
//	ImGui::End();
//}

#endif