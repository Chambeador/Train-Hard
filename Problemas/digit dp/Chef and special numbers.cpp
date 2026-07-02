//https://www.codechef.com/problems/WORKCHEF
#include<bits/stdc++.h>
//optimizacion con padding a la izquierda y memorizar el k para el idAct
using namespace std;

const int MOD = 2520;
const int LEN = 19; 

int k, n;
int idAct = 0;
int lastK = -1;  
string num;


long long memo[LEN+1][MOD][(1 << 9)];
long long vis [LEN+1][MOD][(1 << 9)];

int divsCount[1 << 9][MOD]; 
void precalcDivs() {
    for (int mask = 0; mask < (1 << 9); mask++) {
        for (int mod = 0; mod < MOD; mod++) {
            int c = 0;
            for (int i = 0; i < 9; i++) {
                if ((mask & (1 << i)) && (mod % (i + 1) == 0)) c++;
            }
            divsCount[mask][mod] = c;
        }
    }
}

long long dp(int pos, int mod, int pref, int mask, int start) {
    if (pos == n) {
        if (start) {
            return (divsCount[mask][mod] >= k);
        }
        return 0;
    }
    if (!pref and vis[pos][mod][mask] == idAct) {
        return memo[pos][mod][mask];
    }

    long long ans = 0;
    int limit = pref ? num[pos] - '0' : 9;

    for (int d = 0; d <= limit; d++) {
        int nPref = pref && (d == limit);
        int nStart = start || (d != 0);
        int nMask = mask;
        if (d > 0) {
            nMask = mask | (1LL << (d - 1));
        }
        int nMod = nStart ? (mod * 10 + d) % MOD : 0;
        ans += dp(pos + 1, nMod, nPref, nMask, nStart);
    }

    if (!pref) {
        vis[pos][mod][mask] = idAct;
        memo[pos][mod][mask] = ans;
    }
    return ans;
}

long long f(long long x) {
    string s = to_string(x);
    num = string(LEN-s.size(), '0') + s; //padding a la izquierda
    n = LEN;
    return dp(0, 0, 1, 0, 0);
}

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    precalcDivs();
    int t; cin >> t;
    while (t--) {
        long long a, b; cin >> a >> b >> k;
        if(lastK != k){
            idAct++;
            lastK = k;
        }
        cout << f(b) - f(a - 1) << endl;
    }
}