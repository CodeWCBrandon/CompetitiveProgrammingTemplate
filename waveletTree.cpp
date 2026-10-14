struct Wavelet{
    
    struct Node{
        vector<ll> arr;
        vector<ll> pref;
        Node* left = NULL;
        Node* right = NULL;

        Node(){}
    };

    vector<Node*> tree;
    const ll maxA = 1e9;

    Wavelet(vector<ll>& a)
    {
        tree.push_back(new Node());
        tree[0]->arr = a;
    }

    Node* newNode()
    {
        tree.push_back(new Node());
        return tree.back();
    }

    void buildTemplate(Node* currNode, ll leftNode, ll rightNode)
    {
        if(leftNode == rightNode) return;
        ll mid = (leftNode + rightNode) / 2;
        currNode->pref.resize(currNode->arr.size());
          
        bool sendLeft = false;
        bool sendRight = false;
        ll currSum = 0;
        for(int i = 0; i < currNode->arr.size(); ++i)
        {
            if(currNode->arr[i] > mid)
            {
                currSum++;
                sendRight = true;
            }else{
                sendLeft = true;
            }

            currNode->pref[i] = currSum;
        }

        Node* left = (sendLeft) ? newNode() : NULL;
        Node* right = (sendRight) ? newNode() : NULL;
        currNode->left = left;
        currNode->right = right;
        for(int i = 0; i < currNode->arr.size(); ++i)
        {
            if(currNode->arr[i] <= mid) left->arr.push_back(currNode->arr[i]); 
            else right->arr.push_back(currNode->arr[i]);
        }

        if(sendLeft) buildTemplate(currNode->left, leftNode, mid);
        if(sendRight) buildTemplate(currNode->right, mid + 1, rightNode);
    }

    ll numberOfOccurenceTemplate(Node* currNode, ll leftNode, ll rightNode, ll endPoint, ll leftVal, ll rightVal)
    {
        if(leftVal > rightNode || rightVal < leftNode || endPoint == -1 || currNode == NULL) return 0;
        if(leftVal <= leftNode && rightNode <= rightVal)
        {
            return endPoint + 1;
        }

        ll mid = (leftNode + rightNode) / 2;
        ll countRight = currNode->pref[endPoint];
        ll countLeft = endPoint - countRight;

        return numberOfOccurenceTemplate(currNode->left, leftNode, mid, countLeft, leftVal, rightVal) + 
                numberOfOccurenceTemplate(currNode->right, mid + 1, rightNode, countRight - 1, leftVal, rightVal);
    }

    ll kthSmallestElement(Node* currNode, ll leftNode, ll rightNode, ll l, ll r, ll k)
    {
        if(leftNode == rightNode) return leftNode;
        ll mid = (leftNode + rightNode) / 2;
        ll countRightL = (l == 0) ? 0 : currNode->pref[l - 1];
        ll countRightR = currNode->pref[r];
        ll countLeft = (r - l + 1) - (countRightR - countRightL);
        if(k <= countLeft)
        {
            return kthSmallestElement(currNode->left, leftNode, mid, l - countRightL, r - countRightR, k);
        }
        return kthSmallestElement(currNode->right, mid + 1, rightNode, countRightL, countRightR - 1, k - countLeft);
    }


    void build() {buildTemplate(tree[0], 0, maxA);}
    ll numberOfOccurence(ll l, ll r, ll lowBound, ll upBound)
    {
        return numberOfOccurenceTemplate(tree[0], 0, maxA, r, lowBound, upBound) -
                numberOfOccurenceTemplate(tree[0], 0, maxA, l - 1, lowBound, upBound);
    }
    ll kthSmallestElement(ll l, ll r, ll k) {return kthSmallestElement(tree[0], 0, maxA, l, r, k);}
};
