#version 400

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec2 uv;
layout (location = 3) in vec3 tangent;
layout (location = 4) in vec3 bitangent;

out vec2 out_uv;
out vec3 out_normal;
out vec3 out_position;
out float visibility;

uniform mat4 transform;
uniform mat4 view;
uniform mat4 projection;

uniform int fake_lighting;
uniform vec4 plane;

const float density = 0.007f;
const float gradient = 1.5f;

void main()
{
	vec3 real_normal = normal;
	if (fake_lighting > 0.5)
	{
		real_normal = vec3(0.0f, 1.0f, 0.0f);
	}

	vec4 world_position = transform * vec4(position, 1.0f);
	vec4 view_position = view * world_position;
	gl_ClipDistance[0] = dot(world_position, plane);

	float distance = length(view_position.xyz);
	visibility = exp(-pow((distance * density), gradient));
	visibility = clamp(visibility, 0.0f, 1.0f);

    gl_Position = projection * view_position;
	out_uv = uv;
	out_normal = mat3(transpose(inverse(transform))) * real_normal;
	out_position = vec3(transform * vec4(position, 1.0f));
}