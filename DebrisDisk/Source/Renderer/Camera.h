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

		bool bThermal = false;

		glm::vec3 Position;

		float Az = 5.f;
		float Alt = 90.f;
		float Distance = 400.f;

		float Speed = 100.0f;
		float Sensitivity = 0.2f;

		float Intensity = 1.4f;
		float Offset = 0.0f;
		float DustContribution = 0.1f;

		glm::mat4 ProjectionMat;
		glm::mat4 ViewMat;
		glm::mat4 ViewProjectionMat;

	private:
		glm::vec3 Up = glm::vec3(0.f, 1.f, 0.f);
	};
}