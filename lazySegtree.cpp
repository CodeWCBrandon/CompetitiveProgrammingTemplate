struct SegTreeNode{
    ll sum = 0;

    SegTreeNode(){};
};

struct LazySegTreeNode{
    ll val = 0;

    LazySegTreeNode(){};
};

struct LazySegTree{
    vector<SegTreeNode> segTree;
    vector<LazySegTreeNode> lazy;
    ll N;

    LazySegTree(ll n)
    {
        N = 2;
        while(N < n) N *= 2;
        segTree.resize(2 * N);
        lazy.resize(2 * N);
    }

    void push(ll currNode, ll leftNode, ll rightNode)
    {
        segTree[currNode].sum += (lazy[currNode].val * (rightNode - leftNode + 1));
        if(leftNode != rightNode)
        {
            lazy[currNode * 2].val += lazy[currNode].val;
            lazy[currNode * 2 + 1].val += lazy[currNode].val;
        }
        lazy[currNode].val = 0;
    }

    SegTreeNode combine(SegTreeNode first, SegTreeNode second)
    {
        SegTreeNode temp;
        temp.sum = first.sum + second.sum;
        return temp;
    }

    void build(vector<ll>& a)
    {
        for(int i = 0; i < a.size(); ++i)
        {
            segTree[N + i].sum = a[i];
        }

        for(int i = N - 1; i >= 1; --i)
        {
            segTree[i] = combine(segTree[i * 2], segTree[i * 2 + 1]); 
        }
    }

    SegTreeNode queryTemplate(ll currNode, ll leftNode, ll rightNode, ll leftQuery, ll rightQuery)
    {
        push(currNode, leftNode, rightNode);
        if(leftQuery > rightNode || rightQuery < leftNode) return SegTreeNode();
        if(leftQuery <= leftNode && rightNode <= rightQuery) return segTree[currNode];

        ll mid = (leftNode + rightNode) / 2;
        return combine(queryTemplate(currNode * 2, leftNode, mid, leftQuery, rightQuery),
                        queryTemplate(currNode * 2 + 1, mid + 1, rightNode, leftQuery, rightQuery));
    }

    void updateTemplate(ll currNode, ll leftNode, ll rightNode, ll leftQuery, ll rightQuery, ll val)
    {
        push(currNode, leftNode, rightNode);
        if(leftQuery > rightNode || rightQuery < leftNode) return;
        if(leftQuery <= leftNode && rightNode <= rightQuery)
        {
            lazy[currNode].val += val;
            push(currNode, leftNode, rightNode);
            return;
        }

        ll mid = (leftNode + rightNode) / 2;
        updateTemplate(currNode * 2, leftNode, mid, leftQuery, rightQuery, val);
        updateTemplate(currNode * 2 + 1, mid + 1, rightNode, leftQuery, rightQuery, val);
        segTree[currNode] = combine(segTree[currNode * 2], segTree[currNode * 2 + 1]);
    }

    SegTreeNode query(ll leftQuery, ll rightQuery) {return queryTemplate(1, 0, N - 1, leftQuery, rightQuery);}
    void update(ll leftQuery, ll rightQuery, ll val) {return updateTemplate(1, 0, N - 1, leftQuery, rightQuery, val);}

};
