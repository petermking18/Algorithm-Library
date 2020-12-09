//
// Created by Peter King on 9/10/20.
//

#include "SortAlgorithms.h"

vector<int> SortAlgorithms::bubble(vector<int> data) {
    bool didSwap = true;
    while(didSwap){
        didSwap = false;
        for(int i = 0; i < (data.size()-1); i++){
            if(data[i] > data[i+1]){
                int temp = data[i+1];
                data[i+1] = data[i];
                data[i] = temp;
                didSwap = true;
            }
        }
    }
    return data;
}

vector<int> SortAlgorithms::merge(vector<int> data){
    return mergeSort(data, 0, data.size()-1);
}

vector<int> SortAlgorithms::mergeSort(vector<int> data, int l, int r) {
    if(l < r){
        int m = l +(r-l)/2;
        data = mergeSort(data, l,m);
        data = mergeSort(data, m+1, r);
        data = merger(data, l, m, r);
    }
    return data;
}

vector<int> SortAlgorithms::merger(vector<int> data, int l, int m, int r){
    int i, j, k;
    int n1 = m - l + 1;
    int n2 = r - m;

    //Create temp arrays
    int L[n1], R[n2];

    //Copy data to temp arrays
    for(i = 0; i < n1; i++)
        L[i] = data[l+i];
    for(j = 0; j < n2; j++)
        R[j] = data[m+1+j];

    //Merge the temp arrays back into the original
    i = 0;
    j = 0;
    k = l;
    while(i < n1 && j < n2){
        if(L[i] <= R[j]){
            data[k] = L[i];
            i++;
        }else{
            data[k] = R[j];
            j++;
        }
        k++;
    }

    //Copy remaining elements of L[], if there are any
    while(i < n1){
        data[k] = L[i];
        i++;
        k++;
    }

    //Copy remaining elements of R[], if there are any
    while(j < n2){
        data[k] = R[j];
        j++;
        k++;
    }
    return data;
}

vector<int> SortAlgorithms::insertion(vector<int> data) {
    int key = 0;
    int j = 0;
    for(int i = 0; i < data.size(); i++){
        key = data[i];
        j = i - 1;

        while(j >= 0 && data[j] > key){
            data[j+1] = data[j];
            j--;
        }
        data[j+1] = key;
    }
    return data;
}