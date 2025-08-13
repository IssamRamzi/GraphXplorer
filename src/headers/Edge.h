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
    Edge(Node<node_type>* source, Node<node_type>* destination) : m_source(source), m_destination(destination){
        m_weight = 5.0f;
    }   
    ~Edge() = default;

    inline Node<node_type>* GetSource(){return m_source;}
    inline Node<node_type>* GetDestination(){return m_destination;}
    inline float GetWeight(){return m_weight;}
};
