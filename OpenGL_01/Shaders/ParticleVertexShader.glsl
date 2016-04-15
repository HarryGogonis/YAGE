# version 440 core

// Input vertex data
layout(location = 0) in vec3 vertices;
layout(location = 1) in vec4 center;
layout(location = 2) in vec4 color;

// Output data interpolated
out vec2 UV;
out vec4 particleColor;

uniform vec3 CameraRight;
uniform vec3 CameraUp;
uniform mat4 MVP; 

void main()
{
	float particleSize = center.w; // we encoded it this way
	vec3 particleCenter = center.xyz;
	
	vec3 vertexPosition =
		particleCenter +
		CameraRight * vertices.x * particleSize +
		CameraUp * vertices.y * particleSize;

	gl_Position = MVP * vec4(vertexPosition, 1.0f);

	UV = vertices.xy + vec2(0.5, 0.5);
	particleColor = color;
}