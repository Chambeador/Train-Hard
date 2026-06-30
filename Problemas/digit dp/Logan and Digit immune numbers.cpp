//https://www.codechef.com/problems/DIGIMU

#include <bits/stdc++.h>
#define int long long
using namespace std;

const int MOD = 315; 

int memo[20][MOD][2][2][2][2][2][2];

string num;
int n;
vector<int> digitos = {0,3,5,7,9};

int dp(int pos, int mod, int pref, int start, int h3, int h5, int h7, int h9) {
    if (pos == n) {
        if (start) {
            if (h3 && (mod % 3 == 0)) return 0;
            if (h5 && (mod % 5 == 0)) return 0;
            if (h7 && (mod % 7 == 0)) return 0;
            if (h9 && (mod % 9 == 0)) return 0;
            return 1;
        }
        return 0;
    }

    int &a = memo[pos][mod][pref][start][h3][h5][h7][h9];
    if(a == -1){
        a = 0;
        int limit = pref? num[pos]-'0':9;
        int ans = 0;
        for(auto d: digitos){
            if(d > limit) continue;
            int nPref = pref && (d == limit);
            int nStart = start || (d != 0);
            if(d == 0 and nStart) continue;
            int nh3 = h3 || (d == 3);
            int nh5 = h5 || (d == 5);
            int nh7 = h7 || (d == 7);
            int nh9 = h9 || (d == 9);
            int nMod = nStart? (mod*10+d)%MOD: 0;
            a += dp(pos+1, nMod, nPref, nStart, nh3, nh5, nh7, nh9);
        }
    }
    return a;
}

int f(int x) {
    if (x <= 0) return 0;
    num = to_string(x);
    n = num.size();
    memset(memo, -1, sizeof memo);
    return dp(0, 0, 1, 0, 0, 0, 0, 0);
}


void solve(){
    int a,b,k; cin>>a>>b>>k;
    int izq = f(a-1);
    int der = f(b);
    if(der-izq < k){
        cout<<-1<<endl;
        return;
    }
    int buscado = izq+k;
    int l = a, r = b;
    int ans = 0;
    while(l <= r){
        int m = l + (r-l)/2;
        if(f(m) >= buscado){
            ans = m;
            r = m-1;
        }else l = m+1;

    }
    cout<<ans<<endl;
}


signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    int t; cin>>t;
     while(t--)
    solve();
}