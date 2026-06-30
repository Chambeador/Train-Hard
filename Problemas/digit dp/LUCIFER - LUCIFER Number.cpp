//https://www.spoj.com/problems/LUCIFER/
#include<bits/stdc++.h>
#define int long long
using namespace std;

//idea del offset GAAA
string num;
int n;
int memo[11][100][2][2];

const int offset = 45;
int prime[46];

int dp(int pos, int sum, int pref, int start){  
    if(pos == n){
        return sum > 44 and prime[sum-offset] and start;
    }
    int &a = memo[pos][sum][pref][start];
    if(a == -1){
        a = 0;
        int limit = pref? num[pos]-'0': 9;
        for(int d = 0; d <= limit; d++){
            int nPref = pref && (d == limit);
            int nStart = start || (d != 0);
            int nSum = sum;
            if(nStart){
                int nPos = n - pos;
                if(nPos&1){
                    nSum -= d;
                }else{
                    nSum += d;
                }
            }
            a += dp(pos+1, nSum, nPref, nStart);
        }
    }
    return a;
}

//en el peor de los casos son 8 digitos 
//4 impares entonces 4*9 [-36,  36] -> [0 72] sum == 1 == sum == 37
//empiezo en 36 entonces


int f(int x){   
    if(x < 0) return 0;
    num = to_string(x);
    n = num.size();
    memset(memo, -1, sizeof memo);
    return dp(0, 45, 1, 0);

}
void solve(){
    int a,b; cin>>a>>b;
    cout<<f(b)-f(a-1)<<endl;
}

signed main(){
    prime[0] = prime[1] = 0;
    for(int i = 2; i <= 45; i++){
        prime[i] = 1;
        for(int j = 2; j*j <= i; j++){
            if(i % j == 0){
                prime[i] = 0;
                break;
            }
        }
    }
    int t; cin>>t; 
    while(t--){
        solve();
    }
}