#include "Grid.h"

void Grid::createGrid(int mag)
{
   this->mag = mag;
   int size = 2*4*(mag-(-mag) + 1);

   vertexArray = new float[size];

   int it=0;
   for(int i=-mag; i<=mag; i++)         // horizontal lines
   {
        vertexArray[it++] = -mag;
        vertexArray[it++] = i;

        vertexArray[it++] = mag;
        vertexArray[it++] = i;
   }

   for(int i=-mag; i<=mag; i++)         // vertical lines
   {
        vertexArray[it++] = i;
        vertexArray[it++] = -mag;

        vertexArray[it++] = i;
        vertexArray[it++] = mag;
   }

}

void Grid::createMesh()
{
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    glGenBuffers(1,&vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER,2*4*(2*mag+1)*sizeof(float),vertexArray,GL_STATIC_DRAW);

    glVertexAttribPointer(0,2,GL_FLOAT,GL_FALSE,2*sizeof(float),(void*)0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

}

Grid::Grid(int mag)
{
    createGrid(mag);
    createMesh();
}

Grid::~Grid()
{
    delete[] vertexArray;
}

void Grid::bindVao()
{
    glBindVertexArray(vao);
}

void Grid::unbindVao()
{
    glBindVertexArray(0);
}

int Grid::noOfVertices()
{
    return 4*(2*mag+1);
}

void Grid::update()
{
    if( t < 1.0f)
    {
       t += delta;
    }

}

float Grid::getT()
{
    return t;
}

void Grid::setT(float f)
{
    t = f;
}

int Grid::getMagnitude()
{
    return mag;
}

void Grid::setInterpolation(int points)
{
    delta = 1.0f/(float)(points);
}
