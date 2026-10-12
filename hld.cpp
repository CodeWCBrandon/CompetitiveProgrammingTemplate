// Node Value Based HLD
struct HLD{
    vector<vector<ll>> adj;
    vector<ll> subtreeSize, depth, nodeID, topChain, parentNode;
    lazySegtree segTree;

    HLD(ll n)
    {
        adj.resize(n);
        depth.resize(n);
        nodeID.resize(n);
        topChain.resize(n);
        parentNode.assign(n, -1); 
        subtreeSize.assign(n, 1);
        segTree.init(n);

        for(int i = 0; i < n; ++i)
        {
            topChain[i] = i;
        }
    }

    void dfs(ll curr, ll parent)
    {
        for(auto next : adj[curr])
        {
            if(next == parent) continue;
            depth[next] = depth[curr] + 1;
            parentNode[next] = curr;
            dfs(next, curr);
            subtreeSize[curr] += subtreeSize[next];
        }
    }
    ll currentnodeID = 0;
    void nodeIDAssign(ll curr, ll parent)
    {
        nodeID[curr] = currentnodeID++; 
        ll heavyNode = -1;
        for(auto next : adj[curr])
        {
            if(next == parent) continue;

            if(heavyNode == -1 || subtreeSize[next] > subtreeSize[heavyNode])
            {
                heavyNode = next;
            }
        }

        if(heavyNode != -1)
        {
            topChain[heavyNode] = topChain[curr];
            nodeIDAssign(heavyNode, curr);
        }

        for(auto next : adj[curr])
        {
            if(next == parent || next == heavyNode) continue;
            nodeIDAssign(next, curr);
        }
    }

    void init()
    {
        dfs(0, -1);
        nodeIDAssign(0, -1);
    }

    void addEdge(ll u, ll v)
    {
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    void updateValue(ll node, ll val)
    {
        segTree.update(1, 0, segTree.N - 1, nodeID[node], nodeID[node], val);
    }

    void updatePathValue(ll u, ll v, ll val)
    {
        while(topChain[u] != topChain[v])
        {
            if(depth[topChain[u]] < depth[topChain[v]]) swap(u, v);
            segTree.update(1, 0, segTree.N - 1, nodeID[topChain[u]], nodeID[u], val);
            u = parentNode[topChain[u]];
        }
        if(depth[u] > depth[v]) swap(u, v);
        segTree.update(1, 0, segTree.N - 1, nodeID[u], nodeID[v], val);
    }

    void updateSubtreeValue(ll u, ll val)
    {
        segTree.update(1, 0, segTree.N - 1, nodeID[u], nodeID[u] + subtreeSize[u] - 1, val);
    }

    Node queryPath(ll u, ll v)
    {
        Node result = {0, (ll)-1e18, (ll)1e18};
        while(topChain[u] != topChain[v])
        {
            if(depth[topChain[u]] < depth[topChain[v]]) swap(u, v);
            result = segTree.combine(result, segTree.query(1, 0, segTree.N - 1, nodeID[topChain[u]], nodeID[u]));
            u = parentNode[topChain[u]];
        }
        if(depth[u] > depth[v]) swap(u, v);
        result = segTree.combine(result, segTree.query(1, 0, segTree.N - 1, nodeID[u], nodeID[v]));
        return result;
    }

    Node querySubtree(ll u)
    {
        return segTree.query(1, 0, segTree.N - 1, nodeID[u], nodeID[u] + subtreeSize[u] - 1);
    }
};
