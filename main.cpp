//Stefan Popa / s1027672 / Assignment 13 Bonus
//Onno de Gouw / s1025613 / Assignment 13 Bonus

#include <iostream>
#include <fstream>
#include <vector>
#include <cstring>
#include <cassert>
#include <string>

using namespace std;

/*********************************************************************
                Variables and structures declarations
**********************************************************************/

const int MAX_ROWS = 20 ;
const int MAX_COLUMNS = 20 ;

struct position
{
    int row ;
    int column ;
} ;

struct config
{
    int Puzzle[MAX_ROWS][MAX_COLUMNS] ;
    vector<position> boxes ;
    position worker ;
} ;

struct Candidate
{
    config candidate ;
    int parent_candidate ;
} ;

/*********************************************************************
                    Check if puzzle is the same
**********************************************************************/
bool check_array(int a[MAX_ROWS][MAX_COLUMNS], int b[MAX_ROWS][MAX_COLUMNS], int rows, int columns)
{
    //PreCondition
    assert(rows >=0 && columns >= 0) ;
    /*
    PostCondition:
    the function returns true if the maps are the same
    */
    for(int i = 0; i < rows; i++)
        for(int j = 0; j < columns; j++)
            if(a[i][j] != b[i][j])
                return false;
    return true ;
}

/*********************************************************************
                    Read the initial configuration
**********************************************************************/

void read_puzzle(config& start, int& rows, int& columns)
{
    //PreCondition
    assert(rows >=0 && columns >= 0) ;
    /*
    PostCondition:
    the function reads a file and puts in the array different values for each symbol
    */

    string filename;
    cout << "Please enter a filename: " ; getline(cin, filename) ;

    ifstream fin(filename.c_str()) ;

    if(!fin.is_open())
        cout << "Could not open the file." ;

    char c ;
    int column = 0 ;
    int index_box = 3 ;

    fin.get(c);

    while(fin)
    {

        if(c == 'B')
            {
                start.Puzzle[rows][column++] = -1*index_box ;
                position box ;
                box.row = rows ;
                box.column = column - 1;
                start.boxes.push_back(box) ;
                index_box++ ;
            }
        else if (c == 'W')
            {
                start.Puzzle[rows][column++] = -2 ;
                start.worker.row = rows ;
                start.worker.column = column - 1;
            }
        else if (c == '.')
            start.Puzzle[rows][column++] = -1 ;
        else if (c == ' ')
            start.Puzzle[rows][column++] = 0 ;
        else if (c == '*')
            start.Puzzle[rows][column++] = 1 ;
        else if (c == 'w')
            {
                start.Puzzle[rows][column++] = 2 ;
                start.worker.row = rows ;
                start.worker.column = column - 1;
            }
        else if (c == 'b')
            {
                start.Puzzle[rows][column++] = index_box ;
                position box ;
                box.row = rows ;
                box.column = column - 1 ;
                start.boxes.push_back(box) ;
                index_box++ ;
            }
        else
        {
            rows++ ;
            columns = column ;
            column = 0 ;
        }

        fin.get(c);
    }
}

/*********************************************************************
                    Write starting configuration
**********************************************************************/

void output_puzzle(config puzzle, int rows, int columns)
{
    //PreCondition
    assert(rows >=0 && columns >= 0) ;
    /*
    PostCondition:
    the function outputs a given configuration
    */
    for(int i = 0; i < rows; i++)
    {
        for(int j = 0; j < columns; j++)
        {
            if(puzzle.Puzzle[i][j] <= -3)
                cout<<"B" ;
            else if(puzzle.Puzzle[i][j] == -2)
                cout<<"W" ;
            else if(puzzle.Puzzle[i][j] == -1)
                cout<<"." ;
            else if(puzzle.Puzzle[i][j] == 0)
                cout<<" " ;
            else if(puzzle.Puzzle[i][j] == 1)
                cout<<"*" ;
            else if(puzzle.Puzzle[i][j] == 2)
                cout<<"w" ;
            else if(puzzle.Puzzle[i][j] >= 3)
                cout<<"b" ;
        }
        cout<<endl;
    }

}

/*********************************************************************
                         Vector size
**********************************************************************/

int size (vector<position>& boxes)
{
    //PreCondition
    assert(true) ;
    /*
    PostCondition:
    the function will return the size of the vector as an integer
    */
    return static_cast<int> (boxes.size ()) ;
}

int size_candidate (vector<Candidate>& c)
{
    //PreCondition
    assert(true) ;
    /*
    PostCondition:
    the function will return the size of the vector as an integer
    */
    return static_cast<int> (c.size ()) ;
}

int size_config (vector<config>& c)
{
    //PreCondition
    assert(true) ;
    /*
    PostCondition:
    the function will return the size of the vector as an integer
    */
    return static_cast<int> (c.size ()) ;
}

/*********************************************************************
                        Test movement
**********************************************************************/

/*********************************************************************
                            North
**********************************************************************/
bool can_go_north_box (config puzzle, int i, int j)
{
    //PreCondition
    assert(i >=0 && j >= 0) ;
    /*
    PostCondition:
    the function check whether the box can be moved north
    */
    if(puzzle.Puzzle[i-1][j] == 0 || puzzle.Puzzle[i-1][j] == -1)
        return true ;
    return false ;
}

bool can_go_north (config puzzle)
{
    //PreCondition
    assert(true) ;
    /*
    PostCondition:
    the function check whether the worker can be moved north and check for box cases as well
    */
    if(puzzle.Puzzle[puzzle.worker.row - 1][puzzle.worker.column] != 1)
    {
        if(puzzle.Puzzle[puzzle.worker.row - 1][puzzle.worker.column] >= 3 || puzzle.Puzzle[puzzle.worker.row - 1][puzzle.worker.column] <= -3)
            return (can_go_north_box(puzzle, puzzle.worker.row - 1, puzzle.worker.column)) ;
        else return true ;
    }
    return false ;
}

/*********************************************************************
                            South
**********************************************************************/

bool can_go_south_box (config puzzle, int i, int j)
{
    //PreCondition
    assert(i >=0 && j >= 0) ;
    /*
    PostCondition:
    the function check whether the box can be moved south
    */
    if(puzzle.Puzzle[i+1][j] == 0 || puzzle.Puzzle[i+1][j] == -1)
        return true ;
    return false ;
}

bool can_go_south (config puzzle)
{
    //PreCondition
    assert(true) ;
    /*
    PostCondition:
    the function check whether the worker can be moved south and check for box cases as well
    */
    if(puzzle.Puzzle[puzzle.worker.row + 1][puzzle.worker.column] != 1)
    {
        if(puzzle.Puzzle[puzzle.worker.row + 1][puzzle.worker.column] >= 3 || puzzle.Puzzle[puzzle.worker.row + 1][puzzle.worker.column] <= -3)
            return (can_go_south_box(puzzle, puzzle.worker.row + 1, puzzle.worker.column)) ;
        else return true ;
    }
    return false ;
}

/*********************************************************************
                            East
**********************************************************************/

bool can_go_east_box (config puzzle, int i, int j)
{
    //PreCondition
    assert(i >=0 && j >= 0) ;
    /*
    PostCondition:
    the function check whether the box can be moved east
    */
    if(puzzle.Puzzle[i][j+1] == 0 || puzzle.Puzzle[i][j+1] == -1)
        return true ;
    return false ;
}

bool can_go_east (config puzzle)
{
    //PreCondition
    assert(true) ;
    /*
    PostCondition:
    the function check whether the worker can be moved east and check for box cases as well
    */
    if(puzzle.Puzzle[puzzle.worker.row][puzzle.worker.column + 1] != 1)
    {
        if(puzzle.Puzzle[puzzle.worker.row][puzzle.worker.column + 1] >= 3 || puzzle.Puzzle[puzzle.worker.row][puzzle.worker.column + 1] <= -3)
            return (can_go_east_box(puzzle, puzzle.worker.row, puzzle.worker.column + 1)) ;
        else return true ;
    }
    return false ;
}

/*********************************************************************
                            West
**********************************************************************/

bool can_go_west_box (config puzzle, int i, int j)
{
    //PreCondition
    assert(i >=0 && j >= 0) ;
    /*
    PostCondition:
    the function check whether the box can be moved west
    */
    if(puzzle.Puzzle[i][j-1] == 0 || puzzle.Puzzle[i][j-1] == -1)
        return true ;
    return false ;
}

bool can_go_west (config puzzle)
{
    //PreCondition
    assert(true) ;
    /*
    PostCondition:
    the function check whether the worker can be moved west and check for box cases as well
    */
    if(puzzle.Puzzle[puzzle.worker.row][puzzle.worker.column - 1] != 1)
    {
        if(puzzle.Puzzle[puzzle.worker.row][puzzle.worker.column - 1] >= 3 || puzzle.Puzzle[puzzle.worker.row][puzzle.worker.column - 1] <= -3)
            return (can_go_west_box(puzzle, puzzle.worker.row, puzzle.worker.column - 1)) ;
        else return true ;
    }
    return false ;
}

/*********************************************************************
                         New position
**********************************************************************/

/*********************************************************************
                            North
**********************************************************************/

position north (config puzzle)
{
    //PreCondition
    assert(true) ;
    /*
    PostCondition:
    the function calculates the next north position for worker
    */

    position next ;

    next.row = puzzle.worker.row - 1 ;
    next.column = puzzle.worker.column ;

    return next ;
}

/*********************************************************************
                            South
**********************************************************************/

position south (config puzzle)
{
    //PreCondition
    assert(true) ;
    /*
    PostCondition:
    the function calculates the next south position for worker
    */

    position next ;

    next.row = puzzle.worker.row + 1 ;
    next.column = puzzle.worker.column ;

    return next ;
}

/*********************************************************************
                            East
**********************************************************************/

position east (config puzzle)
{
    //PreCondition
    assert(true) ;
    /*
    PostCondition:
    the function calculates the next east position for worker
    */

    position next ;

    next.row = puzzle.worker.row ;
    next.column = puzzle.worker.column + 1 ;

    return next ;
}

/*********************************************************************
                            West
**********************************************************************/

position west (config puzzle)
{
    //PreCondition
    assert(true) ;
    /*
    PostCondition:
    the function calculates the next west position for worker
    */
    position next ;

    next.row = puzzle.worker.row ;
    next.column = puzzle.worker.column - 1 ;

    return next ;
}

/*********************************************************************
                    Change configuration
**********************************************************************/

config change(config puzzle, position next)
{
        //PreCondition
        assert(true) ;
        /*
        PostCondition:
        the function changes position of the worker and/or the box
        */

        if(puzzle.Puzzle[puzzle.worker.row][puzzle.worker.column] == -2)
            puzzle.Puzzle[puzzle.worker.row][puzzle.worker.column] = -1 ;
        else
            puzzle.Puzzle[puzzle.worker.row][puzzle.worker.column] = 0 ;

        int row_box = next.row - puzzle.worker.row ;
        int column_box = next.column - puzzle.worker.column ;

        puzzle.worker.row = next.row ;
        puzzle.worker.column = next.column ;


        if(puzzle.Puzzle[puzzle.worker.row][puzzle.worker.column] == -1)
            puzzle.Puzzle[puzzle.worker.row][puzzle.worker.column] = -2 ;
        else if(puzzle.Puzzle[puzzle.worker.row][puzzle.worker.column] == 0)
            puzzle.Puzzle[puzzle.worker.row][puzzle.worker.column] = 2 ;
        else if(puzzle.Puzzle[puzzle.worker.row][puzzle.worker.column] >= 3 || puzzle.Puzzle[puzzle.worker.row][puzzle.worker.column] <= -3)
        {
            int index = puzzle.Puzzle[puzzle.worker.row][puzzle.worker.column] ;
            int neg = 0 ;

            if(index < 0)
                {
                    index = -1 * index ;
                    neg = 1 ;
                }

            index -= 3 ;

            puzzle.boxes[index].row += row_box ;
            puzzle.boxes[index].column += column_box ;

            if(puzzle.Puzzle[puzzle.boxes[index].row][puzzle.boxes[index].column] == -1)
                puzzle.Puzzle[puzzle.boxes[index].row][puzzle.boxes[index].column] = -1 * (index + 3) ;
            else
                puzzle.Puzzle[puzzle.boxes[index].row][puzzle.boxes[index].column] = index + 3 ;

            if(neg == 1)
                puzzle.Puzzle[puzzle.worker.row][puzzle.worker.column] = -2 ;
            else
                puzzle.Puzzle[puzzle.worker.row][puzzle.worker.column] = 2 ;
        }

    return puzzle;
}

/*********************************************************************
                    Check if puzzle is ready
**********************************************************************/

bool puzzle_ready (config puzzle, int rows, int columns)
{
    //PreCondition
    assert(rows >= 0 && columns >= 0) ;
    /*
    PostCondition:
    the function check if the configuration is a solution
    */
    for (int i = 0; i < rows; i++)
       for (int j = 0; j < columns; j++)
         if(puzzle.Puzzle[i][j] >= 3)
            return false ;
    return true;
}

/*********************************************************************
         Check previous nodes for same configuration _ BFS
**********************************************************************/

bool puzzle_present(vector<Candidate> c, int i, Candidate new_puzzle, int rows, int columns)
{
    //PreCondition
    assert(rows >= 0 && columns >= 0 && i >= 0) ;
    /*
    PostCondition:
    the function check if a configuration was already explored
    */
    for (int index = 0; index < i; index++)
        if(check_array(c[index].candidate.Puzzle, new_puzzle.candidate.Puzzle, rows, columns))
            return true ;

    return false ;
}

/*********************************************************************
                Add the new puzzle to the list _ BFS
**********************************************************************/

void tries(vector<Candidate>& c, int i, position next, int rows, int columns)
{
    //PreCondition
    assert(rows >= 0 && columns >= 0 && i >= 0) ;
    /*
    PostCondition:
    the function adds a configuration to the vector if it is new or skips it if it was already explored
    */

    config p = c[i].candidate ;
    config newp = change(p, next) ;
    Candidate newc = {newp, i} ;

    if(!puzzle_present(c, i, newc, rows, columns))
        c.push_back(newc) ;
}

/*********************************************************************
                            Count steps _ BFS
**********************************************************************/
void show_steps (vector<Candidate> c, int i)
{
    //PreCondition
    assert(i >= 0) ;
    /*
    PostCondition:
    the function shows the number of steps necessary to get to the final, best solution
    */

    int counter = 0 ;

    while (i != -1)
    {
        i = c[i].parent_candidate ;
        counter ++ ;
    }

    cout<<counter - 1;
}


/*********************************************************************
                                BFS
**********************************************************************/
void solve (config start, int rows, int columns)
{
    //PreCondition
    assert(rows >= 0 && columns >= 0) ;
    /*
    PostCondition:
    the function executed a breadth-first search
    */
   vector<Candidate> c = {{start, -1}} ;
   int i = 0 ;
   while (i < size_candidate(c) && !puzzle_ready (c[i].candidate, rows, columns))
   {
       config p = c[i].candidate ;
      if (can_go_north(p))
        tries(c, i, north(p), rows, columns) ;
      if (can_go_south(p))
        tries(c, i, south(p), rows, columns) ;
      if (can_go_west(p))
        tries(c, i, west(p), rows, columns) ;
      if (can_go_east(p))
        tries(c, i, east(p), rows, columns) ;
      i = i+1 ;

   }
   if (i < size_candidate (c))
	   show_steps (c, i) ;
}

/*********************************************************************
        Check previous nodes for same configuration _ DFS
**********************************************************************/

bool puzzle_present_dfs(config new_puzzle, vector<config> attempt, int rows, int columns)
{
    //PreCondition
    assert(rows >= 0 && columns >= 0) ;
    /*
    PostCondition:
    the function check if a configuration was already explored
    */

    for (int index = 0; index < size_config(attempt); index++)
        if(check_array(attempt[index].Puzzle, new_puzzle.Puzzle, rows, columns))
            return true ;

    return false ;
}

/*********************************************************************
            Add the new puzzle to the list _ DFS
**********************************************************************/
void solve_dfs (vector<config>& attempt, vector<config>& shortest, int max_depth, int rows, int columns) ;

void tries_dfs (vector<config>& attempt, position next, vector<config>& shortest, int max_depth, int rows, int columns)
{
    //PreCondition
    assert(rows >= 0 && columns >= 0 && max_depth >= 0) ;
    /*
    PostCondition:
    the function adds a configuration to attempt if it is new or skips it if it was already explored
    */

   config p    = attempt[size_config(attempt) - 1] ;
   config newp = change(p, next) ;

   if (!puzzle_present_dfs (newp, attempt, rows, columns))
   {
       attempt.push_back (newp) ;
       solve_dfs (attempt, shortest, max_depth, rows, columns) ;
       attempt.pop_back () ;
   }
}

/*********************************************************************
                                DFS
**********************************************************************/

void solve_dfs (vector<config>& attempt, vector<config>& shortest, int max_depth, int rows, int columns)
{
    //PreCondition
    assert(rows >= 0 && columns >= 0 && max_depth >= 0 && size_config(attempt) > 0) ;
    /*
    PostCondition:
    the function executes a depth first search
    */
    const int CURRENT = size_config (attempt) ;
    const int BEST    = size_config (shortest) ;
    config p          = attempt[CURRENT-1] ;

    if (BEST > 0 && CURRENT >= BEST)      { return ; }
    else if (CURRENT > max_depth+1)       { return ; }
    else if (puzzle_ready (p, rows, columns)) { shortest = attempt ; return ; }
    if (can_go_north(p))
        tries_dfs (attempt, north(p), shortest, max_depth, rows, columns) ;
    if (can_go_south(p))
        tries_dfs (attempt, south(p), shortest, max_depth, rows, columns) ;
    if (can_go_west(p))
        tries_dfs (attempt, west(p), shortest, max_depth, rows, columns) ;
    if (can_go_east(p))
        tries_dfs (attempt, east(p), shortest, max_depth, rows, columns) ;
}

/*********************************************************************
                         Count steps _ DFS
**********************************************************************/

void steps_dfs (vector<config> shortest)
{
    //PreCondition
    assert(true) ;
    /*
    PostCondition:
    the function returns the number of steps to get to the best solution
    */
    cout<<size_config(shortest) - 1 ;
}

/*********************************************************************
                           User Interface
**********************************************************************/

void user_interface(config& start, int& rows, int& columns)
{
    vector<config> attempt ;
    vector<config> shortest ;

    string method ;

    read_puzzle(start, rows, columns) ;
    output_puzzle(start, rows, columns) ;

    cout << "Pick the searching method (DFS/BFS): " ;
    getline(cin, method) ;

    if (method == "DFS")
    {
        int depth ;
        cout << "Please enter the depth of the search as an integer: " ; cin >> depth ;

        attempt.push_back(start) ;
        solve_dfs (attempt, shortest, depth, rows, columns) ;

        cout << "Method of choice: DFS" << endl ;
        cout << "Depth: " << depth << endl ;
        cout << "Number of steps to solution: " ;
        steps_dfs(shortest) ;
        cout << endl ;
    }
    else
    {
        cout << "Method of choice: BFS" << endl ;
        cout << "Number of steps to get to solution: " ;
        solve(start, rows, columns) ;
        cout << endl ;
    }
}

int main()
{
    int rows = 0, columns = 0 ;
    config start ;

    user_interface(start, rows, columns) ;

    return 0;
}
