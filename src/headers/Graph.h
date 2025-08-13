#pragma once

#include "Node.h"
#include "Edge.h"
#include <vector>
#include <algorithm>

template<typename T>
class Graph
{
private:    
    std::vector<Node<T>*> nodes;
    std::vector<Edge<T>*> edges;
    static int current_value;

public:

    Graph() {}
    
    ~Graph() {
        for(auto node : nodes) {
            delete node;
        }
        for(auto edge : edges) {
            delete edge;
        }
    }

    inline std::vector<Node<T>*> GetNodes() { return nodes; }
    inline std::vector<Edge<T>*> GetEdges() { return edges; }
    
    static int GetCurrentValue() { return current_value; }
    static void IncrementCurrentValue() { current_value++; }
    static void ResetCurrentValue(){current_value = 0;}

    void AddNode(Node<T>* node) {
        nodes.emplace_back(node);
        current_value++; 
    }

    void RemoveNode(Node<T>* node) {
        auto it = std::find(nodes.begin(), nodes.end(), node);
        if(it != nodes.end()) {
            delete *it;
            nodes.erase(it);
        }
    }

    void AddEdge(Edge<T>* edge) {
        edges.emplace_back(edge);
    }

    void RemoveEdge(Edge<T>* edge) {
        auto it = std::find(edges.begin(), edges.end(), edge);
        if(it != edges.end()) {
            delete *it;
            edges.erase(it);
        }
    }
};

template<typename T>
int Graph<T>::current_value = 0;