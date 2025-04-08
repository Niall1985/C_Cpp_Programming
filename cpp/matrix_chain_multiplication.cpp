#include <iostream>
#include <vector>
#include <climits>

using namespace std;

// Function to print the optimal parenthesization
void printOptimalParens(vector<vector<int>>& s, int i, int j) {
    if (i == j) {
        cout << "A" << i + 1;  // Matrices are 1-based indexed
        return;
    }
    cout << "(";
    printOptimalParens(s, i, s[i][j]);   // Left subproblem
    printOptimalParens(s, s[i][j] + 1, j); // Right subproblem
    cout << ")";
}


/* print ((A(BC))D) kinda format
char character = 'A';
void PrintParenthesis(vector<vector<int>>&s, int i, int j){
  if(i == j){
    cout<<character++;
    return;
  }
  
  cout<<"(";
  PrintParenthesis(s, i, s[i][j]);
  PrintParenthesis(s, s[i][j] + 1, j);
  cout<<")";
}
*/

int main() {
    vector<int> arr = {5, 4, 6, 2, 7}; // Dimensions
    int n = arr.size() - 1; // Number of matrices
    vector<vector<int>> m(n, vector<int>(n, 0));
    vector<vector<int>> s(n, vector<int>(n, 0));

    int j, q;
  
    for (int d = 1; d < n; d++) { // Chain length
        for (int i = 0; i < n - d; i++) {
            j = i + d;
            m[i][j] = INT_MAX; // Initialize to large value

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
    cout << "Optimal Parenthesization: ";
    printOptimalParens(s, 0, n - 1);
    cout << endl;

    return 0;
}
