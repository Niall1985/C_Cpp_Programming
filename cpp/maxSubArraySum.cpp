#include <iostream>
#include <climits>
#include <vector>
using namespace std;

int maxSubarraySum(vector<int>&arr){
    int res = arr[0];
    int start = 0, end = 0;
    // int tempStart = 0;

    for(int i = 0 ; i < arr.size() ; i++){
        int currSum = 0;
        for(int j = i ; j < arr.size() ; j++){
            currSum += arr[j];

            if(currSum > res){
                res = currSum;
                start = i;
                end = j;
            }
        }
    }

    cout << "Maximum subarray: ";
    for(int k = start; k <= end; k++) {
        cout << arr[k] << " ";
    }
    cout << endl;

    return res;
}

int main() {
    vector<int> arr = {2, 3, -8, 7, -1, 2, 3};
    int maxSum = maxSubarraySum(arr);
    cout << "Maximum subarray sum: " << maxSum << endl;
    return 0;
}