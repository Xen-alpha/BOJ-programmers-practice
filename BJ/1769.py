counter = 0

def sum_pos(strparam):
    global counter
    if (len(strparam) == 1): # strparam이 처음부터 9 이하 자연수인 경우
        return int(strparam)
    result = 0;
    for c in strparam:
        result += int(c)
    counter += 1
    if (result >= 10):
        result = sum_pos(str(result))
    return result

string1 = input()
value = sum_pos(string1)

print(counter)
if value == 3 or value == 6 or value == 9:
    print("YES")
else:
    print("NO")