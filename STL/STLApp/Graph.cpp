#include <string>
#include <vector>
#include <algorithm>
#include <cstdio>
using namespace std;

int solution1(int n, vector<vector<int>> results) {
    int answer = 0;
    int i = 0, j = 0, k = 0;
    vector<vector<int>> adj_matrix; // -1: a lose to b, 0: a and b are in a tie(or a == b), 1: a win to b
    for (j = 0; j < n; j++) {
        vector<int> row;
        for (i = 0; i < n; i++) {
            if (i == j) {
                row.push_back(0);
            }
            else {
                row.push_back(-10000000);
            }
        }
        adj_matrix.push_back(row);
        row.clear();
    }
    int len = results.size();
    for (i = 0; i < len; i++) { // row num is winner, col num is loser
        adj_matrix[results[i][0]-1][results[i][1]-1] = 1;
        adj_matrix[results[i][1]-1][results[i][0]-1] = -1;
    }
    // floyd-warshall application
    for (k = 0; k < n; k++) { // k: transit node index
        for (j = 0; j < n; j++) { // j: 
            for (i = 0; i < n; i++) {
                if (adj_matrix[i][k] == 1 && adj_matrix[k][j] == 1) {
                    adj_matrix[i][j] = 1;
                    adj_matrix[j][i] = -1;
                }
            }
        }
    }
    // now find -10000000 from adj_matrix
    for (j = 0; j < n; j++) {
        int total = 0;
        for (i = 0; i < n; i++) {
            if (adj_matrix[i][j] == 1 || adj_matrix[i][j] == -1) {
                total += 1;
            }
        }
        if (total != n - 1) {
            answer += 1;
        }
    }
    return n - answer;
}