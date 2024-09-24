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

struct TarjanSCC
{
    ll n, start;
    vvll adj;
    vll st, onSt, id, low;
    ll count, idCount;
    TarjanSCC(vvll &adj, ll start = 1)
    : adj(adj), n(adj.size()), start(start)
    {
        onSt.assign(n, 0);
        low.assign(n, 0);
        id.assign(n, -1);
        count = idCount = 0;
        for (ll i{start}; i < n; i++)
            if (id[i] == -1)
                dfs(i);
        sll st(low.begin() + start, low.end());
        mll mp;
        for (auto &e: st)
            mp[e] = mp.size();
        for (auto &e: low)
            e = mp[e];
    }
    void dfs(ll u)
    {
        st.pb(u);
        onSt[u] = 1;
        low[u] = id[u] = idCount++;
        for (auto &v: adj[u])
        {
            if (id[v] == -1)
                dfs(v);
            if (onSt[v])
                low[u] = min(low[u], low[v]);
        }
        if (low[u] == id[u])
        {
            while (1)
            {
                ll v = st.back();
                low[v] = id[u];
                onSt[v] = 0;
                st.popb();
                if (v == u)
                    break;
            }
            count++;
        }
    }
    vvll getSccs()
    {
        vvll sccs(count);
        for (ll i{start}; i < n; i++)
            sccs[low[i]].pb(i);
        return sccs;
    }
    vvll getCondGraph()
    {
        vvll adjCond(count);
        for (ll u{start}; u < n; u++)
            for (auto &v: adj[u])
                if (low[u] != low[v])
                    adjCond[low[u]].pb(low[v]);
        return adjCond;
    }
};


struct ArtPoints
{
    vvll adj;
    vll vis, low, tin, points, cut;
    ll n, tmr;
    ArtPoints(vvll &adj): adj(adj), n(adj.size())
    {
        vis.resize(n), low.resize(n);
        tin.resize(n), cut.resize(n);
        tmr = 0;
        for (ll i{}; i < n; i++)
        {
            if (!vis[i])
                dfs(i, -1);
            if (cut[i])
                points.pb(i);
        } 
    }
    void dfs(ll u, ll p)
    {
        vis[u] = 1, low[u] = tin[u] = tmr++;
        ll children = 0;
        for (auto &v: adj[u])
        {
            if (!vis[v])
            {
                dfs(v, u);
                low[u] = min(low[u], low[v]);
                if (~p && low[v] >= tin[u])
                    cut[u] = 1;
                children++;
            }
            else if (v != p)
                low[u] = min(low[u], tin[v]);
        }
        if (p == -1 && children > 1)
            cut[u] = 1;
    }
};

struct Bridges
{
    vvpll adj;
    vll vis, low, tin, cut, bridges;
    ll n, m, tmr;
    Bridges(vvpll &adj, ll m): adj(adj), n(adj.size()), m(m)
    {
        vis.resize(n), low.resize(n);
        tin.resize(n), cut.resize(m);
        tmr = 0;
        for (ll i{}; i < n; i++)
            if (!vis[i])
                dfs(i, -1);

        for (ll i{}; i < m; i++)
            if (cut[i])
                bridges.pb(i);
    }
    void dfs(ll u, ll p)
    {
        vis[u] = 1, low[u] = tin[u] = tmr++;
        bool skipped = false;
        for (auto &[v, i]: adj[u])
        {
            if (!vis[v])
            {
                dfs(v, u);
                low[u] = min(low[u], low[v]);
                if (low[v] > tin[u])
                    cut[i] = 1;
            }
            else if (v == p && !skipped)
                skipped = true;
            else
                low[u] = min(low[u], tin[v]);
        }
    }
    vpll getBridges()
    {
        vpll res;
        for (ll u{}; u < n; u++)
            for (auto &[v, i]: adj[u])
                if (v > u && cut[i])
                    res.pb({u, v});
        return res;
    }
    ll dfsTrav(vll &cur, ll u)
    {
        vis[u] = 1, cur.pb(u);
        ll cnt = 1;
        for  (auto &[v, i]: adj[u])
            if (!vis[v] && !cut[i])
                cnt += dfsTrav(cur, v);
        return cnt;
    }
    // one based
    pair<vvll, vll> genTree()
    {
        fill(all(vis), 0);
        vll comp(n), sz;
        for (ll i{}; i < n; i++)
        {
            if (vis[i])
                continue;
            vll cur;
            sz.pb(dfsTrav(cur, i));
            for (auto &e: cur)
                comp[e] = sz.size() - 1;
        }
        vvll tAdj(sz.size());
        for (auto [a, b]: getBridges())
            a = comp[a], b = comp[b], tAdj[a].pb(b), tAdj[b].pb(a);
        return {tAdj, sz};
    }
};