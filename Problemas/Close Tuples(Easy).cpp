#include<bits/stdc++.h>
#define int long long
using namespace std;
const int MAXN = 100005;

const int MOD =  1e9 +7;
const int N = 200005;
int fact[N];
int invfact[N];
 
int binpow(int a, int b, int m) {
    int res = 1;
    while (b > 0) {
        if (b & 1) {
            res = (res * a) % m;
        }
        a = (a * a) % m;
        b >>= 1;
    }
    return res;
}
 
int inversoFermat(int a, int m){
    return binpow(a, m-2, m);
}
 
void procesar(){
     fact[0] = fact[1] = 1;
     invfact[0] = invfact[1] = inversoFermat(1, MOD);
     for(int i = 2; i < N; i++){
         fact[i] = i*fact[i-1]%MOD;
         invfact[i] = inversoFermat(fact[i], MOD);
     }
}
 
int nCk(int n, int k){
    if(k == n) return 1;
    if(k > n) return 0;
    int res = fact[n] * invfact[n-k] % MOD * invfact[k] % MOD;
    return res;
}

void solve(){
    int n; cin>>n;
    int m,k; cin>>m>>k;
    vector<int> a(n);
    for(auto &x: a) cin>>x;
    sort(a.begin(), a.end());
    int l = 0;
    int ans = 0;
    for(int i = m-1; i < n; i++){
        while(l < i and a[i]-a[l] > k){
            l++;
        }
        int tam = i-l;
        if(tam < m-1) continue;
        ans = (ans%MOD + nCk(tam, m-1)%MOD)%MOD;
        
    }
    cout<<ans<<endl;
}


signed main(){

    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    procesar();
    int t; cin>>t; while(t--)
    solve();
}