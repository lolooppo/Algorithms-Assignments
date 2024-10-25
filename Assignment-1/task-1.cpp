#include<iostream>
#include<vector>
#include<assert.h>

/***************************************/
/*          Fibonacci functions        */
/***************************************/
long long fib_recursion(int n){
    if(n==0 or n==1)
        return n;
    return fib_recursion(n-1) + fib_recursion(n-2);
}

long long fib_dynamic_programming(int n){
    if(n == 0 or n == 1)
        return n;

    std::vector<long long> fib(n+1, 0);

    fib[0] = 0;
    fib[1] = 1;

    for(int i = 2; i<= n; i++){
        fib[i] = fib[i-1] + fib[i-2];
    }

    return fib[n];
}

int main(){
    
}
