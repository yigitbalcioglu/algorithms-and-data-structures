#include <iostream>
#include <queue>
#include <unordered_map>
#include <vector>

using namespace std;

// Huffman Ağacı için düğüm yapısı
struct Node {
    char ch;
    int freq;
    Node* left;
    Node* right;

    Node(char character, int frequency) : ch(character), freq(frequency), left(nullptr), right(nullptr) {}
};

// Öncelik sırasına göre karşılaştırma yapmak için operator overloading
struct compare {
    bool operator()(Node* left, Node* right) {
        return left->freq > right->freq;
    }
};

// Huffman ağacını dolaşarak her karakter için kodu çıkarır
void encode(Node* root, string str, unordered_map<char, string>& huffmanCode) {
    if (root == nullptr) return;

    // Yaprak düğümse
    if (!root->left && !root->right) {
        huffmanCode[root->ch] = str;
    }

    encode(root->left, str + "0", huffmanCode);
    encode(root->right, str + "1", huffmanCode);
}

// Hafızayı temizlemek için ağacı serbest bırakır
void freeTree(Node* root) {
    if (root == nullptr) return;
    freeTree(root->left);
    freeTree(root->right);
    delete root;
}

// Huffman Coding algoritmasını uygular
void buildHuffmanTree(const string& text) {
    // Karakter frekanslarını hesaplayın
    unordered_map<char, int> freq;
    for (char ch : text) {
        freq[ch]++;
    }

    // Min-Heap oluşturun
    priority_queue<Node*, vector<Node*>, compare> pq;

    // Tüm karakterleri min-heap'e ekleyin
    for (auto pair : freq) {
        pq.push(new Node(pair.first, pair.second));
    }

    // Ağacı inşa edin
    while (pq.size() > 1) {
        Node* left = pq.top(); pq.pop();
        Node* right = pq.top(); pq.pop();

        int sum = left->freq + right->freq;
        Node* newNode = new Node('\0', sum);  // İç düğüm, karakter yok ('\0')
        newNode->left = left;
        newNode->right = right;
        pq.push(newNode);
    }

    // Kök düğüm
    Node* root = pq.top();

    // Huffman kodlarını saklamak için bir map kullanın
    unordered_map<char, string> huffmanCode;
    encode(root, "", huffmanCode);

    // Karakterlerin Huffman kodlarını ekrana yazdırın
    cout << "Huffman Kodları:\n";
    for (auto pair : huffmanCode) {
        cout << pair.first << " " << pair.second << endl;
    }

    // Sıkıştırılmış metni ekrana yazdırın
    cout << "\nSıkıştırılmış metin: ";
    string compressedText;
    for (char ch : text) {
        compressedText += huffmanCode[ch];
    }
    cout << compressedText << endl;

    // Hafızayı temizle
    freeTree(root);
}

int main() {
    string text = "AACDDEEFF";
    buildHuffmanTree(text);
    return 0;
}
