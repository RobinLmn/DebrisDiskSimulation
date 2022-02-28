#include "CameraController.h"
#include "Engine/Input.h"
#include "GLFW/glfw3.h"

namespace DebrisDisk
{
	RCameraController::RCameraController(RCamera* Camera)
		: Camera(Camera)
	{
	}

	void RCameraController::Update(float DeltaTime)
	{
		if (FInput::IsKeyPressed(GLFW_KEY_A) || FInput::IsKeyPressed(GLFW_KEY_LEFT))
			Camera->IncAz(DeltaTime * Camera->Sensitivity);
		if (FInput::IsKeyPressed(GLFW_KEY_D) || FInput::IsKeyPressed(GLFW_KEY_RIGHT))
			Camera->IncAz(-DeltaTime * Camera->Sensitivity);

		if (FInput::IsKeyPressed(GLFW_KEY_S) || FInput::IsKeyPressed(GLFW_KEY_DOWN))
			Camera->IncAlt(-DeltaTime * Camera->Sensitivity);
		if (FInput::IsKeyPressed(GLFW_KEY_W) || FInput::IsKeyPressed(GLFW_KEY_UP))
			Camera->IncAlt(DeltaTime * Camera->Sensitivity);

		if (FInput::IsKeyPressed(GLFW_KEY_SPACE))
			Camera->Distance += Camera->Speed * DeltaTime;
		if (FInput::IsKeyPressed(GLFW_KEY_LEFT_SHIFT) || FInput::IsKeyPressed(GLFW_KEY_RIGHT_SHIFT))
			Camera->Distance -= Camera->Speed * DeltaTime;

		Camera->Recalculate();
	}
}