#include <bits/stdc++.h>
using namespace std;

using ll = long long;

struct DSU {
    vector<int> p, sz;

    DSU(int n = 0) { init(n); }

    void init(int n) {
        p.resize(n + 1);
        sz.assign(n + 1, 1);
        iota(p.begin(), p.end(), 0);
    }

    int find(int x) {
        if (p[x] == x) return x;
        return p[x] = find(p[x]);
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, M;
    cin >> N >> M;

    vector<ll> D(N + 1);
    for (int i = 1; i <= N; i++) cin >> D[i];

    vector<vector<int>> g(N + 1);
    for (int i = 0; i < M; i++) {
        int u, v;
        cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }

    vector<int> ord(N);
    iota(ord.begin(), ord.end(), 1);
    sort(ord.begin(), ord.end(), [&](int a, int b) {
        if (D[a] != D[b]) return D[a] < D[b];
        return a < b;
    });

    int maxNodes = 2 * N + 5;
    vector<int> L(maxNodes, 0), R(maxNodes, 0);
    vector<ll> W(maxNodes, 0);

    DSU dsu(N);
    vector<int> rep(N + 1);
    vector<char> active(N + 1, 0);

    for (int i = 1; i <= N; i++) rep[i] = i;

    int tot = N;

    for (int u : ord) {
        active[u] = 1;

        for (int v : g[u]) {
            if (!active[v]) continue;

            int a = dsu.find(u);
            int b = dsu.find(v);

            if (a == b) continue;

            if (dsu.sz[a] < dsu.sz[b]) swap(a, b);

            int p = ++tot;
            W[p] = D[u];
            L[p] = rep[a];
            R[p] = rep[b];

            dsu.p[b] = a;
            dsu.sz[a] += dsu.sz[b];
            rep[a] = p;
        }
    }

    int root = rep[dsu.find(1)];

    vector<int> sz(tot + 1, 0);
    vector<int> order;
    order.reserve(tot);

    stack<int> st;
    st.push(root);

    while (!st.empty()) {
        int x = st.top();
        st.pop();
        order.push_back(x);

        if (x > N) {
            st.push(L[x]);
            st.push(R[x]);
        }
    }

    for (int i = (int)order.size() - 1; i >= 0; i--) {
        int x = order[i];
        if (x <= N) sz[x] = 1;
        else sz[x] = sz[L[x]] + sz[R[x]];
    }

    vector<ll> down(tot + 1, 0), ans(N + 1, 0);

    stack<int> st2;
    st2.push(root);

    while (!st2.empty()) {
        int x = st2.top();
        st2.pop();

        if (x <= N) continue;

        int l = L[x], r = R[x];

        down[l] = down[x] + 1LL * sz[r] * W[x];
        down[r] = down[x] + 1LL * sz[l] * W[x];

        st2.push(l);
        st2.push(r);
    }

    for (int i = 1; i <= N; i++) {
        ans[i] = down[i] + D[i]; // f(i,i) = D[i]
    }

    for (int i = 1; i <= N; i++) {
        cout << ans[i] << (i == N ? '\n' : ' ');
    }

    return 0;
}