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

const ll INF = 1e18;

vll bfs(vvll &adj, vll start)
{
    ll n = adj.size();
    deque<ll> dq;
    vll dist(n, INF);
    for (auto &e: start)
        dist[e] = 0, dq.pb(e);
    while (!dq.empty())
    {
        ll u = dq.front();
        dq.popf();

        for (auto &v: adj[u])
            if (dist[v] > dist[u] + 1)
                dist[v] = dist[u] + 1, dq.pb(v);
    }
    return dist;
}

vll dijkstra(vvpll &adj, vll start)
{
    ll n = adj.size();
    priority_queue<pll> pq;
    vll dist(n, INF);
    for (auto &e: start)
        dist[e] = 0, pq.push({0, e});
    while (!pq.empty())
    {
        ll d, u;
        tie(d, u) = pq.top();
        pq.pop();
        if (-d != dist[u])
            continue;
        for (auto &[v, w]: adj[u])
            if (dist[v] > dist[u] + w)
                dist[v] = dist[u] + w, pq.push({-dist[v], v});
    }
    return dist;
}

struct Edge
{
    ll u, v, w;
};

vll bellmanFord(vector<Edge> &edges, ll n, ll start)
{
    vll d(n + 1, INF);
    d[start] = 0;
    for (ll i{}; i < n - 1; i++)
        for (auto &e: edges)
            if (d[e.v] > d[e.u] + e.w)
                d[e.v] = d[e.u] + e.w;

    for (ll i{}; i < n - 1; i++)
        for (auto &e: edges)
            if (d[e.v] > d[e.u] + e.w)
                d[e.v] = -INF;
    return d;
}

vvll floydWarshall(vvpll &adj)
{
    ll n = adj.size();
    vvll d(n, vll(n, INF));
    for (ll u{}; u < n; u++)
        d[u][u] = 0;

    for (ll u{}; u < n; u++)
        for (auto [v, c]: adj[u])
            d[u][v] = min(d[u][v], c);
    
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