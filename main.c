// standard libraries
#include <stdio.h>
#include <stdlib.h>

// custom libraries
#include "curve-point.c" // includes field-element.c and uint31.c

int main()
{
    // Curve Parameters
    struct FieldElement A = {.upper = 371610194, .lower = 1493483305}; // 798026816538591017 = 371610194 * 2^31 + 1493483305
    struct FieldElement B = {.upper = 0, .lower = 1};

    // Generator point on the curve
    struct FieldElement Px = {.upper = 268485549, .lower = 486145363}; // 576568326687948115 = 268485549 * 2^31 + 486145363
    struct FieldElement Py = {.upper = 966706990, .lower = 792006786}; // 2075987454224306306 = 966706990n * 2^31 + 792006786
    struct CurvePoint P = {.x = Px, .y = Py};                          // P=(576568326687948115,2075987454224306306)
    // P ** ordP is Point at Infinity or Identity Point
    struct FieldElement ordP = {.upper = 268435456, .lower = 12309815}; // ord(P) = 576460752315733303 = 268435456 * 2^31 + 12309815

    // LOGIC:
    struct FieldElement a = {.upper = 1 << 28, .lower = 1 << 30};
    struct FieldElement b = {.upper = 1 << 28, .lower = 1 << 30};
    struct FieldElement n = {.upper = 1 << 29, .lower = 1 << 30};
    printBinaryFEWithLabel("a", &a);
    printBinaryFEWithLabel("b", &b);
    printBinaryFEWithLabel("n", &b);

    struct FieldElement res = addFE(&a, &b);
    printBinaryFEWithLabel("addFE(a,b)", &res);

    struct FieldElement resSub = subFE(&res, &b);
    printBinaryFEWithLabel("subFE(a+b,b)", &resSub);

    struct FieldElement resMul = mulFE(&a, &b);
    printBinaryFEWithLabel("mulFE(a,b)", &resMul);

    struct FieldElement resPow = powFE(&a, &b);
    printBinaryFEWithLabel("powFE(a,b)", &resPow);

    struct CurvePoint Q = {.x = Px, .y = Py, .z = a};
    struct CurvePoint ladder = montgomeryLadder(&Q, &n);
    printCPBinaryWithLabel("montgomeryLadder", &ladder);
    
    struct CurvePoint Q1 = {.x = a, .y = b, .z = n};
    struct CurvePoint Q2 = {.x = ladder.x, .y = b, .z = n};
    struct FieldElement retrive_y = retrive_yn(&Q1, &Q2);
    printBinaryFEWithLabel("retrive_yn()", &retrive_y);
    // TODO add solution code

    return 0;
}
