#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <vector>
#include <iostream>
#include <utility>

#include "Utility.h"
#include "Cellurar.hpp"
#include "InfoStorage.hpp"

using namespace std;

class Graphics
{
	Cellurar automata;
	uint height;
	uint width;
	float square_height;
	float square_width;
	int *argc;
	char** argv;
	uint window_height;
	uint window_width;
	bool lines_enabled;
	bool cycle_started;
	vector<VM::vec2> vert_line_mesh;
	vector<VM::vec2> hor_line_mesh;
	vector<VM::vec2> square_mesh;
	GLuint vert_line_prog;
	GLuint hor_line_prog;
	GLuint squares_prog;
	GLuint vertVAO;
	GLuint horVAO;
	GLuint squaresVAO;

	uint timer_delay;
	

	vector<GLfloat> vert_line_positions;
	vector<GLfloat> hor_line_positions;
	vector<VM::vec2> squares_positions;
	vector<GLuint> squares_colors;
	GLuint colorsBuffer;
	void CreateLines();
	void CreateSquares();
	void DrawLines();
	void DrawSquares();
	vector<GLfloat> GenerateLinePositions(uint size);
	void GenerateSquareMesh();
	void GenerateSquaresPositions();
	void UpdateSquaresColors();
	void FetchSquaresColors();


	int last_rmb_state;
	int last_lmb_state;
	void FinishProgram();
	void StartCycling();
public:
	Graphics(const InfoStorage& info, int* argc, char** argv);
	static char mesa_version_override[];
	void InitGlut();
	void InitGlew();
	void CreateField();
	void DrawField();
	void IdleFunc();
	void MainLoop();
	void MouseClick(int button, int state, int x, int y);
	void KeyboardFunc(unsigned char key, int x, int y);
	void TimerFunc(int value);
	void ReshapeFunc(GLint newWidth, GLint newHeight);
};

extern Graphics* ThisIsAVeryBadIdeaButOhWellIHaveToDoItCuzOfFuckingStandard;

void Graphics_DrawField();
void Graphics_KeyboardFunc(unsigned char key, int x, int y);
void Graphics_IdleFunc();
void Graphics_MouseClick(int button, int state, int x, int y);
void Graphics_TimerFunc(int value);
void Graphics_ReshapeFunc(GLint newWidth, GLint newHeight);


#endif
