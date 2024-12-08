#include<bits/stdc++.h>
using namespace std;


struct Data{
    int key{-1};
    int value{0};
};









int HashingByDivision(int K, int N){
    return (K % N);
}

int HashingByMultiplication(int K, int N, float A){
    double fractional_part = (K*A) - floor(K*A);

    return floor(N * fractional_part);
}

int HashingByMidSquare(int K, int N){
    long long square = (long long)K * K;
    string squared_string = to_string(square);


    int r = ceil(log10(N));
    int len = squared_string.length();
    int mid_start = (len / 2) - (r / 2);

    string middle_digits = squared_string.substr(mid_start, r);
    int middle_value = stoi(middle_digits);

    return middle_value % N;
}

int HashingByFolding(int K, int N){
    string K_string = to_string(K);

    int total_partitions_sum{0};
    int partitioning_size = ceil(log10(N));
    int partition_start_idx{0};
    while(partition_start_idx < (int)K_string.length()){
        string partition = K_string.substr(partition_start_idx, partitioning_size);
        partition_start_idx += partitioning_size;
        total_partitions_sum += stoi(partition);
    }

    return total_partitions_sum % N;
}










bool InsertByOpenAdressing(int K, int N, vector<Data*>& table){
    int address = K;

    for(int steps = 0; steps < N; steps++, address++){
        address = HashingByDivision(address, N);
        if(table[address] == nullptr){
            table[address] = new Data;
            table[address]->key = address, table[address]->value = K;
            return true;
        }
    }

    return false;
}


bool InsertByChaining(int K, int N, vector<set<int>>& table){
    int address = HashingByDivision(K, N);
    table[address].insert(K);

    return true;
}


bool InsertByDoubleHashing(int K, int N, vector<Data*>& table){
    int address = K;

    for(int step=0; step<N; step++){
        address = (HashingByDivision(K, N) + step * (7-(K%7))) % N;
        if(table[address] == nullptr){
            table[address] = new Data;
            table[address]->key = address, table[address]->value = K;
            return true;
        }
    }

    return false;
}









void test_open_addressing(){
    vector<Data*> table(11);
    InsertByOpenAdressing(7, 11, table);
    InsertByOpenAdressing(36, 11, table);
    InsertByOpenAdressing(18, 11, table);
    InsertByOpenAdressing(62, 11, table);

    for(int i=0; i<11; i++){
        if(table[i] != nullptr)
            cerr    <<  table[i]->key   <<  ":\t"    <<  table[i]->value <<  "\n";
    }

    cerr    <<  "\n";
}


void test_chaining(){
    vector<set<int>> table(10);
    InsertByChaining(10, 10, table);
    InsertByChaining(20, 10, table);
    InsertByChaining(11, 10, table);
    InsertByChaining(1, 10, table);
    InsertByChaining(7, 10, table);

    for(int i=0; i<10; i++){
        if(table[i].empty())
            continue;
        cerr    <<    i <<":\t";
        for(auto it=table[i].begin(); it!=table[i].end(); it++)
            cerr    <<  *it <<  ", ";
        cerr    <<  "\n";
    }

    cerr    <<  "\n";
}


void test_double_hashing(){
    vector<Data*> table(10);
    InsertByDoubleHashing(37, 10, table);
    InsertByDoubleHashing(90, 10, table);
    InsertByDoubleHashing(45, 10, table);
    InsertByDoubleHashing(22, 10, table);
    InsertByDoubleHashing(17, 10, table);
    InsertByDoubleHashing(49, 10, table);
    InsertByDoubleHashing(55, 10, table);

    for(int i=0; i<10; i++){
        if(table[i] != nullptr)
            cerr    <<  table[i]->key   <<  ":\t"    <<  table[i]->value <<  "\n";
    }

    cerr    <<  "\n";
}






int main(){
    //test_open_addressing();
    //test_chaining();
    //test_double_hashing();
}