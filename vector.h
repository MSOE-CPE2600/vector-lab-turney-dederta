/*
 * File: vector.h
 * Date: 9/29/25
 * Author: Ashlyn Dedert
 * Description: Header file for vector operations.
*/

#ifndef VECTOR_H
#define VECTOR_H

#include <stddef.h>

#define NAME_LENGTH 10

typedef struct Vector
{
    char name[NAME_LENGTH];
    double val[3];
} Vector;

// storage functions
void clearVectors();
void listVectors();
int addVector(char* name, double x, double y, double z);
int getVector(char* name, Vector *out);

// Dynamic memory cleanup
void freeVectors();

// File I/O
int loadVectors(const char *filename);
int saveVectors(const char *filename);

// math functions
Vector add(Vector a, Vector b);
Vector subtract(Vector a, Vector b);
Vector scalarMultiply(Vector v, double scalar);
Vector cross(Vector a, Vector b);
double dot(Vector a, Vector b);

#endif