def main():
    validInput = False

    while not validInput:
        print("l - Load level")
        print("n - Creat new level")

        cmd = raw_input("> ")

        if cmd == "l" or cmd == "n":
            levelName = raw_input("Level name: ")
            file = levelName + ".txt"

print("Level editor not implemented yet")

#main()

