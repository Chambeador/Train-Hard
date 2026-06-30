#include <bits/stdc++.h>
using namespace std;

#define int long long

void solve() {
    int n;
    cin >> n;

    vector<int> a(n), b(n);
    for (auto &x : a) cin >> x;
    for (auto &x : b) cin >> x;
    bool sePuede = 1;
    for(int i = n-1; i >= 0 ; i--){
        if(a[i] == b[i]){ 
            continue;
        }
        if(a[i] < b[i]){
            a[i] = b[i];
        }else{
            //a[i] > b[i]
            if(i == 0) sePuede = 0;
            else{
                int dif = a[i]-b[i];
                a[i] = b[i];
                a[i-1] += dif;
            }
        }
    }
    if(sePuede) cout<<"YES"<<endl;
    else cout<<"NO"<<endl;
}

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;
    while (t--) solve();
}