/**********************************************************************************
* Ethan Nguyen, etqnguye
* 2021 Winter CSE 101 pa7
* BigInteger.c
* Code and functions for BigInteger ADT
*********************************************************************************/

#include "BigInteger.h"


// Exported type -------------------------------------------------------------

// BigInteger reference type
typedef struct BigIntegerObj{
    int sign;
    List number;
} BigIntegerObj;


// Constructors-Destructors ---------------------------------------------------

// newBigInteger()
// Returns a reference to a new BigInteger object in the zero state.
BigInteger newBigInteger(void){
    BigInteger B = malloc(sizeof(BigIntegerObj));
    B->sign = 0;
    B->number = newList();
    return B;
}

void freeHelper(BigInteger pN){
    freeList(&pN->number);
    
}

// freeBigInteger()
// Frees heap memory associated with *pN, sets *pN to NULL.
void freeBigInteger(BigInteger* pN){
    if(*pN != NULL && pN != NULL){
        freeHelper(*pN);
        free(*pN);
        pN = NULL;
    }
}

// Access functions -----------------------------------------------------------

// sign()
// Returns -1 if N is negative, 1 if N is positive, and 0 if N is in the zero
// state.
int sign(BigInteger N){
    return N->sign;
}

//removeZero()
//removes leading zeroes
void removeZero(BigInteger A){
    if(length(A->number) == 1 && front(A->number) == 0){
        makeZero(A);
    }
    if(length(A->number) > 1){
        while(back(A->number) == 0){
            deleteBack(A->number);
            if(length(A->number) == 1 && front(A->number) == 0){
                makeZero(A);
                return;
            }
        }
    }
}

// compare()
// Returns -1 if A<B, 1 if A>B, and 0 if A=B.
int compare(BigInteger A, BigInteger B){
    if(A->sign == -1 && B->sign == 1){
        return -1;
    }
    else if(A->sign == 1 && B->sign == -1){
        return 1;
    }
    else if(A->sign == -1 && B->sign == -1){
        if(length(A->number) > length(B->number)){
            return -1;
        }
        else if(length(B->number) > length(A->number)){
            return 1;
        }
        else{
            moveBack(A->number);
            moveBack(B->number);
            while(Index(A->number) != -1 || Index(B->number) != -1){
                if(get(A->number) > get(B->number)){
                    return -1;
                }
                else if(get(A->number) < get(B->number)){
                    return 1;
                }
                else{
                    movePrev(A->number);
                    movePrev(B->number);
                }
            }
            return 0;
        }
    
    }
    else{
        if(length(A->number) > length(B->number)){
            return 1;
        }
        else if(length(B->number) > length(A->number)){
            return -1;
        }
        else{
            moveBack(A->number);
            moveBack(B->number);
            while(Index(A->number) != -1 || Index(B->number) != -1){
                if(get(A->number) > get(B->number)){
                    return 1;
                }
                else if(get(A->number) < get(B->number)){
                    return -1;
                }
                else{
                    movePrev(A->number);
                    movePrev(B->number);
                }
            }
        }
        return 0;
    }
}



// equals()
// Return true (1) if A and B are equal, false (0) otherwise.
int equals(BigInteger A, BigInteger B){
    if(compare(A, B) == 0){
        return 1;
    }
    else{
        return 0;
    }
}

// Manipulation procedures ----------------------------------------------------

// makeZero()
// Re-sets N to the zero state.
void makeZero(BigInteger N){
    N->sign = 0;
    Clear(N->number);
}

// negate()
// Reverses the sign of N: positive <--> negative. Does nothing if N is in the
// zero state.
void negate(BigInteger N){
    if(N->sign == 0){
        return;
    }
    else{
        if(N->sign == 1){
            N->sign = -1;
        }
        else{
            N->sign = 1;
        }
    }
}

// BigInteger Arithmetic operations -----------------------------------------------

// stringToBigInteger()
// Returns a reference to a new BigInteger object representing the decimal integer
// represented in base 10 by the string s.
// Pre: s is a non-empty string containing only base ten digits {0,1,2,3,4,5,6,7,8,9}
// and an optional sign {+, -} prefix.
BigInteger stringToBigInteger(char* s){
    BigInteger B = newBigInteger();
    int length = (int)strlen(s);
    int remain = length % POWER;
    int total = length/POWER;
    char buff[9];
    if(s[0]== '-'){
        B->sign = -1;
    }
    else{
        B->sign = 1;
    }
    for(int i = 1; i <= total; i++){
        memcpy(buff, &s[length-POWER], POWER);
        long num = atol(buff);
        num = labs(num);
        append(B->number, num);
        length -= POWER;
    }
    char remainbuff[remain];
    if(remain > 0){
        if(remain == 1 && (s[0] == '+' || s[0] == '-')){
            return B;
        }
        else{
            memcpy(remainbuff, &s[0], remain);
            long num = atol(remainbuff);
            num = labs(num);
            append(B->number, num);
            removeZero(B);
            return B;
        }
    }
    removeZero(B);
    return B;
}

// copy()
// Returns a reference to a new BigInteger object in the same state as N.
BigInteger copy(BigInteger N){
    BigInteger B = newBigInteger();
    B->sign = N->sign;
    B->number = copyList(N->number);
    return B;
}

// add()
// Places the sum of A and B in the existing BigInteger S, overwriting its
// current state: S = A + B
void add(BigInteger S, BigInteger A, BigInteger B){
    BigInteger CA = copy(A);
    BigInteger CB = copy(B);
    makeZero(S);
    if(CA->sign == 0){
        moveFront(CB->number);
        negate(CB);
        while(Index(CB->number) != -1){
            append(S->number, get(CB->number));
            S->sign = CB->sign;
            moveNext(CB->number);
        }
    }
    else if(CB->sign == 0){
        moveFront(CA->number);
        while(Index(CA->number) != -1){
            append(S->number, get(CA->number));
            S->sign = CA->sign;
            moveNext(CA->number);
        }
    }
    if((CA->sign == 1 && CB->sign == 1) || (CA->sign == -1 && CB->sign == -1)){
        if(CA->sign == 1){
            S->sign = 1;
        }
        else if(CA->sign == -1){
            S->sign = -1;
        }
        long carry = 0, sum;
        moveFront(CA->number);
        moveFront(CB->number);
        while(Index(CA->number) != -1 || Index(CB->number) != -1){
            sum = carry;
            if(Index(CA->number) != -1){
                sum += get(CA->number);
            }
            if(Index(CB->number) != -1){
                sum += get(CB->number);
            }
            if(sum >= BASE){
                carry = 1;
            }
            else{
                carry = 0;
            }
            
            sum = sum % BASE;
            append(S->number, sum);
            if(Index(CA->number) != -1){
                moveNext(CA->number);
            }
            if(Index(CB->number) != -1){
                moveNext(CB->number);
            }
        }
        if(carry > 0){
            append(S->number, carry);
        }
    }
    else if(CA->sign == -1 && CB->sign == 1){
        CB->sign = -1;
        subtract(S, CA, CB);
    }
    else if(CA->sign == 1 && CB->sign == -1){
        CB->sign = 1;
        subtract(S, CA, CB);
    }
    removeZero(S);
    freeBigInteger(&CA);
    freeBigInteger(&CB);
}

// sum()
// Returns a reference to a new BigInteger object representing A + B.
BigInteger sum(BigInteger A, BigInteger B){
    BigInteger S = newBigInteger();
    add(S, A, B);
    return S;
}

// subtract()
// Places the difference of A and B in the existing BigInteger D, overwriting
// its current state: D = A - B
void subtract(BigInteger D, BigInteger A, BigInteger B){
    BigInteger CA = copy(A);
    BigInteger CB = copy(B);
    makeZero(D);
    if(CA->sign == 0){
        moveFront(CB->number);
        while(Index(CB->number) != -1){
            append(D->number, get(CB->number));
            D->sign = CB->sign;
            moveNext(CB->number);
            
        }
    }
    else if(CB->sign == 0){
        moveFront(CA->number);
        while(Index(CA->number) != -1){
            append(D->number, get(CA->number));
            D->sign = CA->sign;
            moveNext(CA->number);
        }
    }
   
    long borrow = 0, differ;
    
    if((CA->sign == 1 && CB->sign == 1) || (CA->sign == -1 && CB->sign == -1)){
        BigInteger large, small;
        if(CA->sign == 1){
            int x = compare(CA, CB);
            if(x == 1){
                large = CA;
                small = CB;
                D->sign = 1;
            }
            else{
                large = CB;
                small = CA;
                D->sign = -1;
            }
        }
        else{
            int x = compare(CA, CB);
            if(x == 1){
                large = CB;
                small = CA;
                D->sign = 1;
            }
            else{
                large = CA;
                small = CB;
                D->sign = -1;
            }
        }
        
        moveFront(large->number);
        moveFront(small->number);
        while(Index(large->number) != -1){
            differ = borrow;
            if(Index(large->number) != -1){
                differ += get(large->number);
            }
            if(Index(small->number) != -1){
                differ -= get(small->number);
            }
            if(differ < 0){
                differ += BASE;
                borrow = -1;
            }
            else{
                borrow = 0;
            }
            append(D->number, differ);
            if(Index(large->number) != -1){
                moveNext(large->number);
            }
            if(Index(small->number) != -1){
                moveNext(small->number);
            }
            
        }
        
    }
    else if(CA->sign == -1 && CB->sign == 1){
        CB->sign = -1;
        add(D, CA, CB);
    }
    else if(CA->sign == 1 && CB->sign == -1){
        CB->sign = 1;
        add(D, CA, CB);
    }
    removeZero(D);
    freeBigInteger(&CA);
    freeBigInteger(&CB);
}

// diff()
// Returns a reference to a new BigInteger object representing A - B.
BigInteger diff(BigInteger A, BigInteger B){
    BigInteger D = newBigInteger();
    subtract(D, A, B);
    return D;
}

//scalMult()
//helperFunction to multiply()
void scalMult(BigInteger S, BigInteger A, LIST_ELEMENT b){
    LIST_ELEMENT a, product, carry = 0;
    Clear(S->number);
    moveFront(A->number);
    S->sign = 1;
    while(Index(A->number) != -1){
        a = get(A->number);
        product = (a * b) + carry;
        if(product >= BASE){
            carry = product/BASE;
//            printf("%ld\n", carry);
        }
        else{
            carry = 0;
        }
        product = product % BASE;
        append(S->number, product);
        moveNext(A->number);
    }
    if(carry > 0){
        append(S->number, carry);
    }
    
}

// multiply()
// Places the product of A and B in the existing BigInteger P, overwriting
// its current state: P = A*B
void multiply(BigInteger P, BigInteger A, BigInteger B){
    BigInteger CA = copy(A);
    BigInteger CB = copy(B);
    BigInteger S1 = newBigInteger();
    S1->sign = 1;
    makeZero(P);
    moveFront(CA->number);
    moveFront(CB->number);
    P->sign = 1;
    if(A->sign == 0 || B->sign == 0){
        makeZero(P);
        return;
    }
    int count = 0;
    while(Index(CB->number) != -1){
        LIST_ELEMENT scal = get(CB->number);
        if(scal == 0){
            append(P->number, 0);
        }
        else{
            scalMult(S1, CA, scal);
            if(count > 0){
                for(int i = 0; i < count; i++){
                    prepend(S1->number, 0);
//                    printBigInteger(stdout, S1);
                }
            }
            add(P, P, S1);
        }
        moveNext(CB->number);
        count++;
    }
    if(A->sign == -1 && B->sign == -1){
        P->sign = 1;
    }
    else if(A->sign == 1 && B->sign == 1){
        P->sign = 1;
    }
    else{
        P->sign = -1;
    }
    freeBigInteger(&CA);
    freeBigInteger(&CB);
    freeBigInteger(&S1);
}

// prod()
// Returns a reference to a new BigInteger object representing A*B
BigInteger prod(BigInteger A, BigInteger B){
    BigInteger P = newBigInteger();
    multiply(P, A, B);
    return P;
}

// Other operations -----------------------------------------------------------

// printBigInteger()
// Prints a base 10 string representation of N to filestream out.
void printBigInteger(FILE* out, BigInteger N){
    moveBack(N->number);
    if(N->sign == -1){
        fprintf(out, "-");
    }
    else if(N->sign == 0){
        fprintf(out, "0\n");
        return;
    }
    fprintf(out, "%ld", get(N->number));
    movePrev(N->number);
    while(Index(N->number) != -1){
        LIST_ELEMENT x = get(N->number);
        LIST_ELEMENT base  = BASE/10;
        if(x == 0){
            for(int i = 1; i < base; i*=10){
                fprintf(out,"0");
            }
        }
        else if(x/base == 0){
            for(LIST_ELEMENT y = x; y < base; y*=10){
                fprintf(out, "0");
            }
        }
        fprintf(out, "%ld", get(N->number));
        movePrev(N->number);
    }
    
    fprintf(out, "\n");
}
