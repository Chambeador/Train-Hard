#include<bits/stdc++.h>
#define int long long
using namespace std;
const int MOD = 1e9+7;

int dp[100];

long long f(int n){
    if(n == 0) return 1;
    if(n == 1) return 0;

    if(dp[n] != -1) return dp[n];

    return dp[n] = (n - 1) * (f(n - 1) + f(n - 2));
}


signed main(){
    memset(dp, -1, sizeof(dp));
    int n; cin >> n;

    int fact = 1;
    for (int i = 1; i <= n; i++)
        fact *= i;

    int ans = 0;
    int cur = fact;
    for (int i = 0; i <= n; i++) {
        ans += (i % 2 == 0 ? cur : -cur);
        if (i != n)
            cur /= (i + 1);
    }

    cout << ans << '\n';

    cout<<f(9)<<endl;
}
