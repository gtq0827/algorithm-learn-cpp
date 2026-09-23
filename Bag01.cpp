//
// Created by 顾天齐 on 2026/7/15.
//

#include "Bag01.h"
#include <cstdio>
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    // 一维dp数组实现

    // 读取 M 和 N：M物品数量，N背包容量
    int M, N;
    cin >> M >> N;

    vector<int> costs(M);
    vector<int> values(M);

    for (int i = 0; i < M; i++) {
        cin >> costs[i];
    }
    for (int j = 0; j < M; j++) {
        cin >> values[j];
    }

    // 创建一个动态规划数组dp，初始值为0
    vector<int> dp(N + 1, 0);
    cout << "===== 初始dp数组（未处理任何物品）=====\n";
    for (int k = 0; k <= N; k++) {
        cout << dp[k] << " ";
    }
    cout << "\n\n";

    // 外层循环遍历每个类型的研究材料
    for (int i = 0; i < M; ++i) {
        // 内层循环从 N 空间逐渐减少到当前研究材料所占空间
        for (int j = N; j >= costs[i]; --j) {
            // 考虑当前研究材料选择和不选择的情况，选择最大值
            dp[j] = max(dp[j], dp[j - costs[i]] + values[i]);
        }

        // 处理完第i件物品，打印当前dp全貌
        cout << "===== 处理完第" << i + 1 << "件物品 代价:" << costs[i] << " 价值:" << values[i] << " =====\n";
        for (int k = 0; k <= N; k++) {
            cout << dp[k] << " ";
        }
        cout << "\n\n";
    }

    // 输出dp[N]，即在给定 N 行李空间可以携带的研究材料最大价值
    cout << "背包容量" << N << "下最大价值：" << dp[N] << endl;

    return 0;
}