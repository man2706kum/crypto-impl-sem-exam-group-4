/*
    -----------------FLOW OF THE PROGRAM-------------------------
    
    1. FieldElement is used to denote the field elements(elements in Fp)
    2. CurvePoint is use to denote the point on the curve E_M
    3. Each elements is stored in structure with two limbs (base 2^31 representation))
    4. The function convertToUnsignedLong converts a number in base 2^31 to unsigned long integer
    5. The function convertToFieldElement converts a unsigned long integer to a number in base 2^31
    6. addFE, subFE, mulFE functions calculates the field addition, subtraction and multiplication modulo p respectively
    7. powFE calculates exponentiation mod p for implementating Euler's Theorem
    8. montgomeryLadder computes the (Xn,.,Zn) the x and z coordinate of nP in projective space
    9. In the montgomeryLadder function we are using functions doubleCP and addCP which is doubling and addition of two points on the elliptic curve in projective space
    10. From the (Xn,.Zn) we apply Euler's theorem to get x_n by using function powFE
    11. From the value returned from montgomeryLadder, we use the function retrive_yn to compute the corresponding y_n
    12. Then (x_n, y_n) is the required sclar multiplication
*/



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
    printf("P=(576568326687948115,2075987454224306306)\n");
    // P ** ordP is Point at Infinity or Identity Point
    struct FieldElement ordP = {.upper = 268435456, .lower = 12309815}; // ord(P) = 576460752315733303 = 268435456 * 2^31 + 12309815

    // LOGIC:
    struct FieldElement a = {.upper = 1 << 28, .lower = 1 << 30};
    struct FieldElement b = {.upper = 1 << 28, .lower = 1 << 30};
    struct FieldElement n = {.upper = 1 << 21, .lower = 1 << 0};
    //printBinaryFEWithLabel("a", &a);
    //printBinaryFEWithLabel("b", &b);
    //printBinaryFEWithLabel("n", &b);
    unsigned long int N = convertToUnsignedLong(&n);
    printf("n = %lu\n", N);

    struct FieldElement res = addFE(&a, &b);
    //printBinaryFEWithLabel("addFE(a,b)", &res);

    struct FieldElement resSub = subFE(&res, &b);
    //printBinaryFEWithLabel("subFE(a+b,b)", &resSub);

    struct FieldElement resMul = mulFE(&a, &b);
    //printBinaryFEWithLabel("mulFE(a,b)", &resMul);

    struct FieldElement resPow = powFE(&a, &b);
    //printBinaryFEWithLabel("powFE(a,b)", &resPow);

    struct CurvePoint Q = {.x = Px, .y = Py, .z = a};
    struct CurvePoint ladder = montgomeryLadder(&Q, &n);
    //printCPBinaryWithLabel("montgomeryLadder", &ladder);
    
    struct CurvePoint Q1 = {.x = a, .y = b, .z = n};
    struct CurvePoint Q2 = {.x = ladder.x, .y = b, .z = n};
    struct FieldElement retrive_y = retrive_yn(&Q1, &Q2);
    //printBinaryFEWithLabel("retrive_yn()", &retrive_y);
    // TODO add solution code
    unsigned long int xn = convertToUnsignedLong(&ladder.x);
    unsigned long int yn = convertToUnsignedLong(&retrive_y);
    printf("\n\nThe sclar multiplication of P with n is :\n");
    printf("nP = (%lu, %lu)\n", xn, yn);

    return 0;
}
