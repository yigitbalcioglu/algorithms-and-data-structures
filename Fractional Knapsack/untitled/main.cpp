#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Item {
    int weight;
    int value;
};

bool compare(Item a, Item b) {
    double r1 = (double)a.value / a.weight;
    double r2 = (double)b.value / b.weight;
    return r1 > r2;
}

double fractionalKnapsack(int W, vector<Item>& items) {

    sort(items.begin(), items.end(), compare);

    double maxValue = 0.0;

    for (const auto& item : items) {
        if (W >= item.weight) {

            W -= item.weight;
            maxValue += item.value;
        } else {

            maxValue += item.value * ((double)W / item.weight);
            break;
        }
    }

    return maxValue;
}

int main() {
    int W = 50;
    vector<Item> items = {{2, 30},{5, 45},{10, 60}, {20, 100}, {30, 120}};  // Eşyalar

    double maxVal = fractionalKnapsack(W, items);
    cout << "Maksimum değer: " << maxVal << endl;

    return 0;
}
