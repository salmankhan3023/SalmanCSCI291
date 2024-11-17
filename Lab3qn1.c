#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#define SIZE 24
#define nRows 8
#define nCols 3

// PROTOTYPES
void print_array(int array[], int length);
void print_matrix(int mat[][nCols], int rows);
bool isValid(const int arr[], int length, int pos);
void remove_element(int arr[], int length, int pos);
void insert_element(int arr[], int length, int pos, int value);
void reshape(const int arr[], int length, int arr2d[nRows][nCols]);
void trans_matrix(int inputMat[nRows][nCols], int outputMat[nCols][nRows]);
bool found_duplicate(int arr[], int length);

// Variables
int arr[SIZE];
int arr2d[nRows][nCols];
int mat_transp[nCols][nRows];
int test[] = {0, 1, 2, 3, 4, 5, 6,7, 8,10};

int main() {
    bool truth = found_duplicate(test, 10);
    printf("%d\n", truth);

    int arr[SIZE] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23};
printf("isValid(arr, 5, SIZE): %d\n", isValid(arr, 5, SIZE));  // Expected: 1 (true)
printf("isValid(arr, -1, SIZE): %d\n", isValid(arr, -1, SIZE)); // Expected: 0 (false)
printf("isValid(arr, 24, SIZE): %d\n", isValid(arr, 24, SIZE)); // Expected: 0 (false)

int arr1[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
remove_element(arr1, 10, 3); // Remove element at index 3
print_array(arr1, 10); // Expected: 0, 1, 2, 4, 5, 6, 7, 8, 9, 0

int arr2[] = {0, 1, 2, 4, 5, 6, 7, 8, 9, 0};
insert_element(arr2, 10, 3, 3); // Insert 3 at index 3
print_array(arr2, 10); // Expected: 0, 1, 2, 3, 4, 5, 6, 7, 8, 9

int arr3[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23};
reshape(arr3, SIZE, arr2d);
print_matrix(arr2d, nRows); // Expected: 2D array with 8 rows and 3 columns

int arr2d_trans[nCols][nRows];
trans_matrix(arr2d, arr2d_trans);
print_matrix(arr2d_trans, nCols); // Expected: Transposed 2D array with 3 rows and 8 columns

int test1[] = {0, 1, 2, 3, 4, 5, 6, 7, 7, 8};
int test2[] = {0, 1, 2, 3, 4, 5, 6, 8, 9, 10};
printf("found_duplicate(test1, 10): %d\n", found_duplicate(test1, 10)); 
printf("found_duplicate(test2, 10): %d\n", found_duplicate(test2, 10)); 


    return 0;
}

void print_array(int array[], int length) {
    for (int i = 0; i < length; i++)
        printf("array[%d]= %d\n", i, array[i]);
}

void print_matrix(int mat[][nCols], int rows) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < nCols; j++)
            printf("mat[%d][%d]= %d\n", i, j, mat[i][j]);
        puts("");
    }
}

bool isValid(const int arr[], int pos, int length) {
    return (pos < (length - 1) && pos >= 0);
}

void remove_element(int arr[], int length, int pos) {
    bool valid = isValid(arr, pos, length);
    if (valid) {
        for (int i = pos; i < length - 1; i++) {
            arr[i] = arr[i + 1];
        }
        arr[length - 1] = 0; 
    } else {
        printf("Pos is Invalid\n");
    }
}

void insert_element(int arr[], int length, int pos, int value) {
    bool valid = isValid(arr, pos, length);
    if (valid) {
        for (int i = length - 1; i > pos; i--) {
            arr[i] = arr[i - 1];
        }
        arr[pos] = value;
    } else {
        printf("Pos is Invalid\n");
    }
}

void reshape(const int arr[], int length, int arr2d[nRows][nCols]) {
    if (length == nRows * nCols) {
        int count = 0;
        for (int i = 0; i < nRows; i++) {
            for (int j = 0; j < nCols; j++) {
                arr2d[i][j] = arr[count];
                count++;
            }
        }
    } else {
        printf("1D array length does not match number of elements in 2D array\n");
        exit(-1);
    }
}

void trans_matrix(int inputMat[nRows][nCols], int outputMat[nCols][nRows]) {
    for (int i = 0; i < nRows; i++) {
        for (int j = 0; j < nCols; j++) {
            outputMat[j][i] = inputMat[i][j];
        }
    }
}

bool found_duplicate(int arr[], int length) {
    for (int i = 0; i < length; i++) {
        for (int j = i + 1; j < length; j++) {
            if (arr[i] == arr[j]) {
                return true;
            }
        }
    }
    return false;
}
