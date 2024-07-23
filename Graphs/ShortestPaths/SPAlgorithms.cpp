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

const ll N = 2e5 + 1, MX = 1e1, MOD = 1e9 + 7, INF = 1e18;

vll bfs(vvll &adj, vll start)
{
    ll n = adj.size();
    deque<ll> dq;
    vll dist(n, INF);
    for (each e: start)
        dist[e] = 0, dq.pb(e);
    while (!dq.empty())
    {
        ll u = dq.front();
        dq.popf();

        for (each v: adj[u])
            if (dist[v] > dist[u] + 1)
                dist[v] = dist[u] + 1, dq.pb(v);
    }
}

vll dijkstra(vvpll &adj, vll start)
{
    ll n = adj.size();
    priority_queue<pll> pq;
    vll dist(n, INF);
    for (each e: start)
        dist[e] = 0, pq.push({0, e});
    while (!pq.empty())
    {
        ll d, u;
        tie(d, u) = pq.top();
        pq.pop();
        if (-d != dist[u])
            continue;
        for (each v: adj[u])
            if (dist[v.first] > dist[u] + v.second)
                dist[v.first] = dist[u] + v.second, pq.push({-dist[v.first], v.first});
    }
    return dist;
}

vvll floyedWarshall(vvpll &adj)
{
    ll n = adj.size();
    vvll d(n, vll(n, INF));
    for (ll u{}; u < n; u++)
        d[u][u] = 0;

    for (ll u{}; u < n; u++)
        for (each v: adj[u])
            d[u][v.first] = min(d[u][v.first], v.second);
    
    for (ll k{}; k < n; k++)
        for (ll i{}; i < n; i++)
            for (ll j{}; j < n; j++)
                if (d[i][j] > d[i][k] + d[k][j])
                    d[i][j] = d[i][k] + d[k][j];

    for (ll k{}; k < n; k++)
        for (ll i{}; i < n; i++)
            for (ll j{}; j < n; j++)
                if (d[i][j] > d[i][k] + d[k][j])
                    d[i][j] = -INF;
    return d;
}