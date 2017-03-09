#ifndef CELLURAR_H
#define CELLURAR_H

#include <string>
#include <math.h>
#include <iostream>

using namespace std;

typedef unsigned int uint;

class Cellurar
{
	uint height;
	uint width;
	unsigned char **marray;
	unsigned char **sarray;
	unsigned char Rule(unsigned char* neighbors, unsigned char cell);
public:
	Cellurar(uint height_in, uint width_in);
	~Cellurar();
	void UpdateSecondaryBuffer();
	void SwapBuffers();
	void Randomize();
	void Clear();
	void FirstPattern();
	void SecondPattern();
	void ThirdPattern();
	void FourthPattern();
	void FifthPattern();
	void SixthPattern();
	void SeventhPattern();
	void EighthPattern();
	void NinthPattern();
	void TenthPattern();
	unsigned char& operator()(uint x, uint y);
};

#endif
