//https://www.spoj.com/problems/SANVI/
#include<bits/stdc++.h>
using namespace std;

const int MOD = 1e9 + 7;

struct MixedRadix {
    vector<int> bases;
    vector<int> pesos;
    int max_mask;
    MixedRadix(){}
    
    void init (vector<int> & cBases){
        bases = cBases;
        int n = bases.size();
        pesos.resize(n);
        pesos[0] = 1;
        for(int i = 1; i < n; i++){
            pesos[i] = pesos[i-1]*bases[i-1];
        }
        max_mask = pesos[n-1]*bases[n-1];
    }

    int get(int mask, int pos){
        if(pesos[pos] == 0 or bases[pos] == 0) return 0;
        return (mask/pesos[pos])%bases[pos];
    }

    int set(int mask, int pos, int nVal) {
    if (nVal >= bases[pos]) nVal = bases[pos]-1;
    int actV = (mask/pesos[pos])%bases[pos];
    return mask-(actV*pesos[pos])+(nVal*pesos[pos]);
}
};

MixedRadix baseM;

string num;
int k, m, n;

int mask_v[82945];
int mask_diff[82945];


int memo[19][82945][2];
int vis [19][82945][2];
int idAct = 0;

bool prime(int d) {
    return (d == 2 || d == 3 || d == 5 || d == 7);
}


void preC(){
    vector<int> b = {1,4,3,3,4,3,4,3,4,4};
    baseM.init(b);
    for(int m = 0; m < 82944; m++){
        int v = 0;
        int dif = 0;
        for(int d = 1; d <= 9; d++){
            int c = baseM.get(m, d);
            if(!prime(d)){
                //puede violar la regla
                if(c == 3) v++;
                dif += min(c, 2);
            }else{
                dif -= c;
            }
        }
        mask_v[m] = v;
        mask_diff[m] = abs(dif);

    }
    
}

int dp(int pos, int pref, int start, int mask){
    if(mask < 0 or mask >= 82944) return 0;
    if(pos == n){
        return start && mask_diff[mask] <= k;
    }

    if(!pref && vis[pos][mask][start] == idAct){
        return memo[pos][mask][start];
    }
    int ans = 0;
    int limit = pref? num[pos]-'0':9;
    for(int d = 0; d <= limit; d++){
        int nPref = pref && ( d == limit);
        int nStart = start or (d != 0);
        if(nStart and d ==  0) continue;
        if(!nStart and d == 0){
            ans = (ans+dp(pos+1, nPref, nStart, mask))%MOD;
        }else{
            int canti = baseM.get(mask, d);
            if(prime(d) && canti == 2) continue;
            int nMask = mask;
            if(prime(d)){
                //primo
                nMask = baseM.set(mask, d, canti+1);
            }else{
                //no es primo
                canti = min(canti+1, 3);
                nMask = baseM.set(mask, d, canti);

            }
            if(nMask < 0 or nMask >= 82944) continue;
            if(mask_v[nMask] > m) continue;
            ans = (ans+dp(pos+1, nPref, nStart, nMask))%MOD;
        }
    }

    if(!pref){
        vis [pos][mask][start] = idAct;
        memo[pos][mask][start] = ans;
    }
    return ans;
}


signed main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    preC();
    while(cin>>num>>k>>m){
        n = num.size();
        idAct++;
        cout<<dp(0,1,0,0)<<endl;
    }
}
