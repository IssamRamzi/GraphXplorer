#pragma once    

#include "Node.h"

template<typename node_type>
class Edge
{
private:
    Node<node_type>* m_source;
    Node<node_type>* m_destination;

    float m_weight;
public:

    static bool activeWeight;
    Edge(Node<node_type>* source, Node<node_type>* destination) : m_source(source), m_destination(destination){
        m_weight = 5.0f;
        logger.Log(INFO, std::format("Created new edge between {} and {} with a weight of {}", source->GetId(), destination->GetId(), m_weight));
    }
    
    Edge(Node<node_type>* source, Node<node_type>* destination, float weight) : m_source(source), m_destination(destination){
        m_weight = weight;
        logger.Log(INFO, std::format("Created new edge between {} and {} with a weight of {}", source->GetId(), destination->GetId(), m_weight));
    }
    ~Edge() = default;

    inline Node<node_type>* GetSource() const {return m_source;}
    inline Node<node_type>* GetDestination() const {return m_destination;}
    inline float GetWeight(){return m_weight;}
};

template<typename T>
bool Edge<T>::activeWeight = true;


