struct LCA{
    struct Node{
        ll parent;
    };
    vector<vector<Node>> binaryLift;
    vector<ll> depth;
    ll n, pw;

    LCA(ll n, ll pw)
    {
        this->n = n;
        this->pw = pw;

        binaryLift.assign(n + 5, vector<Node>(pw, {-1LL}));
        depth.assign(n + 5, 0);
    }

    void build(vector<vector<ll>>& adj, ll root)
    {
        queue<ll> q;
        q.push(root);

        while(!q.empty())
        {
            ll curr = q.front(); q.pop();

            for(auto next : adj[curr])
            {
                if(binaryLift[next][0].parent != -1 || next == root) continue;
                depth[next] = depth[curr] + 1;
                binaryLift[next][0].parent = curr;
                q.push(next);
            }
        }

        for(int k = 1; k < pw; ++k)
        {
            for(int i = 0; i < n; ++i)
            {
                if(binaryLift[i][k - 1].parent == -1LL) continue;
                binaryLift[i][k].parent = binaryLift[binaryLift[i][k - 1].parent][k - 1].parent;
            }
        }
    }

    ll getLCA(ll u, ll v)
    {
        if(depth[u] < depth[v]) swap(u, v); 
        ll diff = depth[u] - depth[v];

        for(int i = 0; i < pw; ++i)
        {
            if((diff >> i) & 1)
            {
                u = binaryLift[u][i].parent;
            }
        }

        if(u == v) return u;

        for(int i = pw - 1; i >= 0; --i)
        {
            ll pu = binaryLift[u][i].parent;
            ll pv = binaryLift[v][i].parent;
            if(pu == pv) continue;
            u = pu;
            v = pv;
        }

        return binaryLift[u][0].parent;
    }

    ll getDistance(ll u, ll v)
    {
        return depth[u] + depth[v] - (2 * depth[getLCA(u, v)]);
    }
};
