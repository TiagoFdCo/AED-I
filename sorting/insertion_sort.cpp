#include <iostream>

using namespace std;

void insertion_sort(int arr[], int n){
    int aux = 0;
    int key = 0;
    int j = 0;

// TEM QUE MUDAR ISSO AQUI 

    for(int i = 1; i < n; i++){
        key = arr[i];
        j = i - 1;
        while( j >= 0 && arr[j] > key){
            aux = key;
            arr[i] = arr[j];
            j--;
        }
        arr[j] = aux;
    }

    for (int k = 0; k < n; k++){
        cout << arr[k] << " ";
    }
}


int main(){
    int arr[] = {3, 2, 1, 5};
    int n = sizeof(arr) / sizeof(arr[0]);

    insertion_sort(arr, n);
    return 0;
}