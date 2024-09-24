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
typedef vector<vvll> vvvll;
typedef vector<pll> vpll;
typedef vector<vpll> vvpll;
typedef vector<vvpll> vvvpll;

vll getEulerPath(vector<multiset<ll>> adj)
{
    ll n = adj.size(), m = 0, odd = 0, start = 1;
    for (ll i{}; i < n; m += adj[i++].size())
        if (adj[i].size() % 2)
            odd++, start = i;
    if (odd != 0 && odd != 2)
        return vll();
    m /= 2;
    vll sol;
    function<void(ll)> dfs = [&](ll u){
        while (!adj[u].empty())
        {
            ll v = *adj[u].begin();
            adj[u].erase(adj[u].find(v));
            adj[v].erase(adj[v].find(u));
            dfs(v);
        }
        sol.pb(u);
    };
    dfs(start);
    if (sol.size() != m + 1)
        return vll();
    return sol;
}

vll getEulerPathDi(vvll adj)
{
    ll n = adj.size(), m{}, start{-1}, end{-1};
    vll in(n), out(n);
    for (ll i{}; i < n; m += adj[i++].size())
    {
        out[i] = adj[i].size();
        for (auto &j: adj[i])
            in[j]++;
    }
    bool ok = 1;
    for (ll i{}; i < n; i++)
    {
        if (out[i] - in[i] == 1)
        {
            if (~start)
                ok = 0;
            else
                start = i;
        }
        else if (in[i] - out[i] == 1)
        {
            if (~end)
                ok = 0;
            else
                end = i;
        }
        else if (in[i] != out[i])
            ok = 0;
    }
    if (!ok)
        return vll();
    if (!~start)
        start = 1;
    vll sol;
    function<void(ll)> dfs = [&](ll u){
        while (out[u])
            dfs(adj[u][--out[u]]);
        sol.pb(u);
    };
    dfs(start);
    reverse(all(sol));
    if (sol.size() != m + 1)
        return vll();
    return sol;
}