# write code that swaps two numbers

def num_swap(a, b):
    a = a ^ b
    b = a ^ b
    a = a ^ b
    return a, b


if __name__ == "__main__":
    a = 5
    b = 6
    a, b = num_swap(a, b)
    print(a)
    print(b)
