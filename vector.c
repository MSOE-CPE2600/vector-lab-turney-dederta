/*
 * File: vector.c
 * Date: 9/29/25
 * Author: Ashlyn Dedert
 * Description:
 * Compile Instructions:
*/

#include <stdio.h>
#include <string.h>
#include "vector.h"

static Vector vectors[MAX_VECTORS];

// Storage
void clearVectors() 
{
    for (int i = 0; i < MAX_VECTORS; i++) {
        vectors[i].in_use = 0;
    }
}

void listVectors() 
{
    for (int i = 0; i < MAX_VECTORS; i++) {
        if (vectors[i].in_use) {
            printf("%s: (%.2f, %.2f, %.2f)\n", 
                vectors[i].name, 
                vectors[i].val[0], 
                vectors[i].val[1], 
                vectors[i].val[2]);
        }
    }
}

int addVector(char* name, double x, double y, double z) 
{
    // Replace if exists
    for (int i = 0; i < MAX_VECTORS; i++) {
        if (vectors[i].in_use && strcmp(vectors[i].name, name) == 0) {
            vectors[i].val[0] = x;
            vectors[i].val[1] = y;
            vectors[i].val[2] = z;
            return 1; // Success
        }
    }
    // insert into free slot
    for (int i = 0; i < MAX_VECTORS; i++) {
        if (!vectors[i].in_use) {
            strncpy(vectors[i].name, name, sizeof(vectors[i].name)-1);
            vectors[i].name[sizeof(vectors[i].name)-1] = '\0';
            vectors[i].val[0] = x;
            vectors[i].val[1] = y;
            vectors[i].val[2] = z;
            vectors[i].in_use = 1;
            return 1; // Success
        }
    }
    return 0; // Full
}

int getVector(char* name, Vector *out) 
{
    for (int i = 0; i < MAX_VECTORS; i++) {
        if (vectors[i].in_use && strcmp(vectors[i].name, name) == 0) {
            *out = vectors[i];
            return 1; // Found
        }
    }
    return 0; // Not found
}

// Math
Vector add(Vector a, Vector b) 
{
    Vector result = { .in_use = 0 };
    result.val[0] = a.val[0] + b.val[0];
    result.val[1] = a.val[1] + b.val[1];
    result.val[2] = a.val[2] + b.val[2];
    return result;
}

Vector subtract(Vector a, Vector b) 
{
    Vector result = { .in_use = 0 };
    result.val[0] = a.val[0] - b.val[0];
    result.val[1] = a.val[1] - b.val[1];
    result.val[2] = a.val[2] - b.val[2];
    return result;
}

Vector scalarMultiply(Vector v, double scalar) 
{
    Vector result = { .in_use = 0 };
    result.val[0] = v.val[0] * scalar;
    result.val[1] = v.val[1] * scalar;
    result.val[2] = v.val[2] * scalar;
    return result;
}

Vector cross(Vector a, Vector b) 
{
    Vector result = { .in_use = 0 };
    result.val[0] = a.val[1]*b.val[2] - a.val[2]*b.val[1];
    result.val[1] = a.val[2]*b.val[0] - a.val[0]*b.val[2];
    result.val[2] = a.val[0]*b.val[1] - a.val[1]*b.val[0];
    return result;
}

double dot(Vector a, Vector b) 
{
    return a.val[0]*b.val[0] + a.val[1]*b.val[1] + a.val[2]*b.val[2];
}