/* ClassicGrid.cpp
  This is the main class file for Assignment 2 and is supposed to replicate Conway's Game of Life
  @author Sebastian Brumm
  @author brumm@chapman.edu
  @author Id:2319132
*/
#include "ClassicGrid.h"
#include <iostream>
#include <fstream>
#include <random>

using namespace std;

//Default constructor of the class
ClassicGrid::ClassicGrid(){
  gridRows = 10;
  gridColumns = 10;
  grid = new char*[gridRows];
  for (int i = 0; i < 10; i++){
    grid[i] = new char[10];
  }
  shadowGrid = new char*[gridRows];
  for (int i = 0; i < 10; i++){
    shadowGrid[i] = new char[10];
  }
}

//Overloaded constructor of the class
ClassicGrid::ClassicGrid(int rows, int columns){
  gridRows = rows;
  gridColumns = columns;
  grid = new char*[rows];
  for (int i = 0; i < rows; i++){
    grid[i] = new char[columns];
  }
  shadowGrid = new char*[rows];
  for (int i = 0; i < rows; i++){
    shadowGrid[i] = new char[columns];
  }
}

//Decontructor of the class
ClassicGrid::~ClassicGrid(){
  for (int i = 0; i < gridRows; i++){
    delete[] grid[i];
  }
  delete[] grid;
  for (int i = 0; i < gridRows; i++){
    delete[] shadowGrid[i];
  }
  delete[] shadowGrid;
}

//The main function of this class that reads the grid, computes the new generation on a secondary shadowGrid, and then sets the original grid
//equal to the shadowGrid
bool ClassicGrid::play(int mode){
  bool stable = false;
  int temp;
  for (int i = 0; i < gridRows; i++){
    for (int j = 0; j < gridColumns; j++){
      if(mode == 0){
        temp = getNeighborsClassic(i,j);
      }else if(mode == 1){
        temp = getNeighborsMirror(i,j);
      }else{
        temp = getNeighborsDonut(i,j);
      }
      if (temp <= 1){
        shadowGrid[i][j] = '-';
      } else if (temp == 3){
        shadowGrid[i][j] = 'X';
      } else if (temp > 3){
        shadowGrid[i][j] = '-';
      }
    }
  }
  stable = isStable();
  for (int i = 0; i < gridRows; i++){
    for (int j = 0; j < gridColumns; j++){
      grid[i][j] = shadowGrid[i][j];
    }
  }
  return stable;
}

//This is the algorithm that determines the number of neighbors a space in the grid has constrained by the Classic mode
int ClassicGrid::getNeighborsClassic(int row, int column){
  int temp = 0;
  if ((row == gridRows-1)&&(column == gridColumns-1)){ //bottom right corner check
    if (grid[row-1][column] == 'X'){
      ++temp;
    }
    if (grid[row-1][column-1] == 'X'){
      ++temp;
    }
    if (grid[row][column-1] == 'X'){
      ++temp;
    }
  } else if ((row == 0)&&(column == gridColumns-1)){ //top right corner check
    if (grid[row][column-1] == 'X'){
      ++temp;
    }
    if (grid[row+1][column] == 'X'){
      ++temp;
    }
    if (grid[row+1][column-1] == 'X'){
      ++temp;
    }
  } else if ((row == 0)&&(column == 0)){ //top left corner check
    if (grid[row][column+1] == 'X'){
      ++temp;
    }
    if (grid[row+1][column] == 'X'){
      ++temp;
    }
    if (grid[row+1][column+1] == 'X'){
      ++temp;
    }
  } else if ((row == gridRows-1)&&(column == 0)){ //bottom left corner check
    if (grid[row][column+1] == 'X'){
      ++temp;
    }
    if (grid[row-1][column] == 'X'){
      ++temp;
    }
    if (grid[row-1][column+1] == 'X'){
      ++temp;
    }
  } else if (row == 0){ //top row check
    if (grid[row][column+1] == 'X'){
      ++temp;
    }
    if (grid[row][column-1] == 'X'){
      ++temp;
    }
    if (grid[row+1][column] == 'X'){
      ++temp;
    }
    if (grid[row+1][column+1] == 'X'){
      ++temp;
    }
    if (grid[row+1][column-1] == 'X'){
      ++temp;
    }
  } else if (row == gridRows-1){ //bottom row check
    if (grid[row][column+1] == 'X'){
      ++temp;
    }
    if (grid[row][column-1] == 'X'){
      ++temp;
    }
    if (grid[row-1][column] == 'X'){
      ++temp;
    }
    if (grid[row-1][column+1] == 'X'){
      ++temp;
    }
    if (grid[row-1][column-1] == 'X'){
      ++temp;
    }
  } else if (column == 0){ //first column check
    if (grid[row-1][column] == 'X'){
      ++temp;
    }
    if (grid[row+1][column] == 'X'){
      ++temp;
    }
    if (grid[row][column+1] == 'X'){
      ++temp;
    }
    if (grid[row-1][column+1] == 'X'){
      ++temp;
    }
    if (grid[row+1][column+1] == 'X'){
      ++temp;
    }
  } else if (column == gridColumns-1){ //last column check
    if (grid[row-1][column] == 'X'){
      ++temp;
    }
    if (grid[row+1][column] == 'X'){
      ++temp;
    }
    if (grid[row][column-1] == 'X'){
      ++temp;
    }
    if (grid[row-1][column-1] == 'X'){
      ++temp;
    }
    if (grid[row+1][column-1] == 'X'){
      ++temp;
    }
  } else { //every other square
    if (grid[row-1][column] == 'X'){
      ++temp;
    }
    if (grid[row+1][column] == 'X'){
      ++temp;
    }
    if (grid[row][column+1] == 'X'){
      ++temp;
    }
    if (grid[row][column-1] == 'X'){
      ++temp;
    }
    if (grid[row-1][column+1] == 'X'){
      ++temp;
    }
    if (grid[row+1][column+1] == 'X'){
      ++temp;
    }
    if (grid[row+1][column-1] == 'X'){
      ++temp;
    }
    if (grid[row-1][column-1] == 'X'){
      ++temp;
    }
  }
  return temp;
}

//This is the algorithm that determines the number of neighbors a space in the grid has constrained by the Mirror mode
int ClassicGrid::getNeighborsMirror(int row, int column){
  int temp = 0;
  if ((row == gridRows-1)&&(column == gridColumns-1)){ //bottom right corner check
    if (grid[row-1][column] == 'X'){
      temp = temp + 2;
    }
    if (grid[row-1][column-1] == 'X'){
      ++temp;
    }
    if (grid[row][column-1] == 'X'){
      temp = temp + 2;
    }
    if (grid[row][column] == 'X'){
      temp = temp + 3;
    }
  } else if ((row == 0)&&(column == gridColumns-1)){ //top right corner check
    if (grid[row][column-1] == 'X'){
      temp = temp + 2;
    }
    if (grid[row+1][column] == 'X'){
      temp = temp + 2;
    }
    if (grid[row+1][column-1] == 'X'){
      ++temp;
    }
    if (grid[row][column] == 'X'){
      temp = temp + 3;
    }
  } else if ((row == 0)&&(column == 0)){ //top left corner check
    if (grid[row][column+1] == 'X'){
      temp = temp + 2;
    }
    if (grid[row+1][column] == 'X'){
      temp = temp + 2;
    }
    if (grid[row+1][column+1] == 'X'){
      ++temp;
    }
    if (grid[row][column] == 'X'){
      temp = temp + 3;
    }
  } else if ((row == gridRows-1)&&(column == 0)){ //bottom left corner check
    if (grid[row][column+1] == 'X'){
      temp = temp + 2;
    }
    if (grid[row-1][column] == 'X'){
      temp = temp + 2;
    }
    if (grid[row-1][column+1] == 'X'){
      ++temp;
    }
    if (grid[row][column] == 'X'){
      temp = temp + 3;
    }
  } else if (row == 0){ //top row check
    if (grid[row][column+1] == 'X'){
      temp = temp + 2;
    }
    if (grid[row][column-1] == 'X'){
      temp = temp + 2;
    }
    if (grid[row+1][column] == 'X'){
      ++temp;
    }
    if (grid[row+1][column+1] == 'X'){
      ++temp;
    }
    if (grid[row+1][column-1] == 'X'){
      ++temp;
    }
    if (grid[row][column] == 'X'){
      ++temp;
    }
  } else if (row == gridRows-1){ //bottom row check
    if (grid[row][column+1] == 'X'){
      temp = temp + 2;
    }
    if (grid[row][column-1] == 'X'){
      temp = temp + 2;
    }
    if (grid[row-1][column] == 'X'){
      ++temp;
    }
    if (grid[row-1][column+1] == 'X'){
      ++temp;
    }
    if (grid[row-1][column-1] == 'X'){
      ++temp;
    }
    if (grid[row][column] == 'X'){
      ++temp;
    }
  } else if (column == 0){ //first column check
    if (grid[row-1][column] == 'X'){
      temp = temp + 2;
    }
    if (grid[row+1][column] == 'X'){
      temp = temp + 2;
    }
    if (grid[row][column+1] == 'X'){
      ++temp;
    }
    if (grid[row-1][column+1] == 'X'){
      ++temp;
    }
    if (grid[row+1][column+1] == 'X'){
      ++temp;
    }
    if (grid[row][column] == 'X'){
      ++temp;
    }
  } else if (column == gridColumns-1){ //last column check
    if (grid[row-1][column] == 'X'){
      temp = temp + 2;
    }
    if (grid[row+1][column] == 'X'){
      temp = temp + 2;
    }
    if (grid[row][column-1] == 'X'){
      ++temp;
    }
    if (grid[row-1][column-1] == 'X'){
      ++temp;
    }
    if (grid[row+1][column-1] == 'X'){
      ++temp;
    }
    if (grid[row][column] == 'X'){
      ++temp;
    }
  } else { //every other square
    if (grid[row-1][column] == 'X'){
      ++temp;
    }
    if (grid[row+1][column] == 'X'){
      ++temp;
    }
    if (grid[row][column+1] == 'X'){
      ++temp;
    }
    if (grid[row][column-1] == 'X'){
      ++temp;
    }
    if (grid[row-1][column+1] == 'X'){
      ++temp;
    }
    if (grid[row+1][column+1] == 'X'){
      ++temp;
    }
    if (grid[row+1][column-1] == 'X'){
      ++temp;
    }
    if (grid[row-1][column-1] == 'X'){
      ++temp;
    }
  }
  return temp;
}

//This is the algorithm that determines the number of neighbors a space in the grid has constrained by the Donut mode
int ClassicGrid::getNeighborsDonut(int row, int column){
  int temp = 0;
  if ((row == gridRows-1)&&(column == gridColumns-1)){ //bottom right corner check
    if (grid[row-1][column] == 'X'){
      ++temp;
    }
    if (grid[row-1][column-1] == 'X'){
      ++temp;
    }
    if (grid[row][column-1] == 'X'){
      ++temp;
    }
    if (grid[0][0] == 'X'){
      ++temp;
    }
    if (grid[0][gridColumns-1] == 'X'){
      ++temp;
    }
    if (grid[gridRows-1][0] == 'X'){
      ++temp;
    }
    if (grid[0][gridColumns-2] == 'X'){
      ++temp;
    }
    if (grid[gridRows-2][0]){
      ++temp;
    }
  } else if ((row == 0)&&(column == gridColumns-1)){ //top right corner check
    if (grid[row][column-1] == 'X'){
      ++temp;
    }
    if (grid[row+1][column] == 'X'){
      ++temp;
    }
    if (grid[row+1][column-1] == 'X'){
      ++temp;
    }
    if (grid[0][0] == 'X'){
      ++temp;
    }
    if (grid[gridRows-1][0] == 'X'){
      ++temp;
    }
    if (grid[gridRows-1][gridColumns-1] == 'X'){
      ++temp;
    }
    if (grid[gridRows-1][gridColumns-2] == 'X'){
      ++temp;
    }
    if (grid[1][0] == 'X'){
      ++temp;
    }
  } else if ((row == 0)&&(column == 0)){ //top left corner check
    if (grid[row][column+1] == 'X'){
      ++temp;
    }
    if (grid[row+1][column] == 'X'){
      ++temp;
    }
    if (grid[row+1][column+1] == 'X'){
      ++temp;
    }
    if (grid[gridRows-1][0] == 'X'){
      ++temp;
    }
    if (grid[gridRows-1][gridColumns-1] == 'X'){
      ++temp;
    }
    if (grid[0][gridColumns-1] == 'X'){
      ++temp;
    }
    if (grid[gridRows-1][1] == 'X'){
      ++temp;
    }
    if (grid[gridRows-1][1] == 'X'){
      ++temp;
    }
  } else if ((row == gridRows-1)&&(column == 0)){ //bottom left corner check
    if (grid[row][column+1] == 'X'){
      ++temp;
    }
    if (grid[row-1][column] == 'X'){
      ++temp;
    }
    if (grid[row-1][column+1] == 'X'){
      ++temp;
    }
    if (grid[gridRows-1][gridColumns-1] == 'X'){
      ++temp;
    }
    if (grid[0][gridColumns-1] == 'X'){
      ++temp;
    }
    if (grid[0][0] == 'X'){
      ++temp;
    }
    if (grid[0][1] == 'X'){
      ++temp;
    }
    if (grid[gridRows-2][gridColumns-1] == 'X'){
      ++temp;
    }
  } else if (row == 0){ //top row check
    if (grid[row][column+1] == 'X'){
      ++temp;
    }
    if (grid[row][column-1] == 'X'){
      ++temp;
    }
    if (grid[row+1][column] == 'X'){
      ++temp;
    }
    if (grid[row+1][column+1] == 'X'){
      ++temp;
    }
    if (grid[row+1][column-1] == 'X'){
      ++temp;
    }
    if (grid[gridRows-1][column] == 'X'){
      ++temp;
    }
    if (grid[gridRows-1][column+1] == 'X'){
      ++temp;
    }
    if (grid[gridRows-1][column-1] == 'X'){
      ++temp;
    }
  } else if (row == gridRows-1){ //bottom row check
    if (grid[row][column+1] == 'X'){
      ++temp;
    }
    if (grid[row][column-1] == 'X'){
      ++temp;
    }
    if (grid[row-1][column] == 'X'){
      ++temp;
    }
    if (grid[row-1][column+1] == 'X'){
      ++temp;
    }
    if (grid[row-1][column-1] == 'X'){
      ++temp;
    }
    if (grid[0][column] == 'X'){
      ++temp;
    }
    if (grid[0][column+1] == 'X'){
      ++temp;
    }
    if (grid[0][column-1] == 'X'){
      ++temp;
    }
  } else if (column == 0){ //first column check
    if (grid[row-1][column] == 'X'){
      ++temp;
    }
    if (grid[row+1][column] == 'X'){
      ++temp;
    }
    if (grid[row][column+1] == 'X'){
      ++temp;
    }
    if (grid[row-1][column+1] == 'X'){
      ++temp;
    }
    if (grid[row+1][column+1] == 'X'){
      ++temp;
    }
    if (grid[row][gridColumns-1] == 'X'){
      ++temp;
    }
    if (grid[row+1][gridColumns-1] == 'X'){
      ++temp;
    }
    if (grid[row-1][gridColumns-1] == 'X'){
      ++temp;
    }
  } else if (column == gridColumns-1){ //last column check
    if (grid[row-1][column] == 'X'){
      ++temp;
    }
    if (grid[row+1][column] == 'X'){
      ++temp;
    }
    if (grid[row][column-1] == 'X'){
      ++temp;
    }
    if (grid[row-1][column-1] == 'X'){
      ++temp;
    }
    if (grid[row+1][column-1] == 'X'){
      ++temp;
    }
    if (grid[row][0] == 'X'){
      ++temp;
    }
    if (grid[row+1][0] == 'X'){
      ++temp;
    }
    if (grid[row-1][0] == 'X'){
      ++temp;
    }
  } else { //every other square
    if (grid[row-1][column] == 'X'){
      ++temp;
    }
    if (grid[row+1][column] == 'X'){
      ++temp;
    }
    if (grid[row][column+1] == 'X'){
      ++temp;
    }
    if (grid[row][column-1] == 'X'){
      ++temp;
    }
    if (grid[row-1][column+1] == 'X'){
      ++temp;
    }
    if (grid[row+1][column+1] == 'X'){
      ++temp;
    }
    if (grid[row+1][column-1] == 'X'){
      ++temp;
    }
    if (grid[row-1][column-1] == 'X'){
      ++temp;
    }
  }
  return temp;
}

//This function randomly generates a grid given the density of the population as input
void ClassicGrid::initializeNoFile(double density){
  for (int i = 0; i < gridRows; i++){
    for (int j = 0; j < gridColumns; j++){
      grid[i][j] = '-';
    }
  }
   srand(time(0));
   int startingAmount;
   if (density <= 1){
     startingAmount = (gridRows*gridColumns)*(density);
   }else{
     startingAmount = (gridRows*gridColumns);
   }
   for (int x = 0; x < startingAmount; x++){
     int tempRow = rand() % gridRows;
     int tempColumn = rand() % gridColumns;
     if (grid[tempRow][tempColumn] == 'X'){
       --x;
     }else{
       grid[tempRow][tempColumn] = 'X';
     }
   }
  for (int i = 0; i < gridRows; i++){
    for (int j = 0; j < gridColumns; j++){
      shadowGrid[i][j] = grid[i][j];
    }
  }
}

//Converts a string into a row in the grid and that row number is taken as input
void ClassicGrid::initializeFile(int row, string line){
  for (int i = 0; i < gridColumns; i++){
    grid[row][i] = line[i];
    shadowGrid[row][i] = line[i];
  }
}

//Returns true if the grid is empty of cells and false if it isn't
bool ClassicGrid::isEmpty(){
  for (int i = 0; i < gridRows; i++){
    for (int j = 0; j < gridColumns; j++){
      if (grid[i][j] == 'X'){
        return false;
      }
    }
  }
  return true;
}

//Returns true if the grid is the same as the next generation and false if it isn't
bool ClassicGrid::isStable(){
  for (int i = 0; i < gridRows; i++){
    for (int j = 0; j < gridColumns; j++){
      if (!(grid[i][j] == shadowGrid[i][j])){
        return false;
      }
    }
  }
  return true;
}

//Prints the grid to a file along with the generation number
void ClassicGrid::printToFile(ofstream& output, int gen){
  output << "Generation: " << gen << endl;
  for (int i = 0; i < gridRows; i++){
    for (int j = 0; j < gridColumns; j++){
      output << grid[i][j];
    }
    output << endl;
  }
  output << endl;
}

//Prints the grid to the terminal along with the generation number
void ClassicGrid::printToOut(int gen){
  cout << "Generation: " << gen << endl;
  for (int i = 0; i < gridRows; i++){
    for (int j = 0; j < gridColumns; j++){
      cout << grid[i][j];
    }
    cout << endl;
  }
  cout << endl;
}
