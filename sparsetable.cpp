struct sparseTable{
    struct SparseTableNode{
        ll mx;
        ll mn;
    };
    vector<vector<SparseTableNode>> a;
    ll n, p;

    sparseTable(ll n, ll p)
    {
        this->n = n;
        this->p = p;

        a.assign(n + 5, vector<SparseTableNode>(p, {(ll)-1e18, (ll)1e18}));
    }

    SparseTableNode combine(SparseTableNode first, SparseTableNode second)
    {
        SparseTableNode res;
        res.mx = max(first.mx, second.mx);
        res.mn = min(first.mn, second.mn);

        return res;
    }

    void build(vector<ll>& arr)
    {
        for(int i = 0; i < n; ++i)
        {
            a[i][0] = {arr[i], arr[i]};
        }

        for(int k = 1; k < p; ++k)
        {
            for(int i = 0; i + (1LL << (k - 1)) <= n; ++i)
            {
                a[i][k] = combine(a[i][k - 1], a[i + (1LL << (k - 1))][k - 1]); 
            }
        }
    }

    SparseTableNode query(ll l, ll r)
    {
        if(r < l) swap(l, r);
        ll len = (r - l + 1);
        ll pw = __builtin_clzll(1LL) - __builtin_clzll(len);
        return combine(a[l][pw], a[r - (1LL << pw) + 1][pw]);
    }
};
