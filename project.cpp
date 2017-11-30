/*****************************************************************************
Oregon State University
CS 325 Final Project - Group 31
30 November 2017
Shawn Cuddhy
Michael Ennis
Gerlin Guillaume
Implementation of approximation algorithm Random Nearest Neighbor.

Usage: <filename> <option>
    Option 1 = <= 3 minute run for number of cities 1 to 5000
    Option 2 = Unlimited time.

Description:
1. Takes input from file and created matrix graph.
2. Runs RNNA Algorithm and sets time based on option.
3. Outputs to filename.tour with minimum calculated distance followed by path.

* For timing output uncomment line 89, 97, 156-158
* Compile with -std=c++0x
*****************************************************************************/

#include <vector>
#include <iostream>
#include <string.h>
#include <fstream>
#include <math.h>
#include <climits>
#include <stdio.h>
#include <cstdlib>
#include <time.h>

/**************************************
                  city
Generic Structure to hold the necessary
data of the city in order to run the
RNNA Algorithm.
***************************************/
struct city{
public:
    int name;
    int x;
    int y;
    bool visited;
    city(){};
};

/**************************************
                  graph
Holds a vector of city pointers with
function to easily add cities. Also
Holds a count of number of cities added.
***************************************/
class graph{
public:
    std::vector<city*> graphCity;
    int cities = 0;
    void addCity(int name, int x, int y);
};

/**************************************
                  addcity()
Function that dynamically allocated a new
city to the graph vector.
***************************************/
void graph::addCity(int cityName, int x_cord, int y_cord)
{
    graphCity.push_back(new city);
    graphCity[cities]->name = cityName;
    graphCity[cities]->x = x_cord;
    graphCity[cities]->y = y_cord;
    graphCity[cities]->visited = false;
    cities += 1;
}

//Function Prototypes
int nearestNeighbor(graph G, int *path);
int repetitivenearestNeighbor(graph G, int *path, int numberToRun);
void printPath(int distance, int *path, int length,  std::string fileName);


int main(int argc, char* argv[])
{
    graph myGraph;
    int option = atoi(argv[2]);         // Set option for runtime
    int distance;                       // Receives distance from RNNA Algorithm
    int runAmount;                      // Times to run the RNNA Algorithm
    int *RNNAPath;                      // Holds the path of the TSP Approximation results
    //srand(time(NULL));
    if(argc != 3)
    {
        std::cout << "USAGE: <filename> <option>" << std::endl;
        std::cout << "Option 1: 0 ~ 3 Minute run." << std::endl;
        std::cout << "Option 2: 1 = Unlimited Time." << std::endl;
        return 1;
    }
    //clock_t begin = clock();            // Start Timing

    std::ifstream inputFile;
    std::string fileName;
    fileName = argv[1];                 // Set file to open to argv[1]
    inputFile.open(fileName);           // Open the file.
    if(!inputFile)
    {
        std::cout << "Error Opening file." << std::endl;
        return 1;
    }

    int intName, intX, intY, i;         // Temp variables for input.

    while(inputFile >> intName >> intX >> intY)
    {
        myGraph.addCity(intName, intX, intY);
    }

    /***********************************************
    Option 1 is meant to limit the time of the run
    to less than 3 minutes. Values based off running
    on flip.engr.oregonstate.edu at 9AM PST on
    30Nov2017. Times may vary based on server load.
    ***********************************************/
    if(option == 1)
    {
        if((myGraph.cities >= 0) && (myGraph.cities <= 1000))
        {
            runAmount = myGraph.cities;
        }
        else if((myGraph.cities >= 1001) && (myGraph.cities <= 2000))
        {
            runAmount = 950;
        }
        else if((myGraph.cities >= 2001) && (myGraph.cities <= 5000))
        {
            runAmount = 175;
        }
        else if(myGraph.cities >= 5001)
        {
            runAmount = 346; // Intended for 1 hour run on tsp_example_1.txt
        }
    }
    else if(option == 2)    // Override option for unlimited time run.
    {
        runAmount = myGraph.cities;
    }
    else
    {
        std::cout << "Invalid Option" << std::endl;
        return 1;
    }

    // Allocate path, Call Algorithm, Print Results
    RNNAPath = new int[myGraph.cities];
    distance = repetitivenearestNeighbor(myGraph, RNNAPath, runAmount);
    printPath(distance, RNNAPath, myGraph.cities, fileName);

    //clock_t end = clock();
    //double time_spent = (((double)(end - begin)) / CLOCKS_PER_SEC);
    //std::cout << "Cities: " << myGraph.cities << " Cities Ran: " << runAmount << " Took: " << time_spent << " seconds" << std::endl;

    return 0;
}

/*****************************************************************
Repetitive Nearest Neighbor Algorithm (Repetitive Aspect)
For 0 to Number of Times to Run.
Call NNA with starting point incrementing from 0 to times to run
Keep best distance and set path in main if new best past found.
Return Best Distance.
*****************************************************************/
int repetitivenearestNeighbor(graph G, int *path, int numberToRun)
{
    int roundDistance, roundCity, checker, index, start, i, j, k;   // Temp Variables
    int bestDistance = INT_MAX;         // Tracks best distance after each round. Initialized to max int value.
    int currentRoundDistance = INT_MAX; // Tracks current round distance. Initialized to max int value
    int tempPath[G.cities];             // Temp variable to hold path of current best path.
    double x, y, dist;                  // Used for calculating ellucian distance.
    city *currentCity;

    for(k = 0; k < numberToRun; k++)    // Runs from city 0 to numberToRun(Max G.cities)
    {
        // Used to work around bool visited.
        if(k % 2 == 0)  // even
            checker = 0;
        else            // odd
            checker = 1;

        // Set up starting variables
        index = 0;
        currentRoundDistance = 0;

        // Places starting city in Path.
        // Sets it to the current city.
        // Sets appropriate true false value.
        tempPath[index] = G.graphCity[k]->name;
        currentCity = G.graphCity[k];
        if(checker == 0)
            G.graphCity[k]->visited = true;
        else
            G.graphCity[k]->visited = false;

        /*****************************************************************************
        Nearest Neighbor Algorithm (Non-Repetitive Aspect))
        For 0 to Number of Cities
        Find closest city by Ellucean Distance
            Add closest city to path
            Increment distance
            Set boolean
        Add Distance from last city to starting point

        *****************************************************************************/
        for(j = 0; j < G.cities; j++)
        {
            roundDistance = INT_MAX;
            for(i = 0; i < G.cities; i++)
            {
                if(((G.graphCity[i]->visited == false) && (checker == 0)) || ((G.graphCity[i]->visited == true) && (checker == 1)))
                {
                    if(currentCity->name != G.graphCity[i]->name)
                    {
                        x = (currentCity->x - G.graphCity[i]->x);
                        y = (currentCity->y - G.graphCity[i]->y);
                        dist = pow(x, 2) + pow(y, 2);
                        dist = sqrt(dist);
                        dist = fabs(dist);
                        if(dist < roundDistance)
                        {
                            roundDistance = round(dist);
                            roundCity = i;
                        }
                    }
                }
            }
            if(j < G.cities-1)  // otherwise prints distance from last node to nowhere.
            {
                index++;
                tempPath[index] = G.graphCity[roundCity]->name;
                currentRoundDistance += roundDistance;
                currentCity = G.graphCity[roundCity];

                if(checker == 0)
                    G.graphCity[roundCity]->visited = true;
                else
                    G.graphCity[roundCity]->visited = false;
            }
        }
        // distance last city to start
        x = (currentCity->x - G.graphCity[k]->x);
        y = (currentCity->y - G.graphCity[k]->y);
        dist = pow(x, 2) + pow(y, 2);
        dist = sqrt(dist);
        dist = fabs(dist);
        roundDistance = round(dist);
        currentRoundDistance += roundDistance;

        // Determines if the current result is better than best result found.
        // If true, Keeps the distance and copies the path to the pointer path in main.
        if((currentRoundDistance < bestDistance) && (currentRoundDistance > 0))
        {
            bestDistance = currentRoundDistance;
            for(i = 0; i < G.cities; i++)
                path[i] = tempPath[i];
        }
    }
    return bestDistance;
}

/********************************************************************
            printPath()
Takes the original filename and appends .tour to the end of it.
Prints the best distance found and the city names of the best tour.
********************************************************************/
void printPath(int distance, int *path, int length,  std::string fileName)
{
    std::string outFileName = fileName + ".tour";
    std::ofstream outputFile;
    outputFile.open(outFileName);
    outputFile << distance << std::endl;
    int i;
    for(i = 0; i < length; i++)
    {
        outputFile << path[i] << std::endl;
    }
    outputFile.close();
}
