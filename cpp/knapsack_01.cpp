#include <iostream>
#include <vector>

using namespace std;

// Function to solve 0/1 Knapsack and track items taken
int knapsack(int W, vector<int>& values, vector<int>& weights, int n) {
    vector<vector<int>> dp(n + 1, vector<int>(W + 1, 0));

    // Build DP table
    for (int i = 1; i <= n; i++) {
        for (int w = 1; w <= W; w++) {
            if (weights[i - 1] <= w) {
                dp[i][w] = max(values[i - 1] + dp[i - 1][w - weights[i - 1]], dp[i - 1][w]);
            } else {
                dp[i][w] = dp[i - 1][w];
            }
        }
    }

    // Track the items taken
    vector<int> taken(n, 0); // 0 = not taken, 1 = taken
    int w = W;
    for (int i = n; i > 0 && w > 0; i--) {
        if (dp[i][w] != dp[i - 1][w]) { // item i-1 was taken
            taken[i - 1] = 1;
            w -= weights[i - 1];
        }
    }

    // Print taken items
    cout << "Items taken (1 = yes, 0 = no): ";
    for (int x : taken) cout << x << " ";
    cout << endl;

    return dp[n][W];
}

int main() {
    int W, n;
    cout << "Enter the capacity of the knapsack: ";
    cin >> W;
    cout << "Enter the number of items: ";
    cin >> n;

    vector<int> values(n), weights(n);

    cout << "Enter the values of the items: ";
    for (int i = 0; i < n; i++) cin >> values[i];

    cout << "Enter the weights of the items: ";
    for (int i = 0; i < n; i++) cin >> weights[i];

    int max_value = knapsack(W, values, weights, n);
    cout << "Maximum value that can be obtained: " << max_value << endl;

    return 0;
}
