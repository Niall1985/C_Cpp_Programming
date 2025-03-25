#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// Structure to store activity with start and end times
struct Activity {
    int start, end;
};

// Comparator function to sort activities by their finish time
bool compare(Activity a, Activity b) {
    return a.end < b.end;
}

// Function to find the maximum number of non-overlapping activities
int maxActivities(vector<Activity>& activities) {
    // Sort activities by their finish time
    sort(activities.begin(), activities.end(), compare);

    int count = 1; // Select the first activity
    int last_end_time = activities[0].end;

    // Iterate through the remaining activities
    for (int i = 1; i < activities.size(); i++) {
        if (activities[i].start >= last_end_time) {
            count++;
            last_end_time = activities[i].end; // Update the last selected activity's end time
        }
    }
    return count;
}

int main() {
    int n;
    cout << "Enter the number of activities: ";
    cin >> n;

    vector<Activity> activities(n);
    cout << "Enter start and end times of activities:\n";
    for (int i = 0; i < n; i++) {
        cin >> activities[i].start >> activities[i].end;
    }

    int maxCount = maxActivities(activities);
    cout << "Maximum number of non-overlapping activities: " << maxCount << endl;

    return 0;
}
