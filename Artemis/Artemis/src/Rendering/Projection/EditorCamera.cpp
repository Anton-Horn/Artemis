
#include "EditorCamera.h"

#include <glfw/glfw3.h>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/quaternion.hpp>

#include "Core/Input.h"
#include "Core/Application.h"

namespace Athena {

	EditorCamera::EditorCamera(float fov, float aspectRatio, float nearClip, float farClip)
		: m_fov(fov), m_aspect_ratio(aspectRatio), m_near_clip(nearClip), m_far_clip(farClip), Camera(glm::perspective(glm::radians(fov), aspectRatio, nearClip, farClip))
	{
		UpdateView();
	}

	void EditorCamera::UpdateProjection()
	{
		m_aspect_ratio = m_viewport_width / m_viewport_height;
		if (m_type == ProjectionType::Perspective) {
			m_projection = glm::perspective(glm::radians(m_fov), m_aspect_ratio, m_near_clip, m_far_clip);
		}
		
		if (m_type == ProjectionType::Orthographic) {
			float left = -0.5f * m_orthographic_size * m_aspect_ratio;
			float right = 0.5f * m_orthographic_size * m_aspect_ratio;
			float top = -0.5f * m_orthographic_size;
			float bottom = 0.5f * m_orthographic_size;
			m_projection = glm::ortho(left, right, bottom, top, -m_far_clip, m_near_clip);
		}

	}

	void EditorCamera::UpdateView()
	{
		m_yaw = m_pitch = 0.0f; // Lock the camera's rotation
		if (m_type == ProjectionType::Orthographic) {
			m_view_matrix = glm::translate(glm::mat4(1.0f), m_position);
			m_view_matrix = glm::inverse(m_view_matrix);
		}

		if (m_type == ProjectionType::Perspective) {
			m_position = CalculatePosition();
			glm::quat orientation = GetOrientation();
			m_view_matrix = glm::translate(glm::mat4(1.0f), m_position) * glm::toMat4(orientation);
			m_view_matrix = glm::inverse(m_view_matrix);
		}
	}

	std::pair<float, float> EditorCamera::PanSpeed() const
	{
		float x = std::min(m_viewport_width / 1000.0f, 2.4f); // max = 2.4f
		float xFactor = 0.0366f * (x * x) - 0.1778f * x + 0.3021f;

		float y = std::min(m_viewport_height / 1000.0f, 2.4f); // max = 2.4f
		float yFactor = 0.0366f * (y * y) - 0.1778f * y + 0.3021f;

		return { xFactor, yFactor };
	}

	float EditorCamera::RotationSpeed() const
	{
		return 0.8f;
	}

	float EditorCamera::ZoomSpeed() const
	{

		if (m_type == ProjectionType::Perspective) {
			float distance = m_distance * 0.2f;
			distance = std::max(distance, 0.0f);
			float speed = distance * distance;
			speed = std::min(speed, 100.0f); // max speed = 100
			return speed;
		} 

		if (m_type == ProjectionType::Orthographic) {
			float distance = m_orthographic_size * 0.2f;
			distance = std::max(distance, 0.0f);
			float speed = distance * distance;
			speed = std::min(speed, 100.0f); // max speed = 100
			return speed;
		}
		return 0.0f;
		
	}

	glm::vec2 EditorCamera::GetOrthographicViewport() const
	{
		float aspect_ratio = m_viewport_width / m_viewport_height;
	
		float width = m_orthographic_size * aspect_ratio;
		float height = m_orthographic_size;

		return glm::vec2(width, height);

	}
	float lastvalue = 0.0f;
	void EditorCamera::OnUpdate()
	{
		lastvalue = Application::GetInput().GetMouseWheelValue();
		if (Application::GetInput().KeyPressed(KeyCode::LEFT_CONTROL))
		{
			const glm::vec2& mouse{ Application::GetInput().GetMouseX(), Application::GetInput().GetMouseY() };
			glm::vec2 delta = (mouse - m_initial_mouse_position) * 0.003f;
			m_initial_mouse_position = mouse;

			if (Application::GetInput().MouseButtonPressed(MouseCode::BUTTON_MIDDLE))
				MousePan(delta);
			else if (Application::GetInput().MouseButtonPressed(MouseCode::BUTTON_LEFT))
				MouseRotate(delta);
			else if (Application::GetInput().MouseButtonPressed(MouseCode::BUTTON_RIGHT))
				MouseZoom(delta.y);
		}

		UpdateView();
	}

	float EditorCamera::GetOrthographicSize()
	{
		return m_orthographic_size;
	}

	void EditorCamera::HandleInput()
	{
		float delta = (lastvalue - Application::GetInput().GetMouseWheelValue()) * 0.1f;
		lastvalue = Application::GetInput().GetMouseWheelValue();
		MouseZoom(delta); 
		UpdateView();
	}

	void EditorCamera::MousePan(const glm::vec2& delta)
	{
		if (m_type == ProjectionType::Perspective) {
			auto [xSpeed, ySpeed] = PanSpeed();
			m_focal_point += -GetRightDirection() * delta.x * xSpeed * m_distance;
			m_focal_point += GetUpDirection() * delta.y * ySpeed * m_distance;
		}

		if (m_type == ProjectionType::Orthographic) {
			auto [xSpeed, ySpeed] = PanSpeed();
			m_position.x += -delta.x * xSpeed * m_orthographic_size;
			m_position.y -= -delta.y * ySpeed * m_orthographic_size;
		}

	}

	void EditorCamera::MouseRotate(const glm::vec2& delta)
	{
		float yawSign = GetUpDirection().y < 0 ? -1.0f : 1.0f;
		m_yaw += yawSign * delta.x * RotationSpeed();
		m_pitch += delta.y * RotationSpeed();
	}

	void EditorCamera::MouseZoom(float delta)
	{

		if (m_type == ProjectionType::Perspective) {

			m_distance += delta * ZoomSpeed();
			if (m_distance < 1.0f)
			{
				m_focal_point += GetForwardDirection();
				m_distance = 1.0f;
			}
		}

		if (m_type == ProjectionType::Orthographic) {
			m_orthographic_size += delta * ZoomSpeed();
			if (m_orthographic_size < 1.0f)
			{				
				m_orthographic_size = 1.0f;
			}
			UpdateProjection();
		}
	}

	glm::vec3 EditorCamera::GetUpDirection() const
	{
		return glm::rotate(GetOrientation(), glm::vec3(0.0f, 1.0f, 0.0f));
	}

	glm::vec3 EditorCamera::GetRightDirection() const
	{
		return glm::rotate(GetOrientation(), glm::vec3(1.0f, 0.0f, 0.0f));
	}

	glm::vec3 EditorCamera::GetForwardDirection() const
	{
		return glm::rotate(GetOrientation(), glm::vec3(0.0f, 0.0f, -1.0f));
	}

	glm::vec3 EditorCamera::CalculatePosition() const
	{
		if (m_type == ProjectionType::Perspective) {
			return m_focal_point - GetForwardDirection() * m_distance;
		}
		return glm::vec3(0.0f);
	}

	glm::quat EditorCamera::GetOrientation() const
	{
		return glm::quat(glm::vec3(-m_pitch, -m_yaw, 0.0f));
	}

	void EditorCamera::SetViewProjection(glm::mat4 view_projection)
	{
		m_view_matrix = view_projection;
	}

}
