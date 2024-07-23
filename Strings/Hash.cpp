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


struct Hash
{
    // all one based
    ll n, MOD;
    vll hash, revHash, pows;
    Hash() = default;
    Hash(string s, ll p = 31, ll MOD = 1e9 + 7, char dil = 'a'): n(s.size()), MOD(MOD)
    {
        string rev = s;
        reverse(all(rev));
        hash = revHash = pows = vll(n + 1);
        pows[0] = 1;
        for (ll i{1}; i <= n; i++)
            pows[i] = (pows[i - 1] * p) % MOD;
        for (ll i{}; i < n; i++)
            hash[i + 1] = (hash[i] + ((s[i] - dil + 1) * pows[i]) % MOD) % MOD;
        for (ll i{}; i < n; i++)
            revHash[i + 1] = (revHash[i] + ((rev[i] - dil + 1) * pows[i]) % MOD) % MOD;
    }
    ll comp()
    {
        return hash[n];
    }
    ll operator[](ll i)
    {
        return hash[i];
    }
    ll jumpWithPow(ll h, ll r)
    {
        return h * pows[n - r] % MOD;
    }
    ll range(ll a, ll b)
    {
        if (a > b)
            return 0;
        return jumpWithPow((hash[b] - hash[a - 1] + MOD) % MOD, b);
    }
    ll revRange(ll a, ll b)
    {
        if (a > b)
            return 0;
        return jumpWithPow((revHash[b] - revHash[a - 1] + MOD) % MOD, b);
    }
    bool isPal(ll a, ll b)
    {
        ll x = n - b + 1, y = n - a + 1;
        return range(a, b) == revRange(x, y);
    }
};

struct DoubleHash
{
    ll p1, p2, mod1, mod2;
    Hash h1, h2;
    DoubleHash() = default;
    DoubleHash(string s, ll p1 = 53, ll p2 = 61, ll mod1 = 1e9 + 9, ll mod2 = 998244353)
    : p1(p1), p2(p2), mod1(mod1), mod2(mod2)
    {
        h1 = Hash(s, p1, mod1);
        h2 = Hash(s, p2, mod2);
    }
    pll comp()
    {
        return {h1.comp(), h2.comp()};
    }
    pll operator[](ll i)
    {
        return {h1[i], h2[i]};
    }
    pll range(ll a, ll b)
    {
        return {h1.range(a, b), h2.range(a, b)};
    }
    bool isPal(ll a, ll b)
    {
        return h1.isPal(a, b) && h2.isPal(a, b);
    }
};