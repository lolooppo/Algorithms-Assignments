#include<iostream>
#include<vector>
#include<assert.h>

/************************************/
/*  Sequential Searching functions  */
/************************************/

int sequential_search_iterative(int n, int arr[], int target){
    for(int idx = 0; idx < n; idx++){
        if(arr[idx] == target)
            return idx;
    }

    return -1;
}

int sequential_search_recursive(int n, int arr[], int target, int idx = 0){
    if(idx == n)
        return -1;

    if(arr[idx] == target)
        return idx;

    return sequential_search_recursive(n, arr, target, idx + 1);
}



/************************************/
/*    Binary Searching functions    */
/************************************/

int binary_search_iterative(int n, int arr[], int target){
    int left{0}, right{n-1};

    while(left <= right){
        int mid = left + (right - left) / 2;

        if(arr[mid] == target)
            return mid;

        if(arr[mid] > target)
            right = mid - 1;
        else
            left = mid + 1;
    }

    return -1;
}

int binary_search_recursive(int left, int right, int arr[], int target){
    if(left > right)
        return -1;

    int mid = left + (right - left) / 2;
    if(arr[mid] == target)
        return mid;

    if(arr[mid] > target)
        return binary_search_recursive(left, mid - 1, arr, target);

    return  binary_search_recursive(mid + 1, right, arr, target);
}

int main(){

    // Test the functions here
}
