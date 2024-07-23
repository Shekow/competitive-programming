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

struct BiPGraph
{
    vll p, r, dis;
    ll sz;
    BiPGraph(ll n): sz(n)
    {
        p = r = dis = vll(sz + 1);
        for (ll i{1}; i <= sz; i++)
            p[i] = i;
    }
    pll get(ll a)
    {
        if (a != p[a])
        {
            pll val = get(p[a]);
            p[a] = val.first, dis[a] += val.second, dis[a] %= 2;
        }
        return {p[a], dis[a]};
    }
    bool unite(ll a, ll b)
    {
        pll valA = get(a), valB = get(b);
        if (valA.first == valB.first)
            return dis[a] != dis[b];
        if (r[valA.first] == r[valA.first]) 
            r[valA.first]++;
        else if (r[valA.first] < r[valA.first]) 
            swap(a, b);
        p[valB.first] = valA.first;
        dis[valB.first] = valB.second + valA.second + 1, dis[valB.first] %= 2;
        return true;
    }
};