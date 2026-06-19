#include <iostream>
#include <map>
#include <set>
#include <unordered_set>
using namespace std;
struct TreeNode {
    int val;                // 节点存储的值
    TreeNode *left;         // 左孩子指针，指向左子节点
    TreeNode *right;        // 右孩子指针，指向右子节点


};
class Solution {
public:
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
        unordered_map<char,int> map;
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
        unordered_map<int,int> map;
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
        unordered_map<int,int> map;
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
