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

template<class T, class F>
struct LCA
{
    vvll goUp;
    vector<vector<T>> fn;
    vll depth;
    ll n, lg;
    F merge;

    LCA(vector<vector<pair<ll, T>>> &adj, ll root = 1): n(adj.size()), lg(log2(n) + 1)
    {
        goUp.assign(n, vll(lg));
        fn.assign(n, vector<T>(lg));
        depth.assign(n, 0);
        dfs(adj, root);
    }
    void dfs(vector<vector<pair<ll, T>>> &adj, ll node, ll par = -1, ll dep = 0, T w = T())
    {
        depth[node] = dep;
        goUp[node][0] = par;
        fn[node][0] = w;
        for (ll i{1}; i < lg && (1 << i) <= dep; i++)
        {
            goUp[node][i] = goUp[goUp[node][i - 1]][i - 1];
            fn[node][i] = merge(fn[node][i - 1], fn[goUp[node][i - 1]][i - 1]);
        }

        for (each e: adj[node])
            if (e.first != par)
                dfs(adj, e.first, node, dep + 1, e.second);
    }
    ll getKthAnc(ll u, ll k)
    {
        for (ll i{lg - 1}; i >= 0 && k; i--)
            if ((1 << i) <= k)
                u = goUp[u][i], k -= (1 << i);
        return u;
    }
    ll query(ll u, ll v)
    {
        if (depth[u] < depth[v])
            swap(u, v);
        u = getKthAnc(u, depth[u] - depth[v]);
        if (u == v)
            return u;
        for (ll i{lg - 1}; i >= 0; i--)
            if (goUp[u][i] != goUp[v][i])
                u = goUp[u][i], v = goUp[v][i];
        return goUp[u][0];
    }
    ll distance(ll u, ll v)
    {
        ll d = depth[query(u, v)];
        return depth[u] + depth[v] - d * 2;
    }
    T getKthFn(ll u, ll k)
    {
        T cuVal = T();
        bool start = true;
        for (ll i{lg - 1}; i >= 0 && k; i--)
        {
            if ((1 << i) <= k)
            {
                cuVal = (start ? fn[u][i] : merge(cuVal, fn[u][i]));
                start = false;
                u = goUp[u][i], k -= (1 << i);
            }
        }
        return cuVal;
    }
    T getFn(ll u, ll v)
    {
        ll d = depth[query(u, v)];
        return merge(getKthFn(u, depth[u] - d), getKthFn(v, depth[v] - d));
    }
};

struct Seg
{
    ll minW, maxW;
    Seg(ll minW = 1e18, ll maxW = -1e18)
    : minW(minW), maxW(maxW){}
};

struct Merge
{
    Seg operator()(Seg a, Seg b)
    {
        return Seg{
            min(a.minW, b.minW),
            max(a.maxW, b.maxW),
        };
    }
};