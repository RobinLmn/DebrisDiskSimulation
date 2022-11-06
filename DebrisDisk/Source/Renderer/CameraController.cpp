#include "CameraController.h"
#include "Engine/Input.h"
#include "GLFW/glfw3.h"

namespace DebrisDisk
{
	RCameraController::RCameraController(RCamera* Camera)
		: Camera(Camera), MousePosition(glm::vec2(0.0f))
	{
	}

	void RCameraController::Update(float DeltaTime)
	{
		const glm::vec2& CurrentMousePosition = FInput::GetMousePos();

		if (FInput::IsMouseButtonPressed(GLFW_MOUSE_BUTTON_2))
		{
			Camera->IncAz((CurrentMousePosition.y - MousePosition.y) * Camera->Sensitivity);
			Camera->IncAlt(-(CurrentMousePosition.x - MousePosition.x) * Camera->Sensitivity);
		}

		if (FInput::IsKeyPressed(GLFW_KEY_A))
			Camera->IncAlt(DeltaTime * Camera->Speed);
		if (FInput::IsKeyPressed(GLFW_KEY_D))
			Camera->IncAlt(-DeltaTime * Camera->Speed);

		if (FInput::IsKeyPressed(GLFW_KEY_S))
			Camera->IncAz(-DeltaTime * Camera->Speed);
		if (FInput::IsKeyPressed(GLFW_KEY_W))
			Camera->IncAz(DeltaTime * Camera->Speed);

		if (FInput::IsKeyPressed(GLFW_KEY_UP))
			Camera->Distance -= Camera->Speed * DeltaTime;
		if (FInput::IsKeyPressed(GLFW_KEY_DOWN))
			Camera->Distance += Camera->Speed * DeltaTime;

		MousePosition = CurrentMousePosition;
		Camera->Recalculate();
	}
}