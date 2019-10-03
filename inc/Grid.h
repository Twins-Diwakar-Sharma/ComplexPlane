#ifndef H_GRID_H
#define H_GRID_H

#include "allGL.h"
#include <iostream>
class Grid
{
    private:
        unsigned int vao;
        unsigned int vbo;
        float* vertexArray;
        int mag;

        float t = 0, delta = 0.1f;

        void createGrid(int); // grid is from x : -int to +int and y: -int to +int
        void createMesh();

    public:
        Grid(int);
        ~Grid();
        void bindVao();
        void unbindVao();
        int noOfVertices();
        void update();
        float getT();
        void setT(float);
        int getMagnitude();
        void setInterpolation(int);

};

#endif
