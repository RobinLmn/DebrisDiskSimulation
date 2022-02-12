#pragma once
#include <glm/glm.hpp>

namespace DebrisDisk
{
	class RCamera
	{
	public:
		RCamera(glm::vec3 Pos, float Fov, float AspectRatio, float NearPlane, float FarPlane);

		void IncPitch(float DeltaPitch) { Pitch += DeltaPitch; Recalculate(); }
		void IncYaw(float DeltaYaw) { Yaw += DeltaYaw; Recalculate(); }
	
	private:
		void Recalculate();

	public:
		glm::mat4 ProjectionMat;
		glm::mat4 ViewMat;
		glm::mat4 ViewProjectionMat;

		glm::vec3 Position;
		glm::vec3 Up = glm::vec3(0.f, 1.f, 0.f);
		glm::vec3 Front = glm::vec3(0.f, 0.f, -1.f);

		float Speed = 500.0f;		// meters per sec
		float Sensitivity = 0.1f;	
		float Pitch = 0.f;		// degrees
		float Yaw = 90.f;			// degrees
	};
}