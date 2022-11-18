#pragma once
#include "Core\Core.h"
#include "glm\glm.hpp"

struct Camera {

public:

		glm::mat4 projection;
		Camera() = default;
		Camera(glm::mat4 projection) : projection(projection) {

		}
		Camera(const Camera&) = default;
		const glm::mat4& GetProjection() {
			return projection;
		}

	};
