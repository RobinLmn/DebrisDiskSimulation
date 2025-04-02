#include "camera.hpp"

#include "engine/core/input.hpp"

#include <algorithm>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/rotate_vector.hpp>

#include <glfw/glfw3.h>

namespace app
{
	camera::camera(const float fov, const float aspect_ratio, const float near_plane, const float far_plane, std::function<void()>&& on_camera_moved)
		: fov{ fov }
		, aspect_ratio{ aspect_ratio }
		, near_plane{ near_plane }
		, far_plane{ far_plane }
		, is_dirty{ true }
		, projection{ glm::perspective(glm::radians(fov), aspect_ratio, near_plane, far_plane) }
		, on_camera_moved{ std::move(on_camera_moved) }
	{
	}

	void camera::set_aspect_ratio(const float aspect_ratio)
	{
		projection = glm::perspective(glm::radians(fov), aspect_ratio, near_plane, far_plane);
		is_dirty = true;
	}

	void camera::teleport(const float distance, const float az, const float alt)
	{
		this->distance = distance;
		this->az = az;
		this->alt = alt;

		is_dirty = true;
	}

	void camera::set_settings(const float speed, const float sensitivity)
	{
		this->speed = speed;
		this->sensitivity = sensitivity;
	}

	void camera::update(const float delta_time)
	{
		const glm::vec2 mouse_position = engine::input_manager::get_mouse_position();

		if (engine::input_manager::is_mouse_button_pressed(GLFW_MOUSE_BUTTON_2))
		{
			increment_alt(-(mouse_position.y - last_mouse_position.y) * sensitivity);
			increment_az((mouse_position.x - last_mouse_position.x) * sensitivity);
		}

		if (engine::input_manager::is_key_pressed(GLFW_KEY_A))
			increment_az(-delta_time * speed);

		if (engine::input_manager::is_key_pressed(GLFW_KEY_D))
			increment_az(delta_time * speed);

		if (engine::input_manager::is_key_pressed(GLFW_KEY_S))
			increment_alt(-delta_time * speed);

		if (engine::input_manager::is_key_pressed(GLFW_KEY_W))
			increment_alt(delta_time * speed);

		if (engine::input_manager::is_key_pressed(GLFW_KEY_UP))
			increment_distance(-delta_time * speed);

		if (engine::input_manager::is_key_pressed(GLFW_KEY_DOWN))
			increment_distance(delta_time * speed);

		last_mouse_position = mouse_position;

		if (is_dirty)
		{
			recalculate();
			on_camera_moved();
		}
	}

	glm::mat4 camera::get_view_projection() const
	{
		return view_projection;
	}

	glm::vec3 camera::get_position() const
	{
		return position;
	}

	float camera::get_distance() const
	{
		return distance;
	}

	float camera::get_altitude() const
	{
		return alt;
	}

	float camera::get_azimuth() const
	{
		return az;
	}

	float camera::get_speed() const
	{
		return speed;
	}

	float camera::get_sensitivity() const
	{
		return sensitivity;
	}

	void camera::increment_az(const float delta_az)
	{
		az = std::clamp(az + delta_az, 0.0f, 180.0f);
		is_dirty = true;
	}

	void camera::increment_alt(const float delta_alt)
	{
		alt = std::clamp(alt + delta_alt, -90.0f, 90.0f);
		is_dirty = true;
	}

	void camera::increment_distance(const float delta_distance)
	{
		distance += delta_distance;
		is_dirty = true;
	}

	void camera::recalculate()
	{
		const float az_radians = glm::radians(az);
		const float alt_radians = glm::radians(alt);

		const float x = distance * glm::cos(alt_radians) * glm::cos(az_radians);
		const float y = distance * glm::sin(alt_radians);
		const float z = distance * glm::cos(alt_radians) * glm::sin(az_radians);

		position = glm::vec3{ x, y, z };
		up = glm::rotateY(up, az);

		view = glm::lookAt(position, glm::vec3{ 0.0f }, up);
		view_projection = projection * view;

		is_dirty = false;
	}
}
