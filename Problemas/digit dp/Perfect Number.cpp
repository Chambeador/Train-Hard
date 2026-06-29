//https://codeforces.com/contest/919/problem/B
#include<bits/stdc++.h>
#define int long long
using namespace std;

string num;
int memo[20][11][2][2];
int n;
int dp(int pos, int sum, int pref, int start){
    if(sum > 10) return 0;
    if(pos == n) return start and sum == 10;

    int &a = memo[pos][sum][pref][start];
    if(a == -1){
        a = 0;
        int limit = pref? num[pos]-'0': 9;
        for(int d = 0; d <= limit; d++){
            int nPref = pref and (d == limit);
            int nStart = start or (d != 0);
            int nSum = nStart? sum +d: 0;
            a += dp(pos+1, nSum, nPref, nStart);
        }
    }
    return a;
}


int f(int x){
    num = to_string(x);
    n = num.size();
    memset(memo, -1, sizeof memo);
    return dp(0,0,1,0);
}
signed main(){
    int k; cin>>k;
    int l = 1;
    int r = 1e18;
    int ans = 1;
    while(l <= r){
        int m = l + (r-l)/2;
        if(f(m) >= k){
            ans = m;
            r = m-1;
        }else l = m+1;
    }
    cout<<ans<<endl;
}