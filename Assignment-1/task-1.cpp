#include<iostream>
#include<vector>
#include<assert.h>

/***************************************/
/*          Fibonacci functions        */
/***************************************/
long long fib_recursion(int n){
    //ensure it is 1-based
    assert(n>0);

    //0 for the first and 1 for the second in fib series.
    if(n==1 or n==2)
        return n-1;
    return fib_recursion(n-1) + fib_recursion(n-2);
}

long long fib_dynamic_programming(int n){
    //ensure it is 1-based
    assert(n>0);

    if(n == 1 or n == 2)
        return n-1;

    std::vector<long long> fib(n+1, 0);

    fib[1] = 0;
    fib[2] = 1;

    for(int i = 3; i<= n; i++){
        fib[i] = fib[i-1] + fib[i-2];
    }

    return fib[n];
}


int main(){

    //  Test the functions here

}
