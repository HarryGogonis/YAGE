#version 430 core
layout(location = 0) in vec3 in_position;
layout(location = 1) in vec2 in_texture;
layout(location = 2) in vec3 in_normal;
layout(location = 3) in vec3 in_tangent;
layout(location = 4) in vec3 in_bitangent;

out vec2 UV;
out mat3 TBN;
out vec4 Position;
out vec3 EyeDirection;
out vec4 ShadowCoord; 

//TODO refactor to
/* out VS_FS_INTERFACE
{
	vec4 shadow_coord;
	vec3 world_coord; // position
	vec3 eye_coord;
	vec3 normal
} vertex; */

uniform mat4 MVP;
uniform mat4 MV;
uniform mat4 TransformMatrix; //TODO Refactor to Transform
uniform mat4 DepthMVP;
uniform mat3 ScaleConst;

void main(void)
{
	UV = in_texture;
	
	// TODO refactor out?
	mat3 MV3 = mat3(MV);
	vec3 t = normalize(in_tangent);
	vec3 b = normalize(in_bitangent);
	vec3 n = normalize(in_normal);
	TBN = transpose(mat3(t, b, n));

	Position = TransformMatrix * vec4(in_position, 1);
	
	EyeDirection = normalize(TBN * vec3(MV * Position));

	ShadowCoord = DepthMVP * Position;

	gl_Position = MVP * Position;
}