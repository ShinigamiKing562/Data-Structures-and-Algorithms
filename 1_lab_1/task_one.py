def sum(num):
    sum = 0
    for i in num:
        sum += i

    return sum

def max(num):
    max = num[0]
    for num in num[1:]:
        if num > max :
            max = num
        return max

def main():
    n = int(input("How many numbers do you require?"))
    num = []
    for i in range(n):
        element = int(input("Enter number:"))
        num.append(element)

    print(f'Sum is = {sum(num)}')
    print(f'Max is = {max(num)}')

if __name__ == "__main__":
    main()