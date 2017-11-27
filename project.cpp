#include <vector>
#include <iostream>
#include <string>
#include <fstream>

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


int main(int argc, char* argv[])
{
    graph myGraph;

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
    for(i = 0; i < myGraph.cities; i++)
    {
        std::cout << "City: " << myGraph.graphCity[i]->name << " x: " << myGraph.graphCity[i]->x << " y: " << myGraph.graphCity[i]->y << std::endl;
    }

    return 0;
}
