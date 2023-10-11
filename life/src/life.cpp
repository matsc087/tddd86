//eller228
//matsc087
/**
 * Will ask you for a file name
 * the program will then open the file and display it
 * (only the grid) you then have the option to tick,
 * animate or quit.
 *
 * nextGen() is used for the tick and animate
 * PrintGridRep() is used to print a readable grid
 * calcNeighbours() is used create a new grid with
 * integers to know how many neighbours each cell has
 * getGrid() and GetFileContents() is used to read the file
 * animate() is used to animate
 */

#include <iostream>
#include "grid.h"
#include "lifeutil.h"
#include <string>
#include <fstream>

std::string getFileContents(Grid<char> &grid);
Grid<char> getGrid(const std::string file_contents,  Grid<char> &grid);
void printGridRep(const Grid<char> &grid);
Grid<int> createNeighbourGrid(const int rows,const int cols);
Grid<int> calcNeighbours(const Grid<char> &grid);
void nextGen(Grid<char>& grid);
void animate(Grid<char>& grid);

int main(){
    /**
     * @brief main
     * gets the desired textfile from user
     * then prints the grid and asks for
     * input from the user which then either
     * animates, ticks or quits.
     *
     */

    Grid<char>grid;
    std::string file_contents = getFileContents(grid);
    getGrid(file_contents, grid);
    printGridRep(grid);
    bool running = true;
    while(running)
    {
        std::cout << "a)nimate, t)ick, q)uit? " << std::endl;
        char input;
        std::cin >> input;
        std::cout << std::endl;

        switch (input)
        {
            case 't':
            nextGen(grid);

            break;

        case 'a':
            animate(grid);
            break;

        case 'q':
            std::cout << "Have a nice life!" << std::endl;
            running = false;
            break;
        }
    }
    return 0;
}


std::string getFileContents(Grid<char> &grid){
    /**
     * @brief gridstring saves the filecontent
     * in a string variable, using & as a way
     * to differentiate between rows. Which is
     * Utilized in the getGrid function.
     *
     */
    std::string gridString;
    std::string line;
    int row, column;
    std::string fileName = "";
    std::cout << "Choose a file: "  << std::endl;
    std::getline(std::cin, fileName);
    std::ifstream file(fileName);

    file >> row >> column;

    while (std::getline(file, line)) {
        gridString += line + "&";
    }

    file.close();
    grid.resize(row,column);
    return gridString;
}


Grid<char> getGrid(const std::string file_contents, Grid<char> &grid){
    /**
     * @brief grid is now created by observing file_contents.
     * When the while loop encounters an '&' sign
     * it increments row and starts adding values in column
     * until the next & sign.
     */
    std::string gridString = file_contents;
    int row = grid.numRows();
    int rowNumb = 0, columnNumb = 0;
    int i = 0;

    while(rowNumb < row){
        char value = gridString[i];
        if(value == '&'){
            rowNumb++;
            columnNumb = 0;
        }
        else{
            grid.set(rowNumb, columnNumb, value);
            columnNumb++;
        }
        i++;

    }
     return grid;
}


void printGridRep(const Grid<char> &grid)
{
    /**
     * @brief Gets the values in grid and prints them
     *
     */
    int nRows = grid.numRows();
    int nColumn = grid.numCols();
    for(int row = 0;row < nRows;row++)
    {
        for(int column = 0; column < nColumn; column++){
            char value = grid.get(row, column);
            std::cout << value;
        }
        std::cout << std::endl;

    }
}

Grid<int> calcNeighbours(const Grid<char> &grid){
    /**
     * @brief Returns a grid with number of neighbours in
     * each cell. the Neighbourgrid is then used in
     * nextGen() to calculate the next generation according
     * to the rules.
     *
     */
    int nRows = grid.numRows();
    int nColumn = grid.numCols();
    int directionsx[] = {-1, 0, 1, 0, -1, -1, 1, 1};
    int directionsy[] = {0, -1, 0, 1, -1, 1, -1, 1};
    //Grid<gridState>gridSpecifics(nRows, nColumn);
    Grid<int>neighbourGrid = createNeighbourGrid(nRows, nColumn);
    for(int row = 0;row < nRows;row++)
    {
        for(int column = 0; column < nColumn; column++){
            char value = grid.get(row, column);
            if(value == 'X')
            {
                for(int i = 0; i < 8; i++)
                {
                    int posRow = row + directionsy[i];
                    int posCol = column + directionsx[i];
                    if (grid.inBounds(posRow, posCol)){
                        int preValue = neighbourGrid.get(posRow, posCol);
                        neighbourGrid.set(posRow, posCol, preValue + 1);
                    }
                }
            }
        }
    }

    return neighbourGrid;
}

void nextGen(Grid<char> &grid){
    /**
     * @brief neighbourGrid
     * Calculates the next generation and
     * updates the existing grid with the
     * new values.
     */
    Grid<int> neighbourGrid = calcNeighbours(grid);
    int nRows = neighbourGrid.numRows();
    int nColumn = neighbourGrid.numCols();

    for(int row = 0;row < nRows;row++)
    {
        for(int column = 0; column < nColumn; column++){
            int value = neighbourGrid.get(row, column);
            if(value == 0 || value == 1)
            {
                grid.set(row, column, '-');
            }
            else if(value == 3)
            {
                grid.set(row, column, 'X');
            }
            else if(value > 3)
            {
                grid.set(row, column, '-');
            }
        }
    }
    printGridRep(grid);
}





Grid<int> createNeighbourGrid(const int rows, const int cols){
    /**
     * @brief neighbourGrid
     * @return a Grid with 0 in all cells
     * with the same width and heigth as
     * the grid
     */
    Grid<int>neighbourGrid(rows,cols);
    int nRows = neighbourGrid.numRows();
    int nColumn = neighbourGrid.numCols();

    for(int row = 0;row < nRows;row++)
    {
        for(int column = 0; column < nColumn; column++){
            neighbourGrid.set(row, column, 0);
        }
    }
    return neighbourGrid;
}

void animate(Grid<char>& grid)
{
     /**
      * Runs nextGen() with
      * 100ms intervalls
      */

    while(true)
    {
         nextGen(grid);
         pause(100);

    }
}




