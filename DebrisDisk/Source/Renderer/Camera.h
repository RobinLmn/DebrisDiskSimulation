#pragma once
#include <glm/glm.hpp>

namespace DebrisDisk
{
	class RCamera
	{
	public:
		RCamera(float Fov, float AspectRatio, float NearPlane, float FarPlane);

		void IncAlt(float DeltaAlt);
		void IncAz(float DeltaAz);
	
		void Recalculate();

	public:
		glm::vec3 Position;

		float Az = 0.f;
		float Alt = 0.0001f;
		float Distance = 1000.f;

		float Speed = 100.0f;
		float Sensitivity = 100.0f;

		glm::mat4 ProjectionMat;
		glm::mat4 ViewMat;
		glm::mat4 ViewProjectionMat;

	private:
		glm::vec3 Up = glm::vec3(0.f, 1.f, 0.f);
	};
}