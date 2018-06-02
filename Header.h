//Rohan Chaturvedi
//Umair Haneef
//UOWD CSCI 323 Artificial Intelligence
//Maze Solver using Genetic Algorithm
//"Headher.h"

#include <string>
#include <iostream>
#include <ctime>
#include <fstream>
#include <Windows.h>
#include <vector>
class walker
{
private:
	std::string genome;
	int x;//horizontal position
	int y;//vertical position
	int fitness;
public:
	walker(){};//default constructor
	void nextGen(walker newGen[10], walker p1, walker p2);
	std::string getGeneCode();
	void setGeneCode(std::string);
	int getX();
	int getY();
	int getFitness();
	void setFitness(int);
	void genesis();//initialise with random genome
	void move(char direction, char maze[10][10]);//single step
	void walk(char maze[10][10], int enX, int enY, int exX, int exY);
	void printWalk(char maze[10][10], int enX, int enY, int exX, int exY, int gen);
	int calcFitness(int distances[10][10]);
};



void walker::genesis()
{
	std::string temp;
	char genes[] = { 'u', 'd', 'l', 'r' };
	for (int i = 0; i < 30; i++)
	{
		int r = rand() % 4;
		//std::cout << r;
		temp += (genes[r]);
		//std::cout << "\n" << i << "genome is: " << temp;
	}
	this->genome = temp;
}

std::string walker::getGeneCode()
{
	return genome;
}

void walker::setGeneCode(std::string g)
{
	this->genome = g;
}

int walker::getX()
{
	return this->x;
}

int walker::getY()
{
	return this->y;
}

int walker::getFitness()
{
	return this->fitness;
}

void walker::setFitness(int f)
{
	this->fitness = f;
}

void walker::move(char direction, char maze[10][10])//single step
{
	//std::cout << "\nInitiating move: " << direction << '\n';
	
	if (direction == 'u')
	{
		if (this->y != 0)//prevent out of bounds
		{
			if (maze[(this->y) - 1][this->x] != '#')//check for wall
			{
				this->y -= 1;
				//std::cout << "\nWalker moved UP\n";
			}
		}
		
		//else std::cout << "\nCould not move UP\n";
	}

	else if (direction == 'd')
	{
		if (this->y != 9)//prevent out of bounds
		{
			if (maze[(this->y) + 1][this->x] != '#')//check for wall
			{
				this->y += 1;
				//std::cout << "\nWalker moved DOWN\n";
			}
		}
		
		//else std::cout << "\nCould not move to " << this->x << (this->y)+1 << '\n' ;
	}
	else if (direction == 'l')
	{
		if (this->x != 0)//prevent out of bounds
		{
			if (maze[this->y][(this->x) - 1] != '#')//check for wall
			{
				this->x -= 1;
				//std::cout << "\nWalker moved LEFT\n";
			}
		}
		
		//else std::cout << "\nCould not move LEFT\n";
	}
	else if (direction == 'r')
	{
		if (this->x != 9)//prevent out of bounds
		{
			if (maze[this->y][(this->x) + 1] != '#')//check for wall
			{
				this->x += 1;
				//std::cout << "\nWalker moved RIGHT\n";
			}
		}
		
		//else std::cout << "\nCould not move RIGHT\n";
	}
	
	
	
}

void walker::walk(char maze[10][10], int enX, int enY, int exX, int exY)
{
	std::string geneCode = this->getGeneCode();
	int genesize = geneCode.length();
	
	this->x = enX;
	this->y = enY;
	
	for (int i = 0; i < genesize; i++)
	{
		if ((this->x == exX) && (this->y == exY))
		{
			std::cout << "\nWalker found exit!\n";
			break;
		}
		else
		{
			char g = geneCode[i];
			
			this->move(g, maze);

		}

	}
}

void walker::printWalk(char maze[10][10], int enX, int enY, int exX, int exY, int gen)
{
	std::string geneCode = this->getGeneCode();
	int genesize = geneCode.length();
	std::cout << "\nStarting Walk...\n";
	this->x = enX;
	this->y = enY;

	for (int i = 0; i < genesize; i++)
	{
		for (int i = 0; i < 10; i++)//prints the maze with current position of walker
		{
			std::cout << '\n';
			for (int j = 0; j < 10; j++)
			{
				if ((this->y == i) && (this->x == j)) std::cout << "W";
				else std::cout << maze[i][j];
			}
			
		}
		Sleep(100);

		//system("pause");
		system("cls");
		std::cout << "\nGeneration: " << gen;
		std::cout << "\nFitness: " << this->getFitness() << "\n\n";
		
		

		if ((this->x == exX) && (this->y == exY))
		{
			std::cout << "\nWalker found exit!\n";
			
			break;
		}
		else
		{
			char g = geneCode[i];
			//std::cout << "\nCurrent gene letter is " << g << '\n';
			this->move(g, maze);
			
		}
		
		
		
	}

}

int walker::calcFitness(int distances[10][10])
{
	int endX = this->x;//end point after finishing walk or current point
	int endY = this->y;

	int f = 100 - distances[endY][endX];
	this->setFitness(f);
	return f;
}

//-----------------End of walker class member functions----------------

void loadMaze(char board [10][10])//loads the maze from a text file into memory
{
	std::cout << "\nLoading maze...\n";
	std::ifstream mazefile;
	mazefile.open("maze.txt");
	if (mazefile.fail())
	{
		std::cout << "\nError opening maze file!\n";
	}
	else { std::cout << "\nOpened maze file...\n"; }
	//for (int i = 10; i < 10; i++)
	std::string temp;
	int i = 0;
	while (getline(mazefile, temp))
	{
		
		//getline(mazefile, temp);
		for (int j = 0; j < 10; j++)
		{
			if (temp[j] != ' ')
			{
				board[i][j] = '#';
				std::cout << "\nWall at " << i << j << '\n';
			}
		}
		i++;
	}
	std::cout << "\nMaze loaded!\n";
}

void loadDistanceMatrix(int distances[10][10])//loads the matrix of cell distances into memory
{
	std::cout << "\nLoading distance matrix...\n";
	std::ifstream distfile;
	distfile.open("distances.txt");
	if (distfile.fail())
	{
		std::cout << "\nError opening distance matrix file!\n";
	}
	else { std::cout << "\nOpened distance matrix file...\n"; }

	int temp;
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			distfile >> temp;
			distances[i][j] = temp;
		}
		
	}
}

void printDistances(int distances[10][10])
{
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			std::cout << distances[i][j] << '\t'  ;
		}
		std::cout << '\n';
	}
}

void printMaze(char maze[10][10])
{
	for (int i = 0; i < 10; i++)
	
	{
		std::cout << '\n';
		for (int j = 0; j < 10; j++)
		{
			std::cout << maze[i][j];
		}
	}
}

int parent1(int fitness[10])// return index to most fit parent
{
	int max = 0;
	for (int i = 0; i < 10; i++)
	{
		if (fitness[i] > fitness[max])
		{
			max = i;
		}
	}
	return max;
}

int parent2(int fitness[10])//returns index to 2nd most fit parent
{
	
	int max = 0;
	int p1 = parent1(fitness);//index to parent 1
	for (int i = 0; i < 10; i++)
	{
		if (fitness[i] >= fitness[max])
		{
			if (i != parent1(fitness))
			{
				max = i;
			}
		}
	}
	return max;
	
}

void nextGen(walker newGen[10], walker p1, walker p2)
{
	std::string p1code = p1.getGeneCode();
	std::string p2code = p2.getGeneCode();
	int geneLength = p1code.length();
	int halfLen = 15; // try to generalise this as  floor(geneLength / 2);
	for (int i = 0; i < 5; i++)
	{
		std::string geneCode1 = p1code; //only done for initialisation
		std::string geneCode2 = p1code; //both strings are overwritten in the loop below

		//Gene inheritance from parents (1 point crossover)
		//for (int j = 0; j < halfLen; j++)
		//{
		//	geneCode1[j] = p1code[j];
		//	geneCode2[j] = p2code[j];
		//	//std::cout << '\n' << j + halfLen;
		//	geneCode1[j + (halfLen)] = p2code[j + (halfLen)];
		//	geneCode2[j + (halfLen)] = p1code[j + (halfLen)];
		//}
		
		//2 point crossover ( middle 10 genes)
		std::string temp = geneCode1;
		for (int i = 0; i < 10; i++) 
		{
			geneCode1[9 + i] = geneCode2[9 + i];
			geneCode2[9 + i] = temp[9 + i];
		}
		
		//Mutation
		int n = 4;//how many random genes are mutated
		char genes[] = { 'u', 'd', 'l', 'r' };
		
		for (int i = 0; i < n; i++)
		{
			int index = rand() % 30; // index of which gene will mutate
			int r = rand() % n; // used to pick random gene 
			geneCode1[index] = genes[r];

			index = rand() % 30;
			r = rand() % n;
			geneCode2[index] = genes[r];
		}

		newGen[i].setGeneCode(geneCode1);
		newGen[i + 1].setGeneCode(geneCode2);
	}
}

double avgFitness(int fitness[], int n)
{
	double average = 0;
	int sum = 0;
	for (int i = 0; i < n; i++)
	{
		sum += fitness[i];
	}
	average = sum / n;

	return average;
}