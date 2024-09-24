#include <bits/stdc++.h>
#define each auto &
#define endl '\n'
#define all(v) v.begin(), v.end()
#define pb push_back
#define pf push_front
#define popb pop_back
#define popf pop_front
#define fi first
#define se second
using namespace std;

typedef long long ll;
typedef unsigned long long ull;
typedef long double ld;
typedef pair<ll, ll> pll;
typedef vector<ll> vll;
typedef vector<pll> vpll;
typedef vector<vector<ll>> vvll;
typedef vector<vector<pll>> vvpll;
typedef map<ll, ll> mll;
typedef set<ll> sll;

vll prefixFn(string s)
{
    ll n = s.size();
    vll pi(n);
    for (ll i{1}; i < n; i++)
    {
        ll j = pi[i - 1];
        while (j > 0 && s[i] != s[j])
            j = pi[j - 1];
        j += (s[i] == s[j]);
        pi[i] = j;
    }
    return pi;
}

vvll buildAuto(string s)
{
    vvll bigPi(s.size() + 1, vll(26));
    string t = s + "#" + s;
    ll n = t.size();
    vll pi = prefixFn(t);
 
    for (ll i = s.size() + 1, len = 0; i <= n; i++, len++)
    {
        for (ll c = 0; c < 26; c++)
        {
            char ch = c + 'a';
            ll j = pi[i - 1];
            while (j > 0 && ch != s[j])
                j = pi[j - 1];
            j += (ch == s[j]);
            bigPi[len][c] = j;
        }
    }
    return bigPi;
}

vector<ll> zFn(string s) 
{
    ll n = s.size();
    vector<ll> z(n);
    ll l{}, r{};
    for(ll i{1}; i < n; i++) 
    {
        if(i < r) 
            z[i] = min(r - i, z[i - l]);
        while(i + z[i] < n && s[z[i]] == s[i + z[i]]) 
            z[i]++;
        if(i + z[i] > r) 
            l = i, r = i + z[i];
    }
    return z;
}