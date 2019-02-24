#version 400

in vec2 out_uv;
in vec3 out_normal;
in vec3 out_position;
in float visibility;

uniform sampler2D sampler;
uniform vec3 view_position;
uniform vec3 light_colour[4];
uniform vec3 light_position[4];
uniform vec3 attenuation[4];
uniform vec3 sky_colour;

void main()
{
	//Ambient
	float ambient_strength = 0.1f;

	//Diffuse
	vec3 N = normalize(out_normal);
	float specular_strength = 0.5;
	vec3 view_direction = normalize(view_position - out_position);

	vec3 total_diffuse;
	vec3 total_specular;
	for (int i = 0; i < 4; i++) 
	{	
		float distance = length(light_position[i] - out_position);
		float attenuation_factor = attenuation[i].x + (attenuation[i].y * distance) + (attenuation[i].y * pow(distance, 2.0));
		vec3 L = normalize(light_position[i] - out_position);
		float diffuse_brightness = max(dot(N, L), 0.0f);
		vec3 reflect_direction = reflect(-L, N);
		float specular_brightness = pow(max(dot(view_direction, reflect_direction), 0.0f), 32);
		total_diffuse += (diffuse_brightness * light_colour[i]) / attenuation_factor;
		total_specular += (specular_strength * specular_brightness * light_colour[i]) / attenuation_factor;
	}
	
	total_diffuse = max(total_diffuse, 0.2);

	vec4 texture_colour = texture(sampler, out_uv);
	if (texture_colour.a < 0.5)
	{
		discard;
	}

	gl_FragColor = vec4(total_diffuse, 1.0f) * texture_colour + vec4(total_specular, 1.0f);
	gl_FragColor = mix(vec4(sky_colour, 1.0f), gl_FragColor, visibility);
}