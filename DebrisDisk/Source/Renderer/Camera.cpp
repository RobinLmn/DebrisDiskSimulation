#include "Camera.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/rotate_vector.hpp >

namespace DebrisDisk
{
	RCamera::RCamera(float Fov, float AspectRatio, float NearPlane, float FarPlane)
		: ProjectionMat(glm::perspective(glm::radians(Fov), AspectRatio, NearPlane, FarPlane))
	{
		Recalculate();
	}

	void RCamera::IncAlt(float DeltaAlt)
	{
		float newAlt = DeltaAlt + Alt;
		if (newAlt > 179.999f)
			Alt = 179.999f;
		else if (newAlt < 0.0001f)
			Alt = 0.0001f;
		else
			Alt = newAlt;

		Recalculate();
	}

	void RCamera::IncAz(float DeltAz) 
	{ 
		float newAz = DeltAz + Az;
		if (newAz > 180.f)
			Az = 180.f;
		else if (newAz < -180.f)
			Az = -180.f;
		else
			Az = newAz;

		Recalculate(); 
	}

	void RCamera::Recalculate()
	{

		float AzRad = glm::radians(Az);
		float AltRad = glm::radians(Alt);

		float x = Distance * glm::cos(AltRad) * glm::sin(AzRad);
		float y = Distance * glm::sin(AltRad) * glm::sin(AzRad);
		float z = Distance * glm::cos(AzRad);

		Position = glm::vec3(y, z, -x);

		Up = glm::rotateY(Up, Az);

		ViewMat = glm::lookAt(Position, glm::vec3(0.f), Up);
		ViewProjectionMat = ProjectionMat * ViewMat;
	}
}