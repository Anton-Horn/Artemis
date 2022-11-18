#include "Shader.h"

#include <fstream>

#include "Rendering/OpenGL/OpenGLShader.h"

#include "Core/Log.h"
#include "Core/Debug_Test.h"

std::string Shader::LoadShaderSource(const std::filesystem::path& path)
{
	std::string content;

	std::ifstream in(path.string());

	if (in.is_open()) {

		std::string line;

		while (std::getline(in, line)) {
			content += line + "\n";
		}
		in.close();

	}
	else {
		ART_ABORT("Invalid path to load a shader! path: {0}", path.string().c_str());
	}
	return content;
}

Shader* Shader::Create(const std::string& VertexSource, const std::string& FragmentSource, RenderingAPI api)
{

	if (api == RenderingAPI::OpenGL) {
		return new OpenGLShader(VertexSource, FragmentSource);
	}
	return nullptr;

}


