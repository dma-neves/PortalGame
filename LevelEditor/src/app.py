import levelEditor
import level
import vector2D
import os

LEVEL_DIR = "../../Assets/Levels/"

def main():
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
        lvlEditor = levelEditor.LevelEditor(level = level.Level(levelFile))

    else:
        texturePack = None
        validInput = False
        while not validInput:
            texturePack = raw_input("Texture Pack: ")
            file = open("../../Assets/Textures/texturePacks.txt","r")
            content = file.read().splitlines()

            for pack in content:
                if pack == texturePack:
                    validInput = True
                    break

            if not validInput:
                print("Error: Invalid input")

        validInput = False
        while not validInput:
            levelWidth = input("Level width: ")
            levelHeight = input("Level height: ")

            if levelWidth > 0 and levelHeight > 0:
                validInput = True
            else:
                print("Error: Invalid Input")
        
        lvlEditor = levelEditor.LevelEditor(level = level.Level(levelFile, texturePack, size = vector2D.Vector2D(levelWidth, levelHeight)))
    
    lvlEditor.run()

print("------------------------------------")
print("| EDITOR NOT FULLY IMPLEMENTED YET |")
print("------------------------------------")

main()

