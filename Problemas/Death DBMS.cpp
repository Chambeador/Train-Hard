#include<bits/stdc++.h>
//#define int long long
#define mem(a, v) memset(a, v, sizeof(a))

using namespace std;


//pq no son sus ojos
const int K = 26;

struct vertex{
    int go[K], pch,par,link = -1, super = -1, leaf = 0;
    multiset<int> valores;
    vertex(): link(0), super(0){
        mem(go, -1);
    }

    vertex(int ch, int from): pch(ch), par(from){
        mem(go, -1);
    }
};


vector<int> peso;
vector<vertex> t(1);
int go(int node, int ch);
int suff(int node);
int superLink(int node);

//index de patron y numero de nodo
map<int, int> mapita;
void add(string &s, int index){
    int node = 0;
    for(auto ch: s){
        ch -= 'a';
        if(t[node].go[ch] == -1){
            t[node].go[ch] = t.size();
            t.emplace_back(ch, node);
        }
        node = t[node].go[ch];
    }
    t[node].valores.insert(0);
    mapita[index] = node;
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


signed main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int n,q; cin>>n>>q;
    for(int i = 0; i < n; i++){
        string s; cin>>s;
        add(s, i);
    }
    //nos vamos moviendo por nodos terminales del arbol
    vector<int> valAct(n, 0);
    while(q--){
        int tipo; cin>>tipo;
        if(tipo == 1){
            int u,k; cin>>u>>k; u--;
            int nodito = mapita[u];
            int valorAnt = valAct[u];
            auto it = t[nodito].valores.find(valorAnt);
            t[nodito].valores.erase(it);
            t[nodito].valores.insert(k);
            valAct[u] = k; 
        }else{
            int ans = -1;
            string s; cin>>s;
            int nodo = 0;
            for(auto &ch: s){
                nodo = go(nodo, ch-'a');
                int x = nodo;
                while(x){
                    if(t[x].leaf){
                        ans = max(ans, *t[x].valores.rbegin());
                    }
                    x = superLink(x);
                }
            }
            cout<<ans<<"\n";
        }
    }
}