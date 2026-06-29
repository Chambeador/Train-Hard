#include<bits/stdc++.h>
#define int long long
#define mem(a, v) memset(a, v, sizeof(a))

using namespace std;

const int K = 26;

struct vertex{
    int go[K], pch,par,cost,link = -1, super = -1, leaf = 0;
    vertex(): link(0), super(0){
        mem(go, -1);
    }

    vertex(int ch, int from, int costo): pch(ch), par(from), cost(costo){
        mem(go, -1);
    }
};

vector<vertex> t(1);
int go(int node, int ch);
int suff(int node);
int superLink(int node);

void add(string &s, int costo){
    int node = 0;
    for(auto ch: s){
        ch -= 'a';
        if(t[node].go[ch] == -1){
            t[node].go[ch] = t.size();
            t.emplace_back(ch, node, costo);
        }
        node = t[node].go[ch];
    }
    t[node].leaf = 1;
}


//suffix link que hace?
//sufijo propio mas largo que existe en el trie como prefijo
int suff(int node){
    if(t[node].link == -1){
        if(t[node].par == 0){
            t[node].link = 0;
        }else{
            t[node].link = go(suff(t[node].par), t[node].pch);
        }
    }
    return t[node].link;
}


//gogogogo avanzar con una letra
//a que estado me muevo?
int go(int node, int ch){
    if(t[node].go[ch] == -1){
        if(node == 0) t[node].go[ch] = 0;
        else t[node].go[ch] = go(suff(node), ch);
    }
    return t[node].go[ch];
}

//desde este nodo cual es le siguiente ancetro
//suffix link que es terminal
int superLink(int node){
    if(t[node].super == -1){
        int next = suff(node);
        if(t[next].leaf) t[node].super = next;
        else t[node].super= superLink(next);
    }
    return t[node].super;
}


int l;
int ans = 0;
void dfs(int nodo, int prof){
    int x = nodo;
    for(int i = 0; i < 26; i++){
        nodo = go(nodo,i);
        dfs(nodo, prof+1);
        x = nodo;
    }

    int costo = 0;
    while(x){
        if(t[x].leaf){
            costo += t[x].cost;
        }
        x = superLink(x);
    }
    if(prof != 0){
        ans = max(ans, (l/prof)*costo);
    }
}
signed main(){
    //que tenemos que hacer una fuerza bruta
    //inteligente?

    int n; cin>>n>>l;
    vector<int> valores(n);
    for(auto &x: valores) cin>>x;
    for(int i = 0; i < n; i++){
        string s; cin>>s;
        add(s, valores[i]);
    } 
    dfs(0, 0);
    cout<<ans<<endl;
}