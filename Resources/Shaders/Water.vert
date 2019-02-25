#version 400

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec2 uv;
layout (location = 3) in vec3 tangent;
layout (location = 4) in vec3 bitangent;

out vec4 clip_space;
out vec2 out_uv;

uniform mat4 transform;
uniform mat4 view;
uniform mat4 projection;

const float tiling = 6.0f;

void main()
{
	clip_space = projection * view * transform * vec4(position.x, 0.0f, position.z, 1.0f);
    gl_Position = projection * view * transform * vec4(position.x, 0.0f, position.z, 1.0f);
	out_uv = vec2(position.x / 2.0f + 0.5f, position.z / 2.0f + 0.5f) * tiling;
}