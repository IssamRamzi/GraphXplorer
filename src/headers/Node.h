#pragma once
#include "raylib.h"
#include <math.h>

#define             NODE_RADIUS 30
#define             MIN_DISTANCE 40

const Color         DEFAULT_NODE_COLOR = {222, 95, 83, 255};
const Color         HOVER_NODE_COLOR = {222, 95, 83, 220};
const Color         SELECTED_NODE_COLOR = {83, 95, 222, 255};
const Color         LINK_NODE_COLOR = {0};


const Color         NODE_TEXT_COLOR = {201, 201, 201, 255};
const int           NODE_TEXT_SIZE = 25;



template<typename T>
class Node
{
private:
    T m_id;
    Vector2 m_position;
    Color m_color = DEFAULT_NODE_COLOR;
public:
    Node(T id, Vector2 position) : m_id(id), m_position(position){

    }

    Node(T id, int x, int y) : m_id(id){
        m_position.x = x, m_position.y = y;
    }

    ~Node(){

    }

    inline T GetId(){return m_id;}
    inline Vector2 GetPosition(){return m_position;}
    inline void SetPosition(Vector2 position){m_position = position;}
    inline Color GetColor(){return m_color;}
    inline void SetColor(Color ncolor){m_color = ncolor;}
    inline void ResetColor(){m_color = DEFAULT_NODE_COLOR;}

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
