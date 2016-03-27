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

uniform sampler2D texture_diffuse;
uniform sampler2D texture_normal;
uniform sampler2D texture_specular;

// set of lights to apply, per invocation of this shader
const int MaxLights = 5; 
uniform LightProperties Lights[MaxLights];

uniform float Shininess;
uniform float Strength;
uniform mat4 MVP;
uniform mat4 MV;

in vec2 UV;
in vec4 Position;
in mat3 TBN;
in vec3 EyeDirection;

void main(void)
{
	vec3 scatteredLight = vec3(0.0);
	vec3 reflectedLight = vec3(0.0);

	vec3 Normal = normalize(texture(texture_normal, UV).rgb * 2.0 - vec3(1.0));

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
			lightDirection = TBN * (lightDirection - vec3(Position));
			lightDistance = length(lightDirection); //!warning! length does expensive SQRT
			lightDirection = normalize(lightDirection);

			attenuation = 1.0 /
				(Lights[light].constantAttenuation
				+ Lights[light].linearAttenuation * lightDistance
				+ Lights[light].quadraticAttenuation * lightDistance * lightDistance);
			
			halfVector = normalize(lightDirection + EyeDirection);
			//halfVector = reflect(-lightDirection, Normal);
		}
		else // Spot Light
		{ 
			// TODO Implement
		}

		float diffuseCoefficient = clamp(dot(Normal, lightDirection), 0, 1);
		float specularCoefficient = max(0.0, dot(EyeDirection, halfVector));
		//float specularCoefficient = max(0.0, dot(EyeDirection, halfVector));

		if (diffuseCoefficient == 0.0)
			specularCoefficient = 0.0;
		else
			specularCoefficient = pow(specularCoefficient , Shininess);

		// Accumulate all the light's effects
		scatteredLight += Lights[light].ambient * attenuation + 
						  Lights[light].color * diffuseCoefficient * attenuation;
		reflectedLight += Lights[light].color * specularCoefficient * attenuation;
	}

	vec4 MaterialDiffuse = texture(texture_diffuse, UV).rgba;
	vec3 MaterialSpecular = texture(texture_specular, UV).rgb;

	vec3 rgb = min( MaterialDiffuse.rgb * scatteredLight + MaterialSpecular * reflectedLight, vec3(1.0));
	out_color = vec4(rgb, MaterialDiffuse.a);
}