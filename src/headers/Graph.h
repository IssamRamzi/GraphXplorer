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
    bool activeWeight = true;
    
    Graph() {}
    
    ~Graph() {
        for(auto node : nodes) {
            delete node;
        }
        for(auto edge : edges) {
            delete edge;
        }
    }

    inline std::vector<Node<T>*>& GetNodes() { return nodes; }
    inline std::vector<Edge<T>*>& GetEdges() { return edges; }
    
    static int GetCurrentValue() { return current_value; }
    static void IncrementCurrentValue() { current_value++; }
    static void ResetCurrentValue(){current_value = 0;}

    Node<T>* GetNodeById(int id){
        for(auto& node : nodes){
            if(node->GetId() == id){
                return node;
            }

        }
        return nullptr;
    }

    void AddNode(Node<T>* node) {
        nodes.emplace_back(node);
        if(node->GetId() >= current_value) {
            current_value = node->GetId() + 1;
        }
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
    void Reset(){
        for(auto* edge : edges) delete edge;
        edges.clear();
        edges.shrink_to_fit();

        for(auto* node : nodes) delete node;
        nodes.clear();
        nodes.shrink_to_fit();

        //seems need reset to cur value
        ResetCurrentValue();
    }

    bool IsValid() const {
        for(const auto* node : nodes) {
            if(node == nullptr) {
                std::cerr << "Found NULL node in graph!" << std::endl;
                return false;
            }
        }
        for(const auto* edge : edges) {
            if(edge == nullptr) {
                std::cerr << "Found NULL edge in graph!" << std::endl;
                return false;
            }
            if(edge->GetSource() == nullptr || edge->GetDestination() == nullptr) {
                std::cerr << "Found edge with NULL nodes!" << std::endl;
                return false;
            }
        }
        return true;
    }
};

template<typename T>
int Graph<T>::current_value = 0;