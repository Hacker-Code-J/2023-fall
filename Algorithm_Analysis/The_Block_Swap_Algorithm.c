// Function to reverse a sub-array [start, end]
void reverse(int arr[], int start, int end) {
    int temp;
    while (start < end) {
        temp = arr[start];
        arr[start] = arr[end];
        arr[end] = temp;
        start++;
        end--;
    }
}

// Function to rotate an array
void rotateArray(int arr[], int n, int d) {
    if (d == 0 || d == n) {
        return;
    }

    // Reverse the first 'd' elements
    reverse(arr, 0, d - 1);

    // Reverse the remaining 'n-d' elements
    reverse(arr, d, n - 1);

    // Reverse the whole array
    reverse(arr, 0, n - 1);
}

// Main function
int main() {
    int arr[] = {1, 2, 3, 4, 5, 6, 7};
    int n = sizeof(arr) / sizeof(arr[0]);
    int d = 2;

    rotateArray(arr, n, d);

    // Code to print the rotated array
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }

    return 0;
}
