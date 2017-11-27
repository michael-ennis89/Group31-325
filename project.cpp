#include <vector>
#include <iostream>

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


int main()
{
    graph myGraph;

    myGraph.addCity(1, 20, 25);
    myGraph.addCity(2, 21, 26);

    std::cout << "City 0: " << myGraph.graphCity[0]->name << " " << myGraph.graphCity[0]->x << " " << myGraph.graphCity[0]->y << " visited: " << myGraph.graphCity[0]->visited << std::endl;
    std::cout << "City 1: " << myGraph.graphCity[1]->name << " " << myGraph.graphCity[1]->x << " " << myGraph.graphCity[1]->y << " visited: " << myGraph.graphCity[1]->visited << std::endl;
    std::cout << "City Count: " << myGraph.cities << std::endl;
    return 0;
}
