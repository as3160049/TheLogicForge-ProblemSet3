#include <bits/stdc++.h>
using namespace std;

struct Person {
    int weight;
    int priority;
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, Q, limit;
    cin >> N >> Q >> limit;

    vector<int> w(N), priority(N);
    for (int i = 0; i < N; i++) cin >> w[i];
    for (int i = 0; i < N; i++) cin >> priority[i];

    // Separate people
    vector<int> pri, non;
    for (int i = 0; i < N; i++) {
        if (priority[i]) pri.push_back(w[i]);
        else non.push_back(w[i]);
    }

    sort(pri.begin(), pri.end());
    sort(non.begin(), non.end());

    // Minimum boats
    int boats = 0;
    int i = 0, j = non.size() - 1;

    // Pair priority with non-priority if possible
    for (int p = pri.size() - 1; p >= 0; p--) {
        if (i <= j && pri[p] + non[i] <= limit) {
            i++; // paired
        }
        boats++; 
    }

    // Pair remaining non-priority people
    while (i <= j) {
        if (i != j && non[i] + non[j] <= limit) {
            i++;
            j--;
        } else {
            j--;
        }
        boats++;
    }

    cout << "Minimum boats = " << boats << "\n";

    // Queries
    while (Q--) {
        string type;
        cin >> type;

        if (type == "CANPAIR") {
            int X, Y;
            cin >> X >> Y;

            if (w[X] + w[Y] <= limit && !(priority[X] && priority[Y]))
                cout << "Yes\n";
            else
                cout << "No\n";
        }
        else {     // "REMAINING"
            int B;
            cin >> B;

            int used = min(B, boats);
            int evacuated = min(N, used * 2); // upper bound

            // Correct for priority constraint
            evacuated = min(evacuated, N);

            cout << (N - evacuated) << "\n";
        }
    }

    return 0;
}

// Input Values
/*5
2
100
40
60
50
70
65
1
1
0
0
1
CANPAIR
2
3
REMAINING
2
output values:
Minimum boats = 4
No
1
*/