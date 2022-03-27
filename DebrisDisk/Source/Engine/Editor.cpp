#include "Editor.h"

#include "tracy/Tracy.hpp"

#include "ImGui/imgui.h"
#include "ImGui/backends/imgui_impl_opengl3.cpp"
#include "ImGui/backends/imgui_impl_glfw.cpp"

#include "Engine.h"

namespace DebrisDisk
{
	FEditor::FEditor(RCamera* Camera)
		: Camera(Camera)
	{
	}

	void FEditor::Init()
	{
		IMGUI_CHECKVERSION();
		ImGui::CreateContext();
		ImGuiIO& IO = ImGui::GetIO(); (void)IO;
		IO.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;

		ImGui::StyleColorsDark();

		FEngine& Engine = FEngine::GetEngine();
		GLFWwindow* Window = static_cast<GLFWwindow*>(Engine.GetWindow().GetNativeWindow());

		// Setup Platform/Renderer bindings
		ImGui_ImplGlfw_InitForOpenGL(Window, true);
		ImGui_ImplOpenGL3_Init("#version 450");
	}

	void FEditor::NewFrame()
	{
		ZoneScoped
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();
	}

	void FEditor::Update(float DeltaTime)
	{
		ZoneScoped

		ImGui::Begin("Photo Mode");
		ImGui::InputText("Save as", Filename, IM_ARRAYSIZE(Filename));
		if (ImGui::Button("Save"))
		{
			bScreenshot = true;
		}
		ImGui::End();

		ImGui::Begin("Camera");
		ImGui::InputFloat("Speed", &Camera->Speed);
		ImGui::InputFloat("Sensitivity", &Camera->Sensitivity);
		ImGui::InputFloat("Az", &Camera->Az);
		ImGui::InputFloat("Alt", &Camera->Alt);
		ImGui::InputFloat("Distance", &Camera->Distance);
		ImGui::InputFloat("Intensity", &Camera->Intensity);
		ImGui::SliderFloat("Offset", &Camera->Offset, 0.f, 0.25f);
		ImGui::SliderFloat("Dust Contribution", &Camera->DustContribution, 0.f, 1.f);

		std::string ButtonName = Camera->bThermal ? "Scattering" : "Thermal";
		ImGui::Checkbox("Thermal", &Camera->bThermal);
		bool opp = !Camera->bThermal;
		ImGui::Checkbox("Scattering", &opp);
		if (opp != !Camera->bThermal)
			Camera->bThermal = !opp;

		if (ImGui::Button("Reset"))
		{
			Camera->Alt = 0.0001f;
			Camera->Az = 0.0001f;
			Camera->Distance = 1000.f;
		}
		ImGui::End();
	}

	void FEditor::Render()
	{
		ZoneScoped

		if (bScreenshot)
		{
			FEngine::GetEngine().Screenshot(Filename);
			bScreenshot = false;
		}

		ImGuiIO& IO = ImGui::GetIO();
		FEngine& Engine = FEngine::GetEngine();
		IO.DisplaySize = ImVec2(static_cast<float>(Engine.GetWindow().Width), static_cast<float>(Engine.GetWindow().Height));

		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
		if (IO.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
		{
			ZoneScopedN("ImGuiSystem_UpdateViewports")
			GLFWwindow* BackupCurrentContext = glfwGetCurrentContext();
			ImGui::UpdatePlatformWindows();
			ImGui::RenderPlatformWindowsDefault();
			glfwMakeContextCurrent(BackupCurrentContext);
		}
	}

	void FEditor::Terminate()
	{
		ImGui_ImplOpenGL3_Shutdown();
		ImGui_ImplGlfw_Shutdown();
		ImGui::DestroyContext();
	}
}
