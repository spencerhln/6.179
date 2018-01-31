#include <iostream>
#include <vector>
#include <algorithm>
#include <memory>
#include <map>

#include "search.h"

typedef std::pair<int, int> coord;

coord operator+(const coord &l, const coord &r){
    return {l.first + r.first, l.second + r.second};
}

std::vector<coord> moves = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};
std::vector<std::string> map;

std::vector<coord> mapSuccessor(Node<coord>* locNode) {
    coord location = locNode->value;
    std::vector<coord> result;
    for (int i = 0; i < moves.size(); i++) {
        coord this_loc = moves[i] + location;
        if (map[this_loc.first][this_loc.second] != '#') {
            result.push_back(this_loc);
        }
    }
    return result;
}

std::map<coord, char> drawPath(std::vector<coord> path) {
    std::map<coord, char> result;
    result[path[0]] = 'S';
    for (int i = 1; i < path.size(); i++) {
        coord point = path[i];
        if (i+1 == path.size()){
            result[point] = 'G';
        }
        else {
            switch (point.first - path[i+1].first){
                case -1:
                    result[point] = 'v';
                    break;
                case 1:
                    result[point] = '^';
                    break;
            }
            switch (point.second - path[i+1].second) {
                case 1:
                    result[point] = '<';
                    break;
                case -1:
                    result[point] = '>';
                    break;
            }
        }
    }
    return result;
}

void drawMap(std::vector<std::string> map) {
    for (int i = 0; i < map.size(); i++) {
        std::cout << map[i] << "\n";
    }
}

/// main function that executes map search ///

int main() {
    int height, width;
    std::cout << "Please enter the height of your map (including boundaries) in the following format: height width\n";
    std::cin >> height >> width;
    //std::vector<std::string> map is defined above as so not to throw an error
    std::cout << "\nPlease enter your map line-by-line, starting with the first line.\n";
    getchar();
    for (int i = 0; i < height; i++) {
        std::string this_line;
        std::cout << "Please enter the next line of your map (include boundaries):\n";
        std::getline (std::cin, this_line);
        map.push_back(this_line);
    }
    std::cout << "The following is a display of your map:\n";
    drawMap(map);
    coord startState;
    coord goalState;
    std::cout << "Please enter a starting state in the following format: x y\n";
    std::cin >> startState.first >> startState.second;
    std::cout << "Please enter a goal state in the following format: x y\n";
    std::cin >> goalState.first >> goalState.second;
    std::cout << "Here is the path from the start to goal on the map you provided:\n";
    Node<coord> startNode = Node<coord>(startState);
    Node<coord> result = search(startNode, goalState, mapSuccessor);
    std::vector<coord> pathResult = path(std::make_shared<Node<coord>>(result));
    std::map<coord, char> pathPicture = drawPath(pathResult);
    for (int i = 0; i < pathResult.size(); i++) {
        coord point = pathResult[i];
        map[point.first][point.second] = pathPicture[point];
    }
    drawMap(map);
    return 0;
}

//5 5
//#####
//#   #
//# # #
//#   #
//#####
//1 1
//3 3
//
//9 11
//###########
//# #      ##
//# #  # # ##
//#    # #  #
//# #########
//#    #    #
//####  #   #
//#####     #
//###########
//1 1
//5 9
