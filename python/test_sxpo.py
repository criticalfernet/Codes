def main():
    int = 0
    div = 7
    while True:
        val = div * int
        strval = str(val)
        validcheck = True
        for char in strval:
            if char != "9":
                validcheck = False
        if validcheck:
            print(val + 1)
            break
        int = int + 1


if __name__ == "__main__":
    main()
