(* Joe, a data analyst at a tech company, is tasked with analyzing sales data from a grid representing monthly sales figures for various products. He needs to find all contiguous sub-squares within the grid whose total sales equal a specified target value, S. Joe must develop a program that counts how many such sub-squares exist in the grid.



Example



Input:

3

1 2 3

4 5 6

7 8 9

16

Output:

1

Explanation:

In the given matrix, the sub-square(0, 1) to (1, 2) with sum = 2 + 3 + 5 + 6 = 16. So, the output is the count of all the square sub-squares, the sum of whose elements is equal to S, which is 1. *)
#include <stdio.h>

#define MAX 100

int main() {
    int matrix[MAX][MAX];
    int prefix_sum[MAX][MAX];
    int n, target_sum;

    // Read matrix dimensions
    printf("Enter the size of the matrix: ");
    scanf("%d", &n);

    // Read matrix elements
    printf("Enter the matrix elements:\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            scanf("%d", &matrix[i][j]);
        }
    }

    // Read target sum
    printf("Enter the target sum: ");
    scanf("%d", &target_sum);

    // Compute prefix sums
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            prefix_sum[i][j] = matrix[i][j];
            if (i > 0) prefix_sum[i][j] += prefix_sum[i-1][j];
            if (j > 0) prefix_sum[i][j] += prefix_sum[i][j-1];
            if (i > 0 && j > 0) prefix_sum[i][j] -= prefix_sum[i-1][j-1];
        }
    }

    // Count the number of valid sub-squares
    int count = 0;

    for (int size = 1; size <= n; size++) {  // size of sub-square
        for (int r1 = 0; r1 <= n - size; r1++) {  // top-left row
            for (int c1 = 0; c1 <= n - size; c1++) {  // top-left column
                int r2 = r1 + size - 1;  // bottom-right row
                int c2 = c1 + size - 1;  // bottom-right column

                // Calculate sum of the current sub-square
                int total = prefix_sum[r2][c2];
                if (r1 > 0) total -= prefix_sum[r1-1][c2];
                if (c1 > 0) total -= prefix_sum[r2][c1-1];
                if (r1 > 0 && c1 > 0) total += prefix_sum[r1-1][c1-1];

                // Check if the sum matches the target sum
                if (total == target_sum) {
                    count++;
                }
            }
        }
    }

    // Output the result
    printf("Number of sub-squares with sum equal to %d: %d\n", target_sum, count);

    return 0;
}


