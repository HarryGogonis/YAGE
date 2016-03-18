#pragma once

#include "GL/glew.h"
#include "GL/freeglut.h"
#include "../Rendering/IGameObject.h"
#include <vector>

/* ======== Shader Factory ============
 * Singleton to load and create multiple shaders, leaving
 * implementation jargon under wraps
 */
class Shader_Factory
{
private:
	Shader_Factory(void);
	std::string ReadShader(const std::string& filename);
	GLuint CreateShader(GLenum shaderType,
						const std::string& source,
						const std::string&  shaderName);

	static Shader_Factory* mShaderFactory;
public:
	static Shader_Factory* GetInstance();
	~Shader_Factory(void);
	const GLuint& CreateProgram(const std::string& shaderName,
					   const std::string&  VertexShaderFilename,
					   const std::string&  FragmentShaderFilename);
	const void SetTextureShader(IGameObject& model);

};