//https://vjudge.net/problem/LightOJ-1205
#include<bits/stdc++.h>
#define int long long
using namespace std;

string num;
int memo[20][20][2][2][2];

int dp(int pos, int bPos, int pref, int start, int big){
    if(pos > bPos){
        if(pref && big) return 0;
        return 1;
    }
    int &a = memo[pos][bPos][pref][start][big];
    if(a == -1){
        a = 0;
        int limit = pref ? (num[pos]-'0') : 9;
        for(int d=0; d<=limit; d++){
            int nPref = pref && (d == (num[pos]-'0'));
            int nStart = start || (d != 0);
            if(!start && d == 0){
                a += dp(pos+1,bPos,nPref,nStart,big);
            }else if(pos == bPos){
                a += dp(pos+1,bPos,nPref,nStart,big);
            }else{
                int bDigit = num[bPos]-'0';
                if(d==bDigit){
                    a += dp(pos+1,bPos-1,nPref,nStart,big);
                }else{
                    a += dp(pos+1,bPos-1,nPref,nStart,d>bDigit);
                }
            }
        }
    }
    return a;
}

int f(int x){
    if(x<0) return 0;
    num=to_string(x);
    memset(memo,-1,sizeof(memo));
    return dp(0,num.size()-1,1,0,0);
}

int c=1;

void solve(){

    int a,b;
    cin>>a>>b;

    int i=min(a,b);
    int j=max(a,b);

    cout<<"Case "<<c++<<": "<<f(j)-f(i-1)<<"\n";
}

signed main(){

    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin>>t;

    while(t--)
        solve();
}