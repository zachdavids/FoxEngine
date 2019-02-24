#version 400

in vec2 out_uv;

uniform sampler2D gui;

void main()
{
	gl_FragColor = texture(gui, out_uv);
}