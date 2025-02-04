#include <iostream>
#include <climits>
#include <vector>
using namespace std;

int main() {
    vector<int> arr = {5, 4, 6, 2, 7};
    int n = arr.size() - 1; // Number of matrices
    vector<vector<int>> m(n, vector<int>(n, 0));
    vector<vector<int>> s(n, vector<int>(n, 0));

    int j, q;
  
    for (int d = 1; d < n; d++) { // Chain length
        for (int i = 0; i < n - d; i++) {
            j = i + d;
            m[i][j] = INT_MAX; // Initialize to a large value

            for (int k = i; k < j; k++) { // Try different partitions
                q = m[i][k] + m[k+1][j] + arr[i] * arr[k+1] * arr[j+1];

                if (q < m[i][j]) {
                    m[i][j] = q;
                    s[i][j] = k; // Store split position
                }
            }
        }
    }

    cout << "Minimum Cost: " << m[0][n-1] << endl;
    return 0;
}
