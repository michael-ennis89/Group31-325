#include <vector>
#include <iostream>
#include <string>
#include <fstream>
#include <math.h>
#include <climits>

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


int main(int argc, char* argv[])
{
    graph myGraph;
    int distance;
    int *shortestPath;

    // Change to 3 with Usage <filename> <option> when implemented.
    /*if(argc != 2)
    {
        std::cout << "USAGE: <filename>" << std::endl;
        return 1;
    }*/

    std::ifstream inputFile;
    std::string fileName;
    fileName = "tsp_example_1.txt"; //argv[1]; // Hard Coded for because my compiler sucks
    inputFile.open(fileName);
    int intName, intX, intY, i;

    while(inputFile >> intName >> intX >> intY)
    {
        myGraph.addCity(intName, intX, intY);
    }

    // Example to print out created graph.
    /*for(i = 0; i < myGraph.cities; i++)
    {
        std::cout << "City: " << myGraph.graphCity[i]->name << " x: " << myGraph.graphCity[i]->x << " y: " << myGraph.graphCity[i]->y << std::endl;
    }*/
    shortestPath = new int[myGraph.cities];
    distance = nearestNeighbor(myGraph, shortestPath);

    // un-comment to print distance afterwards.
    std::cout << "Distance: " << distance << std::endl;
    // un-comment to print path afterwards.
    //for(i = 0; i < myGraph.cities; i++)
        //std::cout << shortestPath[i] << std::endl;

    return 0;
}

int nearestNeighbor(graph G, int *path)
{
    int currentDistance = 0;
    int roundDistance;
    int roundCity;
    int index = 0;
    int i, j;
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
            //un-comment if you want to see distances as you go.
            //std::cout << "Current Distance: " << currentDistance << std::endl;
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
    path[G.cities] = G.graphCity[0]->name;
    return currentDistance;
}
