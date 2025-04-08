#include <iostream>
#include <vector>
using namespace std;

// Function to solve the activity selection problem
int activitySelection(vector<int> &start, vector<int> &end) {

    // to store results.
    int ans = 0;
    vector<int>activity;
    // to store the end time of last activity
    int finish = -1;

    for(int i = 0; i < start.size(); i++) {
        if (start[i] > finish) {
            finish = end[i];
            activity.push_back(i);
            ans++;
        }
    }
    for (int a : activity){
      cout<<a<<" "; 
    }
    cout<<endl;
    
    return ans;
}

int main() {
    vector<int> start = { 1, 3, 0, 5, 8, 5 };
    vector<int> end = { 2, 4, 6, 7, 9, 9 };
    cout<<activitySelection(start, end);
    return 0;
}
