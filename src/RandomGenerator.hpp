//Tomasz Dakowicz 261438

#include <stdlib.h>
#include <time.h>
#include <iostream>

class RandomGenerator
{
private:
	Tree tree;

public:
	RandomGenerator();
	~RandomGenerator();

	void generate();
	void addConnection();
};