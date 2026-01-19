#include<bits/stdc++.h>
using namespace std;

string longestPalindromicSubstring(const string& s) {
    int n = s.size();
    if (n == 0) return "";

    int start = 0, maxLen = 1;

    auto expand = [&](int L, int R) {
        while (L >= 0 && R < n && s[L] == s[R]) {
            int len = R - L + 1;
            if (len > maxLen) {
                maxLen = len;
                start = L;
            }
            L--;
            R++;
        }
    };

    for (int i = 0; i < n; i++) {
        expand(i, i);       // odd-length palindrome
        expand(i, i + 1);   // even-length palindrome
    }

    return s.substr(start, maxLen);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string s;
    cin >> s;

    string result = longestPalindromicSubstring(s);
    cout << result << "\n";

    return 0;
}
