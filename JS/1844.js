// 1844.js 게임 맵 최단 거리
// 풀이 전략: BFS(Breath-First Search)
// 주의: 효율성 테스트를 통과하려면 mapClone에 방문 표시(-1 대입)하는 작업을 다음 이동 지역 후보에 먼저 하고 지역 큐에서 pop해야 한다.
// 이동한 총 칸 갯수를 반환해야 하므로 counter는 1에서 시작하게 작성했다.

function isInArea(m, n, x, y){
    return (x >= 0 && x < n) && (y >= 0 && y < m);
}


function solution(maps) {
    var answer = -1;
    let mapClone = maps;
    let loop = true;
    let queue = [[0,0]];
    const m = maps.length;
    const n = maps[0].length;
    
    if ( n === 1 && m === 1) return 1; // 특수 케이스 하나
    
    let counter = 1;
    mapClone[0][0] = -1;
    while (loop){
        let queue_next = [];
        loop = false;
        while ( queue.length > 0 ) {
            const [x, y] = queue[0];
            if (x === n-1 && y === m-1) return counter;
            if (isInArea(m,n,x-1,y) && mapClone[y][x-1] === 1) {
                queue_next.push([x-1, y]);
                loop = true;
                mapClone[y][x-1] = -1;
            }
            if (isInArea(m,n,x+1,y) && mapClone[y][x+1] === 1) {
                queue_next.push([x+1, y]);
                loop = true;
                mapClone[y][x+1] = -1;
            }
            if (isInArea(m,n,x,y-1) && mapClone[y-1][x] === 1) {
                queue_next.push([x, y-1]);
                loop = true;
                mapClone[y-1][x] = -1;
            }
            if (isInArea(m,n,x,y+1) && mapClone[y+1][x] === 1) {
                queue_next.push([x, y+1]);
                loop = true;
                mapClone[y+1][x] = -1;
            }
            queue.splice(0,1);
        }
        queue = queue_next;
        counter += 1;
    }
    
    return answer;
}