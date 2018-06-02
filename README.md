## AI-Maze-Solver
Using a genetic algorithm based artifial intelligence to solve a simple 10 x 10 maze. Takes ~30 generations on average to solve the given sample maze


This goal of this project was to use a Genetic Algorithm to teach a program how to solve a maze. The project was implemented in C++ without the use of any external machine learning or genetic algorithm libraries. I represent the maze as a 10 x 10 array of cells in memory, which are loaded from a text file. The idea behind this decision was to make the program modular, allowing for any maze to be solved. 

# Walkers
The use of Genetic Algorithm meant that I had to develop the program to run for an indefinite number of iterations corresponding to each generation. I created a class for objects that would traverse or walk through the maze which we refer to as ‘walkers’.  A walker is defined primarily by its genome or genetic code, which is a 30 character long sequence of 4 gene letters: ‘u’, ‘d’, ‘l’, ‘r’ which represent the up, down, left and right directions respectively. In addition, each walker keeps track of its position in the maze by way of an x,y co-ordinate pair, and has a fitness value associated with it. The fitness of each walker was calculated after it finished its walk. 


# Generations
Each generation comprises of ten walkers. The first generation has its genetic code initialized as a random string of gene letters, representing a random sequence of moves through the maze. Successive generations are created by inheriting their genomes from the previous generation’s fittest individuals, and applying a degree of mutation. The fitness of each member of the previous generation is calculated, and the two fittest individuals are chosen to perform a two-point crossover. Four random genes are also mutated. 


# Fitness
I chose to define the fitness of each walker as the distance between its final position and the exit of the maze. However distance here could be defined in several ways. We considered measuring the Euclidian distance between the walker’s final position and exit point of the maze and while this is simple to compute, it not a very helpful heuristic as it does not account for obstacles such as walls or turns between the walker’s position and the exit.  We also considered calculating the Manhattan distance and while this heuristic came closer to a true measure of a walker’s success in getting closer to the exit, it suffered the same problem as the Euclidian approach in that it did not account the structure of the maze. Eventually, we decided to score each cell of the maze with a distance value corresponding to its distance from the exit. Thus the walker’s fitness would be calculated as: 
[100-distance(final position)]. We loaded the distance values corresponding to each cell of the maze from a file. 


# Scope for improvement
•	Further optimization: there are several methods of optimizing genetic algorithms such as pruning which could be employed to achieve much better results.
•	Modularity: the program could be enhanced to read any maze of any size from a file to solve. While this in itself is not very challenging to implement, the issue of measuring distance for an unknown maze would have to be resolved.
•	Visualization: while viewing the path of the walkers is currently possible in the terminal window during program execution, a more aesthetically pleasing visualization of the maze and path taken by the walkers could be implemented to get a better sense of the trend of improvement through the generations
•	Active fitness measurement: It might be possible to identify a successful solution of the maze earlier by measuring fitness of walker after each move, however this would dramatically slow down program execution in the current implement. Perhaps an efficient way of doing this could be found including running walkers in individual threads. 

