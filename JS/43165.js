// 타겟 넘버
function dfs(list, currentidx, sum, targetvalue){
    // 반환값은 currentidx === list.length -1일 때 sum === targetvalue이면 1, 아니면 0을 반환
    // 반환값들은 되돌아가면서 재귀적으로 합산되어 최종적으로 조건에 맞는 합의 경우의 수가 됨
    if (list.length === currentidx){
        return sum === targetvalue ? 1 : 0;
    }
    return dfs(list, currentidx + 1, sum + list[currentidx], targetvalue) + dfs(list, currentidx + 1, sum - list[currentidx], targetvalue);
    
}

function solution(numbers, target) {
    // 순서를 바꾸지 않는다 하였으므로 리스트에서 각 노드를 1회 방문할 때마다 +, - 된 모든 자식들을 탐색한다.
    return dfs(numbers, 0, 0, target);
}