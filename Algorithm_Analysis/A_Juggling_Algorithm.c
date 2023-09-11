#include<stdio.h>

// Function to find the greatest common divisor (GCD)
int gcd(int a, int b) {
    if (b == 0) {
        return a;
    }
    return gcd(b, a % b);
}

// Function to rotate an array
void rotateArray(int arr[], int n, int d) {
    int i, j, k, temp;
    
    // Find GCD of n and d
    int g = gcd(d, n);
    
    for (i = 0; i < g; i++) {
        // Store the first element of the current set
        temp = arr[i];
        
        j = i;
        
        // Shift each element of the set
        while (1) {
            k = j + d;
            
            // If k exceeds the array size, bring it within bounds
            if (k >= n) {
                k = k - n;
            }
            
            // If we are back to the initial position, break the loop
            if (k == i) {
                break;
            }
            
            // Move the element
            arr[j] = arr[k];
            
            // Update j for the next iteration
            j = k;
        }
        
        // Put the first element in its correct position within the set
        arr[j] = temp;
    }
}

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
