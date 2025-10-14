/*
 * File: vector.c
 * Date: 9/29/25
 * Author: Ashlyn Dedert
 * Description: Implementation of vector operations.
 * Compile Instructions: gcc vector.c -o vector OR make
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "vector.h"

static Vector *vectors = NULL;
static int vectorCount = 0;
static int vectorCapacity = 0;

// Storage
void clearVectors() 
{
    if (vectors)
    {
        free(vectors);
        vectors = NULL;
    }
    vectorCount = 0;
    vectorCapacity = 0;
}

void listVectors() 
{
    if (!vectors)
    {
        return;
    }

    for (int i = 0; i < vectorCount; i++) 
    {
        if (vectors[i].in_use) 
        {
            printf("%s: (%.2f, %.2f, %.2f)\n", 
                vectors[i].name, 
                vectors[i].val[0], 
                vectors[i].val[1], 
                vectors[i].val[2]);
        }
    }
}

int addVector(const char* name, double x, double y, double z) 
{
    // Replace if exists
    for (int i = 0; i < vectorCount; i++) {
        if (strcmp(vectors[i].name, name) == 0) 
        {
            vectors[i].val[0] = x;
            vectors[i].val[1] = y;
            vectors[i].val[2] = z;
            return 1; // Success
        }
    }

    // Allocate initial memory if needed
    if (vectorCapacity == 0)
    {
        vectorCapacity = 4;
        vectors = malloc(vectorCapacity * sizeof(Vector));
        if (!vectors)
        {
            fprintf(stderr, "Memory allocation failed\n");
            return 0;
        }
    }

    // Grow dynamically if full
    if (vectorCount >= vectorCapacity) 
    {
        int newCapacity = vectorCapacity * 2;
        Vector *newVectors = realloc(vectors, newCapacity * sizeof(Vector));
        if (!newVectors)
        {
            return 0;
        }
        vectors = newVectors;
        vectorCapacity = newCapacity;
    }

    // Add new vector
    strncpy(vectors[vectorCount].name, name, sizeof(vectors[vectorCount].name) - 1);
    vectors[vectorCount].name[sizeof(vectors[vectorCount].name) - 1] = '\0';
    vectors[vectorCount].val[0] = x;
    vectors[vectorCount].val[1] = y;
    vectors[vectorCount].val[2] = z;
    vectors[vectorCount].in_use = 1;
    vectorCount++;

    return 1;
}

int getVector(char* name, Vector *out) 
{
    for (int i = 0; i < vectorCount; i++) {
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

// I/O Functions

int loadVectors(const char *filename)
{
    // check if the file name ends with .csv
    checkCsvExtension((char *)filename);

    // Open file for reading
    FILE *fp = fopen(filename, "r");
    if (!fp) 
    {
        return 0;
    }

    // Read vectors from file
    char line[256];
    while (fgets(line, sizeof(line), fp))
    {
        if (line[0] != '\n' && line[0] != '\r')
        {
            char name[10];
            double x, y, z;

            if (sscanf(line, "%[^,],%lf,%lf,%lf", name, &x, &y, &z) == 4)
            {
                addVector(name, x, y, z);
            }
        }
        else 
        {
            fprintf(stderr, "Warning: invalid line skipped -> %s", line);
        }
    }

    fclose(fp);
    return 1;
}

int saveVectors(const char *filename)
{
    // check if the file name ends with .csv
    checkCsvExtension((char *)filename);

    // Open file for writing
    FILE *fp = fopen(filename, "w");
    if (!fp)
    {
        return 0;
    }

    // Write vectors to file
    for (int i = 0; i < vectorCount; i++)
    {
        if (vectors[i].in_use) 
        {
            fprintf(fp, "%s,%.2f,%.2f,%.2f\n",
            vectors[i].name, 
            vectors[i].val[0], 
            vectors[i].val[1], 
            vectors[i].val[2]);
        }
    }

    fclose(fp);
    return 1;
}

void checkCsvExtension(char *filename)
{
    const char *dot = strrchr(filename, '.');
    if (!dot || strcmp(dot, ".csv") != 0) 
    {
        // append .csv
        if (strnlen(filename, 256) + 4 < 256) 
        {
            strcat(filename, ".csv");
        }
    }
}

// interruption handler for ctrl-c
void handle_sigint(int sig) 
{
    printf("\nCaught signal %d, exiting...\n", sig);
    clearVectors();
    exit(0);
}