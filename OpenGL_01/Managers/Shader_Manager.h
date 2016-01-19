#pragma once

#include "GL/glew.h"
#include "GL/freeglut.h"
#include <iostream>
#include <map>

/* ======== Shader Manager ============
 * load and create multiple shaders
 * reference specific shaders
 * delete shaders when they are done
 */
class Shader_Manager
{
private:
	std::string ReadShader(const std::string& filename);
	GLuint CreateShader(GLenum shaderType,
						const std::string& source,
						const std::string&  shaderName);
	static std::map<std::string, GLuint> programs;

public:

	Shader_Manager(void);
	~Shader_Manager(void);
	void CreateProgram(const std::string& shaderName,
					   const std::string&  VertexShaderFilename,
					   const std::string&  FragmentShaderFilename);
	static const GLuint GetShader(const std::string&);
	static const void DeleteShader(const std::string&);

};