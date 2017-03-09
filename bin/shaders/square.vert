#version 330

in vec2 point;
in vec2 position;
in uint color_in;

flat out uint color_out;

void main()
{
	color_out = color_in;
	gl_Position = vec4(point.x+position.x, point.y+position.y, 0, 1);
}
