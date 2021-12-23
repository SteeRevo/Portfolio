/**********************************************************************************
* Ethan Nguyen, etqnguye
* 2021 Winter CSE 101 pa7
* ListTest.c
* Testfile for BigInteger ADT
*********************************************************************************/

#include <stdio.h>
#include "BigInteger.h"

int main(int argc, const char * argv[]) {
    char *s = "-04836284957372838";
    char *s2 = "584949384949354";
    BigInteger A = stringToBigInteger(s);
    BigInteger B = stringToBigInteger(s2);
    printBigInteger(stdout, A);
    printBigInteger(stdout, B);
    BigInteger E = newBigInteger();
    
    if(sign(A) != -1){
        printf("Failed Test\n");
    }
    else{
        printf("Sign is -1\n");
    }
    int i = compare(A, B);
    if(i == 0 || i == 1){
        printf("Test failed\n");
    }
    
    negate(A);
    if(sign(A) == 1){
        printf("Sign of A changed to positive\n");
    }
    
    add(E, A, B);
    
    BigInteger D = sum(A, B);
    int j = equals(E, D);
    if(j == 0){
        printf("Test Failed\n");
    }
    printf("Sum of A and B is ");
    printBigInteger(stdout, E);
    
    subtract(E, A, B);
    printf("Difference of A and B is ");
    printBigInteger(stdout, E);
    
    multiply(E, A, B);
    printf("Product of A and B is ");
    printBigInteger(stdout, E);
    
    makeZero(E);
    if(sign(E) == 0){
        printf("Big int E is made zero\n");
    }
    
    freeBigInteger(&A);
    freeBigInteger(&B);
    freeBigInteger(&E);
    freeBigInteger(&D);
    return 0;
}
