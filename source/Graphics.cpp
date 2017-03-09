#include "Graphics.hpp"
#include <unistd.h>

Graphics* ThisIsAVeryBadIdeaButOhWellIHaveToDoItCuzOfFuckingStandard;

char Graphics::mesa_version_override[]= "MESA_GL_VERSION_OVERRIDE=3.3COMPAT";

Graphics::Graphics(const InfoStorage& info,
				   int* argc_in, char** argv_in):automata(info.height, info.width),
	height(info.height), width(info.width),	argc(argc_in), argv(argv_in),
	timer_delay(info.delay)
{
	putenv(mesa_version_override);
	square_height = ((float)2)/height;
	square_width = ((float)2)/width;
	last_rmb_state = GLUT_UP;
	last_lmb_state = GLUT_UP;
	cycle_started = false;
	switch(info.window_size_option)
	{
	case 0:
		window_width = 640;
		window_height = 480;
		break;
	case 1:
		window_width = 800;
		window_height = 600;
		break;
	case 2:
		window_width = 1024;
		window_height = 768;
		break;
	case 3:
		window_width = 1280;
		window_height = 1024;
		break;
	case 4:
		window_width = 1600;
		window_height = 900;
		break;
	case 5:
		window_width = 1680;
		window_height = 1050;
		break;
	default:
		window_width = 1600;
		window_height = 900;
	}
	if (height + height + 1 > window_height || width + width + 1 > window_width)
	{
		const char no_lines[]="Either field is too big or the window is too small: "
			"cannot fit all the separating lines in the window. Drawing without them\n";
		cout << no_lines;
		lines_enabled = false;
	} else
		lines_enabled = true;
}

void Graphics::InitGlut()
{
	glutInit(argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);
	glutInitContextVersion(3, 0);
	glutInitWindowPosition(-1,-1);
	glutInitWindowSize(window_width, window_height);
//	cout << "Window inited with size" << window_width << 'x' << window_height << endl;
	glutCreateWindow("Cellurar Automata");
	glutWarpPointer(window_width/2, window_height/2);
	glutSetCursor(GLUT_CURSOR_RIGHT_ARROW);
	glutDisplayFunc(Graphics_DrawField);
	glutKeyboardFunc(Graphics_KeyboardFunc);
//	glutSpecialFunc(/*Do I even need to add this one?*/);
//	glutIdleFunc(Graphics_IdleFunc);
//	glutPassiveMotionFunc(/*Probably wont need this one too*/);
	glutMouseFunc(Graphics_MouseClick);
	glutReshapeFunc(Graphics_ReshapeFunc);
//	glDisable(GL_CULL_FACE);
//	glFrontFace(GL_CCW);
	glClearColor(0.0f,0.0f,0.0f,0.0f);
	cout << "Glut inited" << endl;
}

void Graphics::MainLoop()
{
	glutMainLoop();
}

void Graphics::InitGlew()
{
	putenv(mesa_version_override);
	glewExperimental = true;
	glewInit();
	cout << "Glew inited" << endl;
}

void Graphics::FinishProgram()
{
	glutDestroyWindow(glutGetWindow());
	exit(0);
}

void Graphics_ReshapeFunc(GLint newWidth, GLint newHeight)
{
	ThisIsAVeryBadIdeaButOhWellIHaveToDoItCuzOfFuckingStandard->ReshapeFunc(newWidth, newHeight);
}

void Graphics::ReshapeFunc(GLint newWidth, GLint newHeight)
{
	glViewport(0, 0, newWidth, newHeight);
	window_height = (uint) newHeight;
	window_width = (uint) newWidth;
	cout << "Window reshaped to " << newWidth << 'x' << newHeight << endl;
}

void Graphics_KeyboardFunc(unsigned char key, int x, int y)
{
	ThisIsAVeryBadIdeaButOhWellIHaveToDoItCuzOfFuckingStandard->KeyboardFunc(key, x, y);
}

void Graphics::KeyboardFunc(unsigned char key, int x, int y)
{
//	cout << key << endl;
	if (key == 27 || key == 'q')
		FinishProgram();
	else if (key == 's')
	{
		if (!cycle_started)
		{
			cycle_started = true;
			StartCycling();
		}
	}
	else if (key == 'r')
	{
		automata.Randomize();
		glutPostRedisplay();
	}
	else if (key == 'c')
	{
		automata.Clear();
		glutPostRedisplay();
	}
	else if (key == '1') 
	{
		automata.FirstPattern();
		glutPostRedisplay();
	}
	else if (key == '2')
	{
		automata.SecondPattern();
		glutPostRedisplay();
	}
	else if (key == '3')
	{
		automata.ThirdPattern();
		glutPostRedisplay();
	}
	else if (key == '4')
	{
		automata.FourthPattern();
		glutPostRedisplay();
	}
	else if (key == '5')
	{
		automata.FifthPattern();
		glutPostRedisplay();
	}
	else if (key == '6')
	{
		automata.SixthPattern();
		glutPostRedisplay();
	}
	else if (key == '7')
	{
		automata.SeventhPattern();
		glutPostRedisplay();
	}
	else if (key == '8')
	{
		automata.EighthPattern();
		glutPostRedisplay();
	}
	else if (key == '9')
	{
		automata.NinthPattern();
		glutPostRedisplay();
	}
	else if (key == '0')
	{
		automata.TenthPattern();
		glutPostRedisplay();
	}
}

void Graphics::StartCycling()
{
	glutMouseFunc(NULL);
	glutTimerFunc(timer_delay, Graphics_TimerFunc, 0);
}

void Graphics_TimerFunc(int value)
{
	ThisIsAVeryBadIdeaButOhWellIHaveToDoItCuzOfFuckingStandard->TimerFunc(value);
}

void Graphics::TimerFunc(int value)
{
	automata.UpdateSecondaryBuffer();
	automata.SwapBuffers();
	glutPostRedisplay();
	glutTimerFunc(timer_delay, Graphics_TimerFunc, 0);
}

void Graphics_IdleFunc()
{
	ThisIsAVeryBadIdeaButOhWellIHaveToDoItCuzOfFuckingStandard->IdleFunc();
}

void Graphics::IdleFunc()
{
	usleep(10000);
	glutPostRedisplay();
}

void Graphics_MouseClick(int button, int state, int x, int y)
{
	ThisIsAVeryBadIdeaButOhWellIHaveToDoItCuzOfFuckingStandard->MouseClick(button, state, x, y);
}

void Graphics::MouseClick(int button, int state, int x, int y)
{
	enum
	{
		dead=0,
		young=1,
		old=2
	};
	if (square_height == 0 || square_width == 0)
		throw (string) "Square height or width = 0";
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN && last_lmb_state == GLUT_UP)	
	{
		uint i = 0,j = 0;
		int new_x = x;
		int new_y = window_height - y;
		float opengl_coord_x = (((float)new_x) / window_width)*2;
		float opengl_coord_y = (((float)new_y) / window_height)*2;

		last_lmb_state = GLUT_DOWN;

		while (opengl_coord_x > square_width)
		{
			j++;
			opengl_coord_x -= square_width;
		}

		while (opengl_coord_y > square_height)
		{
			i++;
			opengl_coord_y -= square_height;
		}
/*		while (vert_line_positions[j] < opengl_coord_x)
			j++;
		j--;

		while (hor_line_positions[i] < opengl_coord_y)
			i++;
		i--;*/

		automata(i,j) = (automata(i,j) + 1)%3;
		glutPostRedisplay();
	} else
	if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN && last_rmb_state == GLUT_UP)	
	{
		uint i = 0,j = 0;
		int new_x = x;
		int new_y = window_height - y;
		float opengl_coord_x = (((float)new_x )/ window_width)*2;
		float opengl_coord_y = (((float)new_y )/ window_height)*2;

		last_rmb_state = GLUT_DOWN;

		while (opengl_coord_x > square_width)
		{
			j++;
			opengl_coord_x -= square_width;
		}

		while (opengl_coord_y > square_height)
		{
			i++;
			opengl_coord_y -= square_height;
		}

/*		while (vert_line_positions[j] < opengl_coord_x)
			j++;
		j--;

		while (hor_line_positions[i] < opengl_coord_y)
			i++;
		i--;*/

		automata(i,j) = (automata(i,j) - 1)%3;
//		cout << (int) automata(i,j) << endl;
		glutPostRedisplay();
	} else
	if (state == GLUT_UP)
	{
		if (button == GLUT_RIGHT_BUTTON)
			last_rmb_state = GLUT_UP;
		else if (button == GLUT_LEFT_BUTTON)
			last_lmb_state = GLUT_UP;
	}
}

void Graphics_DrawField()
{
	ThisIsAVeryBadIdeaButOhWellIHaveToDoItCuzOfFuckingStandard->DrawField();
}

void Graphics::DrawField()
{
	glEnable(GL_DEPTH_TEST);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); CHECK_GL_ERRORS
	DrawSquares();
	if (lines_enabled)
		DrawLines();
	glutSwapBuffers();
//	cout << "Field drawn" << endl;
}

void Graphics::DrawSquares()
{
	glUseProgram(squares_prog); CHECK_GL_ERRORS
	glBindVertexArray(squaresVAO); CHECK_GL_ERRORS
	UpdateSquaresColors();
	glDrawArraysInstanced(GL_TRIANGLES, 0, 6, height*width); CHECK_GL_ERRORS
	glBindVertexArray(0); CHECK_GL_ERRORS
	glUseProgram(0); CHECK_GL_ERRORS
//	cout << "Squares drawn" << endl;
}

void Graphics::UpdateSquaresColors()
{
	FetchSquaresColors();
	glBindBuffer(GL_ARRAY_BUFFER, colorsBuffer); CHECK_GL_ERRORS
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLuint) * squares_colors.size(), squares_colors.data(), GL_STATIC_DRAW); CHECK_GL_ERRORS
	glBindBuffer(GL_ARRAY_BUFFER, 0); CHECK_GL_ERRORS
}


void Graphics::DrawLines()
{
	glUseProgram(vert_line_prog); CHECK_GL_ERRORS
	glBindVertexArray(vertVAO); CHECK_GL_ERRORS
	glDrawArraysInstanced(GL_LINES, 0, 2, width+1); CHECK_GL_ERRORS
	glBindVertexArray(0); CHECK_GL_ERRORS
	glUseProgram(0); CHECK_GL_ERRORS

	glUseProgram(hor_line_prog); CHECK_GL_ERRORS
	glBindVertexArray(horVAO); CHECK_GL_ERRORS
	glDrawArraysInstanced(GL_LINES, 0, 2, height+1); CHECK_GL_ERRORS
	glBindVertexArray(0); CHECK_GL_ERRORS
	glUseProgram(0); CHECK_GL_ERRORS

//	cout << "Lines drawn" << endl;
}

void Graphics::CreateField()
{
	if (lines_enabled)
		CreateLines();
	CreateSquares();
	cout << "Field created" << endl;
}

void Graphics::CreateSquares()
{
	GenerateSquareMesh();
	GenerateSquaresPositions();
	FetchSquaresColors();
	squares_prog = GL::CompileShaderProgram("square"); CHECK_GL_ERRORS

	glGenVertexArrays(1, &squaresVAO); CHECK_GL_ERRORS
	glBindVertexArray(squaresVAO); CHECK_GL_ERRORS
	GLuint pointsBuffer; CHECK_GL_ERRORS
	glGenBuffers(1, &pointsBuffer); CHECK_GL_ERRORS
	glBindBuffer(GL_ARRAY_BUFFER, pointsBuffer); CHECK_GL_ERRORS
	glBufferData(GL_ARRAY_BUFFER, sizeof(VM::vec2) * square_mesh.size(), square_mesh.data(), GL_STATIC_DRAW); CHECK_GL_ERRORS
	GLuint pointsLocation = glGetAttribLocation(squares_prog, "point"); CHECK_GL_ERRORS
	glEnableVertexAttribArray(pointsLocation); CHECK_GL_ERRORS
	glVertexAttribPointer(pointsLocation, 2, GL_FLOAT, GL_FALSE, 0, 0); CHECK_GL_ERRORS


	GLuint positionBuffer;
	glGenBuffers(1, &positionBuffer); CHECK_GL_ERRORS
	glBindBuffer(GL_ARRAY_BUFFER, positionBuffer); CHECK_GL_ERRORS
	glBufferData(GL_ARRAY_BUFFER, sizeof(VM::vec2) * squares_positions.size(), squares_positions.data(), GL_STATIC_DRAW); CHECK_GL_ERRORS

	GLuint positions = glGetAttribLocation(squares_prog, "position"); CHECK_GL_ERRORS
	glEnableVertexAttribArray(positions); CHECK_GL_ERRORS
	glVertexAttribPointer(positions, 2, GL_FLOAT, GL_FALSE, 0, 0); CHECK_GL_ERRORS
	glVertexAttribDivisor(positions, 1); CHECK_GL_ERRORS


	glGenBuffers(1, &colorsBuffer); CHECK_GL_ERRORS
	glBindBuffer(GL_ARRAY_BUFFER, colorsBuffer); CHECK_GL_ERRORS
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLuint) * squares_colors.size(), squares_colors.data(), GL_STATIC_DRAW); CHECK_GL_ERRORS

	GLuint colorsLocation = glGetAttribLocation(squares_prog, "color_in"); CHECK_GL_ERRORS
	glEnableVertexAttribArray(colorsLocation); CHECK_GL_ERRORS
	glVertexAttribPointer(colorsLocation, 1, GL_UNSIGNED_INT, GL_FALSE, 0, 0); CHECK_GL_ERRORS
	glVertexAttribDivisor(colorsLocation, 1); CHECK_GL_ERRORS


	glBindVertexArray(0); CHECK_GL_ERRORS
	glBindBuffer(GL_ARRAY_BUFFER, 0); CHECK_GL_ERRORS

	cout << "Squares created" << endl;
}

void Graphics::FetchSquaresColors()
{
	squares_colors.clear();
	for (uint i = 0; i < height; i++)
	{
		for (uint j = 0; j < width; j++)
		{
			squares_colors.push_back((GLuint) automata(i,j));
//			cout << (GLuint) automata(i,j) << ' ';
		}
//		cout << endl;
	}
}

void Graphics::GenerateSquareMesh()
{
	square_mesh = {
		VM::vec2(0, 0),
		VM::vec2(square_width, 0),
		VM::vec2(0, square_height),

		VM::vec2(square_width, 0),
		VM::vec2(0, square_height),
		VM::vec2(square_width, square_height)
	};
}

void Graphics::GenerateSquaresPositions()
{
	squares_positions.clear();
	for (uint j = 0; j < height; j++)
		for (uint i = 0; i < width; i++)
		{
			squares_positions.push_back(VM::vec2(i*square_width-1, j*square_height-1));
//			cout << i*square_width-1 << ' ' << j*square_height-1 << endl;
		}
}

void Graphics::CreateLines()
{
	vert_line_mesh = {
		VM::vec2(-1, -1),
		VM::vec2(-1, 1)
	};
	hor_line_mesh = {
		VM::vec2(-1, -1),
		VM::vec2(1, -1)
	};
	vert_line_positions = GenerateLinePositions(width);
	hor_line_positions = GenerateLinePositions(height);
	vert_line_prog = GL::CompileShaderProgram("vert_line"); CHECK_GL_ERRORS
	hor_line_prog = GL::CompileShaderProgram("hor_line"); CHECK_GL_ERRORS

	glGenVertexArrays(1, &vertVAO); CHECK_GL_ERRORS
	glBindVertexArray(vertVAO); CHECK_GL_ERRORS

	GLuint pointsBuffer;
	glGenBuffers(1, &pointsBuffer); CHECK_GL_ERRORS
	glBindBuffer(GL_ARRAY_BUFFER, pointsBuffer); CHECK_GL_ERRORS
	glBufferData(GL_ARRAY_BUFFER, sizeof(VM::vec2) * vert_line_mesh.size(), vert_line_mesh.data(), GL_STATIC_DRAW); CHECK_GL_ERRORS

	GLuint pointsLocation = glGetAttribLocation(vert_line_prog, "point"); CHECK_GL_ERRORS
	glEnableVertexAttribArray(pointsLocation); CHECK_GL_ERRORS
	glVertexAttribPointer(pointsLocation, 2, GL_FLOAT, GL_FALSE, 0, 0); CHECK_GL_ERRORS

	GLuint positionBuffer;
	glGenBuffers(1, &positionBuffer); CHECK_GL_ERRORS
	glBindBuffer(GL_ARRAY_BUFFER, positionBuffer); CHECK_GL_ERRORS
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * vert_line_positions.size(), vert_line_positions.data(), GL_STATIC_DRAW); CHECK_GL_ERRORS

	GLuint positions = glGetAttribLocation(vert_line_prog, "position"); CHECK_GL_ERRORS
	glEnableVertexAttribArray(positions); CHECK_GL_ERRORS
	glVertexAttribPointer(positions, 1, GL_FLOAT, GL_FALSE, 0, 0); CHECK_GL_ERRORS
	glVertexAttribDivisor(positions, 1); CHECK_GL_ERRORS


	glGenVertexArrays(1, &horVAO); CHECK_GL_ERRORS
	glBindVertexArray(horVAO); CHECK_GL_ERRORS

	glGenBuffers(1, &pointsBuffer); CHECK_GL_ERRORS
	glBindBuffer(GL_ARRAY_BUFFER, pointsBuffer); CHECK_GL_ERRORS
	glBufferData(GL_ARRAY_BUFFER, sizeof(VM::vec2) * hor_line_mesh.size(), hor_line_mesh.data(), GL_STATIC_DRAW); CHECK_GL_ERRORS
	pointsLocation = glGetAttribLocation(hor_line_prog, "point"); CHECK_GL_ERRORS
	glEnableVertexAttribArray(pointsLocation); CHECK_GL_ERRORS
	glVertexAttribPointer(pointsLocation, 2, GL_FLOAT, GL_FALSE, 0, 0); CHECK_GL_ERRORS
	glGenBuffers(1, &positionBuffer); CHECK_GL_ERRORS
	glBindBuffer(GL_ARRAY_BUFFER, positionBuffer); CHECK_GL_ERRORS
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * hor_line_positions.size(), hor_line_positions.data(), GL_STATIC_DRAW); CHECK_GL_ERRORS
	positions = glGetAttribLocation(hor_line_prog, "position"); CHECK_GL_ERRORS
	glEnableVertexAttribArray(positions); CHECK_GL_ERRORS
	glVertexAttribPointer(positions, 1, GL_FLOAT, GL_FALSE, 0, 0); CHECK_GL_ERRORS
	glVertexAttribDivisor(positions, 1); CHECK_GL_ERRORS


	glBindVertexArray(0); CHECK_GL_ERRORS
	glBindBuffer(GL_ARRAY_BUFFER, 0); CHECK_GL_ERRORS

	cout << "Lines created" << endl;
}

vector<GLfloat> Graphics::GenerateLinePositions(uint size)
{
	vector<GLfloat> result;
	GLfloat step = ((float)2)/size;
	for (uint i = 0; i < size+1; i++)
	{
		result.push_back(step*i);
//		cout << step*i << ' ';
	}
//	cout << endl;
	return result;
}
