#version 400

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec2 uv;
layout (location = 3) in vec3 tangent;
layout (location = 4) in vec3 bitangent;

out vec2 out_uv;

uniform mat4 transform;

void main()
{
    gl_Position = transform * vec4(position.x, position.y, position.z, 1.0f);
	out_uv = vec2((position.x + 1.0f) / 2.0f, 1 - (position.y + 1.0f) / 2.0f);
}