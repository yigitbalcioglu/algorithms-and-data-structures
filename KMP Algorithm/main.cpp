#include <iostream>
#include <vector>
using namespace std;

// LPS (Longest Prefix Suffix) tablosunu oluşturma fonksiyonu
void computeLPSArray(string pattern, int M, vector<int>& lps) {
    int len = 0; // Önceki en uzun prefix/suffix uzunluğu
    lps[0] = 0; // İlk pozisyon için lps 0'dır

    int i = 1;
    while (i < M) {
        if (pattern[i] == pattern[len]) {
            len++;
            lps[i] = len;
            i++;
        }
        else {
            // pattern[i] != pattern[len] ise
            if (len != 0) {
                len = lps[len - 1];
            }
            else {
                lps[i] = 0;
                i++;
            }
        }
    }
}

// KMP algoritması ile desen arama fonksiyonu
void KMPsearch(string pattern, string text) {
    int M = pattern.length();
    int N = text.length();

    // LPS tablosunu hesapla
    vector<int> lps(M);
    computeLPSArray(pattern, M, lps);

    int i = 0; // text'teki index
    int j = 0; // pattern'deki index

    while (i < N) {
        if (pattern[j] == text[i]) {
            j++;
            i++;
        }

        if (j == M) {
            // Desen bulundu (eşleşme)
            cout << "Desen, metinde " << i - j << " indexinde bulundu." << endl;
            j = lps[j - 1];
        }
        else if (i < N && pattern[j] != text[i]) {
            // Eşleşme yoksa, lps tablosuna göre j'yi güncelle
            if (j != 0) {
                j = lps[j - 1];
            }
            else {
                i++;
            }
        }
    }
}

int main() {
    string text = "ABABDABACDABABCABAB";
    string pattern = "ABABCABAB";

    KMPsearch(pattern, text);

    return 0;
}
