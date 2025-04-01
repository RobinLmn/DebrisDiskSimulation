#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace app
{
	class camera
	{
	public:
		camera(const float fov, const float aspect_ratio, const float near_plane, const float far_plane);

	public:
		void teleport(const float distance, const float az, const float alt);
		void set_aspect_ratio(const float aspect_ratio);
		void set_settings(const float speed, const float sensitivity);
		void update(const float delta_time);

		glm::mat4 get_view_projection() const;
		glm::vec3 get_position() const;

		float get_distance() const;
		float get_altitude() const;
		float get_azimuth() const;

		float get_speed() const;
		float get_sensitivity() const;

	private:
		void increment_az(const float delta_az);
		void increment_alt(const float delta_alt);
		void increment_distance(const float delta_distance);

		void recalculate();

	private:
		float distance;
		float az;
		float alt;

		float speed;
		float sensitivity;

		float fov;
		float near_plane;
		float far_plane;
		float aspect_ratio;

		glm::mat4 projection;
		glm::mat4 view;
		glm::mat4 view_projection;

		glm::vec3 position;
		glm::vec3 up{ 0.0f, 1.0f, 0.0f };

		glm::vec2 last_mouse_position{ 0.0f };
		bool is_dirty;
	};
}