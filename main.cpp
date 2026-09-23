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

class Solution {
public:
    int largestRectangleArea(vector<int>& heights) {
       int res=0;
        stack<int>  st;
        heights.insert(heights.begin(), 0); // 数组头部加入元素0
        heights.push_back(0); // 数组尾部加入元素0
        st.push(0);
        for (int i=1;i<heights.size();i++) {
            if (heights[i]>heights[st.top()]) st.push(i);
            else if (heights[i]==heights[st.top()]) {
                st.pop();
                st.push(i);
            }else {
                while (!st.empty()&&heights[i]<heights[st.top()]) {
                    int mid =st.top();
                    st.pop();
                    if (!st.empty()) {
                        int left=st.top();
                        int right=i;
                        int h=heights[mid];
                        int w=right-left-1;
                        res=max(res,h*w);
                    }
                }
                st.push(i);
            }
        }
        return res;
    }
    int trap(vector<int>& height) {
        int sum=0;
        stack<int> st;
        st.push(0);
        for (int i=1;i<height.size();i++) {
            if (height[i]<height[st.top()]) st.push(i);
            else if (height[i]==height[st.top()]) {
                st.pop();
                st.push(i);
            }else {
                while (!st.empty() && height[i] > height[st.top()]) {
                    int mid=st.top();
                    st.pop();
                    if (!st.empty()) {
                        int h = min(height[st.top()], height[i]) - height[mid];
                        int w = i - st.top() - 1; // 注意减一，只求中间宽度
                        sum += h * w;
                    }

                }
                st.push(i);
            }
        }
        return sum;
    }
    vector<int> nextGreaterElements(vector<int> &nums) {
        vector<int> res(nums.size(), -1);
        if (nums.size() == 0) return res;
        stack<int> st;
        st.push(0);
        int size = nums.size();
        for (int i = 1; i < nums.size() * 2; i++) {
            if (nums[i % size] <= nums[st.top()]) st.push(i % size);
            else {
                while (!st.empty() && nums[i % size] > nums[st.top()]) {
                    res[st.top()] = i % size;
                    st.pop();
                }
                st.push(i % size);
            }
        }
        return res;
    }

    vector<int> nextGreaterElement(vector<int> &nums1, vector<int> &nums2) {
        vector<int> result(nums1.size(), -1);
        stack<int> st;
        st.push(0);
        unordered_map<int, int> ump;
        for (int i = 0; i < nums1.size(); i++) {
            ump[nums1[i]] = i;
        }
        for (int i = 1; i < nums2.size(); i++) {
            if (nums2[i] <= nums2[st.top()]) st.push(i);
            else {
                while (!st.empty() && nums2[i] > nums2[st.top()]) {
                    if (ump.count(nums2[st.top()]) > 0) {
                        int index = ump[nums2[st.top()]]; // 根据map找到nums2[st.top()] 在 nums1中的下标
                        result[index] = nums2[i];
                    }
                    st.pop();
                }
                st.push(i);
            }
        }
        return result;
    }

    vector<int> dailyTemperatures(vector<int> &temperatures) {
        vector<int> result(temperatures.size(), 0);
        stack<int> st;
        st.push(0);
        for (int i = 1; i < temperatures.size(); i++) {
            if (temperatures[i] <= temperatures[st.top()]) {
                st.push(i);
            } else {
                while (!st.empty() && temperatures[i] > temperatures[st.top()]) {
                    result[st.top()] = i - st.top();
                    st.pop();
                }
                st.push(i);
            }
        }
        return result;
    }

    int longestPalindromeSubseq(string s) {
        vector<vector<int> > dp(s.size(), vector<int>(s.size(), 0));
        for (int i = 0; i < s.size(); i++) dp[i][i] = 1;
        for (int i = s.size() - 1; i >= 0; i--) {
            for (int j = i + 1; j < s.size(); j++) {
                if (s[j] == s[i]) {
                    dp[i][j] = dp[i + 1][j - 1] + 2;
                } else {
                    dp[i][j] = max(dp[i][j - 1], dp[i + 1][j]);
                }
            }
        }
        return dp[0][s.size() - 1];
    }

    dfa
    int countSubstrings(string s) {
        vector<vector<bool> > dp(s.size(), vector<bool>(s.size(), false));
        int res = 0;
        for (int i = s.size() - 1; i >= 0; i--) {
            for (int j = i; j < s.size(); j++) {
                if (s[j] == s[i]) {
                    if (j - i <= 1) dp[i][j] = true, res++;
                    if (j - i > 1 && dp[i + 1][j - 1]) dp[i][j] = true, res++;
                } else {
                    dp[i][j] = false;
                }
            }
        }
        return res;
    }

    int minDistance(string word1, string word2) {
        vector<vector<int> > dp(word1.size() + 1, vector<int>(word2.size() + 1, 0));
        for (int i = 0; i <= word1.size(); i++) dp[i][0] = i;
        for (int j = 0; j <= word2.size(); j++) dp[0][j] = j;
        for (int i = 1; i <= word1.size(); i++) {
            for (int j = 1; j <= word2.size(); j++) {
                if (word1[i - 1] == word2[j - 1]) {
                    dp[i][j] = dp[i - 1][j - 1];
                } else {
                    dp[i][j] = min({dp[i - 1][j] + 1, dp[i][j - 1] + 1, dp[i - 1][j - 1] + 1});
                }
            }
        }
        return dp[word1.size()][word2.size()];
    }

    int minDistance(string word1, string word2) {
        vector<vector<int> > dp(word1.size() + 1, vector<int>(word2.size() + 1, 0));
        for (int i = 0; i <= word1.size(); i++) dp[i][0] = i;
        for (int j = 0; j <= word2.size(); j++) dp[0][j] = j;
        for (int i = 1; i <= word1.size(); i++) {
            for (int j = 1; j <= word2.size(); j++) {
                if (word1[i - 1] == word2[j - 1]) {
                    dp[i][j] = dp[i - 1][j - 1];
                } else {
                    dp[i][j] = min(dp[i - 1][j] + 1, min(dp[i][j - 1] + 1, dp[i - 1][j - 1] + 2));
                }
            }
        }
        return dp[word1.size()][word2.size()];
    }

    int numDistinct(string s, string t) {
        vector<vector<int> > dp(s.size() + 1, vector<int>(t.size() + 1, 0));
        for (int i = 0; i <= s.size(); i++) dp[i][0] = 1;
        for (int i = 1; i <= s.size(); i++) {
            for (int j = 1; j <= t.size(); j++) {
                if (s[i - 1] == t[j - 1]) {
                    dp[i][j] = dp[i - 1][j - 1] + dp[i - 1][j];
                } else {
                    dp[i][j] = dp[i - 1][j];
                }
            }
        }
        return dp[s.size()][t.size()];
    }

    bool isSubsequence(string s, string t) {
        vector<vector<int> > dp(s.size() + 1, vector<int>(t.size() + 1, 0));
        for (int i = 1; i <= s.size(); i++) {
            for (int j = 1; j <= t.size(); j++) {
                if (s[i - 1] == t[j - 1]) {
                    dp[i][j] = dp[i - 1][j - 1] + 1;
                } else {
                    dp[i][j] = dp[i][j - 1];
                }
            }
        }
        if (dp[s.size()][t.size()] == s.size()) return true;
        return false;
    }

    int maxSubArray(vector<int> &nums) {
        vector<int> dp(nums.size());
        dp[1] = nums[1];
        for (int i = 1; i < nums.size(); i++) {
            dp[i] = max(dp[i - 1] + nums[i], nums[i]);
        }
        return dp[nums.size() - 1];
    }

    int maxUncrossedLines(vector<int> &nums1, vector<int> &nums2) {
        vector<vector<int> > dp(nums1.size() + 1, vector<int>(nums2.size() + 1, 0));
        for (int i = 1; i <= nums1.size(); i++) {
            for (int j = 1; j <= nums2.size(); j++) {
                if (nums1[i - 1] == nums2[j - 1]) {
                    dp[i][j] = dp[i - 1][j - 1] + 1;
                } else {
                    dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
                }
            }
        }
        return dp[nums1.size()][nums2.size()];
    }

    int longestCommonSubsequence(string text1, string text2) {
        vector<vector<int> > dp(text1.size() + 1, vector<int>(text2.size() + 1, 0));
        for (int i = 1; i <= text1.size(); i++) {
            for (int j = 1; j <= text2.size(); j++) {
                if (text1[i - 1] == text2[j - 1]) {
                    dp[i][j] = dp[i - 1][j - 1] + 1;
                } else {
                    dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
                }
            }
        }
        return dp[text1.size()][text2.size()];
    }

    int findLength(vector<int> &nums1, vector<int> &nums2) {
        vector<vector<int> > dp(nums1.size(), vector<int>(nums2.size(), 0));
        int res = 0;
        for (int i = 1; i < nums1.size(); i++) {
            for (int j = 1; j < nums2.size(); j++) {
                if (nums1[i - 1] == nums2[j - 1]) dp[i][j] = dp[i - 1][j - 1] + 1;
                res = max(res, dp[i][j]);
            }
        }
        return res;
    }

    int findLengthOfLCIS(vector<int> &nums) {
        if (nums.size() == 1) return 1;
        int res = 1;
        for (int i = 1; i < nums.size(); i++) {
            if (nums[i] > nums[i - 1]) res++;
            else res = 1;
        }
        return res;
    }

    int lengthOfLIS(vector<int> &nums) {
        vector<int> dp(nums.size(), 1);
        int res = 0;
        for (int i = 1; i < nums.size(); i++) {
            for (int j = 0; j < i; j++) {
                if (nums[i] > nums[j]) dp[i] = max(dp[i], dp[j] + 1);
            }
            res = max(res, dp[i]);
        }
        return res;
    }

    int maxProfit(vector<int> &prices, int fee) {
        vector<vector<int> > dp(prices.size(), vector<int>(2, 0));
        dp[0][0] = -prices[0];
        dp[0][1] = 0;
        //dp[i][0]: 持有当天的股票(可以是当天买入，也可以是之前买入的)
        //dp[i][1]: 不持有当天的股票（可以是当天卖出，也可以是之前就已经卖出）
        for (int i = 1; i < dp.size(); i++) {
            dp[i][0] = max(dp[i - 1][0], dp[i - 1][1] - prices[i]);
            dp[i][1] = max(dp[i - 1][1], dp[i][0] + prices[i] - fee);
        }
        return dp[prices.size() - 1][1];
    }

    int maxProfit(vector<int> &prices) {
        /*
        0:状态一：持有股票状态（今天买入股票，或者是之前就买入了股票然后没有操作，一直持有）
        不持有股票状态，这里就有两种卖出股票状态
        1:状态二：保持卖出股票的状态（两天前就卖出了股票，度过一天冷冻期。或者是前一天就是卖出股票状态，一直没操作）
        2:状态三：今天卖出股票
        3:状态四：今天为冷冻期状态，但冷冻期状态不可持续，只有一天！*/
        vector<vector<int> > dp(prices.size(), vector<int>(4, 0));
        dp[0][0] = -prices[0];
        dp[0][2] = -prices[0];
        for (int i = 0; i < prices.size(); i++) {
            dp[i][0] = max(dp[i - 1][0], max(dp[i - 1][1], dp[i - 1][3]) - prices[i]);
            dp[i][1] = max(dp[i - 1][1], dp[i - 1][3]);
            dp[i][2] = dp[i - 1][1] + prices[i];
            dp[i][3] = dp[i - 1][2];
        }
        return max(dp[prices.size() - 1][2], max(dp[prices.size() - 1][3], dp[prices.size() - 1][1]));
    }

    int maxProfit(int k, vector<int> &prices) {
        vector<vector<int> > dp(prices.size(), vector<int>(2 * k + 1, 0));
        for (int j = 1; j < 2 * k; j += 2) {
            dp[0][j] = -prices[0];
        }
        for (int i = 1; i < dp.size(); i++) {
            for (int j = 1; j < 2 * k + 1; j++) {
                // j偶数 → 1，j奇数 → -1
                int coeff = (j % 2 == 0) ? 1 : -1;
                dp[i][j] = max(dp[i - 1][j], dp[i - 1][j - 1] + coeff * prices[i]);
            }
        }
        return dp[prices.size() - 1][2 * k];
    }

    int maxProfit(vector<int> &prices) {
        /*

        0:第一次持有股票
        1:第一次不持有股票
        2:第二次持有股票
        3:第二次不持有股票*/
        vector<vector<int> > dp(prices.size(), vector<int>(4,INT_MIN));
        dp[0][0] = -prices[0];
        dp[0][1] = 0;
        dp[0][2] = -prices[0];
        dp[0][3] = 0;

        for (int i = 1; i < dp.size(); i++) {
            dp[i][0] = max(dp[i - 1][0], -prices[i]);
            dp[i][1] = max(dp[i - 1][1], dp[i][0] + prices[i]);
            dp[i][2] = max(dp[i - 1][2], dp[i][1] - prices[i]);
            dp[i][3] = max(dp[i - 1][3], dp[i][2] + prices[i]);
        }
        return dp[prices.size() - 1][3];
    }

    int maxProfit(vector<int> &prices) {
        vector<vector<int> > dp(prices.size(), vector<int>(2,INT_MIN));
        dp[0][0] = -prices[0];
        dp[0][1] = 0;
        //dp[i][0]: 持有当天的股票(可以是当天买入，也可以是之前买入的)
        //dp[i][1]: 不持有当天的股票（可以是当天卖出，也可以是之前就已经卖出）
        for (int i = 1; i < dp.size(); i++) {
            dp[i][0] = max(dp[i - 1][0], dp[i - 1][1] - prices[i]);
            dp[i][1] = max(dp[i - 1][1], dp[i][0] + prices[i]);
        }
        return dp[prices.size() - 1][1];
    }

    int maxProfit(vector<int> &prices) {
        vector<vector<int> > dp(prices.size(), vector<int>(2,INT_MIN));
        dp[0][0] = -prices[0];
        dp[0][1] = 0;
        //dp[i][0]: 持有当天的股票(可以是当天买入，也可以是之前买入的)
        //dp[i][1]: 不持有当天的股票（可以是当天卖出，也可以是之前就已经卖出）
        for (int i = 1; i < dp.size(); i++) {
            dp[i][0] = max(dp[i - 1][0], -prices[i]);
            dp[i][1] = max(dp[i - 1][1], dp[i][0] + prices[i]);
        }
        return dp[prices.size() - 1][1];
    }

    int rob(TreeNode *root) {
        vector<int> result = robtree(root);
        return max(result[0], result[1]);
    }

    vector<int> robtree(TreeNode *root) {
        if (root == nullptr) return {0, 0};
        vector<int> left(robtree(root->left));
        vector<int> right(robtree(root->right));
        int val1 = root->val + left[0] + right[0];
        int val2 = max(left[1], left[0]) + max(right[0], right[1]);
        return {val2, val1};
    }

    int rob(vector<int> &nums) {
        if (nums.size() == 1) return nums[0];
        if (nums.size() == 2) return max(nums[0], nums[1]);
        return max(robRange(nums, 0, nums.size() - 2), robRange(nums, 1, nums.size() - 1));
    }

    int robRange(vector<int> &nums, int start, int end) {
        vector<int> dp(nums.size());
        if (start == end) return nums[start];
        dp[start] = nums[start];
        dp[start + 1] = max(nums[start], nums[start + 1]);
        for (int i = start + 2; i <= end; i++) {
            dp[i] = max(dp[i - 2] + nums[i], dp[i - 1]);
        }
        return dp[end];
    }

    bool wordBreak(string s, vector<string> &wordDict) {
        unordered_set<string> word_set(wordDict.begin(), wordDict.end());
        vector<bool> dp(s.size() + 1, false);
        dp[0] = true;
        for (int i = 0; i < s.size() + 1; i++) {
            for (int j = 0; j < i; j++) {
                string word = s.substr(j, i);
                if (dp[j] && word_set.find(word) != word_set.end()) {
                    dp[i] = true;
                }
            }
        }
        return dp[s.size()];
    }

    int numSquares(int n) {
        vector<int> dp(n + 1,INT_MAX);
        dp[0] = 0;
        for (int i = 0; i <= n; i++) {
            //遍历背包
            for (int j = 0; j * j <= i; j++) {
                dp[i] = min(dp[i], dp[i - j * j] + 1);
            }
        }
        return dp[n];
    }

    int coinChange(vector<int> &coins, int amount) {
        vector<int> dp(amount + 1,INT_MAX);
        dp[0] = 0;
        for (int i = 0; i < coins.size(); i++) {
            for (int j = coins[i]; j <= amount; j++) {
                if (dp[j - coins[i]] != INT_MAX) {
                    dp[j] = min(dp[j], dp[j - nums[i]] + 1);
                }
            }
        }
        if (amount == INT_MAX) return -1;
        return dp[amount];
    }

    int combinationSum4(vector<int> &nums, int target) {
        vector<int> dp(target + 1);
        dp[0] = 1;
        for (int i = 0; i < target + 1; i++) {
            for (int j = 0; j < nums.size(); j++) {
                if (i >= nums[j]) {
                    dp[i] += dp[i - nums[j]];
                }
            }
        }
        return dp[target];
    }

    int change(int amount, vector<int> &coins) {
        vector<vector<int> > dp(coins.size(), vector<int>(amount + 1, 0));
        for (int i = 0; i < dp[1].size(); i++) {
            if (i % coins[0] == 0) dp[0][i] = 1;
        }
        for (int j = 0; j < coins.size(); j++) {
            dp[j][0] = 1;
        }

        for (int i = 1; i < dp.size(); i++) {
            for (int j = 1; j < dp[0].size(); j++) {
                if (coins[i] > j) dp[i][j] = dp[i - 1][j];
                else dp[i][j] = dp[i - 1][j] + dp[i][j - coins[i]];
            }
        }
        return dp[coins.size() - 1][amount];
    }

    int findMaxForm(vector<string> &strs, int m, int n) {
        vector<vector<int> > dp(m + 1, vector<int>(n + 1, 0));
        for (auto str: strs) {
            int x = 0;
            int y = 0;
            for (char ch: str) {
                if (ch == '0') x++;
                else y++;
            }
            for (int i = m; i >= x; i--) {
                for (int j = n; j >= y; j--) {
                    dp[i][j] = max(dp[i][j], dp[i - x][j - y] + 1);
                }
            }
        }
        return dp[m][n];
    }

    int findTargetSumWays(vector<int> &nums, int target) {
        int sum = accumulate(nums.begin(), nums.end(), 0);
        if ((sum + target) % 2 == 0 || target > sum) return 0;
        int newTarget = (sum + target) / 2;
        vector<int> dp(nums.size() + 1);
        for (int i = 0; i < nums.size(); i++) {
            for (int j = newTarget; j >= nums[i]; j--) {
                dp[j] += dp[j] + dp[j - nums[i]];
            }
        }
        return dp[nums.size()];
    }

    int lastStoneWeightII(vector<int> &stones) {
        int sum = accumulate(stones.begin(), stones.end(), 0);
        int target = sum / 2;
        vector<int> dp(sum + 1);
        for (int i = 0; i < stones.size(); i++) {
            for (int j = target; j >= stones[i]; j--) {
                dp[j] = max(dp[j], dp[j - stones[i]] + stones[i]);
            }
        }
        return sum - dp[target] * 2;
    }

    bool canPartition(vector<int> &nums) {
        int sum = accumulate(nums.begin(), nums.end(), 0);
        if (sum % 2 != 0) return false;
        sum = sum / 2;
        vector<int> dp(sum + 1);
        for (int i = 0; i < nums.size(); i++) {
            for (int j = dp.size(); j >= nums[i]; j--) {
                dp[j] = max(dp[j], dp[j - nums[i]] + nums[i]);
            }
        }
        if (dp[sum] = sum) return true;
    }

    int numTrees(int n) {
        vector<int> dp(n + 1);
        dp[1] = 1;
        dp[0] = 1;
        for (int i = 2; i < dp.size(); i++) {
            for (int j = 0; j < i; j++) {
                dp[i] += dp[j] * dp[i - j - 1];
            }
        }
        return dp[n];
    }

    int integerBreak(int n) {
        vector<int> dp(n + 1);
        dp[2] = 1;
        for (int i = 3; i < dp.size(); i++) {
            for (int j = 1; j < i - 1; j++) {
                dp[i] = max(dp[i], max(dp[i - j] * j, (i - j) * j));
            }
        }
        return dp[n];
    }

    int uniquePathsWithObstacles(vector<vector<int> > &obstacleGrid) {
        vector<vector<int> > dp(obstacleGrid.size(), vector<int>(obstacleGrid[0].size(), 0));
        for (int i = 0; i < obstacleGrid.size() && obstacleGrid[i][0] == 0; i++) dp[i][0] = 1;
        for (int j = 0; j < obstacleGrid[0].size() && obstacleGrid[0][j] == 0; j++) dp[0][j] = 1;
        for (int i = 1; i < obstacleGrid.size(); i++) {
            for (int j = 1; j < obstacleGrid[0].size(); j++) {
                if (obstacleGrid[i][j] == 1) continue;
                dp[i][j] = dp[i - 1][j] + dp[i][j - 1];
            }
        }
        return dp[obstacleGrid.size() - 1][obstacleGrid[0].size() - 1];
    }

    int uniquePaths(int m, int n) {
        vector<vector<int> > dp(m, vector<int>(n, 1));
        for (int i = 1; i < m; i++) {
            for (int j = 1; j < n; j++) {
                dp[i][j] = dp[i - 1][j] + dp[i][j - 1];
            }
        }
        return dp[m - 1][n - 1];
    }

    int minCostClimbingStairs(vector<int> &cost) {
        vector<int> dp(cost.size(), 0);
        for (int i = 2; i < dp.size(); i++) {
            dp[i] = min(dp[i - 1] + cost[i - 1], dp[i - 2] + cost[i - 2]);
        }
        return dp.back();
    }

    int climbStairs(int n) {
        vector<int> dp(n + 1);
        dp[0] = 0;
        dp[1] = 1;
        for (int i = 2; i < dp.size(); i++) {
            dp[i] = dp[i - 1] + dp[i - 2];
        }
        return dp[n];
    }

    int fib(int n) {
        vector<int> fib(n + 1);
        fib[0] = 0;
        fib[1] = 1;
        for (int i = 2; i < fib.size(); i++) {
            fib[i] = fib[i - 1] + fib[i - 2];
        }
        return fib[n];
    }

    int result = 0;

    int travseral_minCamera(TreeNode *root) {
        if (root == nullptr) return 2;

        //0:摄像头 1：无覆盖 2:有覆盖
        int left = travseral_minCamera(root->left);
        int right = travseral_minCamera(root->right);
        if (left == 2 && right == 2) return 1;
        if (left == 1 || right == 1) {
            result++;
            return 0;
        }
        if (left == 0 || right == 0) return 2;
        return -1;
    }

    int minCameraCover(TreeNode *root) {
        int res = travseral_minCamera(root);
        if (res == 1) result++;
        return result;
    }

    int monotoneIncreasingDigits(int n) {
        string strnum = to_string(n);
        int flag = strnum.size();
        for (int i = strnum.size() - 1; i >= 1; i--) {
            if (strnum[i - 1] > strnum[i]) {
                strnum[i - 1]--;
                flag = i;
            }
        }
        for (int i = flag; i < strnum.size(); i++) {
            strnum[i] = '9';
        }
        return stoi(strnum);
    }

    static bool cmp(vector<int> &a, vector<int> &b) {
        return a[0] < b[0];
    }

    vector<vector<int> > merge(vector<vector<int> > &intervals) {
        vector<vector<int> > res;
        sort(intervals.begin(), intervals.end(), cmp);
        res.push_back(intervals[0]);
        for (int i = 1; i < intervals.size(); i++) {
            if (res.back()[1] > intervals[i][0]) {
                res.back()[1] = max(res.back()[1], intervals[i][1]);
            }
            res.push_back(intervals[i]);
        }
        return res;
    }

    vector<int> partitionLabels(string s) {
        vector<int> hash(27, 0);
        for (int i = 0; i < s.size(); i++) {
            hash[s[i] - 'a'] = i;
        }
        vector<int> res;
        int right = 0;
        int left = 0;
        for (int i = 0; i < s.size(); i++) {
            right = max(right, hash[s[i] - 'a']);
            if (right == i) {
                res.push_back(right - left + 1);
                left = i + 1;
            }
        }
        return res;
    }

    static bool cmp(vector<int> &a, vector<int> &b) {
        return a[0] < b[0];
    }

    int eraseOverlapIntervals(vector<vector<int> > &intervals) {
        int count = 0;
        sort(intervals.begin(), intervals.end(), cmp);
        for (int i = 1; i < intervals.size(); i++) {
            if (intervals[i][0] < intervals[i - 1][1]) {
                count++;
                intervals[i][1] = min(intervals[i - 1][1], intervals[i][1]);
            }
        }
        return count;
    }


    int findMinArrowShots(vector<vector<int> > &points) {
        sort(points.begin(), points.end(), cmp);
        int res = 1;
        for (int i = 1; i < points.size() - 1; i++) {
            if (points[i][0] < points[i - 1][1]) {
                res++;
            } else {
                points[i][1] = min(points[i - 1][1], points[i][1]);
            }
        }
        return res;
    }

    vector<vector<int> > reconstructQueue(vector<vector<int> > &people) {
        sort(people.begin(), people.end(), cmp);
        vector<vector<int> > res;
        for (auto people1: people) {
            int index = people1[1];
            res.insert(res.begin() + index, people1);
        }
        return res;
    }

    bool lemonadeChange(vector<int> &bills) {
        int num5 = 0;
        int num10 = 0;
        for (int bill: bills) {
            if (bill == 5) {
                num5++;
            }

            if (bill == 10) {
                if (num5 < 1) return false;
                num5--;
                num10++;
            }
            if (bill == 20) {
                if (num10 >= 1 && num5 >= 1) {
                    num10--;
                    num5--;
                } else if (num5 >= 3) {
                    num5 -= 3;
                } else {
                    return false;
                }
            }
            return true;
        }
    }

    int candy(vector<int> &ratings) {
        vector<int> candy1(ratings.size(), 1);
        vector<int> candy2(ratings.size(), 1);
        for (int i = 1; i < ratings.size(); i++) {
            if (ratings[i] > ratings[i - 1]) candy1[i] = candy1[i - 1] + 1;
        }
        for (int i = ratings.size() - 1; i >= 0; i--) {
            if (ratings[i - 1] > ratings[i]) candy2[i - 1] = candy2[i] + 1;
        }
        int sum = 0;
        for (int i = 0; i < candy1.size(); i++) {
            sum += max(candy1[i], candy2[i]);
        }
        return sum;
    }

    int canCompleteCircuit(vector<int> &gas, vector<int> &cost) {
        vector<int> rest;
        for (int i = 0; i < gas.size(); i++) {
            rest[i] = gas[i] - cost[i];
        }
        int curgas = 0;
        int start = 0;
        int tol = 0;
        for (int i = 0; i < rest.size(); i++) {
            tol += rest[i];
            curgas += rest[i];
            if (curgas < 0) {
                curgas = 0;
                start = i + 1;
            }
        }
        if (tol < 0)return -1;
        return start;
    }

    /*static bool cmp(int a ,int b) {
        return abs(a)>abs(b);
    }*/
    int largestSumAfterKNegations(vector<int> &nums, int k) {
        sort(nums.begin(), nums.end(), cmp);
        int sum = 0;
        for (int i = 0; i < nums.size(); i++) {
            if (k > 0) {
                if (nums[i] < 0) sum -= nums[i], k--;
                else {
                    if (k % 2 == 0)sum -= nums[i], k = 0;
                    else sum += nums[i], k = 0;
                }
            } else {
                sum += nums[i];
            }
        }
        return sum;
    }

    int jump(vector<int> &nums) {
        int curdistence = 0;
        int nextdistence = 0;
        int ans = 0;
        for (int i = 0; i < nums.size(); i++) {
            nextdistence = max(nextdistence, i + nums[i]);
            if (curdistence == i) {
                ans++;
                curdistence = nextdistence;
                if (curdistence >= nums.size() - 1) break;
            }
        }
        return ans;
    }

    bool canJump(vector<int> &nums) {
        int cover = 0;
        for (int i = 0; i <= cover; i++) {
            cover = max(cover, i + nums[i]);
            if (cover >= nums.size() - 1) return true;
        }
        return false;
    }

    int maxProfit(vector<int> &prices) {
        int maxProfit = 0;
        for (int i = 0; i < prices.size() - 1; i++) {
            int profit = prices[i + 1] - prices[i];
            if (profit > 0) maxProfit += profit;
        }
        return maxProfit;
    }

    int maxSubArray(vector<int> &nums) {
        int res = INT_MIN;
        int count = 0;
        for (int i = 0; i < nums.size(); i++) {
            count += nums[i];
            if (count > res) res = count;
            if (count < 0) count = 0;
        }
        return res;
    }

    int wiggleMaxLength(vector<int> &nums) {
        if (nums.size() <= 1) return nums.size();
        int preDiff = 0;
        int curDiff = 0;
        int res = 1;
        for (int i = 1; i < nums.size(); i++) {
            curDiff = nums[i - 1] - nums[i];
            if ((preDiff <= 0 && curDiff > 0) || (preDiff >= 0 && curDiff < 0)) {
                res++;
                preDiff = curDiff;
            }
        }
        return res;
    }

    int findContentChildren(vector<int> &g, vector<int> &s) {
        sort(g.begin(), g.end());
        sort(s.begin(), s.end());
        int cookie = s.size() - 1;
        int res = 0;
        for (int i = g.size() - 1; i > 0; i--) {
            if (s[cookie] >= g[i] && cookie > 0) {
                res++;
                cookie--;
            }
        }
        return res;
    }

    bool isValid(int row, int col, char val, vector<vector<char> > &board) {
        for (int i = 0; i < 9; i++) {
            // 判断行里是否重复
            if (board[row][i] == val) {
                return false;
            }
        }
        for (int j = 0; j < 9; j++) {
            // 判断列里是否重复
            if (board[j][col] == val) {
                return false;
            }
        }
        int startRow = (row / 3) * 3;
        int startCol = (col / 3) * 3;
        for (int i = startRow; i < startRow + 3; i++) {
            // 判断9方格里是否重复
            for (int j = startCol; j < startCol + 3; j++) {
                if (board[i][j] == val) {
                    return false;
                }
            }
        }
        return true;
    }

    bool solveSudoku_backtracking(vector<vector<char> > &board) {
        for (int i = 0; i < board.size(); i++) {
            for (int j = 0; j < board.size(); j++) {
                if (board[i][j] == '.') {
                    for (char c = '1'; c <= '9'; c++) {
                        if (isValid(i, j, c, board)) {
                            board[i][j] = c;
                            if (solveSudoku_backtracking(board)) return true;
                            board[i][j] = '.';
                        }
                    }
                    return false;
                }
            }
        }
        return true;
    }

    void solveSudoku(vector<vector<char> > &board) {
        solveSudoku_backtracking(board);
    }

    vector<vector<string> > res;

    void solveNQueens_backtracking(int n, int row, vector<string> chessboard) {
        if (row == n) {
            res.push_back(chessboard);
            return;
        }
        for (int i = 0; i < n; i++) {
            if (isvalid(n, row, i, chessboard)) {
                chessboard[row][i] = 'Q';
                solveNQueens_backtracking(n, row + 1, chessboard);
                chessboard[row][i] = '.';
            } else {
                continue;
            }
        }
    }

    vector<vector<string> > solveNQueens(int n) {
        vector<string> chessboard(n);
        solveNQueens_backtracking(n, 0, chessboard);
        return res;
    }

    bool isvalid(int n, int row, int col, vector<string> chessboard) {
        for (int i = 0; i < row; i++) {
            if (chessboard[i][col] == 'Q') return false;
        }
        for (int i = row - 1, j = col - 1; i > 0, j > 0; i--, j--) {
            if (chessboard[i][j] == 'Q') return false;
        }
        for (int i = row - 1, j = col + 1; i > 0, j < n; i--, j++) {
            if (chessboard[i][j] == 'Q') return false;
        }
        return true;
    }

    //vector<int> ans;

    void permuteUnique_backtracking(vector<int> &nums, vector<bool> &used) {
        if (ans.size() == nums.size()) {
            res.push_back(ans);
            return;
        }

        for (int i = 0; i < nums.size(); i++) {
            if (i > 0 && !used[i - 1] && nums[i] == nums[i - 1] || used[i]) continue;
            else {
                used[i] = true;
                ans.push_back(nums[i]);
                permuteUnique_backtracking(nums, used);
                used[i] = false;
                ans.pop_back();
            }
        }
    }

    vector<vector<int> > permuteUnique(vector<int> &nums) {
        sort(nums.begin(), nums.end());
        vector<bool> used(nums.size());
        permuteUnique_backtracking(nums, used);
        return res;
    }

    void premute_backtracking(vector<int> &nums, vector<bool> used) {
        if (ans.size() == nums.size()) {
            res.push_back(ans);
            return;
        }

        for (int i = 0; i < nums.size(); i++) {
            if (used[i]) continue;
            else {
                used[i] = true;
                ans.push_back(nums[i]);
                premute_backtracking(nums, used);
                used[i] = false;
                ans.pop_back();
            }
        }
    }

    vector<vector<int> > permute(vector<int> &nums) {
        vector<bool> used(nums.size());
        premute_backtracking(nums, used);
        return res;
    }


    void findSubsequences_backtracking(vector<int> &nums, int startIndex) {
        if (ans.size() > 1) {
            res.push_back(ans);
        }
        if (startIndex > nums.size()) return;
        unordered_set<int> uset; //对本层元素进行去重
        for (int i = startIndex; i < nums.size(); i++) {
            if ((!ans.empty() && nums[i] < ans.back()) || uset.find(nums[i]) != uset.end()) {
                continue;
            }
            uset.insert(nums[i]);
            ans.push_back(nums[i]);
            findSubsequences_backtracking(nums, i + 1);
            ans.pop_back();
        }
    }

    vector<vector<int> > findSubsequences(vector<int> &nums) {
        findSubsequences_backtracking(nums, 0);
        return res;
    }

    void subsetsWithDup_backtracking(vector<int> &nums, int startIndex) {
        res.push_back(ans);
        if (startIndex > nums.size()) return;
        for (int i = startIndex; i < nums.size(); i++) {
            if (i > startIndex && nums[i] == nums[i - 1]) continue;
            else {
                ans.push_back(nums[i]);
                subsets_backtracking(nums, i + 1);
                ans.pop_back();
            }
        }
    }

    vector<vector<int> > subsetsWithDup(vector<int> &nums) {
        sort(nums.begin(), nums.end());
        subsets_backtracking(nums, 0);
        return res;
    }

    void subsets_backtracking(vector<int> &nums, int startIndex) {
        res.push_back(ans);
        if (startIndex >= nums.size()) {
            return;
        }
        for (int i = startIndex; i < nums.size(); i++) {
            ans.push_back(nums[i]);
            subsets_backtracking(nums, i + 1);
            ans.pop_back();
        }
    }

    vector<vector<int> > subsets(vector<int> &nums) {
        subsets_backtracking(nums, 0);
    }

    //vector<string> res;
    void restoreIpAddresses_backtracking(string &s, int startIndex, int pointNum) {
        if (pointNum == 3) {
            if (isValid(s, startIndex, s.size() - 1)) {
                res.push_back(s);
            }
            return;
        }
        for (int i = startIndex; i < s.size(); i++) {
            if (isValid(s, startIndex, i)) {
                s.insert(s.begin() + i + 1, '.');
                pointNum++;
                restoreIpAddresses_backtracking(s, i + 2, pointNum);
                pointNum--;
                s.erase(s.begin() + i + 1);
            } else {
                break ;
            }
        }
    }

    vector<string> restoreIpAddresses(string s) {
        restoreIpAddresses_backtracking(s, 0, 0);
        return res;
    }

    bool isValid(const string &s, int start, int end) {
        if (start > end) {
            return false;
        }
        if (s[start] == '0' && start != end) {
            // 0开头的数字不合法
            return false;
        }
        int num = 0;
        for (int i = start; i <= end; i++) {
            if (s[i] > '9' || s[i] < '0') {
                // 遇到非数字字符不合法
                return false;
            }
            num = num * 10 + (s[i] - '0');
            if (num > 255) {
                // 如果大于255了不合法
                return false;
            }
        }
        return true;
    }

    vector<string> path;

    void partition_backtracking(string s, int startIndex) {
        if (startIndex >= s.size()) {
            res.push_back(path);
            return;
        }

        for (int i = startIndex; i < s.size(); i++) {
            if (isPalindrome(s, startIndex, i)) {
                path.push_back(s.substr(startIndex, i - startIndex + 1));
            } else {
                continue;
            }
            partition_backtracking(s, i + 1);
            path.pop_back();
        }
    }

    vector<vector<string> > partition(string s) {
        partition_backtracking(s, 0);
        return res;
    }

    //判断是否是会文字符串
    bool isPalindrome(const string &s, int start, int end) {
        for (int i = start, j = end; i < j; i++, j--) {
            if (s[i] != s[j]) return false;
        }
        return true;
    }

    vector<int> nums;
    //vector<vector<int> > res;

    void combinationSum_backtracking(vector<int> &candidates, int target, int startindex) {
        if (accumulate(nums.begin(), nums.end(), 0) == target) {
            res.push_back(nums);
            return;
        } else if (accumulate(nums.begin(), nums.end(), 0) > target) {
            return;
        }


        for (int i = startindex; i < candidates.size(); i++) {
            if (i > startindex && candidates[i] == candidates[i - 1]) continue;
            nums.push_back(candidates[i]);
            combinationSum_backtracking(candidates, target, i + 1);
            nums.pop_back();
        }
    }

    vector<vector<int> > combinationSum2(vector<int> &candidates, int target) {
        sort(candidates.begin(), candidates.end());
        combinationSum_backtracking(candidates, target, 0);
        return res;
    }

    /*vector<int> nums;
    vector<vector<int> > res;

    void combinationSum_backtracking(vector<int> &candidates, int target, int startindex) {
        if (accumulate(nums.begin(), nums.end(), 0) == target) {
            res.push_back(nums);
            return;
        } else if (accumulate(nums.begin(), nums.end(), 0) > target) {
            return;
        }


        for (int i = startindex; i < candidates.size(); i++) {
            nums.push_back(candidates[i]);
            combinationSum_backtracking(candidates, target, i + 1);
            nums.pop_back();
        }
    }

    vector<vector<int> > combinationSum(vector<int> &candidates, int target) {
        combinationSum_backtracking(candidates,target,0);
        return res;
    }*/

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
    //vector<string> res;
    //string path;

    void letterCombination_backtracking(string digits, int index) {
        if (path.size() == digits.size()) {
            res.push_back(path);
            return;
        }
        string letters = letterMap[digits[index] - '0'];
        for (int i = 0; i < letters.size(); i++) {
            path.push_back(letters[i]);
            letterCombination_backtracking(digits, index + 1);
            path.pop_back();
        }
    }

    vector<string> letterCombinations(string digits) {
        letterCombination_backtracking(digits, 0);
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
    int sum = 0;

    void convert_BST(TreeNode *root) {
        if (root == nullptr) return;
        convertBST(root->right);
        sum += root->val;
        root->val = sum;
        convertBST(root->left);
    }

    TreeNode *convertBST(TreeNode *root) {
        convert_BST(root);
        return root;
    }


    TreeNode *sortedArrayToBST(vector<int> &nums) {
        if (nums.empty()) return nullptr;
        TreeNode *root = new TreeNode(nums[nums.size() / 2]);
        vector<int> left(nums.begin(), nums.begin() + nums.size() / 2);
        vector<int> right(nums.begin() + nums.size() / 2 + 1, nums.end());
        root->left = sortedArrayToBST(left);
        root->right = sortedArrayToBST(right);
        return root;
    }

    TreeNode *trimBST(TreeNode *root, int low, int high) {
        if (root == nullptr) return nullptr;
        if (root->val < low) return trimBST(root->right, low, high);
        if (root->val > high) return trimBST(root->left, low, high);
        root->left = trimBST(root->right, low, high);
        root->right = trimBST(root->left, low, high);
        return root;
    }

    TreeNode *deleteNode(TreeNode *root, int key) {
        if (root == nullptr) return nullptr;
        if (root->val == key) {
            TreeNode *left = root->left;
            TreeNode *right = root->right;
            delete(root);
            if (left == nullptr && right == nullptr) return nullptr;
            if (left && !right) return left;
            if (!left && right) return right;
            if (left && right) {
                TreeNode *cur = right;
                while (cur->left != nullptr) {
                    cur = cur->left;
                }
                cur->left = left;
                return right;
            }
        }
        root->left = deleteNode(root->left, key);
        root->right = deleteNode(root->right, key);
        return root;
    }

    TreeNode *insertIntoBST(TreeNode *root, int val) {
        if (root == nullptr) {
            TreeNode *node = new TreeNode(val);
            return node;
        }
        if (val > root->val) root->right = insertIntoBST(root->right, val);
        if (val < root->val) root->left = insertIntoBST(root->left, val);
        return root;
    }

    //二叉搜索树
    TreeNode *lowestCommonAncestor(TreeNode *root, TreeNode *p, TreeNode *q) {
        if (root == nullptr) return nullptr;
        if (root->val > q->val && root->val > p->val) return lowestCommonAncestor(root->left, p, q);
        else if (root->val < q->val && root->val < p->val) return lowestCommonAncestor(root->right, p, q);
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
    void findmode(TreeNode *root, vector<int> &res, int &maxCount, int &curVal, int &curCount) {
        if (root == nullptr) return;
        findmode(root->left, res, maxCount, curVal, curCount);
        if (root->val == curVal) curCount++;
        else curVal = root->val, curCount = 0;
        if (curCount == maxCount) res.push_back(root->val);
        else if (curCount > maxCount) {
            maxCount = curCount;
            res.clear();
            res.push_back(root->val);
        }
        findmode(root->right, res, maxCount, curVal, curCount);
    }

    vector<int> findMode(TreeNode *root) {
        vector<int> res;
        int maxCount = -1, curVal = -1, curCount = 0;
        findmode(root, res, maxCount, curVal, curCount);
        return res;
    }

    TreeNode *pre = nullptr;
    int result = INT_MAX;

    void travsalMin(TreeNode *root) {
        if (root == nullptr) return;
        travsalMin(root->left);
        if (pre) result = min(result, abs(root->val - pre->val));
        pre = root;
        travsalMin(root->right);
    }

    int getMinimumDifference(TreeNode *root) {
        travsalMin(root);
        return result;
    }

    bool isValidBST(TreeNode *root) {
        return check(root,LLONG_MIN,LLONG_MAX);
    }

    bool check(TreeNode *root, long long low, long long high) {
        if (root == nullptr) return true;
        if (root->val < low || root->val > high) return false;
        return check(root->left, low, root->val) && check(root->right, root->val, high);
    }

    TreeNode *searchBST(TreeNode *root, int val) {
        if (root == nullptr)return nullptr;
        if (root->val == val) return root;
        else if (root->val > val) return searchBST(root->left, val);
        else {
            return searchBST(root->right, val);
        }
    }

    TreeNode *mergeTrees(TreeNode *root1, TreeNode *root2) {
        if (root1 == nullptr) return root2;
        if (root2 == nullptr) return root1;
        TreeNode *node = new TreeNode(root1->val + root2->val);
        node->left = mergeTrees(root1->left, root2->left);
        node->right = mergeTrees(root1->right, root2->right);
        return node;
    }

    TreeNode *constructMaximumBinaryTree(vector<int> &nums) {
        if (nums.empty()) return nullptr;
        int max = -1, maxIndex = 0;
        for (int i = 0; i < nums.size(); i++) {
            if (nums[i] > max) max = nums[i], maxIndex = i;
        }
        TreeNode *node = new TreeNode(max);
        vector<int> leftTree(nums.begin(), nums.begin() + maxIndex);
        vector<int> rightTree(nums.begin() + maxIndex + 1, nums.end());
        node->left = constructMaximumBinaryTree(leftTree);
        node->right = constructMaximumBinaryTree(rightTree);
        return node;
    }

    TreeNode *buildTree(vector<int> &inorder, vector<int> &postorder) {
        if (inorder.empty()) return nullptr;
        int val = postorder.back();
        TreeNode *node;
        node->val = val;
        //寻找切割点
        int divide;
        for (divide = 0; divide < inorder.size(); divide++) {
            if (inorder[divide] == val) break;
        }
        //获得左右子树的数组
        vector<int> rightInoder(inorder.begin() + divide + 1, inorder.end());
        vector<int> leftInorder(inorder.begin(), inorder.begin() + divide);
        vector<int> leftPost(postorder.begin(), postorder.begin() + leftInorder.size());
        vector<int> rightPost(postorder.begin() + leftInorder.size(), postorder.end() - 1);
        node->left = buildTree(leftInorder, leftPost);
        node->right = buildTree(rightInoder, rightPost);
        return node;
    }


    bool pathTravsal(TreeNode *root, int pathSum, int targetsum) {
        if (root == nullptr) return false;
        if (root->left == nullptr && root->right == nullptr) if (pathSum + root->val == targetsum) return true;
        return pathTravsal(root->left, pathSum + root->val, targetsum) || pathTravsal(
                   root->right, pathSum + root->val, targetsum);
    }

    bool hasPathSum(TreeNode *root, int targetSum) {
        return pathTravsal(root, 0, targetSum);
    }

    int maxDepth = INT_MIN;
    int result;

    void travasal(TreeNode *root, int depth) {
        if (root->left == nullptr && root->right == nullptr) {
            if (depth > maxDepth) {
                maxDepth = depth;
                result = root->val;
            }
            return;
        }
        if (root->left) travasal(root->left, depth + 1);
        if (root->right) travasal(root->right, depth + 1);
    }

    int findBottomLeftValue(TreeNode *root) {
        travasal(root, 1);
        return result;
    }


    int sumOfLeftLeaves(TreeNode *root) {
        if (root == nullptr) return 0;
        int sum = 0;
        if (root->left != nullptr && root->left->left == nullptr && root->left->right == nullptr)
            sum += root->left->val;
        sum += sumOfLeftLeaves(root->left);
        sum += sumOfLeftLeaves(root->right);
        return sum;
    }

    bool isSameTree(TreeNode *p, TreeNode *q) {
        if (p == nullptr && q == nullptr) return true;
        else if (p != nullptr && q != nullptr) {
            if (p->val == q->val) {
                return isSameTree(p->left, q->left) && isSameTree(p->right, q->right);
            } else {
                return false;
            }
        } else {
            return false;
        }
    }

    void travasal(TreeNode *root, string path, vector<string> &result) {
        path += to_string(root->val);
        if (root->left == nullptr && root->right == nullptr) {
            result.push_back(path);
            return;
        }
        if (root->right) travasal(root->right, path + "->", result);
        if (root->left) travasal(root->left, path + "->", result);
    }

    vector<string> binaryTreePaths(TreeNode *root) {
        string path;
        vector<string> result;
        if (root == nullptr) return result;
        travasal(root, path, result);
        return result;
    }

    bool isBalanced(TreeNode *root) {
        if (root == nullptr) return true;
        int left = depth(root->left);
        int right = depth(root->right);
        if (abs(left - right) > 1) return false;
        return isBalanced(root->right) && isBalanced(root->left);
    }

    int depth(TreeNode *root) {
        if (root == nullptr) return 0;
        return max(depth(root->right), depth(root->left)) + 1;
    }

    //完全二叉树求节点数量
    int countNodes(TreeNode *root) {
        if (root == nullptr) return 0;
        TreeNode *left = root->left;
        TreeNode *right = root->right;
        int rightHeigth = 0, leftHeigth = 0;
        while (right) {
            right = right->right;
            rightHeigth++;
        }
        while (left) {
            left = left->left;
            leftHeigth++;
        }
        if (rightHeigth == leftHeigth) return (2 << leftHeigth) - 1;
        return countNodes(root->left) + countNodes(root->right) + 1;
    }

    vector<vector<int> > levelOrder(TreeNode *root) {
        queue<TreeNode *> queue;
        vector<vector<int> > result;
        if (root == NULL) return result;
        queue.push(root);
        while (!queue.empty()) {
            int size = queue.size();
            vector<int> res;
            while (size--) {
                TreeNode *node = queue.front();
                queue.pop();
                if (node->left != nullptr) queue.push(node->left);
                if (node->right != nullptr) queue.push(node->right);
                res.push_back(node->val);
            }
            result.push_back(res);
        }
    }

    //迭代法遍历二叉树
    vector<int> inOrderIteration(TreeNode *root) {
        stack<TreeNode *> sk;
        vector<int> result;
        sk.push(root);
        while (!sk.empty()) {
            TreeNode *node = sk.top();
            sk.pop();
            if (node == nullptr) {
                continue;
            } else {
                result.push_back(node->val);
                sk.push(node->right);
                sk.push(node->left);
            }
        }
        return result;
    }

    vector<int> postorderTraversal(TreeNode *root) {
        vector<int> result;
        postOrder(root, result);
        return result;
    }

    void postOrder(TreeNode *root, vector<int> &result) {
        if (root == nullptr) return;
        postOrder(root->left, result);
        postOrder(root->right, result);
        result.push_back(root->val);
    }

    vector<int> preorderTraversal(TreeNode *root) {
        vector<int> result;
        preOrder(root, result);
        return result;
    }

    void preOrder(TreeNode *root, vector<int> &result) {
        if (root == nullptr) return;
        result.push_back(root->val);
        preOrder(root->left, result);
        preOrder(root->right, result);
    }

    vector<int> inorderTraversal(TreeNode *root) {
        vector<int> result;
        inOrder(root, result);
        return result;
    }

    void inOrder(TreeNode *root, vector<int> &result) {
        if (root == nullptr) return;
        inOrder(root->left, result);
        result.push_back(root->val);
        inOrder(root->right, result);
    }


    class myComparion {
    public:
        bool operator()(const pair<int, int> &lhs, const pair<int, int> &rhs) {
            return lhs.second > rhs.second;
        }
    };

    vector<int> topKFrequent(vector<int> &nums, int k) {
        map<int, int> map;
        vector<int> result;
        priority_queue<pair<int, int>, vector<pair<int, int> >, myComparion> pq;
        for (int num: nums) {
            map[num]++;
        }
        auto it = map.begin();
        for (int i = 0; i < k; i++) {
            pq.push(*it);
            ++it;
        }
        while (it != map.end()) {
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
        auto next = getNext(s);
        if (s.size() % (s.size() - next[s.size()]) == 0) return true;
        else return false;
    }

    int strStr(string haystack, string needle) {
        auto next = getNext(needle);
        for (int i = 0, j = 0; i < haystack.size(); i++) {
            //如果当前的字符不匹配，用next数组让j指向下一个匹配的字符，如果j=0且第一个字符匹配时候，j移动下一个继续下一轮匹配时
            //如果j=0但是第一个字符不相等时，那么j不动，进入下一轮，i++
            while (j > 0 && haystack[i] != needle[j]) j = next[j];
            if (haystack[i] == needle[j]) j++;
            //找到needle的末尾后，说明当前匹配的字符串已经找到，返回起点下标
            if (j == needle.size()) return i - needle.size() + 1;
        }
        return -1;
    }

    vector<int> getNext(string s) {
        vector<int> next(s.size() + 1, 0);
        for (int j = 2, i = 0; j < s.size() + 1; j++) {
            while (i > 0 && s[i] != s[j - 1]) i = next[i];
            if (s[i] == s[j - 1]) i++;
            next[j] = i;
        }
        return next;
    }

    string reverseWords(string s) {
        vector<string> vec;
        string ans;
        string str = "";
        for (int i = 0; i < s.size(); i++) {
            if (s[i] == ' ') {
                if (str == "") {
                    continue;
                } else {
                    vec.push_back(str);
                    str = "";
                }
            } else {
                str += s[i];
            }
        }
        if (str != "") vec.push_back(str);
        for (int i = vec.size() - 1; i >= 0; i--) {
            ans += vec[i];
            if (i != 0) ans += ' ';
        }
        return ans;
    }

    string reverseStr(string s, int k) {
        for (int i = 0; i < s.size(); i += 2 * k) {
            if (s.size() - i >= k) reverseStringFromNToM(s, i, i + k);
            if (s.size() - i < k) reverseStringFromNToM(s, i, s.size() - i);
        }
        return s;
    }

    void reverseStringFromNToM(string &s, int n, int m) {
        for (int i = n, j = m; i < j; i++, j--) {
            swap(s[i], s[j]);
        }
    }

    void reverseString(vector<char> &s) {
        for (int i = 0; i < s.size() / 2; i++) {
            char temp;
            temp = s[i];
            s[i] = s[s.size() - i - 1];
            s[s.size() - i - 1] = temp;
        }
    }

    vector<vector<int> > fourSum(vector<int> &nums, int target) {
        vector<vector<int> > result;
        sort(nums.begin(), nums.end());
        for (int i = 0; i < nums.size(); i++) {
            if (nums[i] > target) return result;
            for (int j = i + 1; j < nums.size(); i++) {
                if (nums[j] == nums[j - 1]) continue;
                int right = nums.size() - 1;
                int left = j + 1;
                while (left < right) {
                    if (nums[i] + nums[j] + nums[left] + nums[right] > target) right--;
                    else if (nums[i] + nums[j] + nums[left] + nums[right] < target) left++;
                    else {
                        result.push_back({nums[i], nums[j], nums[left], nums[right]});
                        while (nums[left] == nums[left + 1]) left++;
                        while (nums[right] == nums[right + 1]) right--;

                        left++;
                        right--;
                    }
                }
            }
        }
        return result;
    }

    vector<vector<int> > threeSum(vector<int> &nums) {
        vector<vector<int> > result;
        sort(nums.begin(), nums.end());
        for (int i = 0; i < nums.size(); i++) {
            if (nums[i] > 0) return result;
            if (nums[i] == nums[i - 1]) continue;
            int right = nums.size() - 1;
            int left = i + 1;
            while (left < right) {
                if (nums[i] + nums[left] + nums[right] > 0) right--;
                else if (nums[i] + nums[left] + nums[right] < 0) left++;
                else {
                    result.push_back({nums[i], nums[left], nums[right]});
                    while (nums[left] == nums[left + 1]) left++;
                    while (nums[right] == nums[right + 1]) right--;

                    left++;
                    right--;
                }
            }
        }
        return result;
    }

    bool canConstruct(string ransomNote, string magazine) {
        unordered_set<char, int> map;
        for (char ch: ransomNote) {
            map[ch]++;
        }
        for (char ch: magazine) {
            map[ch]--;
            if (map[ch] < 0) return false;
        }
        return true;
    }

    int fourSumCount(vector<int> &nums1, vector<int> &nums2, vector<int> &nums3, vector<int> &nums4) {
        unordered_set<int, int> map;
        int count = 0;
        for (int i = 0; i < nums1.size(); i++) {
            for (int j = 0; j < nums2.size(); j++) {
                map[nums1[i] + nums2[j]]++;
            }
        }
        for (int i = 0; i < nums3.size(); i++) {
            for (int j = 0; j < nums4.size(); j++) {
                int num = 0 - nums3[i] - nums4[j];
                if (map.find(num) != map.end()) {
                    count += map[num];
                }
            }
        }
        return count;
    }

    vector<int> twoSum(vector<int> &nums, int target) {
        unordered_set<int, int> map;
        for (int i = 0; i < nums.size(); i++) {
            int num = target - nums[i];
            if (map.find(num) != map.end()) {
                vector<int> ans{i, map[num]};
                return ans;
            }
            map.insert({nums[i], i});
        }
        return vector<int>(NULL);
    }


    int getSum(int n) {
        int sum = 0;
        while (n != 0) {
            sum += (n % 10) * (n % 10);
            n /= 10;
        }
        return sum;
    }

    bool isHappy(int n) {
        unordered_set<int> set;
        int sum = n;
        while (true) {
            sum = getSum(sum);
            if (sum == 1) {
                return true;
            }
            if (set.find(sum) != set.end()) {
                return false;
            } else {
                set.insert(sum);
            }
        }
    }

    bool isValid(string s) {
        stack<char> sk;
        for (char c: s) {
            if (c == '(' || c == '[' || c == '{') {
                sk.push(c);
            } else if (!sk.empty()) {
                if ((c == ')' && sk.top() == '(') || (c == ']' && sk.top() == '[') || (c == '}' && sk.top() == '{'))
                    sk.
                            pop();
                else return false;
            } else {
                return false;
            }
        }
        if (sk.empty()) return true;
        else return false;
    }

    string removeDuplicates(string s) {
        stack<char> sk;
        for (char c: s) {
            if (sk.empty()) sk.push(c);
            else if (sk.top() == c) sk.pop();
            else sk.push(c);
        }
        string str;
        while (!sk.empty()) {
            str += sk.top();
            sk.pop();
        }
        reverse(str.begin(), str.end());
        return str;
    }

    int evalRPN(vector<string> &tokens) {
        stack<int> sk;
        for (auto token: tokens) {
            if (token == "+" || token == "-" || token == "*" || token == "/") {
                int num1 = sk.top();
                sk.pop();
                int num2 = sk.top();
                sk.pop();
                int num3 = 0;
                switch (token[0]) {
                    case '+': num3 = num2 + num1;
                        break;
                    case '-': num3 = num2 - num1;
                        break;
                    case '*': num3 = num2 * num1;
                        break;
                    case '/': num3 = num2 / num1;
                        break;
                }
                sk.push(num3);
            } else {
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
        if ((!dq.empty()) && dq.front() == value) dq.pop_front();
    }

    void push(int value) {
        while ((!dq.empty()) && dq.back() < value) dq.pop_back();
        dq.push_back(value);
    }

    int getMax() {
        return dq.front();
    }
};

class Solution1 {
public:
    vector<int> maxSlidingWindow(vector<int> &nums, int k) {
        MyMaxQueue mq;
        vector<int> result;
        for (int i = 0; i < k; i++) {
            mq.push(nums[i]);
        }
        result.push_back(mq.getMax());
        for (int i = k; i < nums.size(); i++) {
            mq.pop(nums[i - k]);
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
        int result = stack2.top();
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
        return stack1.empty() && stack2.empty();
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
        int count = queue.size();
        int result;
        while (count) {
            if (count == 1) {
                result = queue.front();
                queue.pop();
                count--;
            } else {
                queue.push(queue.front());
                queue.pop();
                count--;
            }
        }
        return result;
    }

    int top() {
        int res = this->pop();
        this->push(res);
    }

    bool empty() {
        return queue.empty();
    }
};
