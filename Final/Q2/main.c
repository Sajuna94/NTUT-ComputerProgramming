#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <math.h>

#define shapeText(TYPE)              \
    char name[10];                   \
    int (*perimeter)(struct TYPE *); \
    int (*area)(struct TYPE *);

#define PI 4

typedef struct shape_s
{
    shapeText(shape_s);
} shape_t;

typedef struct circle_s
{
    shapeText(circle_s);
    int radius;
} circle_t;

typedef struct rectangle_s
{
    shapeText(rectangle_s);
    int width, height;
} rectangle_t;

typedef struct square_s
{
    shapeText(square_s);
    int side;
} square_t;

typedef struct triangle_s
{
    shapeText(triangle_s);
    int s1, s2, s3;
} triangle_t;

int perimeterCircle(circle_t* circ) {
    return circ->radius * PI * 2;
}
int perimeterRect(rectangle_t* rect) {
    return (rect->height + rect->width) * 2;
}
int perimeterSquare(square_t* square) {
    return square->side * 4;
}
int perimeterTriangle(triangle_t* triangle) {
    return triangle->s1 + triangle->s2 + triangle->s3;
}
int areaCircle(circle_t* circ) {
    return circ->radius * circ->radius * PI;
}
int areaRect(rectangle_t* rect) {
    return rect->height * rect->width;
}
int areaSquare(square_t* square) {
    return square->side * square->side;
}
int areaTriangle(triangle_t* tri) {
    double s = (tri->s1 + tri->s2 + tri->s3) / 2;
    return (int)sqrt(s * (s - tri->s1) * (s - tri->s2) * (s - tri->s3));
}

int shapeCompare(const void* a, const void* b) {
    shape_t* shapeA = *(shape_t**)a;
    shape_t* shapeB = *(shape_t**)b;

    int perA = shapeA->perimeter(shapeA);
    int perB = shapeB->perimeter(shapeB);

    if (perA != perB) 
        return perB - perA;
    else 
        return shapeB->area(shapeB) - shapeA->area(shapeA);
}

int main(void) {
    int numShape; scanf("%d", &numShape);

    shape_t *shapeList[numShape];

    for (int i = 0; i < numShape; i++) {
        char shapeName[100]; scanf("%s", shapeName);

        if (!strcmp(shapeName, "triangle")) {
            triangle_t* shape = (triangle_t*)malloc(sizeof(triangle_t));
            scanf("%d %d %d", &shape->s1, &shape->s2, &shape->s3);
            strcpy(shape->name, "triangle");
            shape->area = areaTriangle;
            shape->perimeter = perimeterTriangle;
            shapeList[i] = (shape_t*)shape;
        }
        else if (!strcmp(shapeName, "square")) {
            square_t* shape = (square_t*)malloc(sizeof(square_t));
            scanf("%d", &shape->side);
            strcpy(shape->name, "square");
            shape->area = areaSquare;
            shape->perimeter = perimeterSquare;
            shapeList[i] = (shape_t*)shape;
        }
        else if (!strcmp(shapeName, "rectangle")) {
            rectangle_t* shape = (rectangle_t*)malloc(sizeof(rectangle_t));
            scanf("%d %d", &shape->width, &shape->height);
            strcpy(shape->name, "rectangle");
            shape->area = areaRect;
            shape->perimeter = perimeterRect;
            shapeList[i] = (shape_t*)shape;
        }
        else if (!strcmp(shapeName, "circle")) {
            circle_t* shape = (circle_t*)malloc(sizeof(circle_t));
            scanf("%d", &shape->radius);
            strcpy(shape->name, "circle");
            shape->area = areaCircle;
            shape->perimeter = perimeterCircle;
            shapeList[i] = (shape_t*)shape;
        }
    }

    qsort(shapeList, numShape, sizeof(shape_t*), shapeCompare);

    int perTotal = 0, areaTotal = 0;
    for (int i = 0; i < numShape; i++) {
        int per = shapeList[i]->perimeter(shapeList[i]);
        int area = shapeList[i]->area(shapeList[i]);

        printf("%s %d %d\n", shapeList[i]->name, per, area);

        perTotal += per;
        areaTotal += area;
    }

    printf("%d %d\n", perTotal, areaTotal);
}
