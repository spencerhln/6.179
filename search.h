#ifndef search_h
#define search_h

#include <vector>
#include <algorithm>
#include <memory>


/* Search node, which contains some value T (based on the search space) and a
shared pointer (which will be shared among nodes when searching) to its
parent node. */
template <class T>
struct Node {
    std::shared_ptr<Node<T>> parent;
    T value;
    Node() {
        this->parent = NULL;
    }
    Node(T val) {
        this->value = val;
        this->parent = NULL;
    }
    Node(T val, std::shared_ptr<Node<T>> p) {
        this->value = val;
        this->parent = p;
    }
};

/* Path function that, when given the shared pointed to a node, produces the
list of states (as values T) that lead from the initial state to that final
state. */
template <class T>
std::vector<T> path(std::shared_ptr<Node<T>> end) {
    std::vector<T> result;
    while (end->parent != NULL){
        result.push_back(end->value);
        end = end->parent;
    }
    result.push_back(end->value);
    std::reverse(result.begin(), result.end());
    return result;
}

/* Search function. Takes in a Node start state, a value T goalState, and a 
function successors that takes in a pointer to a Node and produces a vector
of potential states (represented as T values) that can be reached from that
state. */
template <class T>
Node<T> search(Node<T> startState, T goalState, std::vector<T> successors(Node<T>* node)) {
    std::vector<T> visited;
    if (goalState == startState.value) {
        return startState;
    }
    std::vector<Node<T>> agenda;
    std::vector<T> successor;
    agenda.push_back(startState);
    while (agenda.size() > 0) {
        std::shared_ptr<Node<T>> node = std::make_shared<Node<T>>(agenda.front());
        agenda.erase(agenda.begin());
        successor = successors(node.get());
        for (auto &state : successor) {
            if (goalState == state) {
                Node<T> result(state, node);
                return result;
            }
            else if (std::find(visited.begin(), visited.end(), state) == visited.end()){
                Node<T> newNode(state, node);
                agenda.push_back(newNode);
                visited.push_back(state);
            }
        }
        successor.empty();
    }
}
            
#endif