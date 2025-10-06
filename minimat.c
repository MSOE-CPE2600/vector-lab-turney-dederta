/*
 * File: minimat.c
 * Date: 9/29/25
 * Author: Ashlyn Dedert
 * Description: A minimalistic matrix/vector calculator.
 * Compile Instructions: gcc -Wall -o minimat minimat.c vector.c OR make
 * // TODO USE TOKENS INSTEAD OF SSCANF
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "vector.h"

void printVector(Vector v) 
{
    printf("%s: (%.2f, %.2f, %.2f)\n", v.name, v.val[0], v.val[1], v.val[2]);
}
void printWithName(Vector v, char* name) 
{
    printf("%s: (%.2f, %.2f, %.2f)\n", name, v.val[0], v.val[1], v.val[2]);
}

void helpHelper(){
    printf("Commands:\n");
    printf("  var = x y z           Assign vector (y,z optional)\n");
    printf("  var = var1 (op) var2  Add/Subtract/Cross/Dot vectors\n");
    printf("  var1 (op) var2        Add/Subtract/Cross/Dot vectors without assignment\n");
    printf("  var                   Print vector\n");
    printf("  list                  List all vectors\n");
    printf("  clear                 Clear all vectors\n");
    printf("  quit                  Exit program\n");
}

void parseAndExecute(char* line)
{
    char lhs[10], rhs1[10], rhs2[10], op;
    double scalar;
    Vector v1, v2, result;

    if (strchr(line, '*') || strchr(line, '+') || strchr(line, '-') || 
    strchr(line, '.') || strchr(line, 'x') || strchr(line, 'X'))
    {
        // Operation with assignment
        if (sscanf(line, "%s = %s %c %s", lhs, rhs1, &op, rhs2) == 4)
        {
            // scalar multiplication
            if (op == '*')
            {
                if (getVector(rhs1, &v1) && (sscanf(rhs2, "%lf", &scalar) == 1))
                {
                    result = scalarMultiply(v1, scalar);
                    addVector(lhs, result.val[0], result.val[1], result.val[2]);
                    printf("%s = (%.2f, %.2f, %.2f)\n", lhs, result.val[0], result.val[1], result.val[2]);
                    return;
                }
                else if (getVector(rhs2, &v2) && (sscanf(rhs1, "%lf", &scalar) == 1))
                {
                    result = scalarMultiply(v2, scalar);
                    addVector(lhs, result.val[0], result.val[1], result.val[2]);
                    printf("%s = (%.2f, %.2f, %.2f)\n", lhs, result.val[0], result.val[1], result.val[2]);
                    return;
                }
                else
                {
                    printf("Invalid scalar multiplication\n");
                    return;
                }
            }

            // vector operations
            if (getVector(rhs1, &v1) && getVector(rhs2, &v2))
            {
                // addition
                if (op == '+')
                {
                    result = add(v1, v2);
                }
                // subtraction
                else if (op == '-')
                {
                    result = subtract(v1, v2);
                } 
                // cross product
                else if (op == 'x' || op == 'X')
                {
                    result = cross(v1, v2);
                    addVector(lhs, result.val[0], result.val[1], result.val[2]);
                    printf("%s = (%.2f, %.2f, %.2f)\n", lhs, result.val[0], result.val[1], result.val[2]);
                    return;
                } 
                // dot product
                else if (op == '.')
                {
                    double dot_product = dot(v1, v2);
                    printf("%s = %.2f\n", lhs, dot_product);
                    return;
                }
                // invalid operator
                else
                {
                    printf("Invalid operator: %c\n", op);
                    return;
                }
            } 
            // vector * scalar
            else if (getVector(rhs1, &v1) && (sscanf(rhs2, "%lf", &scalar) == 1) && (op == '*'))
            {
                result = scalarMultiply(v1, scalar);
            }
            else if (getVector(rhs2, &v2) && (sscanf(rhs1, "%lf", &scalar) == 1) && (op == '*'))
            {
                result = scalarMultiply(v2, scalar);
            }
            // unknowns
            else
            {
                printf("Unknown variable\n");
                return;
            }
            // store and print
            addVector(lhs, result.val[0], result.val[1], result.val[2]);
            getVector(lhs, &result);
            printVector(result);
            return;
        }
    }
    else
    {
        // Assignment of raw numbers 
        double vals[3] = {0};
        int n = sscanf(line, "%s = %lf%*[ ,] %lf%*[ ,] %lf", lhs, &vals[0], &vals[1], &vals[2]);
        if (n >= 2) // at least x
        {
            addVector(lhs, vals[0], vals[1], vals[2]);
            getVector(lhs, &result);
            printVector(result);
            return;
        }
    }

    // Scalar multiplication
    if ((sscanf(line, "%s * %lf", rhs1, &scalar) == 2) && getVector(rhs1, &v1))
    {
        result = scalarMultiply(v1, scalar);
        printf("%.2f * %s = (%.2f, %.2f, %.2f)\n", 
            scalar, rhs1, result.val[0], result.val[1], result.val[2]);
        return;
    }
    if ((sscanf(line, "%lf * %s", &scalar, rhs1) == 2) && getVector(rhs1, &v1))
    {
        result = scalarMultiply(v1, scalar);
        printf("%.2f * %s = (%.2f, %.2f, %.2f)\n", 
            scalar, rhs1, result.val[0], result.val[1], result.val[2]);
        return;
    }

    // Binary operations without assignment
    if (sscanf(line, "%s %c %s", rhs1, &op, rhs2) == 3)
    {
        if (getVector(rhs1, &v1) && getVector(rhs2, &v2))
        {
            if (op == '+')
            {
                result = add(v1, v2);
                printWithName(result, line);
                return;
            }
            else if (op == '-')
            {
                result = subtract(v1, v2);
                printWithName(result, line);
                return;
            }
            else if (op == '.')
            {
                double dot_product = dot(v1, v2);
                printf("%s . %s = %.2f\n", rhs1, rhs2, dot_product);
                return;
            }
            else if (op == 'x' || op == 'X')
            {
                result = cross(v1, v2);
                printWithName(result, line);
                return;
            }
            else
            {
                printf("Invalid operator: %c\n", op);

            }
        }
        else
        {
            printf("Unknown variable\n");
        }
        return;
    }

    // Just a variable to print
    if (sscanf(line, "%s", rhs1) == 1)
    {
        if (getVector(rhs1, &v1))
        {
            printVector(v1);
        }
        else if (strcmp(rhs1, "list") == 0)
        {
            listVectors();
        }
        else if (strcmp(rhs1, "clear") == 0)
        {
            clearVectors();
        }
        else if (strcmp(rhs1, "quit") == 0)
        {
            exit(0);
        }
        else if (strcmp(rhs1, "help") == 0)
        {
            helpHelper();
        }
        else
        {
            printf("Unknown variable or command\n");
        }
        return;
    }

    printf("Could not parse command\n");
}

int main(int argc, char *argv[])
{
    if (argc > 1 && strcmp(argv[1], "-h") == 0)
    {
        helpHelper();
    }

    clearVectors();

    char line[100];
    while (1)
    {
        printf("minimat> ");
        if (!fgets(line, sizeof(line), stdin)) break;
        line[strcspn(line, "\n")] = 0; // Remove newline
        parseAndExecute(line);
    }

    return 0;
}