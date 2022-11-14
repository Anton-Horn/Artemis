#pragma once
#include "Core\Core.h"
#include "glm\glm.hpp"

struct Camera {

public:

		glm::mat4 Projection;
		Camera() = default;
		Camera(glm::mat4 Projection) : Projection(Projection) {

		}
		Camera(const Camera&) = default;
		const glm::mat4& GetProjection() {
			return Projection;
		}

	};
