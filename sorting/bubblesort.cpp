#include <iostream>

using namespace std;

void bubblesort(int arr[], int n){
    int current = 0;

    for(int i = 0; i < n; i++){
        for(int j= i + 1; j< n; j++){
            if(arr[i] > arr[j]){
                current = arr[i];
                arr[i] = arr[j];
                arr[j] = current;
            }
        }
    }

    for(int k = 0; k < n; k++){
        cout << arr[k] << " " << endl;
    }
}

int main(){
    int array[] = {3, 2, 4, 1, 6, 89, 7};
    int n = sizeof(array) / sizeof(array[0]);

    bubblesort(array, n);
    return 0;
}