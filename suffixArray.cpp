#include "bits/stdc++.h"
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

#define ll long long
#define mod 1000000007
#define mod2 998244353
using namespace std;

// random 
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
template<class T> T rand_int(T mn, T mx) { return uniform_int_distribution<T>(mn, mx)(rng);}

// pb_ds stuff
using namespace __gnu_pbds;
const int RANDOM = chrono::high_resolution_clock::now().time_since_epoch().count();
struct chash {
    static uint64_t splitmix64(uint64_t x) {
        x += 0x9e3779b97f4a7c15;
        x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
        x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
        return x ^ (x >> 31);
    }

    size_t operator()(uint64_t x) const {
        static const uint64_t FIXED_RANDOM = std::chrono::steady_clock::now().time_since_epoch().count();
        return splitmix64(x + FIXED_RANDOM);
    }
};

template<class T> using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;
template<class K, class V> using gpmap = gp_hash_table<K, V, chash>;

struct SuffixArray{
    vector<ll> arr;
    ll sz;

    SuffixArray(string s)
    {
        s += '$';
        this->sz = s.size();
        vector<ll> c(sz);
        arr.resize(sz);

        vector<pair<ll, ll>> initial(sz);
        for(int i = 0; i < sz; ++i)
        {
            initial[i] = {s[i], i};
        }
        sort(initial.begin(), initial.end());
        c[initial[0].second] = 0;
        for(int i = 1; i < sz; ++i)
        {
            if(initial[i].first == initial[i - 1].first) 
            {
                c[initial[i].second] = c[initial[i - 1].second];
            }else{
                c[initial[i].second] = c[initial[i - 1].second] + 1;
            }
        }

        ll k = 1;
        while(k < sz)
        {
            vector<pair<pair<ll, ll>, ll>> followUp(sz);
            for(int i = 0; i < sz; ++i)
            {
                followUp[i] = {{c[i], c[(i + k) % sz]}, i}; 
            }
            sort(followUp.begin(), followUp.end());
            c[followUp[0].second] = 0;
            for(int i = 1; i < sz; ++i)
            {
                if(followUp[i].first == followUp[i - 1].first)
                {
                    c[followUp[i].second] = c[followUp[i - 1].second];
                }else{
                    c[followUp[i].second] = c[followUp[i - 1].second] + 1;
                }
            }
            k <<= 1;
            if(c[followUp.back().second] == sz - 1 || k >= sz)
            {
                for(int i = 0; i < sz; ++i) arr[i] = followUp[i].second;
                break;
            }
        }
    }
};

void solve()
{
    
}

int main(void)
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);

    int t;
    cin >> t;
    while(t--)
    {
        solve();
    }
}
