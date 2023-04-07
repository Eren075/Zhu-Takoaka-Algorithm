#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

// Zhu takoaka algoritmas�n�n implemantasyonu
vector<int> zhuTakaoka(const string& pattern) {
    int m = pattern.length();
    vector<int> z(m, 0);

    int l = 0, r = 0;
    for (int i = 1; i < m; i++) {
        if (i < r) {
            z[i] = min(z[i - l], r - i);
        }
        while (i + z[i] < m && pattern[z[i]] == pattern[i + z[i]]) {
            z[i]++;
        }
        if (i + z[i] > r) {
            l = i;
            r = i + z[i];
        }
    }

    return z;
}

int main() {
    string filename = "alice_in_wonderland.txt";
    vector<string> words;
    words.push_back("upon");
    words.push_back("sigh");
    words.push_back("Dormouse");
    words.push_back("jury-box");
    words.push_back("swim");

    // Dosyay� a� ve metni oku
    ifstream file(filename.c_str());
    string text((istreambuf_iterator<char>(file)), istreambuf_iterator<char>());

   // Zhu-Takaoka algoritmas�n� kullanarak her kelimenin olu�um say�s�n� say�n
    for (vector<string>::iterator it = words.begin(); it != words.end(); ++it) {
        string word = *it;


	//Model i�in Z dizisini hesaplay�n
        vector<int> z = zhuTakaoka(word);

        // Metinde kal�b� aray�n
        int count = 0;
        int n = text.length();
        for (int i = 0, j = 0; i < n; i++) {
            while (j > 0 && word[j] != text[i]) {
                j = z[j - 1];
            }
            if (word[j] == text[i]) {
                j++;
            }
            if (j == static_cast<int>(word.length())) {
                count++;
                j = z[j - 1];
            }
        }

        // Print the result
        cout << "Kelime"" " << word << " bulunuyor " << count << " kez" << endl;
    }

    return 0;
}
