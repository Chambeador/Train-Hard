//https://vjudge.net/problem/LightOJ-1068
#include <bits/stdc++.h>
#define int long long
using namespace std;


int memo[11][91][91][2][2];
string num;
int n,k;


int dp(int pos, int numM, int sumM, int act, int start){
    if(pos == n){
        return start && numM == 0 and sumM == 0;
    }

    int &a = memo[pos][numM][sumM][act][start];
    if(a == -1){
        a = 0;
        int limit = act? num[pos]-'0': 9;
        for(int d = 0; d <= limit; d++){
            int nAct = act && (d == limit);
            int nStart =  start || d != 0;
            a += dp(pos+1, (numM*10+d)%k, (sumM+d)%k, nAct, nStart);
        }
    }
    return a;
}


int f(int x){
    if(x <= 0) return 0;
    if(k > 90) return 0;

    num = to_string(x);
    n = num.size();
    memset(memo,-1,sizeof(memo));

    return dp(0,0,0,1,0);
}

int c = 1;
void solve(){
    int a,b; cin>>a>>b>>k;
    cout<<"Case "<<c++<<": "<<f(b)-f(a-1)<<endl;
}
signed main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    int t; cin>>t; while(t--){
        solve();
    }
}