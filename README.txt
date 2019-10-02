Name: Sebastian Brumm
ID: 2319132
Section: 01
Date: 10/1/19
Assignment 2 - Game of Life

References:
None except listening to you

How to run:
Change directory to src and type make to compile
Then ./Assignment2.out

Notes on program:
1. I hardcoded it so that it will automatically stop running after 1000 generations in case it is oscillating.
2. For reading from a file, I couldn't figure out error throwing so the program will spit out the default error if the file DNE or is not in the right format.
3. Yes I know the class file is called ClassicGrid I first thought I would have separate classes for each of the modes but after I created classic mode I realized I only needed
to add two functions to detect the neighbors for the different modes and I didn't want to have to go back and rename everything to just Grid.
4. The main function is probably twice as long as it should be and that is because I had trouble figuring out how to declare objects outside of the scope of if statements.