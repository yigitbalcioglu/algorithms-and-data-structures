#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Job {
    int id;        // İş numarası
    int profit;    // Kazanç
    int deadline;  // Son teslim süresi
};

// İşleri kazançlarına göre sıralayan karşılaştırma fonksiyonu
bool compare(Job a, Job b) {
    return a.profit > b.profit;
}

// Job Sequencing fonksiyonu
int jobSequencing(vector<Job>& jobs, int maxDeadline) {
    // İşleri kazançlarına göre azalan sırada sıralayın
    sort(jobs.begin(), jobs.end(), compare);

    // Son teslim süresine göre işlerin planlanması için bir dizi
    vector<int> schedule(maxDeadline + 1, -1);
    int totalProfit = 0;  // Toplam kazanç tutucu

    // İşleri sırayla planlayın
    for (const auto& job : jobs) {
        // İşin yapılabileceği en son uygun zaman birimini bul
        for (int j = min(maxDeadline, job.deadline); j > 0; j--) {
            if (schedule[j] == -1) {  // Boşsa
                schedule[j] = job.id; // İş ataması yap
                totalProfit += job.profit;
                break;
            }
        }
    }

    // Planlanan iş sırasını ve toplam kazancı ekrana yazdırın
    cout << "Seçilen işler: ";
    for (int i = 1; i <= maxDeadline; i++) {
        if (schedule[i] != -1) {
            cout << "Job" << schedule[i] << " ";
        }
    }
    cout << endl;

    return totalProfit;
}

int main() {
    vector<Job> jobs = {{1, 100, 2}, {2, 19, 1}, {3, 27, 2}, {4, 25, 1}, {5, 15, 3}};
    int maxDeadline = 3; // En büyük son teslim süresi

    int maxProfit = jobSequencing(jobs, maxDeadline);
    cout << "Maksimum kazanç: " << maxProfit << endl;

    return 0;
}
