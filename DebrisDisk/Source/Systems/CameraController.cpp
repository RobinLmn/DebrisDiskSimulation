#include "CameraController.h"
#include "Engine/Input.h"
#include "GLFW/glfw3.h"

namespace DebrisDisk
{
	SCameraController::SCameraController(RCamera* Camera)
		: Camera(Camera), MousePosition(glm::vec3(0.f))
	{
	}

	void SCameraController::Update(float DeltaTime)
	{
		if (FInput::IsKeyPressed(GLFW_KEY_A) || FInput::IsKeyPressed(GLFW_KEY_LEFT))
			Camera->Position -= glm::normalize(glm::cross(Camera->Front, Camera->Up)) * Camera->Speed * DeltaTime;
		if (FInput::IsKeyPressed(GLFW_KEY_D) || FInput::IsKeyPressed(GLFW_KEY_RIGHT))
			Camera->Position += glm::normalize(glm::cross(Camera->Front, Camera->Up)) * Camera->Speed * DeltaTime;
		if (FInput::IsKeyPressed(GLFW_KEY_S) || FInput::IsKeyPressed(GLFW_KEY_DOWN))
			Camera->Position -= Camera->Speed * Camera->Front * DeltaTime;
		if (FInput::IsKeyPressed(GLFW_KEY_W) || FInput::IsKeyPressed(GLFW_KEY_UP))
			Camera->Position += Camera->Speed * Camera->Front * DeltaTime;
		if (FInput::IsKeyPressed(GLFW_KEY_SPACE))
			Camera->Position += Camera->Speed * Camera->Up * DeltaTime;
		if (FInput::IsKeyPressed(GLFW_KEY_LEFT_SHIFT) || FInput::IsKeyPressed(GLFW_KEY_RIGHT_SHIFT))
			Camera->Position -= Camera->Speed * Camera->Up * DeltaTime;

		if (FInput::IsMouseButtonPressed(GLFW_MOUSE_BUTTON_2))
		{
			Camera->IncYaw((FInput::GetMousePos().x - MousePosition.x) * Camera->Sensitivity);
			Camera->IncPitch((MousePosition.y - FInput::GetMousePos().y) * Camera->Sensitivity);
		}

		MousePosition = FInput::GetMousePos();
	}
}