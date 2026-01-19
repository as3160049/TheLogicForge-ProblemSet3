#include<bits/stdc++.h>
using namespace std;

void processNetwork(
    int N,
    int Q,
    int K,
    const vector<vector<string>>& ops
) {
    // subscriptions[u][v] = is u subscribed to v?
    vector<unordered_set<int>> subscriptions(N + 1);

    // messages sent by each unit (store last K only)
    struct Msg {
        int id;
        int time;
        bool critical;
    };
    vector<deque<Msg>> sent(N + 1);

    int currentTime = 0;
    int msgID = 0;

    for (const auto& op : ops) {
        currentTime++;

        if (op[0] == "B") {
            int u = stoi(op[1]);
            int m = stoi(op[2]);

            msgID++;
            bool critical = (m % 3 == 0);

            sent[u].push_back({msgID, currentTime, critical});
            if ((int)sent[u].size() > K)
                sent[u].pop_front();
        }

        else if (op[0] == "S") {
            int u = stoi(op[1]);
            int v = stoi(op[2]);
            subscriptions[u].insert(v);
        }

        else if (op[0] == "U") {
            int u = stoi(op[1]);
            int v = stoi(op[2]);
            subscriptions[u].erase(v);
        }

        else { // "F"
            int u = stoi(op[1]);

            vector<Msg> visible;

            // own messages
            for (auto& m : sent[u])
                visible.push_back(m);

            // subscribed units' messages
            for (int v : subscriptions[u]) {
                for (auto& m : sent[v])
                    visible.push_back(m);
            }

            if (visible.empty()) {
                cout << "EMPTY\n";
                continue;
            }

            // sort by:
            // 1) time desc
            // 2) critical first
            sort(visible.begin(), visible.end(), [](const Msg& a, const Msg& b) {
                if (a.time != b.time) return a.time > b.time;
                return a.critical > b.critical;
            });

            int limit = min(10, (int)visible.size());
            for (int i = 0; i < limit; i++) {
                cout << visible[i].id;
                if (i + 1 < limit) cout << " ";
            }
            cout << "\n";
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, Q, K;
    cin >> N >> Q >> K;

    vector<vector<string>> operations(Q);
    for (int i = 0; i < Q; i++) {
        string op;
        cin >> op;
        if (op == "B") {
            string u, m;
            cin >> u >> m;
            operations[i] = {op, u, m};
        } else if (op == "S" || op == "U") {
            string u, v;
            cin >> u >> v;
            operations[i] = {op, u, v};
        } else { // "F"
            string u;
            cin >> u;
            operations[i] = {op, u};
        }
    }

    processNetwork(N, Q, K, operations);

    return 0;
}

/*
input values:
3
9
2
S
1
2
S
1
3
B
2
5
B
3
9
F
1
U
1
2
B
3
6
F
1
F
2
*/
