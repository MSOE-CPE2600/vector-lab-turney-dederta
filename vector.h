/*
 * File: vector.h
 * Date: 9/29/25
 * Author: Ashlyn Dedert
 * Description: Header file for vector operations.
*/

#ifndef VECTOR_H
#define VECTOR_H

#define MAX_VECTORS 10

typedef struct Vector
{
    char name[10];
    double val[3];
    int in_use; // Flag for whether this slot is filled
} Vector;

// storage functions
void clearVectors();
void listVectors();
int addVector(char* name, double x, double y, double z);
int getVector(char* name, Vector *out);

// math functions
Vector add(Vector a, Vector b);
Vector subtract(Vector a, Vector b);
Vector scalarMultiply(Vector v, double scalar);
Vector cross(Vector a, Vector b);
double dot(Vector a, Vector b);

#endif