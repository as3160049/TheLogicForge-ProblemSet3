#include<bits/stdc++.h>
using namespace std;



vector<string> processTemperatureAlerts(
    int N, int K,
    vector<int>& temp,
    vector<vector<string>>& queries
) {
    vector<int> nextWarmer(N, -1), nextColder(N, -1);
    stack<int> st;

    // Next K-Warmer
    for (int i = N - 1; i >= 0; i--) {
        while (!st.empty() && temp[st.top()] < temp[i] + K)
            st.pop();
        if (!st.empty())
            nextWarmer[i] = st.top();
        st.push(i);
    }

    while (!st.empty()) st.pop();

    // Next K-Colder
    for (int i = N - 1; i >= 0; i--) {
        while (!st.empty() && temp[st.top()] > temp[i] - K)
            st.pop();
        if (!st.empty())
            nextColder[i] = st.top();
        st.push(i);
    }

    // Final Alert Day
    vector<int> alert(N, 0);
    for (int i = 0; i < N; i++) {
        if (nextWarmer[i] == -1 && nextColder[i] == -1)
            alert[i] = 0;
        else if (nextWarmer[i] == -1)
            alert[i] = nextColder[i];
        else if (nextColder[i] == -1)
            alert[i] = nextWarmer[i];
        else
            alert[i] = min(nextWarmer[i], nextColder[i]);
    }

    // Prefix Sum 
    vector<int> pref(N, 0);
    pref[0] = (alert[0] != 0);
    for (int i = 1; i < N; i++)
        pref[i] = pref[i - 1] + (alert[i] != 0);

    // Answer Queries
    vector<string> result;
    for (auto& q : queries) {
        if (q[0] == "NEXT") {
            int X = stoi(q[1]);
            if (alert[X] == 0)
                result.push_back("No Alert");
            else
                result.push_back(to_string(alert[X]));
        } else {
            int L = stoi(q[1]);
            int R = stoi(q[2]);
            int count = pref[R] - (L > 0 ? pref[L - 1] : 0);
            result.push_back(to_string(count));
        }
    }

    return result;
}

int main() {
    int n = 8, k = 5, q = 3;
    vector<int> temp = {30, 25, 20, 28, 35, 22, 18, 40};
    vector<vector<string>> queries = {
        {"NEXT", "2"},
        {"COUNT", "0", "7"},
        {"NEXT", "5"}
    };
    vector<string> results = processTemperatureAlerts(n, k, temp, queries);
    for (const auto& res : results) {
        cout << res << endl;
    }
    return 0;
}
