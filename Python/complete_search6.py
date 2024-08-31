def filtering_true(a):
    return a
def solution(n, wires):
    answer = []
    # 와이어를 하나씩 끊으면서 wires를 탐색
    for j in range(0, len(wires)):
        visited = [] # 방문 기록
        bfsqueue = []
        for i in range(0, n):
            visited.append(False) # false로 채움
        bfsqueue.append(wires[j][0])
        visited[wires[j][0]-1] = True
        # bfsqueue에 currentpoint와 연결된 인접 노드를 append
        while (len(bfsqueue) > 0):
            for i in range(0, len(wires)):
                if (wires[i][0] == wires[j][0] and wires[i][1] == wires[j][1]):
                    continue # 이미 끊은 엣지
                elif (bfsqueue[0] == wires[i][0] and visited[wires[i][1]-1]) or (bfsqueue[0] == wires[i][1] and visited[wires[i][0]-1]):
                    continue # 이미 방문한 버텍스
                elif (wires[i][0] == bfsqueue[0] and not visited[wires[i][1]-1]): # 새 지점 1
                        bfsqueue.append(wires[i][1])
                elif (wires[i][1] == bfsqueue[0] and not visited[wires[i][0]-1]): # 새 지점 2
                        bfsqueue.append(wires[i][0])
            visited[bfsqueue[0]-1] = True
            del bfsqueue[0]
        truelist = list(filter(filtering_true, visited))
        answer.append(abs(len(truelist) - (len(visited)- len(truelist))))
        print(abs(len(truelist) - (len(visited)- len(truelist))))
    return min(answer)
