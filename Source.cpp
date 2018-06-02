//Rohan Chaturvedi
//Maze Solver using Genetic Algorithm
//"Source.cpp"

#include "Header.h"

int main()
{
	char maze[10][10] = { ' ' };
	int distances[10][10];
	int entryX = 5;
	int entryY = 0;
	int exitX = 5;
	int exitY = 9;
	loadMaze(maze);
	printMaze(maze);

	loadDistanceMatrix(distances);
	//printDistances(distances);
	system("pause");
	
	
	srand(time(0));

	walker gen1[10];
	walker gen2[10];
	int fitness[10] = { 0 };
	int gen = 0;
	bool solved = false;
	std::vector <walker> parents;//track parents for each successive generation
	while (solved == false)
	{
		if (gen == 0)//pioneer generation
		{
			for (int i = 0; i < 10; i++)
			{
				
				gen1[i].genesis();//initialise with random genomes
				gen1[i].walk(maze, entryX, entryY, exitX, exitY);// use this to walk faster without printing
				
				fitness[i] = gen1[i].calcFitness(distances);
				std::cout << " Fitness: " << fitness[i] << '\n';
			}
			parents.push_back(gen1[parent1(fitness)]);
			parents.push_back(gen1[parent2(fitness)]);
			
			
			gen1[parent1(fitness)].printWalk(maze, entryX, entryY, exitX, exitY, gen);
			gen1[parent2(fitness)].printWalk(maze, entryX, entryY, exitX, exitY, gen);
		}
		else
		{
			
			int parentSize = parents.size();
			nextGen(gen2, parents[parentSize - 2], parents[parentSize - 1]);//populate gen2
			int fitness2[10];
			for (int i = 0; i < 10; i++)
			{
				gen2[i].walk(maze, entryX, entryY, exitX, exitY);
				fitness[i] = gen2[i].calcFitness(distances);
				if (fitness[i] == 100)
				{
					std::cout << "\nMaze exit found!\n";
					gen2[i].printWalk(maze, entryX, entryY, exitX, exitY, gen);
					system("pause");
					solved = true;
				}
			}
			std::cout << '\n' << gen << '\n';
			if ((gen % 10) == 0)//prints maze walk every 10 generations
			{
				std::cout << "\nWalking two fittest bots from Generation " << gen << "\n";
				//system("pause");
				gen2[parent1(fitness)].printWalk(maze, entryX, entryY, exitX, exitY, gen);
				gen2[parent2(fitness)].printWalk(maze, entryX, entryY, exitX, exitY, gen);
			}
						
			parents.push_back(gen2[parent1(fitness)]);
			parents.push_back(gen2[parent2(fitness)]);
			parentSize = parents.size();
			for (int i = 0; i < 10; i++)
			{
				gen1[i] = gen2[i];//overwrite gen1 with gen2 for next iteration;
				
			}
		}
		gen++;

		
	}

	std::cout << "\nGenome                            Fitness\n";
	for (int i = 0; i < parents.size(); i++)
	{
		std::cout << '\n' << parents[i].getGeneCode() << "    " <<parents[i].getFitness();
	}

	//-----------------
	
		
	std::cout << "\nDONE\n";

	char pause;
	std::cin >> pause;
}
