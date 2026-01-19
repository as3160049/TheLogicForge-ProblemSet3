#include<bits/stdc++.h>
using namespace std;

vector<int> findAnagramIndices(const string& s, const string& p) {
    vector<int> result;
    int n = s.size(), m = p.size();
    if (m > n) return result;

    vector<int> freqP(26, 0), freqW(26, 0);

    // frequency of pattern p
    for (char c : p)
        freqP[c - 'a']++;

    int left = 0;

    for (int right = 0; right < n; right++) {
        // add current character to window
        freqW[s[right] - 'a']++;

        // shrink window if size exceeds p
        if (right - left + 1 > m) {
            freqW[s[left] - 'a']--;
            left++;
        }

        // check match
        if (right - left + 1 == m && freqW == freqP) {
            result.push_back(left);
        }
    }

    return result;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string s, p;
    cin >> s >> p;

    vector<int> indices = findAnagramIndices(s, p);

    if (indices.empty()) {
        cout << "-1\n";
    } else {
        for (size_t i = 0; i < indices.size(); i++) {
            cout << indices[i];
            if (i + 1 < indices.size()) cout << " ";
        }
        cout << "\n";
    }

    return 0;
}
