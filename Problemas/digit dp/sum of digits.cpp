//https://www.spoj.com/problems/CPCRC1C/
//https://www.spoj.com/problems/PR003004/
#include<bits/stdc++.h>
#define int long long
using namespace std;

pair<int,int> memo[16][2];
int n;
string num;


pair<int, int> dp(int pos, int pref){
    if(pos == n) return {1, 0};
    auto &[cantidad, sumita] = memo[pos][pref];
    if(cantidad == -1){
        cantidad = 0;
        sumita = 0;
        int limit = pref? num[pos]-'0': 9;
        for(int d = 0; d <= limit; d++){
            int nPref = pref && (d == limit);
            auto [c, s] = dp(pos+1, nPref);
            cantidad += c;
            sumita +=  d*c + s;
        }
    } 
    return {cantidad, sumita};
}


int f(int x){
    if(x < 0) return 0; 
    num = to_string(x);
    n = num.size();
    for(int i = 0; i < 16; i++)
        for(int j = 0; j < 2; j++)
            memo[i][j] = {-1,-1};

    return dp(0,1).second;
}

// signed main(){
//     while(true){
//         int a,b; cin>>a>>b;
//         if(a == -1 && b == -1) break;
//         cout<<f(b)-f(a-1)<<endl;
//     }
// }

signed main(){
    int t; cin>>t; while(t--){
        int a,b; cin>>a>>b;
        cout<<f(b)-f(a-1)<<endl;
    }
}