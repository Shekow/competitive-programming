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
typedef vector<string> vs;
typedef vector<vs> vvs;
typedef vector<vvs> vvvs;
typedef set<ll> sll;
typedef set<sll> ssll;
typedef set<pll> spll;
typedef set<spll> sspll;
typedef set<string> ss;
typedef set<ss> sss;
typedef map<ll, ll> mll;

vll treeCenters(vvll &adj)
{
    deque<ll> leaves;
    ll n = adj.size();
    vll degree(n);
    for (ll u{}; u < n; u++)
        if ((degree[u] = adj[u].size()) < 2)
            leaves.pb(u);
    ll count = leaves.size();
    while (count < n)
    {
        ll sz = leaves.size();
        for (ll i{}; i < sz; i++)
        {
            ll u = leaves.front();
            leaves.popf();
            for (each v: adj[u])
                if (--degree[v] == 1)
                    leaves.pb(v), count++;
        }
    }
    return vll(all(leaves));
}

string encodeTree(vvll &adj, ll u, ll p = 0)
{
    vector<string> children;
    string cu{'('};
    for (each v: adj[u])
        if (v != p)
            children.pb(encodeTree(adj, v, u));
    sort(all(children));
    for (each e: children)
        cu.append(e);
    cu.pb(')');
    return cu;
}

ll encodeTreeHash(vvll &adj, ll u, ll p = 0, ll dep = 53, ll MOD = 1e9 + 7)
{
    ll hash{1};
    for (each v: adj[u])
        if (v != p)
            hash *= encodeTreeHash(adj, v, u, dep * 53 % MOD), hash %= MOD;

    return (hash + 1) * dep % MOD;
}