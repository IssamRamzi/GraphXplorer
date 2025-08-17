#pragma once
#include <format>

#include "raylib.h"
#include <math.h>
#include "utils.h"

#include <ostream>

template<typename T>
class Node
{
private:
    T m_id;
    Vector2 m_position;
    Color m_color;
public:
    Node(T id, Vector2 position) : m_id(id), m_position(position){
        logger.Log(INFO, std::format("Created new node with a value of {} and a position of ({},{})",id, position.x, position.y));
        m_color = GColors::DEFAULT_NODE_COLOR;
    }

    Node(T id, int x, int y) : m_id(id){
        logger.Log(INFO, std::format("Created new node with a value of {} and a position of ({},{})",id, x, y));
        m_position.x = x, m_position.y = y;
        m_color = GColors::DEFAULT_NODE_COLOR;
    }

    ~Node(){

    }

    inline T GetId(){return m_id;}
    inline Vector2& GetPosition(){return m_position;}
    inline void SetPosition(Vector2 position){m_position = position;}
    inline Color& GetColor(){return m_color;}
    inline void SetColor(Color ncolor){m_color = ncolor;}
    inline void ResetColor(){m_color = GColors::DEFAULT_NODE_COLOR;}

    float GetDistance(Vector2 another_pos);
    float GetDistance(Node<T>* another_node);
    static float GetDistance(Vector2 position, Vector2 another_position);
    static float GetDistance(Node<T>* node, Node<T>* another_node);

    
};

template <typename T>
inline float Node<T>::GetDistance(Vector2 another_pos)
{
    return sqrt(pow(m_position.x - another_pos.x, 2) + pow(m_position.y - another_pos.y, 2));
}

template <typename T>
inline float Node<T>::GetDistance(Node<T> *another_node)
{
    return sqrt(pow(m_position.x - another_node->GetPosition().x, 2) + pow(m_position.y - another_node->GetPosition().y, 2));
}

template <typename T>
inline float Node<T>::GetDistance(Vector2 position, Vector2 another_pos)
{   
    return sqrt(pow(position.x - another_pos.x, 2) + pow(position.y - another_pos.y, 2));
}

template <typename T>
inline float Node<T>::GetDistance(Node<T> *node, Node<T> *another_node)
{
    return sqrt(pow(node->GetPosition().x - another_node->GetPosition().x, 2) + pow(node->GetPosition().y - another_node->GetPosition().y, 2));
}

template<typename T>
std::ostream& operator <<(std::ostream& os, const Node<T> node){
        return os << node.m_id << "," << node.m_position.x << "," << node.m_position.y;
}
