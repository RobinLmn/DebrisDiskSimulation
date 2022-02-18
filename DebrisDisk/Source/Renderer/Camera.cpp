#include "Camera.h"
#include <glm/gtc/matrix_transform.hpp>

namespace DebrisDisk
{
	RCamera::RCamera(glm::vec3 Pos, float Fov, float AspectRatio, float NearPlane, float FarPlane)
		: Position(Pos), ProjectionMat(glm::perspective(glm::radians(Fov), AspectRatio, NearPlane, FarPlane))
	{
		ViewMat = glm::lookAt(Position, Position + Front, Up);
		ViewProjectionMat = ProjectionMat * ViewMat;
	}

	void RCamera::IncPitch(float DeltaPitch)
	{
		Pitch += DeltaPitch;
		if (Pitch > 89.f) Pitch = 89.f;
		if (Pitch < -89.f) Pitch = -89.f;
		Recalculate();
	}

	void RCamera::IncYaw(float DeltaYaw) 
	{ 
		Yaw += DeltaYaw; 
		Recalculate(); 
	}

	void RCamera::Recalculate()
	{
		float YawRad = glm::radians(Yaw);
		float PitchRad = glm::radians(Pitch);

		Front.x = cos(YawRad) * cos(PitchRad);
		Front.y = sin(PitchRad);
		Front.z = sin(YawRad) * cos(PitchRad);
		Front = glm::normalize(Front);

		ViewMat = glm::lookAt(Position, Position + Front, Up);
		ViewProjectionMat = ProjectionMat * ViewMat;
	}
}