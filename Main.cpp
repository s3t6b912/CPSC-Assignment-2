/* Main.cpp
  This is the main function and implementation for Assignment 2 which is supposed to simulate Conway's Game of Life
  @author Sebastian Brumm
  @author brumm@chapman.edu
  @author Id:2319132
*/
#include <iostream>
#include <fstream>
#include <unistd.h>
#include "ClassicGrid.h"

using namespace std;

//Main function
//This is mainly just setting up the class ClassicGrid and deals with interaction with the user
int main(int argc, char *argv[]) {
  string answer;
  int mode;
  cout << "Welcome to a simulation of Conway's Game of Life!\n";
  cout << "There are three different modes you can choose from; Classic, Mirror or Donut.\n";
  cout << "These are how the boundries of the grid are calculated.\n";
  cout << "Which mode would you like to run? (classic/mirror/donut):\n";
  cin >> answer;
  if(answer == "classic"){
    mode = 0;
  }else if(answer == "mirror"){
    mode = 1;
  }else{
    mode = 2;
  }
  cout << "You can also choose to either provide a map file of the world you would like to simulate or generate a random one and give dimensions and initial population density.\n";
  cout << "Would you like to provide a map file or generate a world? (file/gen)\n";
  cin >> answer;
  if (answer == "file"){
    cout << "What is the name of the file? (include extension and make sure it is in the same folder)\n";
    string fileName;
    cin >> fileName;
    ifstream input (fileName);
    int temp = 1;
    int rows;
    int columns;
    string line;
    while(getline(input,line)){
      if(temp == 1){
        rows = stoi(line);
        if (rows < 2){
          rows = 2;
        }
        temp++;
      } else if (temp == 2){
        columns = stoi(line);
        if (columns < 2){
          columns = 2;
        }
        break;
      }
    }
    ClassicGrid game(rows,columns);
    temp = 0;
    while(getline(input,line)){
      game.initializeFile(temp++,line);
    }
    cout << "Do you want to generate the results to standard out or a file? (out/file)\n";
    cin >> answer;
    if (answer == "out"){
      cout << "Do you want to have to press enter after every generation, otherwise there will just be a slight pause. (y/n)\n";
      cin >> answer;
      int generation = 0;
      bool stable = false;
      if (answer == "y"){
        game.printToOut(generation);
        cin.get();
        while(!((stable)||(game.isEmpty()))){
          stable = game.play(mode);
          ++generation;
          game.printToOut(generation);
          cout << "Press enter to continue.\n";
          cin.get();
          if (stable || generation > 1000){
            cout << "Simulation has stablized.\n";
            cout << "Press enter to exit the program.\n";
            cin.get();
            cin.get();
            break;
          }
          if (game.isEmpty()){
            cout << "Everything is dead.\n";
            cout << "Press enter to exit the program.\n";
            cin.get();
            cin.get();
          }
        }
      }else{
        game.printToOut(generation);
        sleep(1);
        while(!((stable)||(game.isEmpty()))){
          stable = game.play(mode);
          ++generation;
          game.printToOut(generation);
          sleep(1);
          if (stable || generation > 1000){
            cout << "Simulation has stablized.\n";
            cout << "Press enter to exit the program.\n";
            cin.get();
            cin.get();
            break;
          }
          if (game.isEmpty()){
            cout << "Everything is dead.\n";
            cout << "Press enter to exit the program.\n";
            cin.get();
            cin.get();
          }
        }
      }
    }else{
      string outputFile;
      cout << "Enter the name of the output file with extension: \n";
      cin >> outputFile;
      ofstream output (outputFile);
      int generation = 0;
      bool stable = false;
      game.printToFile(output,generation);
      while(!((stable)||(game.isEmpty()))){
        stable = game.play(mode);
        ++generation;
        game.printToFile(output,generation);
        if (stable || generation > 1000){
          output << "Simulation has stablized.\n";
          cout << "Press enter to exit the program.\n";
          cin.get();
          cin.get();
          break;
        }
        if (game.isEmpty()){
          output << "Everything is dead.\n";
          cout << "Press enter to exit the program.\n";
          cin.get();
          cin.get();
        }
      }
    }
  }else{
    int rows;
    int columns;
    double density;
    cout << "How many rows: \n";
    cin >> rows;
    if (rows < 2){
      rows = 2;
    }
    cout << "How many columns: \n";
    cin >> columns;
    if (columns < 2){
      columns = 2;
    }
    cout << "What is the starting population density? (Enter a decimal value greater than zero and less than or equal to one)\n";
    cin >> density;
    ClassicGrid game(rows,columns);
    game.initializeNoFile(density);
    cout << "Do you want to generate the results to standard out or a file? (out/file)\n";
    cin >> answer;
    if (answer == "out"){
      cout << "Do you want to have to press enter after every generation, otherwise there will just be a slight pause. (y/n)\n";
      cin >> answer;
      int generation = 0;
      bool stable = false;
      if (answer == "y"){
        game.printToOut(generation);
        cin.get();
        while(!((stable)||(game.isEmpty()))){
          stable = game.play(mode);
          ++generation;
          game.printToOut(generation);
          cout << "Press enter to continue.\n";
          cin.get();
          if (stable || generation > 1000){
            cout << "Simulation has stablized.\n";
            cout << "Press enter to exit the program.\n";
            cin.get();
            cin.get();
            break;
          }
          if (game.isEmpty()){
            cout << "Everything is dead.\n";
            cout << "Press enter to exit the program.\n";
            cin.get();
            cin.get();
          }
        }
      }else{
        game.printToOut(generation);
        sleep(1);
        while(!((stable)||(game.isEmpty()))){
          stable = game.play(mode);
          ++generation;
          game.printToOut(generation);
          sleep(1);
          if (stable || generation > 1000){
            cout << "Simulation has stablized.\n";
            cout << "Press enter to exit the program.\n";
            cin.get();
            cin.get();
            break;
          }
          if (game.isEmpty()){
            cout << "Everything is dead.\n";
            cout << "Press enter to exit the program.\n";
            cin.get();
            cin.get();
          }
        }
      }
    }else{
      string outputFile;
      cout << "Enter the name of the output file with extension: \n";
      cin >> outputFile;
      ofstream output (outputFile);
      int generation = 0;
      bool stable = false;
      game.printToFile(output,generation);
      while(!((stable)||(game.isEmpty()))){
        stable = game.play(mode);
        ++generation;
        game.printToFile(output,generation);
        if (stable || generation > 1000){
          output << "Simulation has stablized.\n";
          cout << "Press enter to exit the program.\n";
          cin.get();
          cin.get();
          break;
        }
        if (game.isEmpty()){
          output << "Everything is dead.\n";
          cout << "Press enter to exit the program.\n";
          cin.get();
          cin.get();
        }
      }
    }
  }
  return 0;
}
