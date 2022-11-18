#pragma once

#include "Camera.h"
#include <glm/glm.hpp>
#include <tuple>

namespace Athena {

	enum class ProjectionType {
		Orthographic,
		Perspective
	};

	class EditorCamera : public Camera
	{
	public:
		EditorCamera() = default;
		EditorCamera(float fov, float aspectRatio, float nearClip, float farClip);

		void OnUpdate();

		inline float GetDistance() const { return m_distance; }
		inline void SetDistance(float distance) { m_distance = distance; }

		inline void SetViewportSize(float width, float height) { m_viewport_width = width; m_viewport_height = height; UpdateProjection(); }

		ProjectionType GetProjectionType() {
			return m_type;
		}
		const glm::mat4& GetViewMatrix() const { return m_view_matrix; }
		glm::mat4 GetViewProjection() const { return m_projection * m_view_matrix; }

		glm::vec3 GetUpDirection() const;
		glm::vec3 GetRightDirection() const;
		glm::vec3 GetForwardDirection() const;
		const glm::vec3& GetPosition() const { return m_position; }
		glm::quat GetOrientation() const;

		void SetViewProjection(glm::mat4 view_projection);

		glm::vec2 GetOrthographicViewport() const;

		float GetPitch() const { return m_pitch; }
		float GetYaw() const { return m_yaw; }

		float GetOrthographicSize();

		void HandleInput();

	private:
		void UpdateProjection();
		void UpdateView();

		void MousePan(const glm::vec2& delta);
		void MouseRotate(const glm::vec2& delta);
		void MouseZoom(float delta);

		glm::vec3 CalculatePosition() const;

		std::pair<float, float> PanSpeed() const;
		float RotationSpeed() const;
		float ZoomSpeed() const;

	private:
		float m_fov = 45.0f, m_aspect_ratio = 1.778f, m_near_clip = 0.1f, m_far_clip = 1000.0f;
		float m_orthographic_size = 10.0f;

		ProjectionType m_type = ProjectionType::Orthographic;

		glm::mat4 m_view_matrix;
		glm::vec3 m_position = { 0.0f, 0.0f, 0.0f };
		glm::vec3 m_focal_point = { 0.0f, 0.0f, 0.0f };

		glm::mat4 m_projection;

		glm::vec2 m_initial_mouse_position = { 0.0f, 0.0f };

		float m_distance = 10.0f;
		float m_pitch = 3.1415f, m_yaw = 0.0f;

		float m_viewport_width = 1600, m_viewport_height = 900;
	};

}

