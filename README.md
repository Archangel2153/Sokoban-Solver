# Sokoban-Solver

Group:
- Onno de Gouw
- Stefan Popa

---------------------------------------------------------------------

In this program, we have used both Breadth-First Search (BFS) and Depth-First Search (BFS) to solve various Sokoban puzzles. In these text files a puzzle starting configuration is described by a matrix of cells that have the following representation:
- a wall cell by ‘*’,
- an empty cell by ‘ ’ (space character),
- an empty destination cell by ‘.’,
- the worker on an empty cell by ‘w’, and the worker on a destination cell by ‘W’,
- a box on an empty cell by ‘b’, and a box on a destination cell by ‘B’.

Moreover, a console application offers the following commands to the user:
- Enter the name of a Sokoban configuration file: reads the file, and reports whether or not this was successful, and if it was successful, shows the Sokoban configuration,
- Enter the choice to solve the Sokoban puzzle via depth first search or breadth first search; if the choice is depth first search, then the user must also provide an upper bound on the depth.

The project was made for the course Imperative Programming at Radboud University, cohort 2018.

Note: Parts of the coded were implemented by the professors of the course.
