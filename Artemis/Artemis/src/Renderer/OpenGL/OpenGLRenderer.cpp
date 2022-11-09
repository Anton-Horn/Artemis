#include "OpenGLRenderer.h"	

#include "glad/glad.h"

#include "Core/Debug_Test.h"

void OpenGLRenderer::Create()
{

	ART_ASSERT(gladLoadGL());

}
