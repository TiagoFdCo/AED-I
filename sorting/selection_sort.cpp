#include <iostream>

using namespace std;

void selection_sort(int arr[], int n){
    int min = 0;
    int aux = 0;

    for(int i = 0; i < n; i++){
        min = i;
        for(int j = i + 1; j < n; j++){
            if(arr[j] < arr[min]){
                min = j;
            }
        }
        aux = arr[i];
        arr[i] = arr[min];
        arr[min] = aux;
    }

    for(int k = 0; k < n; k++){
        cout << arr[k] << " ";
    }
}

int main(){
    int arr[] = {3, 2, 1, 5, 6, 192, 22};
    int n = sizeof(arr) / sizeof(arr[0]);

    selection_sort(arr, n);

    return 0;
}