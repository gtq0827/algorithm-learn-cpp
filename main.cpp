#include <iostream>
#include <map>
#include <set>
#include <unordered_set>
#include <vector>
#include <stack>
#include <queue>
#include <algorithm>
#include <cmath>
#include <numeric>

using namespace std;

struct TreeNode {
    int val;                // 节点存储的值
    TreeNode *left;         // 左孩子指针，指向左子节点
    TreeNode *right;        // 右孩子指针，指向右子节点
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}

};

class Solution {


public:
    const string letterMap[10] = {
        "", // 0
        "", // 1
        "abc", // 2
        "def", // 3
        "ghi", // 4
        "jkl", // 5
        "mno", // 6
        "pqrs", // 7
        "tuv", // 8
        "wxyz", // 9
    };
    vector<string> res;
    string path;
    void letterCombination_backtracking(string digits,int index) {
        if (path.size()==digits.size()) {
            res.push_back(path);
            return ;
        }
        string letters=letterMap[digits[index]-'0'];
        for (int i=0;i<letters.size();i++) {
            path.push_back(letters[i]);
            letterCombination_backtracking(digits,index+1);
            path.pop_back();
        }
    }

    vector<string> letterCombinations(string digits) {
        letterCombination_backtracking(digits,0);
        return res;
    }
    /*vector<vector<int>> res;
    vector<int> path;

    void combinationSum3_backtracking(int k, int n,int startindex) {
        if ( path.size()==k) {
            if (accumulate(path.begin(), path.end(), 0)==n) {
                res.push_back(path);
                return;
            }else {
                return;
            }
        }

        for (int i=startindex;i<=9-k+path.size()+1;i++) {
            path.push_back(i);
            combinationSum3_backtracking(k,n,i+1);
            path.pop_back();
        }
    }
    vector<vector<int>> combinationSum3(int k, int n) {
        combinationSum3_backtracking(k,n,1);
        return res;
    }


    void combine_backtracking(int n,int k,int startindex) {
        if (path.size()==k) {
            res.push_back(path);
            return ;
        }
        for (int i=startindex;i<n;i++) {
            path.push_back(i);
            combine_backtracking(n,k,i+1);
            path.pop_back();
        }
    }
    //回溯算法
    vector<vector<int>> combine(int n, int k) {
        combine_backtracking(n,k,0);
        return res;
    }*/
    //反中序遍历
    int sum=0;
    void convert_BST(TreeNode* root){
        if (root== nullptr) return ;
        convertBST(root->right);
        sum+=root->val;
        root->val=sum;
        convertBST(root->left);
    }
    TreeNode* convertBST(TreeNode* root) {
        convert_BST(root);
        return root;

    }


    TreeNode* sortedArrayToBST(vector<int>& nums) {
        if (nums.empty()) return nullptr;
        TreeNode* root=new TreeNode(nums[nums.size()/2]);
        vector<int> left(nums.begin(),nums.begin()+nums.size()/2);
        vector<int> right(nums.begin()+nums.size()/2+1,nums.end());
        root->left= sortedArrayToBST(left);
        root->right= sortedArrayToBST(right);
        return root;
    }
    TreeNode* trimBST(TreeNode* root, int low, int high) {
        if (root== nullptr) return nullptr;
        if (root->val<low) return trimBST(root->right,low,high);
        if (root->val>high) return trimBST(root->left,low,high);
        root->left=trimBST(root->right,low,high);
        root->right=trimBST(root->left,low,high);
        return root;
    }

    TreeNode* deleteNode(TreeNode* root, int key) {
        if (root== nullptr) return nullptr;
        if (root->val==key){
            TreeNode* left = root->left;
            TreeNode* right = root->right;
            delete(root);
            if (left== nullptr&&right== nullptr) return nullptr;
            if (left&&!right) return left;
            if (!left&&right) return right;
            if (left&&right) {
                TreeNode* cur=right;
                while (cur->left!= nullptr){
                    cur =cur->left;
                }
                cur->left=left;
                return right;
            }
        }
        root->left= deleteNode(root->left,key);
        root->right= deleteNode(root->right,key);
        return root;
    }

    TreeNode* insertIntoBST(TreeNode* root, int val) {
        if (root== nullptr) {
            TreeNode* node =new TreeNode(val);
            return node ;
        }
        if (val>root->val) root->right= insertIntoBST(root->right,val);
        if (val<root->val) root->left= insertIntoBST(root->left,val);
        return root;
    }
    //二叉搜索树
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        if (root== nullptr) return nullptr;
        if (root->val>q->val &&root->val>p->val) return lowestCommonAncestor(root->left,p,q);
        else if (root->val<q->val&&root->val<p->val) return lowestCommonAncestor(root->right,p,q);
        else return root;
    }
    /*TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        if(root== nullptr) return nullptr;
        if(root==p||root==q) return root;
        TreeNode* left= lowestCommonAncestor(root->left,p,q);
        TreeNode* right= lowestCommonAncestor(root->right,p,q);
        if (left!= nullptr&&right!= nullptr) return root;
        if (left== nullptr&&right!= nullptr) return right;
        if (left!= nullptr&&right== nullptr) return left;
        return nullptr;
    }*/
    void findmode(TreeNode* root, vector<int>& res, int& maxCount, int& curVal, int& curCount){
        if (root== nullptr) return;
        findmode(root->left,res,maxCount,curVal,curCount);
        if (root->val==curVal) curCount++;
        else curVal=root->val,curCount=0;
        if (curCount==maxCount) res.push_back(root->val);
        else if (curCount> maxCount){
            maxCount=curCount;
            res.clear();
            res.push_back(root->val);
        }
        findmode(root->right,res,maxCount,curVal,curCount);
    }

    vector<int> findMode(TreeNode* root) {
        vector<int> res;
        int maxCount=-1,curVal=-1,curCount=0;
        findmode(root,res,maxCount,curVal,curCount);
        return res;
    }
    TreeNode*pre= nullptr;
    int result=INT_MAX;
    void travsalMin(TreeNode* root){
        if (root== nullptr) return ;
        travsalMin(root->left);
        if (pre) result = min(result, abs(root->val - pre->val));
        pre=root;
        travsalMin(root->right);
    }

    int getMinimumDifference(TreeNode* root) {
        travsalMin(root);
        return result;
    }
    bool isValidBST(TreeNode* root) {
        return check(root,LLONG_MIN,LLONG_MAX);
    }
    bool check(TreeNode* root,long long low,long long high){
        if (root== nullptr) return true;
        if (root->val<low|| root->val>high) return false;
        return check(root->left,low,root->val)&& check(root->right,root->val,high);
    }
    TreeNode* searchBST(TreeNode* root, int val) {
        if (root==nullptr)return nullptr;
        if (root->val==val) return root;
        else if(root->val>val) return searchBST(root->left,val);
        else {
            return searchBST(root->right,val);
        }
    }
    TreeNode* mergeTrees(TreeNode* root1, TreeNode* root2) {
        if (root1== nullptr) return root2;
        if (root2== nullptr) return root1;
        TreeNode* node=new TreeNode(root1->val + root2->val);
        node->left= mergeTrees(root1->left,root2->left);
        node->right= mergeTrees(root1->right,root2->right);
        return node;

    }
    TreeNode* constructMaximumBinaryTree(vector<int>& nums) {
        if (nums.empty()) return nullptr;
        int max=-1,maxIndex=0;
        for(int i=0;i<nums.size();i++){
            if (nums[i]>max) max=nums[i],maxIndex=i;
        }
        TreeNode* node=new TreeNode(max);
        vector<int> leftTree(nums.begin(),nums.begin()+maxIndex);
        vector<int> rightTree(nums.begin()+maxIndex+1,nums.end());
        node->left= constructMaximumBinaryTree(leftTree);
        node->right= constructMaximumBinaryTree(rightTree);
        return node;
    }

    TreeNode* buildTree(vector<int>& inorder, vector<int>& postorder) {
        if (inorder.empty()) return nullptr;
        int val=postorder.back();
        TreeNode* node;
        node->val=val;
        //寻找切割点
        int divide;
        for (divide=0;divide<inorder.size();divide++){
            if (inorder[divide]==val) break;
        }
        //获得左右子树的数组
        vector<int> rightInoder(inorder.begin()+divide+1,inorder.end());
        vector<int> leftInorder(inorder.begin(),inorder.begin()+divide);
        vector<int> leftPost(postorder.begin(),postorder.begin()+leftInorder.size());
        vector<int> rightPost(postorder.begin()+leftInorder.size(),postorder.end()-1);
        node->left= buildTree(leftInorder, leftPost);
        node->right= buildTree(rightInoder,rightPost);
        return node;
    }


    bool pathTravsal(TreeNode* root,int pathSum,int targetsum){
        if (root== nullptr) return false;
        if (root->left== nullptr&&root->right== nullptr) if (pathSum+root->val==targetsum) return true;
        return pathTravsal(root->left,pathSum+root->val,targetsum)|| pathTravsal(root->right,pathSum+root->val,targetsum);
    }

    bool hasPathSum(TreeNode* root, int targetSum) {
        return pathTravsal(root,0,targetSum);
    }
    int maxDepth=INT_MIN;
    int result;
    void travasal(TreeNode* root,int depth){
        if (root->left== nullptr&&root->right== nullptr){
            if (depth>maxDepth) {
                maxDepth=depth;
                result=root->val;
            }
            return;
        }
        if (root->left) travasal(root->left,depth+1);
        if (root->right) travasal(root->right,depth+1);

    }
    int findBottomLeftValue(TreeNode* root) {
        travasal(root,1);
        return result;

    }


    int sumOfLeftLeaves(TreeNode* root) {
        if (root== nullptr) return 0;
        int sum=0;
        if (root->left!= nullptr&&root->left->left== nullptr&&root->left->right== nullptr) sum += root->left->val;
        sum+= sumOfLeftLeaves(root->left);
        sum+= sumOfLeftLeaves(root->right);
        return sum;
    }

    bool isSameTree(TreeNode* p, TreeNode* q) {
        if (p== nullptr&&q== nullptr) return true;
        else if (p!= nullptr&&q!= nullptr) {
            if(p->val==q->val) {
                return isSameTree(p->left,q->left)&& isSameTree(p->right,q->right);
            }else{
                return false;
            }
        }else{
            return false;
        }
    }
    void travasal(TreeNode* root,string path,vector<string>& result){
        path+= to_string(root->val);
        if (root->left== nullptr&&root->right== nullptr){
            result.push_back(path);
            return;
        }
        if (root->right) travasal(root->right,path+"->",result);
        if (root->left) travasal(root->left,path+"->",result);
    }
    vector<string> binaryTreePaths(TreeNode* root) {
        string  path;
        vector<string> result;
        if (root== nullptr) return result;
        travasal(root,path,result);
        return result;
    }
    bool isBalanced(TreeNode* root) {
        if (root== nullptr) return true;
        int left= depth(root->left);
        int right= depth(root->right);
        if (abs(left-right)>1) return false;
        return isBalanced(root->right)&& isBalanced(root->left);
    }
    int depth(TreeNode* root){
        if (root== nullptr) return 0;
        return max(depth(root->right),depth(root->left))+1;
    }
    //完全二叉树求节点数量
    int countNodes(TreeNode* root) {
        if (root== nullptr) return 0;
        TreeNode* left=root->left;
        TreeNode* right=root->right;
        int rightHeigth=0,leftHeigth=0;
        while(right){
            right=right->right;
            rightHeigth++;
        }
        while (left){
            left=left->left;
            leftHeigth++;
        }
        if (rightHeigth==leftHeigth) return (2<<leftHeigth)-1;
        return countNodes(root->left)+ countNodes(root->right)+1;
    }
    vector<vector<int>> levelOrder(TreeNode* root) {
        queue<TreeNode*> queue;
        vector<vector<int>> result;
        if (root==NULL) return result;
        queue.push(root);
        while(!queue.empty()){
            int size =queue.size();
            vector<int> res;
            while(size--){
                TreeNode* node=queue.front();
                queue.pop();
                if(node->left!= nullptr) queue.push(node->left);
                if (node->right!= nullptr) queue.push(node->right);
                res.push_back(node->val);
            }
            result.push_back(res);
        }
    }
    //迭代法遍历二叉树
    vector<int> inOrderIteration(TreeNode* root) {
        stack<TreeNode*> sk;
        vector<int> result ;
        sk.push(root);
        while (!sk.empty()) {
            TreeNode* node=sk.top();
            sk.pop();
            if (node==nullptr) {
                continue;
            }else {
                result.push_back(node->val);
                sk.push(node->right);
                sk.push(node->left);
            }
        }
        return result;
    }
    vector<int> postorderTraversal(TreeNode* root) {
        vector<int> result;
        postOrder(root,result);
        return result;
    }
    void postOrder(TreeNode* root,vector<int>& result) {
        if (root==nullptr) return ;
        postOrder(root->left,result);
        postOrder(root->right,result);
        result.push_back(root->val);
    }
    vector<int> preorderTraversal(TreeNode* root) {
        vector<int> result;
        preOrder(root,result);
        return result;
    }
    void preOrder(TreeNode* root,vector<int>& result) {
        if (root==nullptr) return;
        result.push_back(root->val);
        preOrder(root->left,result);
        preOrder(root->right,result);

    }
    vector<int> inorderTraversal(TreeNode* root) {
        vector<int> result;
        inOrder(root,result);
        return result;
    }
    void inOrder(TreeNode* root,vector<int>& result) {
        if (root==nullptr) return;
        inOrder(root->left,result);
        result.push_back(root->val);
        inOrder(root->right,result);
    }


    class myComparion {
    public:
        bool operator()(const pair<int, int>& lhs, const pair<int, int>& rhs)  {
            return lhs.second > rhs.second;
        }
    };

    vector<int> topKFrequent(vector<int>& nums, int k) {
        map<int,int> map;
        vector<int> result;
        priority_queue<pair<int,int>,vector<pair<int,int>>,myComparion> pq;
        for (int num : nums) {
            map[num]++;
        }
        auto it=map.begin();
        for (int i=0;i<k;i++) {
            pq.push(*it);
            ++it;
        }
        while (it!=map.end()) {
            pq.push(*it);
            pq.pop();
            ++it;
        }
        while (!pq.empty()) {
            result.push_back(pq.top().first);
            pq.pop();
        }
        return result;

    }
    bool repeatedSubstringPattern(string s) {
        auto next=getNext(s);
        if (s.size()%(s.size()-next[s.size()])==0) return true;
        else return false;
    }
    int strStr(string haystack, string needle) {
        auto next=getNext(needle);
        for (int i=0,j=0; i<haystack.size();i++) {
            //如果当前的字符不匹配，用next数组让j指向下一个匹配的字符，如果j=0且第一个字符匹配时候，j移动下一个继续下一轮匹配时
            //如果j=0但是第一个字符不相等时，那么j不动，进入下一轮，i++
            while (j>0&&haystack[i]!=needle[j]) j=next[j];
            if (haystack[i]==needle[j]) j++;
            //找到needle的末尾后，说明当前匹配的字符串已经找到，返回起点下标
            if (j==needle.size()) return i-needle.size()+1;
        }
        return -1;
    }
    vector<int> getNext(string s){
        vector<int> next(s.size()+1,0);
        for (int j=2,i=0;j<s.size()+1;j++) {
            while (i>0&&s[i]!=s[j-1]) i=next[i];
            if (s[i]==s[j-1]) i++;
            next[j]=i;
        }
        return next;
    }
    string reverseWords(string s) {
        vector<string> vec;
        string ans;
        string str="";
        for (int i=0;i<s.size();i++) {
            if (s[i]==' ') {
                if (str=="") {
                    continue;
                }else {
                    vec.push_back(str);
                    str="";
                }
            }else {
                str+=s[i];
            }

        }
        if (str!="") vec.push_back(str);
        for (int i=vec.size()-1;i>=0;i--) {
            ans+=vec[i];
            if (i!=0) ans+=' ';
        }
        return ans;

    }
    string reverseStr(string s, int k) {
        for (int i=0;i<s.size();i+=2*k) {
            if (s.size()-i>=k) reverseStringFromNToM(s,i,i+k);
            if (s.size()-i<k) reverseStringFromNToM(s,i,s.size()-i);
        }
        return s;
    }

    void reverseStringFromNToM(string& s,int n,int m) {
        for (int i =n,j=m;i<j;i++,j--){
            swap(s[i],s[j]);
        }
    }
    void reverseString(vector<char>& s) {
        for (int i =0;i<s.size()/2;i++) {
            char temp;
            temp=s[i];
            s[i]=s[s.size()-i-1];
            s[s.size()-i-1]=temp;
        }
    }
    vector<vector<int>> fourSum(vector<int>& nums, int target) {
        vector<vector<int>> result;
        sort(nums.begin(),nums.end());
        for (int i=0;i<nums.size();i++) {
            if (nums[i]>target) return result;
            for (int j=i+1;j<nums.size();i++) {
                if (nums[j]==nums[j-1]) continue;
                int right=nums.size()-1;
                int left =j+1;
                while (left<right) {
                    if (nums[i]+nums[j]+nums[left]+nums[right]>target) right--;
                    else if (nums[i]+nums[j]+nums[left]+nums[right]<target) left++;
                    else {
                        result.push_back({nums[i],nums[j],nums[left],nums[right]});
                        while (nums[left]==nums[left+1]) left++;
                        while (nums[right]==nums[right+1]) right--;

                        left++;
                        right--;
                    }
                }
            }

        }
        return result;
    }
    vector<vector<int>> threeSum(vector<int>& nums) {
        vector<vector<int>> result;
        sort(nums.begin(),nums.end());
        for (int i=0;i<nums.size();i++) {
            if (nums[i]>0) return result;
            if (nums[i]==nums[i-1]) continue;
            int right=nums.size()-1;
            int left =i+1;
            while (left<right) {
                if (nums[i]+nums[left]+nums[right]>0) right--;
                else if (nums[i]+nums[left]+nums[right]<0) left++;
                else {
                    result.push_back({nums[i],nums[left],nums[right]});
                    while (nums[left]==nums[left+1]) left++;
                    while (nums[right]==nums[right+1]) right--;

                    left++;
                    right--;
                }
            }
        }
        return result;
    }
    bool canConstruct(string ransomNote, string magazine) {
        unordered_set<char,int> map;
        for (char ch : ransomNote) {
            map[ch]++;
        }
        for (char ch : magazine) {
            map[ch]--;
            if (map[ch]<0) return false;
        }
        return true;
    }
    int fourSumCount(vector<int>& nums1, vector<int>& nums2, vector<int>& nums3, vector<int>& nums4) {
        unordered_set<int,int> map;
        int count =0;
        for (int i=0;i<nums1.size();i++) {
            for (int j=0;j<nums2.size();j++) {
                map[nums1[i]+nums2[j]]++;
            }
        }
        for (int i=0;i<nums3.size();i++) {
            for (int j=0;j<nums4.size();j++) {
                int num=0-nums3[i]-nums4[j];
                if (map.find(num)!=map.end()) {
                    count+=map[num];
                }
            }
        }
        return count;
    }
    vector<int> twoSum(vector<int>& nums, int target) {
        unordered_set<int,int> map;
        for (int i=0;i<nums.size();i++) {
            int num=target-nums[i];
            if (map.find(num)!=map.end()) {
                vector<int> ans{i,map[num]};
                return ans;
            }
            map.insert({nums[i],i});

        }
        return vector<int>(NULL);
    }


    int getSum(int n) {
        int sum=0;
        while (n!=0) {
            sum+=(n%10)*(n%10);
            n/=10;
        }
        return sum;
    }
    bool isHappy(int n) {
        unordered_set<int> set;
        int sum =n;
        while (true) {
            sum=getSum(sum);
            if (sum==1) {
                return true;
            }
            if (set.find(sum)!=set.end()) {
                return false;
            }else {
                set.insert(sum);
            }
        }

    }
    bool isValid(string s) {
        stack<char> sk;
        for (char c : s) {
            if (c=='('||c=='['||c=='{') {
                sk.push(c);
            }else if (!sk.empty()){
                if ((c==')'&&sk.top()=='(')||(c==']'&&sk.top()=='[')||(c=='}'&&sk.top()=='{')) sk.pop();
                else return false;
            }else {
                return false;
            }
        }
        if (sk.empty()) return true;
        else return false;
    }
    string removeDuplicates(string s) {
        stack<char> sk;
        for (char c : s) {
            if (sk.empty()) sk.push(c);
            else if (sk.top()==c) sk.pop();
            else sk.push(c);
        }
        string str;
        while (!sk.empty()) {
            str+=sk.top();
            sk.pop();
        }
        reverse(str.begin(),str.end());
        return str;
    }
    int evalRPN(vector<string>& tokens) {
        stack<int> sk;
        for (auto token : tokens) {
            if (token =="+"||token=="-"||token=="*"||token=="/") {
                int num1=sk.top();
                sk.pop();
                int num2=sk.top();
                sk.pop();
                int num3=0;
                switch(token[0])
                {
                    case '+': num3=num2+num1;break;
                    case '-': num3=num2-num1;break;
                    case '*': num3=num2*num1;break;
                    case '/': num3=num2/num1;break;
                }
                sk.push(num3);
            }else {
                sk.push(stoi(token));
            }
        }
        return sk.top();
    }
};
//单调队列
class MyMaxQueue {
public:
    deque<int> dq;
    void pop(int value) {
        if ((!dq.empty())&&dq.front()==value) dq.pop_front();
    }
    void push(int value) {
        while ((!dq.empty())&&dq.back()<value) dq.pop_back();
        dq.push_back(value);
    }
    int getMax() {
        return dq.front();
    }
};
class Solution1 {
public:
    vector<int> maxSlidingWindow(vector<int>& nums, int k) {
        MyMaxQueue mq;
        vector<int> result;
        for (int i=0;i<k;i++) {
            mq.push(nums[i]);
        }
        result.push_back(mq.getMax());
        for (int i=k; i<nums.size(); i++) {
            mq.pop(nums[i-k]);
            mq.push(nums[i]);
            result.push_back(mq.getMax());
        }
        return result;
    }
};

class MyQueue {
public:
    stack<int> stack1;
    stack<int> stack2;
    MyQueue() {

    }

    void push(int x) {
        stack1.push(x);
    }

    int pop() {
        if (stack2.empty()) {
            while (!stack1.empty()) {
                stack2.push(stack1.top());
                stack1.pop();
            }
        }
        int result=stack2.top();
        stack2.pop();
        return result;
    }

    int peek() {
        if (stack2.empty()) {
            while (!stack1.empty()) {
                stack2.push(stack1.top());
                stack1.pop();
            }
        }
        return stack2.top();
    }

    bool empty() {
        return stack1.empty()&&stack2.empty();
    }
};

class MyStack {
public:
    queue<int> queue;

    MyStack() {

    }

    void push(int x) {
        queue.push(x);
    }

    int pop() {
        int count=queue.size();
        int result;
        while (count) {
            if (count==1) {
                result=queue.front();
                queue.pop();
                count--;
            }else {
                queue.push(queue.front());
                queue.pop();
                count--;
            }


        }
        return result;
    }

    int top() {
        int res=this->pop();
        this->push(res);
    }

    bool empty() {
        return queue.empty();
    }

};

int main() {
    Solution sol;
    vector<string> v={"4","13","5","/","+"};
    int num=sol.evalRPN(v);

}
