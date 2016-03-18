#include "Shader_Factory.h" 
#include<iostream>
#include<fstream>
#include<vector>

// static instance for the singleton
Shader_Factory *Shader_Factory::mShaderFactory;

// static int that names the programs
static int inc = 0;

// constructor
Shader_Factory::Shader_Factory(void)
{
}

Shader_Factory* Shader_Factory::GetInstance()
{
	if (mShaderFactory == nullptr)
	{
		mShaderFactory = new Shader_Factory();
	}
	return mShaderFactory;
}

Shader_Factory::~Shader_Factory(void)
{
	// Leave program deletion to each model (Scene_Container)
}

// Reads shader from file system into memory
std::string Shader_Factory::ReadShader(const std::string& filename)
{

	std::string shaderCode;
	std::ifstream file(filename.c_str(), std::ios::in);

	if (!file.good())
	{
		std::cout << "Can't read file " << filename.c_str() << std::endl;
		std::terminate();
	}

	file.seekg(0, std::ios::end);
	shaderCode.resize((unsigned int)file.tellg());
	file.seekg(0, std::ios::beg);
	file.read(&shaderCode[0], shaderCode.size());
	file.close();
	return shaderCode;
}

// Compile Shader
GLuint Shader_Factory::CreateShader(GLenum shaderType,
								   const std::string& source,
								   const std::string& shaderName)
{
	std::cout << "compiling shader: " << shaderName.c_str() << std::endl;

	int compile_result = 0;

	GLuint shader = glCreateShader(shaderType);
	const char *shader_code_ptr = source.c_str();
	const int shader_code_size = source.size();

	glShaderSource(shader, 1, &shader_code_ptr, &shader_code_size);
	glCompileShader(shader);
	glGetShaderiv(shader, GL_COMPILE_STATUS, &compile_result);

	//check for errors
	if (compile_result == GL_FALSE)
	{

		int info_log_length = 0;
		glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &info_log_length);
		std::vector<char> shader_log(info_log_length);
		glGetShaderInfoLog(shader, info_log_length, NULL, &shader_log[0]);
		std::cout << "ERROR compiling shader: " << shaderName.c_str() << std::endl << &shader_log[0] << std::endl;
		return 0;
	}
	return shader;
}

// Entry method. Compiles and links shaders into program
const GLuint& Shader_Factory::CreateProgram(const std::string& shaderName,
								   const std::string& vertexShaderFilename,
								   const std::string& fragmentShaderFilename)
{

	//read the shader files and save the code
	std::string vertex_shader_code = ReadShader(vertexShaderFilename);
	std::string fragment_shader_code = ReadShader(fragmentShaderFilename);

	GLuint vertex_shader = CreateShader(GL_VERTEX_SHADER, vertex_shader_code, "vertex shader");
	GLuint fragment_shader = CreateShader(GL_FRAGMENT_SHADER, fragment_shader_code, "fragment shader");

	int link_result = 0;
	//create the program handle, attatch the shaders and link it
	GLuint program = glCreateProgram();
	glAttachShader(program, vertex_shader);
	glAttachShader(program, fragment_shader);

	glLinkProgram(program);
	glGetProgramiv(program, GL_LINK_STATUS, &link_result);
	//check for link errors
	if (link_result == GL_FALSE)
	{

		int info_log_length = 0;
		glGetProgramiv(program, GL_INFO_LOG_LENGTH, &info_log_length);
		std::vector<char> program_log(info_log_length);
		glGetProgramInfoLog(program, info_log_length, NULL, &program_log[0]);
		std::cout << "Shader Loader : LINK ERROR" << std::endl << &program_log[0] << std::endl;
		return 0;
	}

	return program;
}

const void Shader_Factory::SetTextureShader(IGameObject& model)
{
	std::string name = "textureShader" + ++inc;
	GLuint program = CreateProgram(name,
		"Shaders\\TextureVertexShader.glsl",
		"Shaders\\TextureFragmentShader.glsl");
	model.SetProgram(program);
}