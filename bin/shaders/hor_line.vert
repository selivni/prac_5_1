#version 330

in vec2 point;
in float position;

void main()
{
	gl_Position = vec4(point.x, point.y+position, 0, 1);
}
