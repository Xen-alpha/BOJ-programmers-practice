def solution(progresses, speeds):
    input_arr = progresses
    answer = []
    stack = []
    while len(input_arr) > 0:
        arr_size = len(input_arr)
        for i in range(1,arr_size):
            input_arr[arr_size-i] += speeds[arr_size-i]
            if input_arr[arr_size-i] >= 100:
                stack.append(input_arr[arr_size-i])
                del input_arr[arr_size-i]
                del speeds[arr_size-i]
                if arr_size-i == 0:
                    answer.append(len(stack))
                    stack = []
                    break
    
    return answer