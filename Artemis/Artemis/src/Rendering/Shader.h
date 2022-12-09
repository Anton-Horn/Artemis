#pragma once

#include "Core/Core.h"
#include <string>

#include <filesystem>

#include <unordered_map>

enum class UniformDataType {

	Int,
	Int2,
	Int3, 
	Int4,
	UInt,
	UInt2,
	UInt3,
	UInt4,
	Float,
	Float2,
	Float3,
	Float4,
	Mat4,

};

struct Uniform {
	std::string name;
	UniformDataType type;
	uint32_t uniform_location;
};


struct ShaderSpecification {

	std::unordered_map<std::string, Uniform> uniforms;
	std::filesystem::path fragment_path;
	std::filesystem::path vertex_path;

	ShaderSpecification() = default;

};

class Shader
{
	
public:

	Shader() = default;
	virtual ~Shader() = default;

	virtual void Bind() const = 0;
	virtual void UnBind() const = 0;

	template<typename T>
	void SetUniform(std::string_view name, const T& value) {

		ART_ASSERT_S(m_spec.uniforms.find(name) != m_spec.uniforms.end);

		Uniform& uniform = m_spec.uniforms.at(name);
		switch (uniform.type) {

		case UniformDataType::Float:
			break;
		case UniformDataType::Float2:
			break;
		case UniformDataType::Float3:
			break;
		case UniformDataType::Float4:
			break;
		case UniformDataType::Int:
			break;
		case UniformDataType::Int2:
			break;
		case UniformDataType::Int3:
			break;
		case UniformDataType::Int4:
			break;
		case UniformDataType::Mat4:
			break;
		case UniformDataType::UInt:
			break;
		case UniformDataType::UInt2:
			break;
		case UniformDataType::UInt3:
			break;
		case UniformDataType::UInt4:
			break;

		}

	}

	static std::shared_ptr<Shader> Create(const ShaderSpecification& spec, RenderingAPI api);

private:

protected:	

	virtual void SetUniformImpl(std::string_view name, const void* const data_ptr);

	static std::string LoadShaderSource(const std::filesystem::path& path);
	ShaderSpecification m_spec;
};



