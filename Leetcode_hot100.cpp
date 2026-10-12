//
// Created by 顾天齐 on 2026/9/1.
//

#include "Leetcode_hot100.h"
#include <iostream>
#include <map>
#include <set>
#include <unordered_set>
#include <vector>
#include <stack>
#include <queue>
#include <algorithm>
#include <cmath>
#include <list>
#include <numeric>

using namespace std;

struct TreeNode {
    int val; // 节点存储的值
    TreeNode *left; // 左孩子指针，指向左子节点
    TreeNode *right; // 右孩子指针，指向右子节点
    TreeNode() : val(0), left(nullptr), right(nullptr) {
    }

    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {
    }

    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {
    }
};
struct ListNode {
        int val;
        ListNode *next;
        ListNode() : val(0), next(nullptr) {}
        ListNode(int x) : val(x), next(nullptr) {}
        ListNode(int x, ListNode *next) : val(x), next(next) {};
     };


class Solution {
    vector<int> twoSum(vector<int>& nums, int target) {
    //    for (int i=0;i<nums.size();i++) {
    //        for (int j=i;j<nums.size();j++) {
    //            if (nums[i]+nums[j]==target) return vector<int>(i,j);
    //        }
    //    }
    //     return vector<int>();
        unordered_map<int,int> ump;
        for (int i=0;i<nums.size();i++) {
            auto it=ump.find(target-nums[i]);
            if (it!=ump.end()) return {i,it->second};
            else {
                ump.insert(pair<int,int>{nums[i],i});
            }
        }
        return {};
     }
    vector<vector<string>> groupAnagrams(vector<string>& strs) {
        unordered_map<string,vector<string>> ump;
        vector<vector<string>> res;
        for (int i=0;i<strs.size();i++) {
            string str=strs[i];
            sort(strs[i].begin(),strs[i].end());
            ump[strs[i]].push_back(str);
        }
        for (auto pair : ump) {
            res.push_back(pair.second);
        }
        return res;
    }
    int longestConsecutive(vector<int>& nums) {
        unordered_set<int> ust;
        for (const int & num : nums) {
            ust.insert(num);
        }
        int longestStreak=0;
        for (const int & num : ust) {
            if (!ust.count(num-1)) {//若不存在前序列
                int currentNum=num;
                int longStreak=1;
                while (ust.count(num+1)) {//存在后续序列
                    currentNum++;
                    longStreak++;
                }
                longestStreak=max(longestStreak,longStreak);

            }
        }
        return longestStreak;
    }
    void moveZeroes(vector<int>& nums) {
        int left=0,right=0;
        while (right<nums.size()) {
            if (nums[right]) {
                swap(nums[left],nums[right]);
                left++;
            }
            right++;
        }
    }
    //解法二
    void moveZeroes2(vector<int>& nums) {
        int index=0;
        for (int num : nums) {
            if (num) nums[index++]=num;
        }
        for (int i=index;i<nums.size();i++) {
            nums[i]=0;
        }
    }
    int maxArea(vector<int>& height) {
        int left=0;
        int right=height.size();
        int maxArea=0;
        while (left<right) {
            maxArea=max(maxArea,min(height[left],height[right])*(right-left));
            if (height[left]<height[right]) left++;
            else right--;
        }
        return maxArea;
    }
    vector<vector<int>> threeSum(vector<int>& nums) {
        vector<vector<int>> res;
        sort(nums.begin(),nums.end());
        for (int i=0;i<nums.size();i++) {
            if (i>0&&nums[i]==nums[i-1]) continue;
            int left=i+1;
            int right=nums.size()-1;
            while (left<right) {
                if (nums[i]+nums[left]+nums[right]>0) right--;
                else if (nums[i]+nums[left]+nums[right]<0) left++;
                else {
                    res.push_back(vector<int>{nums[i],nums[left],nums[right]});
                    while (left<right&&nums[right]==nums[right-1]) right--;
                    while (left<right&&nums[left]==nums[left+1]) left++;

                    right--;
                    left++;
                }
            }
        }
        return res;
    }
    int trap(vector<int>& height) {
        stack<int> st;
        st.push(0);
        int res=0;
        for (int i=1;i<height.size();i++) {
            if (height[i]<height[st.top()]) st.push(i);
            else if (height[i]==height[st.top()]) st.pop(),st.push(i);
            else {
                while (!st.empty()&&height[i]>height[st.top()]) {
                    int mid=st.top();
                    st.pop();
                    if (!st.empty()) {
                        int h=min(height[i],height[st.top()])-height[mid];
                        int s=i-st.top()-1;
                        res+=h*s;
                    }
                }

            }
            st.push(i);
        }
        return res;
    }
    int lengthOfLongestSubstring(string s) {
        unordered_set<char>  ust;
        int left=0,res=0;
        for (int right=0;right<s.size();right++) {
            while (ust.count(s[right])) {
                ust.erase(s[left++]);
            }
            ust.insert(s[right]);
            res=max(res,right-left+1);
        }
        return res;
    }
    vector<int> findAnagrams(string s, string p) {
        vector<int> res;
        vector<int> sCount(26);
        vector<int> pCount(26);
        int sLen=s.size(),pLen=p.size();
        if (pLen>sLen) return res;
        int right=0,left=0;

        for (;right<pLen;right++) {
            sCount[s[right]-'a']++;
            pCount[p[right]-'a']++;
        }
        if (sCount==pCount) res.push_back(0);
        for (;right<sLen;right++,left++) {
            sCount[s[left-1]-'a']--;
            sCount[s[right]-'a']++;
            if (sCount==pCount) res.push_back(left);
        }
        return res;
    }
    int subarraySum(vector<int>& nums, int k) {

        int res=0;
        unordered_map<int,int> ump;
        ump[0]=1;
        int preSum=0;
        for (const int & num : nums) {
            preSum+=num;
            if (ump.find(preSum-k)!=ump.end()) {
                res+=ump[preSum-k];
            }
            ump[preSum]++;
        }
        return res;
    }
    class MyQueue {
        public:
        deque<int> que;
        void pop(int value) {
            if (!que.empty()&&que.front()==value) que.pop_front();
        }
        void push(int value) {
            while (!que.empty()&&que.back()<value) que.pop_back();
            que.push_back(value);
        }
        int  front() {
            return que.front();
        }
    };
    vector<int> maxSlidingWindow(vector<int>& nums, int k) {
        
        MyQueue myQue;
        vector<int> res;
        for (int i=0;i<k;i++) {
            myQue.push(nums[i]);
        }
        res.push_back(myQue.front());
        for (int i=k;i<nums.size();i++) {
            myQue.pop(nums[i-k]);
            myQue.push(nums[i]);
            res.push_back(myQue.front());
        }
        return res;
    }

    vector<vector<int>> merge(vector<vector<int>>& intervals) {
        sort(intervals.begin(),intervals.end(),[](vector<int> a,vector<int> b) {
            return a[0]<b[0];
        });
        vector<vector<int>> res;
        res.push_back(intervals[0]);
        for (int i=1;i<intervals.size();i++) {
            if (intervals[i][0]<=res.back()[1]) res.back()[1]=intervals[i][1];
            else res.push_back(intervals[i]);
        }
        return res;
    }
    void reverseNtoM(vector<int> &nums,int n,int m) {
        while (n<m) {
            swap(nums[n++],nums[m--]);
        }
    }
    void rotate(vector<int>& nums, int k) {
        reverseNtoM(nums,0,nums.size()-1);
        reverseNtoM(nums,0,k-1);
        reverseNtoM(nums,k-1,nums.size()-1);
    }
    int firstMissingPositive(vector<int>& nums) {
        int res=0;
        for (int i=0;i<nums.size();i++) {
            while (nums[i]>0&&nums[i]<=nums.size()&&nums[nums[i]-1]!=nums[i]) {
                swap(nums[nums[i]-1],nums[i]);
            }
        }
        for (int i=0;i<nums.size();i++) {
            if (nums[i]!=i+1) return i+1;
        }
        return nums.size();
    }

    vector<int> spiralOrder(vector<vector<int>>& matrix) {
        vector<int > res;
        int l=0;
        int r=matrix[0].size()-1;
        int u=0;
        int d=matrix.size()-1;

        while (true) {
            for (int i=l;i<=r;i++) res.push_back(matrix[u][i]);
            if (++u>d) break;
            for (int i=u;i<=d;i++) res.push_back(matrix[i][r]);
            if (--r<l) break;
            for (int i=r;i>=l;i--) res.push_back(matrix[d][i]);
            if (--d<u) break;
            for (int i=d;i>=u;i--) res.push_back(matrix[i][l]);
            if (++l>r) break;

        }
        return res;
    }

    void rotate(vector<vector<int>>& matrix) {
        //先转置矩阵
        for (int i=0;i<matrix.size();i++) {
            for (int j=i+1;j<matrix[0].size();j++) {
                swap(matrix[i][j],matrix[j][i]);
            }
        }
        //倒转每一行
        for (int i=0;i<matrix.size();i++) {
            reverse(matrix[i].begin(),matrix[i].end());
        }

    }
    bool searchMatrix(vector<vector<int>>& matrix, int target) {
        int m=matrix.size();
        int n=matrix[0].size();
        int row=0;
        int col=n-1;
        while (row<m&&col>=0) {
            if (matrix[row][col]==target) return true;
            else if (matrix[row][col]<target) row++;
            else col--;
        }
        return false;
    }
    ListNode *getIntersectionNode(ListNode *headA, ListNode *headB) {
        int lenA=0,lenB=0;
        ListNode *pA=headA;
        ListNode *pB=headB;
        while (pA!=nullptr) {
            lenA++;
            pA=pA->next;
        }
        while (pB!=nullptr) {
            lenB++;
            pB=pB->next;
        }
        pA=headA;
        pB=headB;
        while (pA!=pB) {
            if (lenA>lenB)pA=pA->next,lenA--;
            else if (lenA<lenB)pB=pB->next,lenB--;
            else{
                pA=pA->next;
                pB=pB->next;
            }
        }
        return pA==pB? pA:nullptr;


    }

    ListNode* reverseList(ListNode* head) {
        ListNode *dummy=(ListNode*)malloc(sizeof(ListNode));
        dummy->next=head;
        ListNode* pre=nullptr;
        ListNode* cur=head;
        ListNode* next;
        while (cur!=nullptr) {
            next=cur->next;
            cur->next=pre;
            pre=cur;
            cur=next;
        }
        dummy->next=pre;
        return pre;

    }
    ListNode* reverseBetween(ListNode* head, int left, int right) {
        ListNode* dummy=(ListNode*)malloc(sizeof(ListNode));
        dummy->next=head;
        ListNode* p=dummy;
        ListNode* cur;
        for (int i=1;i<left;i++) {
            p=p->next;
        }
        ListNode* pre=nullptr;
        cur=p->next;
        for (int i=0;i<right-left+1;i++) {
            ListNode* next=cur->next;
            cur->next=pre;
            pre=cur;
            cur=next;
        }
        p->next->next=cur;
        p->next=pre;
        return dummy->next;

    }
    bool isPalindrome(ListNode* head) {
        ListNode* low=head;
        ListNode* fast=head;
        ListNode* p=head;
        while (fast!=nullptr&&fast->next!=nullptr) {
            low=low->next;
            fast=fast->next->next;
        }
        if(fast != nullptr){
            low = low->next;
        }
        ListNode* pre=nullptr;
        while (low!=nullptr) {
            ListNode* next=low->next;
            low->next=pre;
            pre=low;
            low=next;
        }


        while (pre!=nullptr) {
            low=low->next;
            if (low->val!=p->val) return false;
            p=p->next;
        }
        return true;
    }
    bool hasCycle(ListNode *head) {
        ListNode* low=head;
        ListNode* fast=head;
        while (fast!=nullptr&&fast->next!=nullptr) {
            low=low->next;
            fast=fast->next->next;
            if (low==fast) return true;
        }
        return false;
    }
    ListNode* mergeTwoLists(ListNode* list1, ListNode* list2) {
        ListNode* head=nullptr;
        ListNode* cur=nullptr;
        while (list1!=nullptr&&list2!=nullptr) {
            if (list1->val<list2->val) {
                if (head==nullptr) head=list1;
                if (cur==nullptr) cur=list1;
                else {
                    cur->next=list1;
                }
                list1=list1->next;
            }else {
                if (head==nullptr) head=list2;
                if (cur==nullptr) cur=list2;
                else {
                    cur->next=list2;
                }
                list2=list2->next;
            }
        }
        if (list1!=nullptr) cur->next=list1;
        if (list2!=nullptr) cur->next=list2;

        return head;
    }
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        ListNode dummy;
        ListNode* cur=&dummy;
        int carry=0;
        while (l1||l2||carry) {
            int sum=carry;
            if (l1!=nullptr) {
                sum+=l1->val;
                l1=l1->next;
            }
            if (l2!=nullptr) {
                sum+=l2->val;
                l2=l2->next;
            }
            carry=sum/10;
            cur->next=new ListNode(sum%10);
            cur=cur->next;
        }
        return dummy.next;

    }
    ListNode* removeNthFromEnd(ListNode* head, int n) {
        ListNode dummy;
        dummy.next = head;
        ListNode *fast = &dummy;
        ListNode *slow = &dummy;

        for (int i=0;i<n;i++) {
            fast=fast->next;
        }
        while (fast->next!=nullptr) {
            fast=fast->next;
            slow=slow->next;
        }
        slow->next=slow->next->next;
        return dummy.next;
    }
    ListNode* reverseKGroup(ListNode* head, int k) {
        stack<ListNode*> st;
        ListNode dummy;
        dummy.next=head;
        ListNode* pre=&dummy;
        ListNode* cur=head;
        int count =0;
        while (cur!=nullptr) {
            st.push(cur);
            count++;
            cur=cur->next;
            if (count==k) {
                for (int i=0;i<k;i++) {
                    pre->next=st.top();
                    st.pop();
                    pre=pre->next;
                }
                count=0;
            }

        }
        if (count>0) {
            for (int i=0;i<count-1;i++) {
                st.pop();
            }
            pre->next=st.top();
        }else {
            pre->next=nullptr;
        }
        return dummy.next;

    }

    
};

