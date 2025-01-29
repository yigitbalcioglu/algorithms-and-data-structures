#include <iostream>
#include <string>
#include <vector>

using namespace std;

#define d 256 // Karakter setinin boyutu (ASCII için 256)

// Rabin-Karp algoritması ile metinde desen arama
void rabinKarpSearch(const string& text, const string& pattern, int q) {
    int M = pattern.length();
    int N = text.length();
    int i, j;
    int p = 0; // Desenin hash değeri
    int t = 0; // Metnin mevcut pencere hash değeri
    int h = 1;
    vector<int> result; // Eşleşme pozisyonlarını tutar

    // h = pow(d, M-1) % q
    for(i = 0; i < M - 1; i++)
        h = (h * d) % q;

    // İlk hash değerlerini hesapla
    for(i = 0; i < M; i++) {
        p = (d * p + pattern[i]) % q;
        t = (d * t + text[i]) % q;
    }

    // Metni kaydırarak ara
    for(i = 0; i <= N - M; i++) {
        // Hash değerleri eşleşirse
        if(p == t) {
            // Karakter karakter karşılaştırma
            for(j = 0; j < M; j++) {
                if(text[i + j] != pattern[j])
                    break;
            }

            if(j == M) {
                // Eşleşme bulundu
                result.push_back(i);
            }
        }

        // Hash değerini güncelle
        if(i < N - M) {
            t = (d * (t - text[i] * h) + text[i + M]) % q;

            // Negatif hash değerini pozitif yap
            if(t < 0)
                t = (t + q);
        }
    }

    // Sonuçları yazdır
    if(result.empty()) {
        cout << "Desen metinde bulunamadı." << endl;
    } else {
        cout << "Desen şu pozisyonlarda bulundu: ";
        for(int pos : result)
            cout << pos << " ";
        cout << endl;
    }
}

int main() {
    string text = "ABABDABACDABABCABAB";
    string pattern = "ABABCABAB";
    int q = 101; // Bir asal sayı

    rabinKarpSearch(text, pattern, q);

    return 0;
}
