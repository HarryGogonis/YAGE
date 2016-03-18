#version 430 core
layout(location = 0) out vec4 out_color;

struct LightProperties {
	bool isEnabled;
	int type;
	vec3 ambient;
	vec3 color;
	vec3 position;
	vec3 halfVector;
	vec3 coneDirection;
	float spotCosCutoff;
	float spotExponent;
	float constantAttenuation;
	float linearAttenuation;
	float quadraticAttenuation;
};

uniform sampler2D texture_diffuse1;
uniform sampler2D texture_diffuse2;
uniform sampler2D texture_diffuse3;
uniform sampler2D texture_specular1;
uniform sampler2D texture_specular2;

uniform float texture_contributions[3];
uniform float texture_count;

// set of lights to apply, per invocation of this shader
const int MaxLights = 5; 
uniform LightProperties Lights[MaxLights];

uniform float Shininess;
uniform float Strength;
uniform vec3 EyeDirection; // camera position
uniform mat4 MVP;
uniform mat4 MV;

in vec2 UV;
in vec3 Normal;
in vec4 Position;

void main(void)
{
	vec3 scatteredLight = vec3(0.0);
	vec3 reflectedLight = vec3(0.0);

	for (int light = 0; light < MaxLights; ++light)
	{
		if (!Lights[light].isEnabled) continue; // don't use disabled lights
		
		vec3 halfVector;
		vec3 lightDirection = Lights[light].position;
		float attenuation = 1.0;
		float lightDistance = 0.0;

		if (Lights[light].type == 0 ) // Ambient Light
		{
			scatteredLight += Lights[light].ambient;
		}
		else if (Lights[light].type == 1 ) // Directional Light
		{
			halfVector = Lights[light].halfVector;
		}
		else if (Lights[light].type == 2) // Point Light
		{		
			lightDirection = lightDirection - vec3(Position);
			lightDistance = length(lightDirection); //!warning! length does expensive SQRT
			lightDirection = lightDirection / lightDistance;

			attenuation = 1.0 /
				(Lights[light].constantAttenuation
				+ Lights[light].linearAttenuation * lightDistance
				+ Lights[light].quadraticAttenuation * lightDistance * lightDistance);
			
			halfVector = normalize(lightDirection + EyeDirection);
		}
		else // Spot Light
		{ 
			lightDirection = lightDirection - vec3(Position);
			lightDistance = length(lightDirection); //!warning! length does expensive SQRT
			lightDirection = lightDirection / lightDistance;

			attenuation = 1.0 /
				(Lights[light].constantAttenuation
				+ Lights[light].linearAttenuation * lightDistance
				+ Lights[light].quadraticAttenuation * lightDistance * lightDistance);
			
			float spotCos = dot(lightDirection, -Lights[light].coneDirection);
			if (spotCos < Lights[light].spotCosCutoff)
				attenuation = 0.0;
			else 
				attenuation *= pow(spotCos, Lights[light].spotExponent);

			halfVector = normalize(lightDirection + EyeDirection);
		}

		float diffuse = max(0.0, dot(Normal, lightDirection));
		float specular = max(0.0, dot(Normal, halfVector));

		if (diffuse == 0.0)
			specular = 0.0;
		else
			specular = pow(specular, Shininess) * Strength;

		// Accumulate all the light's effects
		scatteredLight += Lights[light].ambient * attenuation + 
						  Lights[light].color * diffuse * attenuation;
		reflectedLight += Lights[light].color * specular * attenuation;
	}
	vec4 texture_color;
	if (texture_count == 1)
	{
		texture_color = texture(texture_diffuse1, UV).rgba;
	}
	else if (texture_count == 2)
	{
		texture_color =	texture(texture_diffuse1, UV).rgba * texture_contributions[0] +
						texture(texture_diffuse2, UV).rgba * texture_contributions[1];
	}
	else
	{
		texture_color =	texture(texture_diffuse1, UV).rgba * texture_contributions[0] +
						texture(texture_diffuse2, UV).rgba * texture_contributions[1] +
						texture(texture_diffuse3, UV).rgba * texture_contributions[2];
	}

	vec3 rgb = min(texture_color.rgb * scatteredLight + reflectedLight, vec3(1.0));
	out_color = vec4(rgb, texture_color.a);
}