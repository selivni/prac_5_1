#version 330

in vec2 point;
in float position;

void main()
{
	gl_Position = vec4(point.x+position, point.y, 0, 1);
}
