#include <bits/stdc++.h>
#define each auto &
#define endl '\n'
#define all(v) v.begin(), v.end()
#define pb push_back
#define pf push_front
#define popb pop_back
#define popf pop_front
using namespace std;

typedef long long ll;
typedef unsigned long long ull;
typedef long double ld;
typedef pair<ll, ll> pll;
typedef vector<ll> vll;
typedef vector<vll> vvll;

struct Sack
{
    ll n;
    vvll adj;
    vll val, sz, dep;
    Sack(vvll &adj, vll val, ll root = 1)
    : n(adj.size()), adj(adj), val(val)
    {
        sz.resize(n);
        dep.resize(n);
        dfsPP(root), dfs(root);
    }
    void process(ll u)
    {
        // processing queries here
    }
    void modify(ll u, ll p, ll largeCh, bool toAdd)
    {
        // adding / removing elements here
        for (auto v: adj[u])
            if (v != p && v != largeCh)
                modify(v, u, largeCh, toAdd);
    }
    void dfsPP(ll u, ll p = -1, ll d = 1)
    {
        sz[u]++, dep[u] = d;
        for (auto &v: adj[u])
            if (v != p)
                dfsPP(v, u, d + 1), sz[u] += sz[v];
    }
    void dfs(ll u, ll p = -1, bool large = 0)
    {
        ll maxSize = 0, largeCh = -1;
        for (auto &v: adj[u])
            if (v != p && sz[v] > maxSize)
                maxSize = sz[v], largeCh = v;
        for (auto v: adj[u])
            if (v != p && v != largeCh)
                dfs(v, u, 0);
        if (~largeCh)
            dfs(largeCh, u, 1);
        modify(u, p, largeCh, 1);
        process(u);
        if (!large)
            modify(u, p, -1, 0);
    }
};