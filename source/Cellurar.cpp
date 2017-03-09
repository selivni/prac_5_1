#include "Cellurar.hpp"

enum
{
	dead=0,
	young=1,
	old=2
};

Cellurar::Cellurar(uint height_in, uint width_in):height(height_in), width(width_in)
{
	marray = new unsigned char* [height+2];
	for (uint i = 0; i < height+2; i++)
		marray[i] = new unsigned char[width+2];

	sarray = new unsigned char* [height+2];

	for (uint i = 0; i < height+2; i++)
		sarray[i] = new unsigned char[width+2];
	
	for (uint i = 0; i < height+2; i++)
		for (uint j = 0; j < width+2; j++)
			marray[i][j] = sarray[i][j] = 0;
}

void Cellurar::UpdateSecondaryBuffer()
{
	unsigned char neighbors[8];
	for (uint i = 1; i < height+1; i++)
		for (uint j = 1; j < width+1; j++)
		{
			neighbors[0] = marray[i-1][j-1];
			neighbors[1] = marray[i-1][j];
			neighbors[2] = marray[i-1][j+1];
			neighbors[3] = marray[i][j-1];
			neighbors[4] = marray[i][j+1];
			neighbors[5] = marray[i+1][j-1];
			neighbors[6] = marray[i+1][j];
			neighbors[7] = marray[i+1][j+1];
			sarray[i][j] = Rule(neighbors,marray[i][j]);
		}
}

unsigned char Cellurar::Rule(unsigned char* neighbors, unsigned char cell)
{
	unsigned char young_count=0, old_count=0;
	if (cell == young)
		return old;
	for (uint i = 0; i < 8; i++)
	{
		if (neighbors[i] == young)
			young_count++;
		else if (neighbors[i] == old)
			old_count++;
	}
	if (cell == dead)
	{
		if (old_count+young_count == 3 && old_count >= 2)
			return young;
		else return dead;
	}
	if (cell == old)
	{
		if (young_count <= 1 && old_count+young_count >= 2 && old_count+young_count <= 3)
			return old;
		else return dead;
	} else throw (string)"Error: invalid cell state\n";//This must be unreachable
}

void Cellurar::Randomize()
{
	for (uint i = 1; i < height+1; i++)
	{
		for (uint j = 1; j < width+1; j++)
		{
			marray[i][j] = (int) trunc((((float)rand())/RAND_MAX)*3-0.0001);
//			cout << (int) marray[i][j];
		}
//		cout << endl;
	}
}

void Cellurar::Clear()
{
	for (uint i = 1; i < height+1; i++)
		for (uint j = 1; j < width+1; j++)
			marray[i][j] = 0;
}
//Explosion #1
void Cellurar::FirstPattern()
{
	int i = (height+2)/2, j = (width+2)/2;
	marray[i][j] = marray[i-1][j] = marray[i+2][j+1] = 2;
	marray[i+1][j] = marray[i-2][j] = 1;
}
//Explosion #2
void Cellurar::SecondPattern()
{
	int i = (height+2)/2, j = (width+2)/2;
	marray[i][j-2] = marray[i][j-1] = marray[i][j] = marray[i][j+1] = marray[i][j+2] = 2;
	marray[i][j-3] = marray[i][j+3] = 1;
}
//Stepper
void Cellurar::ThirdPattern()
{
	int i = (height+2)/6, j = (width+2)/6;
	marray[i][j] = marray[i+1][j] = marray[i+1][j-1] = 2;
	marray[i-1][j-1] = marray[i][j+1] = 1;
}
//ComplicatedStepper
void Cellurar::FourthPattern()
{
	int i = (height+2)/2, j = (width+2)/6;
	marray[i][j] = marray[i-1][j] = marray[i-2][j] = marray[i+1][j] = 2;
	marray[i+2][j-1] = marray[i+3][j-1] = marray[i-3][j-1] = marray[i-4][j-1] = 2;
	marray[i+4][j-3] = marray[i-5][j-3] = 2;
	marray[i][j+1] = marray[i-1][j+1] = marray[i+4][j-1] = marray[i-5][j-1] = 1;
	marray[i+1][j-2] = marray[i+2][j-3] = marray[i-2][j-2] = marray[i-3][j-3] = 1;
}
//Puffer
void Cellurar::FifthPattern()
{
	int i = (height+2)/2, j = (width+2)/6;
	marray[i][j] = marray[i-1][j+1] = marray[i-1][j+3] = marray[i-1][j+4] = 2;
	marray[i][j+4] = marray[i+1][j+4] = marray[i+2][j+4] = marray[i+1][j-4] = 2;
	marray[i][j-2] = marray[i-1][j-2] = marray[i-1][j-3] = marray[i-1][j-4] = 2;
	marray[i][j+1] = marray[i+1][j+1] = marray[i-1][j+2] = marray[i-2][j+2] = 1;
	marray[i-2][j] = marray[i+2][j+3] = marray[i+1][j+5] = marray[i][j+5] = 1;
	marray[i+1][j-3] = marray[i-2][j-2] = marray[i-2][j-3] = 1;
}
//Rake
void Cellurar::SixthPattern()
{
	int i = (height+2)/2, j = (width+2)/6;
	for (int q = i-5; q < i+5; q++)
		marray[q][j+1] = 2;
	for (int q = i-4; q < i+2; q++)
		marray[q][j-1] = 2;
	for (int q = i-4; q < i+4; q++)
		marray[q][j+2] = 1;
	for (int q = i-4; q < i+2; q++)
		marray[q][j-2] = 1;
	marray[i-5][j-2] = 2;
	marray[i-5][j-1] = marray[i+4][j] = 1;
	j -= 9;
	marray[i-3][j] = marray[i-4][j] = marray[i-4][j+1] = marray[i-1][j-2] = 2;
	marray[i][j-2] = marray[i+1][j-4] = 2;
	marray[i-2][j-1] = marray[i-2][j+1] = marray[i-3][j-1] = marray[i-3][j+2] = 1;
	marray[i+1][j-2] = 1;
}
//Multiplier
void Cellurar::SeventhPattern()
{
	int i = (height+2)/10, j = (width+2)/10;
	marray[i][j] = marray[i][j+1] = marray[i+1][j-1] = marray[i+1][j-2] = 2;
	marray[i+2][j+2] = marray[i+3][j-1] = marray[i+4][j] = marray[i+4][j+1] = 2;
	marray[i-1][j-2] = marray[i-3][j-2] = marray[i-4][j-1] = marray[i-4][j+1] = 2;
	marray[i-2][j] = marray[i+4][j-1] = marray[i+4][j+2] = 1;
}
//A gun
void Cellurar::EighthPattern()
{
	int i = (height+2)/2, j = (width+2)/2;
	for (int q = j + 1; q < j+5; q++)
		marray[i][q] = marray[i-5][q] = 2;
	for (int q = i - 4; q < i; q++)
		marray[q][j] = marray[q][j+5] = 2;
}

void Cellurar::NinthPattern()
{
	int i = (height+2)/2, j = (width+2)/10;
	marray[i][j] = marray[i-1][j] = marray[i+2][j+1] = marray[i+3][j+1] = 2;
	marray[i-3][j+1] = marray[i-4][j+1] = marray[i-4][j+2] = marray[i+3][j+2] = 2;
	marray[i+2][j-3] = marray[i+3][j-3] = marray[i-3][j-3] = marray[i-4][j-3] = 2;
	marray[i-5][j-2] = marray[i-2][j-2] = marray[i+1][j-2] = marray[i+4][j-2] = 2;
	marray[i+1][j-1] = marray[i+2][j-1] = marray[i+3][j-1] = marray[i-4][j-1] = 2;
	marray[i-3][j-1] = marray[i-2][j-1] = marray[i-3][j+3] = marray[i-2][j+3] = 2;
	marray[i-1][j+3] = marray[i][j+3] = marray[i+1][j+3] = marray[i+2][j+3] = 2;
}

void Cellurar::TenthPattern()
{
	int i = (height+2)/2, j = (width+2)/2;
	marray[i][j] = marray[i-1][j] = marray[i][j+1] = marray[i-1][j+1] = 2;
	marray[i+1][j-2] = marray[i][j-2] = marray[i-1][j-2] = marray[i-2][j-2] = 2;
	marray[i+2][j-1] = marray[i+2][j] = marray[i+2][j+1] = marray[i+2][j+2] = 2;
	marray[i-3][j-1] = marray[i-3][j] = marray[i-3][j+1] = marray[i-3][j+2] = 2;
	marray[i+1][j+3] = marray[i][j+3] = marray[i-1][j+3] = marray[i-2][j+3] = 2;
	marray[i+1][j-3] = marray[i-2][j-3] = marray[i+1][j-4] = marray[i-2][j-4] = 2;
	marray[i+3][j-1] = marray[i+3][j+2] = marray[i+4][j-1] = marray[i+4][j+2] = 2;
	marray[i+1][j+4] = marray[i-2][j+4] = marray[i+1][j+5] = marray[i-2][j+5] = 2;
	marray[i-4][j-1] = marray[i-4][j+2] = marray[i-5][j-1] = marray[i-5][j+2] = 2;
	marray[i][j-5] = marray[i-1][j-5] = marray[i+5][j] = marray[i+5][j+1] = 2;
	marray[i][j+6] = marray[i-1][j+6] = marray[i-6][j] = marray[i-6][j+1] = 2;
	marray[i][j-7] = marray[i-1][j-7] = marray[i+7][j] = marray[i+7][j+1] = 2;
	marray[i][j+8] = marray[i-1][j+8] = marray[i-8][j] = marray[i-8][j+1] = 2;
	marray[i+2][j-5] = marray[i+2][j-6] = marray[i-3][j-5] = marray[i-3][j-6] = 2;
	marray[i+5][j-2] = marray[i+6][j-2] = marray[i+5][j+3] = marray[i+6][j+3] = 2;
	marray[i+2][j+6] = marray[i+2][j+7] = marray[i-3][j+6] = marray[i-3][j+7] = 2;
	marray[i-6][j-2] = marray[i-7][j-2] = marray[i-6][j+3] = marray[i-7][j+3] = 2;
	marray[i+4][j-3] = marray[i+3][j-4] = marray[i+4][j-5] = marray[i+5][j-4] = 2;
	marray[i+4][j+4] = marray[i+3][j+5] = marray[i+4][j+6] = marray[i+5][j+5] = 2;
	marray[i-4][j+5] = marray[i-5][j+4] = marray[i-6][j+5] = marray[i-5][j+6] = 2;
	marray[i-4][j-4] = marray[i-5][j-3] = marray[i-6][j-4] = marray[i-5][j-5] = 2;
	marray[i+3][j-7] = marray[i+3][j-8] = marray[i-4][j-7] = marray[i-4][j-8] = 2;
	marray[i+7][j-3] = marray[i+8][j-3] = marray[i+7][j+4] = marray[i+8][j+4] = 2;
	marray[i+3][j+8] = marray[i+3][j+9] = marray[i-4][j+8] = marray[i-4][j+9] = 2;
	marray[i-8][j-3] = marray[i-9][j-3] = marray[i-8][j+4] = marray[i-9][j+4] = 2;
	marray[i+1][j-9] = marray[i][j-9] = marray[i-1][j-9] = marray[i-2][j-9] = 2;
	marray[i+9][j-1] = marray[i+9][j] = marray[i+9][j+1] = marray[i+9][j+2] = 2;
	marray[i+1][j+10] = marray[i][j+10] = marray[i-1][j+10] = marray[i-2][j+10] = 2;
	marray[i-10][j-1] = marray[i-10][j] = marray[i-10][j+1] = marray[i-10][j+2] = 2;
}

void Cellurar::SwapBuffers()
{
	unsigned char **tmp = marray;
	marray = sarray;
	sarray = tmp;
}

Cellurar::~Cellurar()
{
	for (uint i = 0; i < height+2; i++)
	{
		delete[] marray[i];
		delete[] sarray[i];
	}
	delete[] marray;
	delete[] sarray;
}

unsigned char& Cellurar::operator()(uint x, uint y)
{
	if (x < 0 || y < 0 || x > height || y > width)
		throw (string) "Error: out of bounds\n";
	return marray[x+1][y+1];
}


