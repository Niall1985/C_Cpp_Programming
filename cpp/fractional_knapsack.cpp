#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// Structure to represent an item
struct Item {
    int value, weight;

    // Constructor
    Item(int v, int w) : value(v), weight(w) {}
};

// Comparator function to sort items by value-to-weight ratio (descending)
bool compare(Item a, Item b) {
    double r1 = (double)a.value / a.weight;
    double r2 = (double)b.value / b.weight;
    return r1 > r2;
}

// Function to solve Fractional Knapsack
double fractionalKnapsack(int W, vector<Item>& items) {
    // Sort items by value-to-weight ratio
    sort(items.begin(), items.end(), compare);

    double maxValue = 0.0; // To store the final maximum value
    for (Item& item : items) {
        if (W >= item.weight) {
            // If we can take the full item
            maxValue += item.value;
            W -= item.weight;
        } else {
            // Take the fraction of the item
            maxValue += item.value * ((double)W / item.weight);
            break; // Knapsack is full
        }
    }
    return maxValue;
}

int main() {
    int W, n;
    cout << "Enter the capacity of the knapsack: ";
    cin >> W;
    cout << "Enter the number of items: ";
    cin >> n;

    vector<Item> items;
    cout << "Enter the values and weights of the items: \n";
    for (int i = 0; i < n; i++) {
        int value, weight;
        cin >> value >> weight;
        items.push_back(Item(value, weight));
    }

    double max_value = fractionalKnapsack(W, items);
    cout << "Maximum value that can be obtained: " << max_value << endl;

    return 0;
}
