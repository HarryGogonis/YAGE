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

uniform sampler2D texture1;

// set of lights to apply, per invocation of this shader
const int MaxLights = 5; 
uniform LightProperties Lights[MaxLights];

uniform float Shininess;
uniform float Strength;
uniform vec3 EyeDirection;

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

		switch(Lights[light].type)
		{
			case 0: // Ambient Light
				scatteredLight += Lights[light].ambient;
				break;
			case 1: // Directional Light
				halfVector = Lights[light].halfVector;
				break;
			case 2: // Point Light
				lightDirection = lightDirection - vec3(Position);
				lightDistance = length(lightDirection); //!warning! length does expensive SQRT
				lightDirection = lightDirection / lightDistance;

				attenuation = 1.0 /
					(Lights[light].constantAttenuation
					+ Lights[light].linearAttenuation * lightDistance
					+ Lights[light].quadraticAttenuation * lightDistance * lightDistance);
				break;
			case 3: // Spot Light
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
				break;
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

	vec4 texcolor = texture(texture1, UV).rgba;

	vec3 rgb = min(texcolor.rgb * scatteredLight + reflectedLight, vec3(1.0));
	out_color = vec4(rgb, texcolor.a);
}