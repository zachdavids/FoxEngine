#version 400

in vec4 clip_space;
in vec2 out_uv;

uniform sampler2D reflection;
uniform sampler2D refraction;
uniform sampler2D dudv;

uniform float move_factor;

const float wave_strength = 0.02;

void main()
{
	vec2 normalized_device = (clip_space.xy / clip_space.w) / 2.0f + 0.5f;
	vec2 distortion1 = (texture(dudv, vec2(out_uv.x + move_factor, out_uv.y)).rg * 2.0f - 1.0f) * wave_strength;
	vec2 distortion2 = (texture(dudv, vec2(-out_uv.x + move_factor, out_uv.y + move_factor)).rg * 2.0f - 1.0f) * wave_strength;
	vec2 total_distortion = distortion1 + distortion2;
	vec2 refraction_uv = clamp(vec2(normalized_device.x, normalized_device.y) + total_distortion, 0.001, 0.999);
	vec2 reflection_uv = vec2(normalized_device.x, -normalized_device.y) + total_distortion;
	reflection_uv.x = clamp(reflection_uv.x, 0.001, 0.999);
	reflection_uv.y = clamp(reflection_uv.y, -0.999, -0.001);

	vec4 reflection_color = texture(reflection, reflection_uv);
	vec4 refraction_color = texture(refraction, refraction_uv);

	gl_FragColor = mix(reflection_color, refraction_color, 0.5f);
	gl_FragColor = mix(gl_FragColor, vec4(0.0, 0.3f, 0.5f, 1.0f), 0.2);
}