//https://www.hackerearth.com/problem/algorithm/sallu-bhai-and-ias-8838ac8d/


//BUENA PLANTILLA PARA DP DIGIT
#include<bits/stdc++.h>
#define int long long
using namespace std;

const int MOD = 2520;

//[pos][mod][start][mask]
int memo[15][MOD][2][1024];
int vis[15][MOD][2][1024];
int id = 0;

int tabla[10];
string num;
int n;


int dp(int pos, int sumMod, int pref, int start, int mask) {
    if (pos == n){
        if (!start) return 0;
        for (int d = 1; d <= 9; d++) {
            if(mask&(1LL<<d)){
                if(sumMod%d!=0)return 0;
            }
        }
        return 1;
    }

    if(!pref && vis[pos][sumMod][start][mask] == id) {
        return memo[pos][sumMod][start][mask];
    }

    int ans = 0;
    int limit = pref ? num[pos]-'0' : 9;
    for (int d = 0; d <= limit; d++){
        int nPref = pref && (d == limit);
        int nStart = start || (d != 0);
        int nSum = nStart ? (sumMod + (d == 0?0:tabla[d]))%MOD:0;
        int nMask = (nStart && d != 0) ? (mask|(1 << d)):mask;
        ans += dp(pos + 1, nSum, nPref, nStart, nMask);
    }

    if (!pref){
        vis[pos][sumMod][start][mask] = id;
        memo[pos][sumMod][start][mask] = ans;
    }
    return ans;
}

long long f(long long x) {
    if (x <= 0) return 0;
    num = to_string(x);
    n = num.size();
    id++; 
    return dp(0, 0, 1, 0, 0);
}

void solve() {
    int a, b; cin>>a>>b;
    cout<<f(b)-f(a-1)<<endl;
}


signed main(){
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    tabla[0] = 0;
    for (int i = 1; i <= 9; i++) {
        tabla[i] = 1;
        for (int j = 1; j <= i; j++) tabla[i] *= i;
    }
    int t; cin>>t; while(t--) solve();
}
