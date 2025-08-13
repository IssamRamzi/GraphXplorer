#pragma once


#include <raylib.h>
#include <math.h>

#include "Graph.h


struct utils
{
    Vector2 CalculateMidPoint(Vector2 start, Vector2 end){
        return (Vector2){
            (start.x + end.x) / 2, 
            (start.y + end.y) / 2
        };
    }

    bool SaveGraph(Graph *graph){

    }
};
