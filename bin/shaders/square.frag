#version 330

flat in uint color_out;

out vec4 outColor;

uint pow (uint a, uint b)
{
	uint result;
	uint i;
	result = uint(1);
	for (i = uint(0); i < b; i++)
		result = result * a;
	return result;
}

void main()
{
	if (color_out == uint(0))
		outColor = vec4(1, 1, 1, 0);
	else if (color_out == uint(1))
		outColor = vec4(0.5, 0.5, 1, 0);
	else if (color_out == uint(2))
		outColor = vec4(0, 0, 1, 0);
	else
	{
		if (color_out > uint(1073741823))
			outColor = vec4(0, 0, 1, 0);
		else outColor = vec4(0.5, 0.5, 1, 0);
	}
}
