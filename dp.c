// find the number of ways in which sum of natural numbers to raised to the power of k can add up to a number

// eg num = 10; pow = 2
// ways: 1
// exp: 1^2+3^2




#include <stdio.h>
#include <math.h>

// Function to find the number of ways to express `num` as a sum of natural numbers raised to power `exponent`
int countWaysRecursive(int num, int exponent, int current) {
    // Base case: If num is 0, there's exactly one way to represent it (using no numbers)
    if (num == 0) {
        return 1;
    }

    // Base case: If num becomes negative, there's no valid way
    if (num < 0) {
        return 0;
    }

    // Initialize count of ways
    int count = 0;

    // Start from the current number and go up to the number whose `exponent` does not exceed `num`
    for (int i = current; pow(i, exponent) <= num; i++) {
        int power = pow(i, exponent);
        count += countWaysRecursive(num - power, exponent, i + 1);
    }

    return count;
}

int main() {
    int num, exponent;

    // Read the input
    printf("Enter the number: ");
    scanf("%d", &num);
    printf("Enter the exponent: ");
    scanf("%d", &exponent);

    // Calculate the number of ways using recursion
    int result = countWaysRecursive(num, exponent, 1);

    // Output the result
    printf("Number of ways to sum to %d using natural numbers raised to the power of %d: %d\n", num, exponent, result);

    return 0;
}
