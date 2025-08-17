#pragma once

#include "Graph.h"

#include <fstream>
#include "iostream"
#include <sstream>

class IO{

public:
    IO(){
    }

    template<typename T>
    bool SaveGraph(Graph<T>* graph, const std::string& path){
        std::string desc = "# Nodes : id,label,x,y\n# Edges : from,dest,weight\n";
        int nNodes = graph->GetNodes().size(), nEdges = graph->GetEdges().size();
        std::ofstream file(path);
        if(!file.is_open()){
            logger.Log(INFO, std::format("Failed to open the file for graph saving at {}", path));
            return false;
        }

        //saving desc + nN, nE
        file << desc << nNodes << " " << nEdges << "\n";

        // saving nodes
        for(auto& node : graph->GetNodes()){
            file << node->GetId() << " " << node->GetPosition().x << " " << node->GetPosition().y << std::endl;    
        }

        // saving edges
        for(auto& edge : graph->GetEdges()){
            file << edge->GetSource()->GetId() << " " << edge->GetDestination()->GetId() << " " << edge->GetWeight() << std::endl;    
        }
        logger.Log(INFO, std::format("Graph saved successfully at {}", path));

        return true;

    }

    template<typename T>
    bool LoadGraph(const std::string& path, Graph<T>* result){

        std::ifstream file(path);
        if(!file.is_open()){
            logger.Log(INFO, std::format("Failed to open the file for graph loading at {}", path));
            return false;
        }
        std::string line;
        std::getline(file, line);
        std::getline(file, line);

        std::getline(file, line);
        std::istringstream iss(line);
        int nNodes, nEdges;
        iss >> nNodes >> nEdges;
        std::cout << "Graph with " << nNodes << " nodes and " << nEdges << " edges." << std::endl;

        if (nNodes < 0 || nEdges < 0) {
            throw std::runtime_error("Invalid graph size in LoadGraph");
        }


        // reading nodes
        for(int i = 0; i < nNodes; i++){
            std::getline(file, line);
            int id;
            float x, y;
            std::istringstream str(line);
            str >> id >> x >> y;
            Vector2 pos = {x,y};
            auto* node = new Node<T>(id, pos);
            // std::cout << "Node " << node->GetId() << " " << node->GetPosition().x << "," << node->GetPosition().y << "Loaded" << std::endl;
            result->AddNode(node);
        }

        // reading edges
        for(int i = 0; i < nEdges; i++){
            std::getline(file, line);
            int source, dest;
            float weight;
            std::istringstream str(line);
            str >> source >> dest >> weight;
            Node<T>* sourceNode = result->GetNodeById(source);
            Node<T>* destNode = result->GetNodeById(dest);

            if(sourceNode == nullptr) {
                std::cerr << "Error: Source node with ID " << source << " not found!" << std::endl;
                return false;
            }

            if(destNode == nullptr) {
                std::cerr << "Error: Destination node with ID " << dest << " not found!" << std::endl;
                return false;
            }

            auto* edge = new Edge<T>(sourceNode, destNode, weight);
            result->AddEdge(edge);
        }

        return true;
    }

};