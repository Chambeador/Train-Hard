//https://codeforces.com/contest/628/problem/D
#include<bits/stdc++.h>
#define int long long
using namespace std;

const int MOD = 1e9+7;
int m,d,n;
int memo[2005][2005][2];
string num;

int dp(int pos, int modN, int pref){
    if(pos == n) return modN == 0;
    int &a = memo[pos][modN][pref];
    if(a == -1){
        a = 0;
        int limit = pref? num[pos]-'0': 9;
        if(pos&1){
            //un 7
            int nPref = pref && (d == limit);
            if(limit >= d){
                a = (a + dp(pos+1, (modN*10+d)%m, nPref)) % MOD;
            }
        }else{
            int ini = pos==0? 1:0;
            for(int digit = ini; digit <= limit; digit++){
                if(digit == d) continue;
                int nPref = pref && digit == limit;
                a += dp(pos+1, (modN*10+digit)%m, nPref)%MOD;
                a %= MOD;
            }
        }
    }
    return a;
}

string resta(string s) {
    int i = s.size() - 1;
    while (i >= 0 && s[i] == '0') {
        s[i] = '9';
        i--;
    }
    if (i >= 0) s[i]--;
    int pos = 0;
    while (pos + 1 < s.size() && s[pos] == '0')
        pos++;
    return s.substr(pos);
}


int f(string x){
    num = x;
    
    n = num.size();
    memset(memo, -1, sizeof(memo));
    return dp(0,0,1);
}
void solve(){
    cin>>m>>d;
    string a,b; cin>>a>>b;
    int c = 1;
    int modu = 0;
    for(int i = 0; i < a.size(); i++){
        int digito1 = a[i]-'0';
        modu = (modu*10+digito1)%m;
        if(i&1){
            if(a[i]-'0' != d) c = 0;
        }else{
            if(a[i]-'0' == d) c = 0;
        }
    }
    if(modu != 0) c = 0;
    cout<<(f(b)-f(a)+c+MOD)%MOD<<endl;
}

signed main(){
    solve();
}