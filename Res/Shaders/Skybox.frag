#version 400

in vec3 out_uv;

uniform samplerCube day_cube;
uniform samplerCube night_cube;
uniform vec3 fog_colour;
uniform float blend_factor;

const float lower_limit = 0.0f;
const float upper_limit = 30.0f;

void main()
{
	vec4 day_color = texture(day_cube, out_uv);
	vec4 night_color = texture(night_cube, out_uv);
	vec4 result_color = mix(day_color, night_color, blend_factor);
	//float visibility = clamp((out_uv.y - lower_limit) / (upper_limit - lower_limit), 0.0f, 1.0f);
	gl_FragColor = result_color;
	//gl_FragColor = mix(vec4(fog_colour, 1.0f), result_color, visibility); 
}