#include <vector>
#include <iostream>
#include <string.h>
#include <fstream>
#include <math.h>
#include <climits>
#include <stdio.h>
#include <cstdlib>

struct city{
public:
    int name;
    int x;
    int y;
    bool visited;
    city(){};
};


class graph{
public:
    std::vector<city*> graphCity;
    int cities = 0;
    void addCity(int name, int x, int y);
};

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
    int option = atoi(argv[2]);
    int overrideOption = atoi(argv[3]);
    int distance;
    int runAmount;
    int *NNAPath;
    int *RNNAPath;

    if(argc != 4)
    {
        std::cout << "USAGE: <filename> <option> <override>" << std::endl;
        std::cout << "Option 1: NNA" << std::endl;
        std::cout << "Option 2: RNNA" << std::endl;
        //std::cout << "Option 3: Brute Force" << std::endl;  // Uncomment when implemented.
        std::cout << "Override: 0 = 3 Minute run." << std::endl;
        std::cout << "Override: 1 = Unlimited Time." << std::endl;
        return 1;
    }

    std::ifstream inputFile;
    std::string fileName;
    fileName = argv[1]; // Hard Coded for because my compiler sucks
    inputFile.open(fileName);
    int intName, intX, intY, i;

    while(inputFile >> intName >> intX >> intY)
    {
        myGraph.addCity(intName, intX, intY);
    }

    std::string comp1 = "1";
    std::string comp2 = "2";
    if(option == 1)
    {
        NNAPath = new int[myGraph.cities];
        distance = nearestNeighbor(myGraph, NNAPath);
        printPath(distance, NNAPath, myGraph.cities, fileName);
    }
    else if(option == 2)
    {
        //Determines how many times to run the RNNA Algorithm to keep under 3 minutes.
        // ***Values need to be determined.***

        if(myGraph.cities >= 0 && myGraph.cities <= 50)
        {
            runAmount = myGraph.cities;
        }
        else if(myGraph.cities >= 51 && myGraph.cities <= 300)
        {
            runAmount = 51;
        }
        if(overrideOption == 1)    // Override option for unlimited time run.
        {
            runAmount = myGraph.cities;
        }
        //runAmount = myGraph.cities; // Remove after if-else above is determined.
        RNNAPath = new int[myGraph.cities];
        distance = repetitivenearestNeighbor(myGraph, RNNAPath, runAmount);
        printPath(distance, RNNAPath, myGraph.cities, fileName);
    }
    else if(option == 3)
    {
        //Brute force Implementation
    }
    else
    {
        std::cout << "Error: Invalid Option" << std::endl;
    }
    return 0;
}

int nearestNeighbor(graph G, int *path)
{
    int currentDistance = 0;
    int index = 0;
    int roundDistance, roundCity, i, j;
    double x, y, dist;
    city *currentCity;

    path[index] = G.graphCity[index]->name;
    G.graphCity[index]->visited = true;
    currentCity = G.graphCity[index];

    for(j = 0; j < G.cities; j++)
    {
        roundDistance = INT_MAX;
        for(i = 0; i < G.cities; i++)
        {
            if(G.graphCity[i]->visited == false)
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
            path[index] = G.graphCity[roundCity]->name;
            currentDistance += roundDistance;
            currentCity = G.graphCity[roundCity];
            G.graphCity[roundCity]->visited = true;
        }
    }
    // distance last city to start
    x = (currentCity->x - G.graphCity[0]->x);
    y = (currentCity->y - G.graphCity[0]->y);
    dist = pow(x, 2) + pow(y, 2);
    dist = sqrt(dist);
    dist = fabs(dist);
    roundDistance = round(dist);
    currentDistance += roundDistance;
    return currentDistance;
}

int repetitivenearestNeighbor(graph G, int *path, int numberToRun)
{
    int roundDistance, roundCity, checker, index, start, i, j, k;
    int bestDistance = INT_MAX;
    int currentRoundDistance = INT_MAX;
    int tempPath[G.cities];
    double x, y, dist;
    city *currentCity;

    for(k = 0; k < numberToRun; k++)
    {
        // Used to work around bool visited.
        if(k % 2 == 0)  // even
            checker = 0;
        else            // odd
            checker = 1;

        // Set up starting variables
        index = 0;
        currentRoundDistance = 0;

        // Set up starting city.
        tempPath[index] = G.graphCity[k]->name;

        if(checker == 0)
            G.graphCity[k]->visited = true;
        else
            G.graphCity[k]->visited = false;

        currentCity = G.graphCity[k];

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
        if((currentRoundDistance < bestDistance) && (currentRoundDistance > 0))
        {
            bestDistance = currentRoundDistance;
            //std::cout << "Current best: " << bestDistance << std::endl;
            for(i = 0; i < G.cities; i++)
                path[i] = tempPath[i];

        }
    }
    return bestDistance;
}

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
