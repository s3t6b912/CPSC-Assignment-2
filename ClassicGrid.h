/* ClassicGrid.h
  This is the header file for ClassicGrid
  @author Sebastian Brumm
  @author brumm@chapman.edu
  @author Id:2319132
*/
#include <iostream>

using namespace std;

class ClassicGrid{
public:
  //constructors
  ClassicGrid();
  ClassicGrid(int rows, int columns);
  ~ClassicGrid();

  //core
  bool play(int mode);
  int getNeighborsClassic(int row, int column);
  int getNeighborsMirror(int row, int column);
  int getNeighborsDonut(int row, int column);
  void initializeNoFile(double density);
  void initializeFile(int row, string line);

  //aux
  bool isEmpty();
  bool isStable();
  void printToFile(ofstream& output, int gen);
  void printToOut(int gen);

  //variables
  int gridRows;
  int gridColumns;
  char** grid;
  char** shadowGrid;
};
