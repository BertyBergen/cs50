import cs50

def blocks(n, height):
    if n == 0:
        return
    blocks(n - 1, height)
    print(f"{' ' * (height - n)}{'#' * n}  {'#' * n}")



def main():
    while(True):
        numbers = cs50.get_int("Height: ")
        if (numbers >= 1 and numbers <= 8):
            break

    blocks(numbers, numbers)

main()
