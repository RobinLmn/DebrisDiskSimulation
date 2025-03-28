#include "camera.hpp"

#include <algorithm>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/rotate_vector.hpp >

#include <glfw/glfw3.h>

#include "input_manager.hpp"

namespace sim
{
	camera::camera(const float fov, const float aspect_ratio, const float near_plane, const float far_plane)
		: projection{ glm::perspective(glm::radians(fov), aspect_ratio, near_plane, far_plane) }
	{
		recalculate();
	}

	void camera::teleport(float in_distance, float in_az, float in_alt)
	{
		distance = in_distance;
		az = in_az;
		alt = in_alt;

		recalculate();
	}

	void camera::set_settings(float in_speed, float in_sensitivity)
	{
		speed = in_speed;
		sensitivity = in_sensitivity;
	}

	void camera::update(const float delta_time)
	{
		const glm::vec2 mouse_position = input_manager::get_mouse_position();

		if (input_manager::is_mouse_button_pressed(GLFW_MOUSE_BUTTON_2))
		{
			increment_az((mouse_position.y - last_mouse_position.y) * sensitivity);
			increment_alt(-(mouse_position.x - last_mouse_position.x) * sensitivity);
		}

		if (input_manager::is_key_pressed(GLFW_KEY_A))
			increment_alt(-delta_time * speed);

		if (input_manager::is_key_pressed(GLFW_KEY_D))
			increment_alt(delta_time * speed);

		if (input_manager::is_key_pressed(GLFW_KEY_S))
			increment_az(-delta_time * speed);

		if (input_manager::is_key_pressed(GLFW_KEY_W))
			increment_az(delta_time * speed);

		if (input_manager::is_key_pressed(GLFW_KEY_UP))
			distance -= delta_time * speed;

		if (input_manager::is_key_pressed(GLFW_KEY_DOWN))
			distance += delta_time * speed;

		last_mouse_position = mouse_position;
		recalculate(); // @todo: detect changes
	}

	glm::mat4 camera::get_view_projection() const
	{
		return view_projection;
	}

	glm::vec3 camera::get_position() const
	{
		return position;
	}

	void camera::increment_az(const float delta_az)
	{
		az = std::clamp(az + delta_az, 0.f, 360.f);
	}

	void camera::increment_alt(const float delta_alt)
	{
		alt = std::clamp(alt + delta_alt, 0.f, 360.f);
	}

	void camera::recalculate()
	{
		const float az_radians = glm::radians(az);
		const float alt_radians = glm::radians(alt);

		const float x = distance * glm::cos(alt_radians) * glm::sin(az_radians);
		const float y = distance * glm::sin(alt_radians) * glm::sin(az_radians);
		const float z = distance * glm::cos(az_radians);

		position = glm::vec3(y, z, -x);

		up = glm::rotateY(up, az);

		view = glm::lookAt(position, glm::vec3(0.f), up);
		view_projection = projection * view;
	}
}
