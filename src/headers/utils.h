#pragma once


#include <raylib.h>
#include <math.h>

#include "Graph.h"
#include "Logger.h"
#include <iostream>

inline Logger logger("logs.txt");

struct utils
{
    Vector2 CalculateMidPoint(Vector2 start, Vector2 end){
        return {
            (start.x + end.x) / 2, 
            (start.y + end.y) / 2
        };
    }

    static bool PointBelongsLine(Vector2 startLine, Vector2 endLine, Vector2 point){
        // Vector from start to end
        Vector2 lineVec = {endLine.x - startLine.x, endLine.y - startLine.y};
        // Vector from start to point
        Vector2 pointVec = {point.x - startLine.x, point.y - startLine.y};

        
        float cross = lineVec.x * pointVec.y - lineVec.y * pointVec.x;

        // Check if point is within the bounding box
        if (point.x < std::min(startLine.x, endLine.x) - 1e-6 || 
            point.x > std::max(startLine.x, endLine.x) + 1e-6 ||
            point.y < std::min(startLine.y, endLine.y) - 1e-6 || 
            point.y > std::max(startLine.y, endLine.y) + 1e-6)
            return false;

        return true;
    }

};


struct GZones {
    Rectangle DrawZone;
    Rectangle MenuZone;
    Rectangle TerminalZone;

    static constexpr int MenuWidth = 250;
    static constexpr int TerminalHeight = 200;
    GZones() {
        float sw = (float)GetScreenWidth();
        float sh = (float)GetScreenHeight();
        DrawZone = {MenuWidth, 0, sw - MenuWidth, sh - TerminalHeight};
        MenuZone = {0, 0, MenuWidth, MenuWidth};
        TerminalZone = {MenuWidth, sh - TerminalHeight, sw - MenuWidth, TerminalHeight};
    }
};

struct GScreen {
    int ScreenWidth;
    int ScreenHeight;
    static constexpr int FPS = 60;

    GScreen(){
        ScreenHeight = GetScreenHeight();
        ScreenHeight = GetScreenWidth();
    }
};

struct GColors {
    // UI
    static constexpr Color BACKGROUND_COLOR_DARK    = {23,23,23,255}; 
    static constexpr Color BACKGROUND_COLOR_LIGHT   = {242, 242, 242, 255};

    // Node
    static constexpr Color DEFAULT_NODE_COLOR       = {222, 95, 83, 255};
    static constexpr Color HOVER_NODE_COLOR         = {222, 95, 83, 220};
    static constexpr Color SELECTED_NODE_COLOR      = {83, 95, 222, 255};
    static constexpr Color LINK_NODE_COLOR          = {0, 0, 0, 255};
    
    // Text 
    static constexpr Color NODE_TEXT_COLOR          = {201, 201, 201, 255};
    static constexpr Color DEFAULT_TEXT_COLOR       = {220, 220, 220, 255};
};

struct GSizes{
    static constexpr int NODE_RADIUS = 30;
    static constexpr int MINIMUM_NODE_DISTANCE = 40;

    static constexpr int NODE_TEXT_SIZE = 25;
    static constexpr int TITLE_TEXT_SIZE = 30;
};