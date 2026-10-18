struct PST{
    struct PSTNode{
        ll sum = 0;
        PSTNode* left = NULL;
        PSTNode* right = NULL;

        PSTNode(){};
        PSTNode(ll val)
        {
            this->sum = val;
        }
    };
    vector<PSTNode*> timeline;
    vector<PSTNode*> segTree;
    ll N;

    PST(ll n)
    {
        N = 2;
        while(N < n) N *= 2;
        segTree.resize(2 * N);
        for(auto &node : segTree) node = new PSTNode();

        for(int i = N - 1; i >= 1; --i)
        {
            segTree[i]->left = segTree[2 * i];
            segTree[i]->right = segTree[2 * i + 1];
        }
        timeline.push_back(segTree[1]);
    }

    void build(vector<ll>& a)
    {
        for(int i = 0; i < a.size(); ++i)
        {
            segTree[N + i]->sum = a[i];
        }

        for(int i = N - 1; i >= 1; --i)
        {
            *segTree[i] = combine(segTree[2 * i], segTree[2 * i + 1]);
        }
    }

    PSTNode combine(PSTNode* first, PSTNode* second)
    {
        PSTNode temp;
        temp.sum = first->sum + second->sum;
        temp.left = first;
        temp.right = second;
        return temp;
    }

    PSTNode combineQuery(PSTNode first, PSTNode second)
    {
        PSTNode temp;
        temp.sum = first.sum + second.sum;
        return temp;
    }

    PSTNode queryTemplate(PSTNode* currNode, ll leftNode, ll rightNode, ll leftQuery, ll rightQuery)
    {
        if(leftQuery > rightNode || rightQuery < leftNode) return PSTNode();
        if(leftQuery <= leftNode && rightNode <= rightQuery) return *currNode;

        ll mid = (leftNode + rightNode) / 2;
        return combineQuery(queryTemplate(currNode->left, leftNode, mid, leftQuery, rightQuery),
                        queryTemplate(currNode->right, mid + 1, rightNode, leftQuery, rightQuery));
    }
    
    PSTNode* updateTemplate(PSTNode* currNode, ll leftNode, ll rightNode, ll idx, ll val)
    {
        ll mid = (leftNode + rightNode) / 2;

        ll dir = -1;
        if(leftNode <= idx && idx <= mid) dir = 0;
        if(mid + 1 <= idx && idx <= rightNode) dir = 1;
        
        PSTNode* newNode = new PSTNode();
        if(leftNode == rightNode)
        {
            newNode->sum = val;
        }else 
        {
            if(dir == 0) *newNode = combine(updateTemplate(currNode->left, leftNode, mid, idx, val), currNode->right);
            else *newNode = combine(currNode->left, updateTemplate(currNode->right, mid + 1, rightNode, idx, val));
        }

        return newNode;
    }

    PSTNode query(ll leftQuery, ll rightQuery, ll time) {return queryTemplate(timeline[time], 0, N - 1, leftQuery, rightQuery);}
    void update(ll idx, ll val, ll time) {timeline.push_back(updateTemplate(timeline[time], 0, N - 1, idx, val));}
};
