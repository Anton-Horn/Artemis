
#include "EditorCamera.h"

#include <glfw/glfw3.h>

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/quaternion.hpp>

#include "Core/Input.h"

namespace Athena {

	EditorCamera::EditorCamera(float fov, float aspectRatio, float nearClip, float farClip)
		: m_FOV(fov), m_AspectRatio(aspectRatio), m_NearClip(nearClip), m_FarClip(farClip), Camera(glm::perspective(glm::radians(fov), aspectRatio, nearClip, farClip))
	{
		UpdateView();
	}

	void EditorCamera::UpdateProjection()
	{
		m_AspectRatio = m_ViewportWidth / m_ViewportHeight;
		if (m_Type == ProjectionType::Perspective) {
			Projection = glm::perspective(glm::radians(m_FOV), m_AspectRatio, m_NearClip, m_FarClip);
		}
		
		if (m_Type == ProjectionType::Orthographic) {
			float left = -0.5f * m_OrthographicSize * m_AspectRatio;
			float right = 0.5f * m_OrthographicSize * m_AspectRatio;
			float top = -0.5f * m_OrthographicSize;
			float bottom = 0.5f * m_OrthographicSize;
			Projection = glm::ortho(left, right, bottom, top, -m_FarClip, m_NearClip);
		}

	}

	void EditorCamera::UpdateView()
	{
		m_Yaw = m_Pitch = 0.0f; // Lock the camera's rotation
		if (m_Type == ProjectionType::Orthographic) {
			m_ViewMatrix = glm::translate(glm::mat4(1.0f), m_Position);
			m_ViewMatrix = glm::inverse(m_ViewMatrix);
		}

		if (m_Type == ProjectionType::Perspective) {
			m_Position = CalculatePosition();
			glm::quat orientation = GetOrientation();
			m_ViewMatrix = glm::translate(glm::mat4(1.0f), m_Position) * glm::toMat4(orientation);
			m_ViewMatrix = glm::inverse(m_ViewMatrix);
		}
	}

	std::pair<float, float> EditorCamera::PanSpeed() const
	{
		float x = std::min(m_ViewportWidth / 1000.0f, 2.4f); // max = 2.4f
		float xFactor = 0.0366f * (x * x) - 0.1778f * x + 0.3021f;

		float y = std::min(m_ViewportHeight / 1000.0f, 2.4f); // max = 2.4f
		float yFactor = 0.0366f * (y * y) - 0.1778f * y + 0.3021f;

		return { xFactor, yFactor };
	}

	float EditorCamera::RotationSpeed() const
	{
		return 0.8f;
	}

	float EditorCamera::ZoomSpeed() const
	{

		if (m_Type == ProjectionType::Perspective) {
			float distance = m_Distance * 0.2f;
			distance = std::max(distance, 0.0f);
			float speed = distance * distance;
			speed = std::min(speed, 100.0f); // max speed = 100
			return speed;
		} 

		if (m_Type == ProjectionType::Orthographic) {
			float distance = m_OrthographicSize * 0.2f;
			distance = std::max(distance, 0.0f);
			float speed = distance * distance;
			speed = std::min(speed, 100.0f); // max speed = 100
			return speed;
		}
		return 0.0f;
		
	}

	glm::vec2 EditorCamera::GetOrthographicViewport() const
	{
		float aspect_ratio = m_ViewportWidth / m_ViewportHeight;
	
		float width = m_OrthographicSize * aspect_ratio;
		float height = m_OrthographicSize;

		return glm::vec2(width, height);

	}
	float lastvalue = 0.0f;
	void EditorCamera::OnUpdate()
	{
		lastvalue = Input::GetMouseWheelValue();
		if (Input::KeyPressed(KeyCode::LEFT_CONTROL))
		{
			const glm::vec2& mouse{ Input::GetMouseX(), Input::GetMouseY() };
			glm::vec2 delta = (mouse - m_InitialMousePosition) * 0.003f;
			m_InitialMousePosition = mouse;

			if (Input::MouseButtonPressed(MouseCode::BUTTON_MIDDLE))
				MousePan(delta);
			else if (Input::MouseButtonPressed(MouseCode::BUTTON_LEFT))
				MouseRotate(delta);
			else if (Input::MouseButtonPressed(MouseCode::BUTTON_RIGHT))
				MouseZoom(delta.y);
		}

		UpdateView();
	}

	float EditorCamera::GetOrthographicSize()
	{
		return m_OrthographicSize;
	}

	void EditorCamera::HandleInput()
	{
		float delta = (lastvalue - Input::GetMouseWheelValue()) * 0.1f;
		lastvalue = Input::GetMouseWheelValue();
		MouseZoom(delta); 
		UpdateView();
	}

	void EditorCamera::MousePan(const glm::vec2& delta)
	{
		if (m_Type == ProjectionType::Perspective) {
			auto [xSpeed, ySpeed] = PanSpeed();
			m_FocalPoint += -GetRightDirection() * delta.x * xSpeed * m_Distance;
			m_FocalPoint += GetUpDirection() * delta.y * ySpeed * m_Distance;
		}

		if (m_Type == ProjectionType::Orthographic) {
			auto [xSpeed, ySpeed] = PanSpeed();
			m_Position.x += -delta.x * xSpeed * m_OrthographicSize;
			m_Position.y -= -delta.y * ySpeed * m_OrthographicSize;
		}

	}

	void EditorCamera::MouseRotate(const glm::vec2& delta)
	{
		float yawSign = GetUpDirection().y < 0 ? -1.0f : 1.0f;
		m_Yaw += yawSign * delta.x * RotationSpeed();
		m_Pitch += delta.y * RotationSpeed();
	}

	void EditorCamera::MouseZoom(float delta)
	{

		if (m_Type == ProjectionType::Perspective) {

			m_Distance += delta * ZoomSpeed();
			if (m_Distance < 1.0f)
			{
				m_FocalPoint += GetForwardDirection();
				m_Distance = 1.0f;
			}
		}

		if (m_Type == ProjectionType::Orthographic) {
			m_OrthographicSize += delta * ZoomSpeed();
			if (m_OrthographicSize < 1.0f)
			{				
				m_OrthographicSize = 1.0f;
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
		if (m_Type == ProjectionType::Perspective) {
			return m_FocalPoint - GetForwardDirection() * m_Distance;
		}
		return glm::vec3(0.0f);
	}

	glm::quat EditorCamera::GetOrientation() const
	{
		return glm::quat(glm::vec3(-m_Pitch, -m_Yaw, 0.0f));
	}

	void EditorCamera::SetViewProjection(glm::mat4 view_projection)
	{
		m_ViewMatrix = view_projection;
	}

}
