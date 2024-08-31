#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <vector>
#include <algorithm>
#include <set>
#include <map>
#include <hash_map>
#include <iostream>
#include <cmath>
#include <cstdlib>
#include <string>
using namespace std;

int solution1(vector<vector<int>> triangle) { // DP 2
    int height = triangle.size();
    vector<int> sum_dp2 = triangle[height-1];
    vector<int> tempvector;
    for (int h = height - 1; h > 0; h--) 
    {
        int curr_size = triangle[h - 1].size();
        for (int c = 0; c < curr_size; c++) 
        {
            tempvector.push_back(sum_dp2[c] > sum_dp2[c + 1] ? sum_dp2[c] + triangle[h - 1][c] : sum_dp2[c + 1] + triangle[h - 1][c]);
        }
        sum_dp2=tempvector;
        tempvector.clear();
    }
    return sum_dp2[0];
}

//-----------------------------------
// calculating sub-max and sub-min together
vector<vector<int>> dp4_list[2]; // dp4_list[0]: max, dp4_list[1]: min, each has 101*101 max elements
int dp4_dfs_max(vector<string> arr) {
    int length = arr.size();
    // now start the main iteration
    for (int j = 3; j <= length; j+=2) {
        for (int k = 0; k < length-j+1; k += 2) { 
            int start = k;
            int end = k + j;
            for (int i = start; i < end-1; i += 2) {
                if (arr[i + 1] == "+") { //[k][y][x]
                    dp4_list[0][start][end - 1] = max(dp4_list[0][start][end - 1], dp4_list[0][start][i] + dp4_list[0][i + 2][end - 1]);
                    dp4_list[1][start][end - 1] = min(dp4_list[1][start][end - 1], dp4_list[1][start][i] + dp4_list[1][i + 2][end - 1]);
                }
                else { // minus
                    dp4_list[0][start][end - 1] = max(dp4_list[0][start][end - 1], dp4_list[0][start][i] - dp4_list[1][i + 2][end - 1]);
                    dp4_list[1][start][end - 1] = min(dp4_list[1][start][end - 1], dp4_list[1][start][i] - dp4_list[0][i + 2][end - 1]);
                }
            }
        }
    }
    return dp4_list[0][0][length-1];
}

int solution2(vector<string> arr) 
{ // DP 4
    int answer = -1;
    int length = arr.size();
    vector<int> vector_max;
    vector<int> vector_min;

    // loop of calculation and memoizationfor for dp4_list[k][0] (single operand) (k = 0 or 1)
    for (int i = 0; i < length; i++) {
        for (int j = 0; j < length; j++) {
            if (j == i && i % 2 == 0 && j % 2 == 0) {
                vector_max.push_back(stoi(arr[i]));
                vector_min.push_back(stoi(arr[i]));
            }
            else { // this part can push dummy elements
                vector_max.push_back(INT_MIN);
                vector_min.push_back(INT_MAX);
            }
        }
        dp4_list[0].push_back(vector_max);
        dp4_list[1].push_back(vector_min);
        vector_max.clear();
        vector_min.clear();
    }
    // call dp4_dfs_max
    answer = dp4_dfs_max(arr); // note: end is inclusive
    return answer;
}
// -------------------------------------------------------------


