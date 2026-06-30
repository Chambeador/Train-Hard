#include<bits/stdc++.h>
#define int long long
using namespace std;

//dif de c3-c6
//dif de c3-c9
int memo[51][34][34][2][2][2];
string num;
const int MOD = 1e9+7;
int n;
int dp(int pos, int c36, int c39,int pref, int start, int h3){
    //cuantos me faltan====?? es igual  a n-pos
    if(c36 < 0 or c39 < 0 or c36 > 33 or c39 > 33) return 0;

    if(pos == n){
        return start and c36 == 17 and c39 == 17 and h3;
    }

    int &a = memo[pos][c36][c39][pref][start][h3];
    if(a == -1){
        a = 0;
        int limit = pref? num[pos]-'0': 9;
        for(int d = 0; d <= limit; d++){
            int nPref = pref && (d == limit);
            int nStart  = start || (d != 0);
            int nC36 = c36;
            int nC39 = c39;
            int nh3 = h3;
            if(nStart){
                if(d == 3) {
                    nC36++;
                    nC39++;
                    nh3 = 1;
                }
                if(d == 6) nC36--;
                if(d == 9) nC39--;
            }
            a += dp(pos+1, nC36, nC39, nPref, nStart, nh3)%MOD;
            a %=MOD;
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
    return dp(0,17,17,1,0,0);
}
void solve(){
    string a,b; cin>>a>>b;
    cout<<(f(b)-f(resta(a))+MOD)%MOD<<endl;
}   

signed main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int t; cin>>t; while(t--)
    solve();
}