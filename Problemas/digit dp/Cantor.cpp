//https://www.spoj.com/problems/TAP2012C/en/
#include<bits/stdc++.h>
#define int long long 
//con toda la sal, y sin la arena del mundo?
using namespace std;
vector<int> use;


string num;
int n;
int memo [100][2][2];
int dp(int pos, int pref, int start, int base){
    if(pos == n) return start;
    int &a = memo[pos][pref][start];
    if(a == -1){
        a = 0;
        int limit = pref? num[pos]-'0': (base-1);
        for(int d = 0; d <= limit; d++){
            if(!start and d == 0){
                int nPref = pref && (d == num[pos]-'0');
                int nStart = start || (d != 0);
                a += dp(pos+1, nPref, nStart, base);
            }else{
                if(use[d]){
                    int nPref = pref && (d == num[pos]-'0');
                    int nStart = start || (d != 0);
                    a += dp(pos+1, nPref, nStart, base); 
                }   
            }
        }
    }
    return a;
}


string convertir(int n, int base){
    if(n == 0) return "0";
    string s;
    while(n){
        s += char('0'+(n%base));
        n /= base;
    }
    reverse(s.begin(), s.end());
    return s;
}

int f(int x, int base){
    if(x <= 0) return 0;
    num = convertir(x, base);
    n = num.size();
    memset(memo, -1, sizeof memo);
    return dp(0,1,0, base);
}

void solve(int a, int b, int base, string &cad){
    use.assign(base, 0);
    for(int i = 0; i < base; i++){
        if(cad[i] == 'S') use[i] = 1;
    }
    cout<<f(b, base)-f(a-1, base)<<endl;
}


signed main(){
    //cout << convertir(10,3) << endl;
    while(1){
        int a,b,base; cin>>a>>b>>base;
        string cadena; cin>>cadena;
        if(a == b and a == base and a == -1 and cadena == "*") break;
        else solve(a,b,base,cadena);
    }
}