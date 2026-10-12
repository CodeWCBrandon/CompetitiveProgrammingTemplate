struct DSU{
    vector<ll> parent;
    ll n;

    DSU(ll n)
    {
        this->n = n;

        parent.resize(n + 5);
    }

    void build()
    {
        for(int i = 0; i < parent.size(); ++i)
        {
            parent[i] = i;
        }
    }

    ll findRoot(ll u)
    {
        if(parent[u] == u) return u;
        else return parent[u] = findRoot(parent[u]);
    }

    bool combine(ll u, ll v)
    {
        ll ru = findRoot(u);
        ll rv = findRoot(v);
        if(ru == rv) return false;

        parent[ru] = parent[rv];
        return true;
    }
};
