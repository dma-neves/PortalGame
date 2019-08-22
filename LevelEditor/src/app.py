import levelEditor
import level
import vector2D
import os
import const

LEVEL_DIR = "../../Assets/Levels/"

def main():

    validInput = False
    print("Window size:")
    print("0) 400*400")
    print("1) 600*600")
    print("2) 800*800")
    print("3) 1000*1000")

    while not validInput:
        option = int(raw_input("> "))
        validInput = True
        if option == 0:
            const.WINDOW_WIDTH = 400
            const.WINDOW_HEIGHT = 400
        elif option == 1:
            const.WINDOW_WIDTH = 600
            const.WINDOW_HEIGHT = 600
        elif option == 2:
            const.WINDOW_WIDTH = 800
            const.WINDOW_HEIGHT = 800
        elif option == 3:
            const.WINDOW_WIDTH = 1000
            const.WINDOW_HEIGHT = 1000
        else: 
            validInput = False
            print("Error: Invalid input")

    print("")

    lvlEditor = None
    levelFile = None
    validInput = False

    while not validInput:
        print("l - Load level")
        print("n - Creat new level")

        cmd = raw_input("> ")

        if cmd == "l" or cmd == "n":
            levelName = raw_input("Level name: ")
            levelFile = levelName + ".txt"
            validInput = True

        else: print("Error: Invalid input")

        if cmd == "l" and not os.path.isfile(LEVEL_DIR + levelFile): 
            validInput = False
            print("Error: Invalid level name")

    if cmd == "l":
        lvlEditor = levelEditor.LevelEditor(level = level.Level(levelFile, levelName))

    else:
        texturePack = "DefaultPack/"

        validInput = False
        while not validInput:
            levelWidth = input("Level width: ")
            levelHeight = input("Level height: ")

            if levelWidth > 0 and levelHeight > 0:
                validInput = True
            else:
                print("Error: Invalid Input")
        
        lvlEditor = levelEditor.LevelEditor(level = level.Level(file = levelFile, name = levelName, texturePack = texturePack, size = vector2D.Vector2D(levelWidth, levelHeight)))
    
    lvlEditor.run()

main()

