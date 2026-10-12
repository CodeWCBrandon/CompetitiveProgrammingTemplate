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

struct PST{
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
    
    void updateTemplate(ll idx, ll val)
    {
        ll curr = N + idx;
        segTree.push_back(new PSTNode(val));
        swap(segTree[curr], segTree.back());

        while(curr != 1)
        {
            ll parent = curr / 2;
            
            segTree.push_back(new PSTNode(0));
            if(curr % 2 == 0)
            {
                segTree.back()->left = segTree[curr];
                segTree.back()->right = segTree[parent]->right; 
            }else
            {
                segTree.back()->right = segTree[curr];
                segTree.back()->left = segTree[parent]->left; 
            }
            curr = parent;
            swap(segTree[parent], segTree.back());

            *segTree[curr] = combine(segTree[curr * 2], segTree[curr * 2 + 1]);
        }
        timeline.push_back(segTree[1]);
    }

    PSTNode query(ll leftQuery, ll rightQuery, ll time) {return queryTemplate(timeline[time], 0, N - 1, leftQuery, rightQuery);}
    void update(ll idx, ll val) {updateTemplate(idx, val);}
};
