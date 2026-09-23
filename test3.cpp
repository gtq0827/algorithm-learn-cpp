//
// Created by 顾天齐 on 2026/7/6.
//
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
#include "test3.h"
using namespace std;
static bool cmp(int a ,int b) {
    return abs(a)>abs(b);
}
int largestSumAfterKNegations(vector<int>& nums, int k) {
    sort(nums.begin(),nums.end(),cmp);
    int sum=0;
    for (int i=0;i<nums.size();i++) {
        if (k>0&&nums[i]<0) nums[i]=-nums[i],k--;
    }
    if (k%2!=0) nums[nums.size()-1]=-nums[nums.size()-1];
    for (int num : nums) sum+=num;
    return sum;
}
int main() {
    vector<int> nums={1,6,3,7,4,-1,-5,-9};
    largestSumAfterKNegations(nums,5);
}