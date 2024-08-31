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

void stl_test( void ) {

	return;
}

int solution1(vector<int> nums) // Hash 1
{
    int answer = 0;
    set<int> hashset;
    for (int n : nums) {
        hashset.insert(n);
    }
    return answer;
}

string solution2(vector<string> participant, vector<string> completion) { // Hash 2
    string answer = "";
    hash_map<string, int> stat;
    for (string person : participant) {
        if (stat.find(person) != stat.end()) {
            stat[person] += 1;
        }
        else {
            stat.insert({ person, 1 });
        }
    }
    for (string person : completion) {
        if (stat[person] > 1) stat[person] -= 1;
        else stat.erase(person);
    }
    answer = (*stat.begin()).first;
    return answer;
}
// ----------------------------------------------
vector<int> memo[10][10];
bool sol3_dfs(int N, int number, int currentdepth) {
    if (currentdepth == 1) {
        if (memo[N][currentdepth].empty()) {
            memo[N][currentdepth].push_back(N);
        }
        if (N == number) return true;
        else return false;
    }
    if (!memo[N][currentdepth].empty()) {
        // search number and return true if there is the value(number)
        if (find(memo[N][currentdepth].begin(), memo[N][currentdepth].end(), number) != memo[N][currentdepth].end()) return true;
    }
    else {
        // build memo[N][currentdepth]
        // 1. concat (calcurating with step 2)
        int concat_all = N;
        // 2. arithmetic
        for (int i = 1; i < currentdepth; i++) {
            concat_all *= 10;
            concat_all += N;
            bool result = false;
            int j = memo[N][i].size();
            int k = memo[N][currentdepth - i].size();
            // combine and memo the result
            for (int a = 0; a < j; a++) {
                for (int b = 0; b < k; b++) {
                    int first = memo[N][i][a];
                    int second = memo[N][currentdepth - i][b];
                    memo[N][currentdepth].push_back(first + second);
                    memo[N][currentdepth].push_back(first - second);
                    memo[N][currentdepth].push_back(first * second);
                    if (second != 0) memo[N][currentdepth].push_back(first / second);
                }
            }
        }
        memo[N][currentdepth].push_back(concat_all);
        // 3. find
        if (find(memo[N][currentdepth].begin(), memo[N][currentdepth].end(), number) != memo[N][currentdepth].end()) return true;
    }
    return false;
}

int solution3(int N, int number) { // N���� ǥ��(DP 1)
    if (N < 1 || N > 9) return -1;
    if (number > 32000 || number <= 0) return -1;
    int answer = 9;
    for (int i = 1; i < 9; i++) {
        bool result = sol3_dfs(N, number, i);
        if (result) {
            answer = i;
            break;
        }
    }
    if (answer == 9) return -1;
    return answer;
}

int main(int argc, char* argv[]) {
	
	return 0;
}

#include <queue>

class Compare {
public:
    Compare( vector<int> arr) : startpoint(arr[0]), length(arr[1]) {
    }
    int startpoint;
    int length;
    bool operator<(const Compare &b) const {
        if (startpoint > b.startpoint) return false;
        else if (startpoint < b.startpoint) return true;
        return length < b.length; // if startpoint == b.startpoint
    }
};

int solution4 (vector<vector<int>> jobs) {
    int answer = 0;
    int timeline = 0;
    priority_queue < Compare > pq;
    for (vector<int> job : jobs) {
        Compare elem = Compare(job);
        pq.push(elem);
    }
    int len = pq.size();
    cout << len;
    vector<Compare> worklist;
    int currentTime = 0;
    for (int i = 0; i < len; i++) {
        if (pq.size() == 1) {
            answer += pq.top().length;
            break;
        }
        else {
            Compare elem1 = pq.top();
            currentTime = elem1.startpoint;
            if (worklist.empty()) {
                answer += elem1.length;
            }
            else {
                for (Compare elem2 : worklist) {

                }
                worklist.push_back(elem1);
            }
        }
    }
    return answer / len;
}

unsigned long long solution4(int n, vector<int> times) {
    unsigned long long answer = 0;
    int times_len = times.size();

    sort(times.begin(), times.end());

    // sort(times.begin(), times.end()); 
    // Idea: 1~ times[0] * n + 1 ���̿��� �̺� Ž���� �ϸ鼭 Ž���� ���� �� times[i]�� ���� ��(�Ҽ��� ����)�� n�� ��
    // Idea 2: ���� �ҿ� �ð��� ���� �ɻ���� ��� ����� ���ΰ�? ->
    unsigned long long minimum = 1;
    unsigned long long maximum = times[0] * ((unsigned long long)n) + 1;

    while (maximum - minimum > 1) {
        unsigned long long mid = (maximum + minimum) / 2;
        unsigned long long divided = 0;
        for (int i = 0; i < times_len; i++) {
            divided += mid / ((unsigned long long)times[i]);
        }
        if (divided >= (unsigned long long) n) {
            answer = mid;
            // there are multiple possible 'divided'
            maximum = mid;
        }
        else { // divided == n
            minimum = mid;
        }
    }

    return answer;
}

int solution5(int distance, vector<int> rocks, int n) {
    int answer = 0;
    sort(rocks.begin(), rocks.end()); // ������ ������ �ʼ�
    rocks.push_back(distance);
    int rocks_num = rocks.size();

    int dist_minimum = 1;
    int dist_maximum = distance + 1;

    while (dist_minimum < dist_maximum) {
        int mid_target = (dist_minimum + dist_maximum) / 2;

        // incremental check
        int removed_rocks = 0;
        int dist_incremental = 0;
        for (int i = 0; i < rocks_num; i++) {
            int distance = rocks[i] - dist_incremental;
            if (distance < mid_target) {
                removed_rocks++;
            }
            else {
                dist_incremental = rocks[i];
            }
        }
        // binary search
        if (removed_rocks < n) { // too little rocks removed -> decrease dist_maximum
            dist_minimum = mid_target + 1;
            answer = mid_target;
        }
        else if (removed_rocks > n) { // too many rocks removed -> increase dist_minimum
            dist_maximum = mid_target;
        }
        else { // ...maybe answer? -> memorize answer and increase dist_minimum
            dist_minimum = mid_target + 1;
            answer = mid_target;
        }
    }

    return answer;
}
int* uf_value = NULL;
int* uf_parent = NULL;

void UF_initArray(int size, int* valuelist) {
    uf_parent = new int[size];
    uf_value = new int[size];

    for (int i = 0; i < size; i++) {
        uf_parent[i] = i;
        uf_value[i] = valuelist[i];
    }

    delete[] uf_parent;
    delete[] uf_value;
    uf_parent = uf_value = NULL;
}

int UF_find_algorithm(int sourceidx) { // find parent - recursive call
    if (uf_parent[sourceidx] = sourceidx) return sourceidx;
    else uf_parent[sourceidx] = UF_find_algorithm(sourceidx);
    return uf_parent[sourceidx];
}

void UF_union_toMax_algorithm(int idx1, int idx2) { // source value < target value
    int x = UF_find_algorithm(idx1);
    int y = UF_find_algorithm(idx2);

    if (x < y) {
        uf_parent[x] = y;
    }
    else if (x > y){
        uf_parent[y] = x;
    }
    return;
}

struct cmp {
    bool operator()(vector<int> a, vector<int> b) { // bigger length get true(=going back)
        return a[1] > b[1];
    }
};

int solution6 (vector<vector<int>> jobs) {
    int answer = 0;
    int n = 0; // timeline
    int jobnum = jobs.size();
    
    priority_queue <vector<int>, vector<vector<int>>, cmp> heap;
    vector<bool> check(jobs.size(), true); // checklist of all request : all items are initialized to 'true'


    int used = 0; // processed job(incremental)
    while (used < jobnum) { // 
        // get request for this timeline
        for (int i = 0; i < jobnum; i++) {
            if (check[i] && jobs[i][0] <= n) {
                heap.push(jobs[i]); // automatically sorted to incremental length
                check[i] = false;
            }
        }
        // case : no waiting jobs -> just increase 1 to n, not increasing 'used', continue to next loop
        if (heap.empty()) {
            n++;
        }
        // case : waiting jobs exist -> increase 'n' and 'used', jump to next process check time( n += heap.top()[1])
        else 
        {
            answer += n - heap.top()[0] + heap.top()[1];
            n += heap.top()[1];
            heap.pop();
            used++; // we only processed one job: increase 1
        }
    }
    return answer / jobnum;
}

// note that alphabet has 26 characters
int solution7(string name) {
    int answer = 0;
    int strsize = name.size();
    int strsize_half = strsize / 2;
    string str_origin(strsize, 'A');

    // 0. if str_origin("AAA...") == name
    if (str_origin == name) return 0;

    // 1. find minimal movement
    // Idea 1: you must turn 'at most once'
    // Idea 2-1: Longest 'A' sequence? -> Dynamic Programming! -> No!
    // Idea 2-2: Brute Force searching? -> Yes!
    int min_movement = strsize - 1;
    for (int i = 0; i < strsize; i++)
    {
        int j = i + 1;
        for (; j < strsize; j++) {
            if (name[j] != 'A') break;
        }
        if (i + i + strsize - j < min_movement) min_movement = i + i + strsize - j;
        if (i + strsize - j + strsize - j < min_movement) min_movement = i + strsize - j + strsize - j;
    }
    answer += min_movement;

    // 2. Change each characters
    for (int i = 0; i < strsize; i++)
    {
        answer += name[i] - 'A' >= 13 ? 'Z' + 1 - name[i] : name[i] - 'A';
    }

    return answer;
}

// 전력망 분할 문제(완전 탐색 응용)
int solution(int n, vector<vector<int>> wires) {
    int answer = n; // note: actually start with n-2...
    for (auto wire : wires) { // wire has vector<int> type
        vector<bool> visited(n, false);
        queue<int> candidate1; // bfs queue
        vector<int> group1;
        queue<int> candidate2;
        vector<int> group2;
        // wire[0] will be in group1, wire[1] will be in group2
        group1.push_back(wire[0]);
        visited[wire[0]] = true;
        group2.push_back(wire[1]);
        visited[wire[1]] = true;
        // init candidate1 and candidate 2
        for (auto elem : wires) { // find first adjacent elements
            if (elem[0] == wire[0] && elem[1] == wire[1]) {
                continue; // note: elem[0] == wire[1] && elem[1] == wire[0] does not exists, so this wire is unique
            }
            else if (elem[0] == wire[0]) {
                candidate1.push(elem[1]);
            }
            else if (elem[1] == wire[0]) {
                candidate1.push(elem[0]);
            }
            else if (elem[0] == wire[1]) {
                candidate2.push(elem[1]);
            }
            else if (elem[1] == wire[1]) {
                candidate2.push(elem[0]);
            }
        }
        // do bfs
        while (!candidate1.empty())
        {

        }
        while (!candidate2.empty()) {

        }
        int diff = group1.size() - group2.size();
        if (diff < 0) diff *= -1;
        if (answer > diff) answer = diff;
    }
    return answer;
}