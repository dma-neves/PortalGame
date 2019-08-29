import levelRenderer
import vector2D
import entity
import const

class Level:

    def __init__(self, file, name, texturePack = None, size = None):

        self.file = file
        self.name = name
        self.entities = []
        self.gates = [] #List of pairs [lever, gate]
        self.renderer = levelRenderer.LevelRenderer()

        if texturePack:
            self.texturePack = texturePack
            self.size = size
        
        else:
            self.loadLevel()

        self.renderer.setSize(self.size)

    def loadLevel(self):
        file = const.LEVEL_DIR + self.file
        file = open(file,"r")
        content = file.read().split()

        self.texturePack = content[0]
        self.size = vector2D.Vector2D( int(content[1]), int(content[2]) )

        strIndex = 3

        for y in range(0, self.size.y):
            row = content[strIndex]
            for x in range(0, self.size.x):
                texture = None
                typ = None
                size = vector2D.Vector2D(1,1)
                pos = vector2D.Vector2D(x,y)
                newEntity = True

                if row[x] == "#": 
                    texture = "staticBlock.png"
                    typ = const.STATIC_BLOCK
                elif row[x] == "O": 
                    texture = "dynamicBlock.png"
                    typ = const.DYNAMIC_BLOCK
                elif row[x] == "F": 
                    texture = "finishBlock.png"
                    typ = const.FINISH_BLOCK
                elif row[x] == "P": 
                    texture = "player.png"
                    pos.y -= 0.5
                    size.y = 2
                    typ = const.PLAYER
                else: newEntity = False

                if newEntity: self.addEntity(entity = entity.Entity(pos = pos, size = size, textureFile = const.TEXTURE_DIR + self.texturePack + texture, typ = typ))

            strIndex += 1

        numGates = int(content[strIndex])
        strIndex += 1

        i = 0
        for i in range(0, numGates):
            gatePos = vector2D.Vector2D( int(content[strIndex]), int(content[strIndex+1]) - 0.5 )
            leverPos = vector2D.Vector2D( int(content[strIndex+2]), int(content[strIndex+3]) )
            strIndex += 4

            self.addLever(entity = entity.Entity(pos = leverPos, size = vector2D.Vector2D(1,1), textureFile = const.TEXTURE_DIR + self.texturePack + "lever.png", typ = const.LEVER))
            self.addGate(entity = entity.Entity(pos = gatePos, size = vector2D.Vector2D(1,2), textureFile = const.TEXTURE_DIR + self.texturePack + "gate.png", typ = const.GATE))

        print("Level loaded successfully")




    def setCamera(self, camera): self.renderer.camera = camera

    def addEntity(self, entity):
        self.entities.append(entity)
        self.renderer.addSprite(entity)

    def removeEntity(self, entity):
        self.entities.remove(entity)
        self.renderer.removeSprite(entity)

        if entity.typ == const.LEVER:
            for pair in self.gates:
                if pair[0] == entity: pair[0] = None

        elif entity.typ == const.GATE:
            for pair in self.gates:
                if pair[1] == entity: pair[1] = None

    def render(self, window):
        self.renderer.render(window)

    def getEntity(self, pos, saveMode = False):
        
        for entity in self.entities:
            if pos.x <= entity.pos.x+entity.size.x/2.0 and pos.x >= entity.pos.x-entity.size.x/2.0 and pos.y <= entity.pos.y+entity.size.y/2.0 and pos.y >= entity.pos.y-entity.size.y/2.0: 
                if not saveMode or entity.size.y == 1: return entity
                
                elif pos.y > entity.pos.y: return entity

        return None

    def addLever(self, entity):
        self.addEntity(entity)

        for pair in self.gates:
            if pair[0] == None and pair[1] != None: 
                pair[0] = entity
                return None

        self.gates.append( [entity, None] )

    def addGate(self, entity):
        self.addEntity(entity)
        added = False

        for pair in self.gates:
            if pair[0] != None and pair[1] == None: 
                pair[1] = entity
                return None

        self.gates.append( [None, entity] )

    def save(self):
        file = const.LEVEL_DIR + self.file
        file = open(file,"w")

        file.write(self.texturePack + "\n")
        file.write( str(self.size.x) + "\n" + str(self.size.y)  + "\n")

        for y in range(0, self.size.y):
            for x in range(0, self.size.x):

                entity = self.getEntity(pos = vector2D.Vector2D(x,y), saveMode = True)
                if entity == None: file.write(".")
                elif entity.typ == const.STATIC_BLOCK: file.write("#")
                elif entity.typ == const.DYNAMIC_BLOCK: file.write("O")
                elif entity.typ == const.FINISH_BLOCK: file.write("F")
                elif entity.typ == const.PLAYER: file.write("P")
                else: file.write(".")
            
            file.write("\n")

        file.write( str(len(self.gates)) + "\n")

        for i in range(0, len(self.gates)):
            file.write( str(int(round(self.gates[i][1].pos.x))) + " " + str(int(round(self.gates[i][1].pos.y))) + "\n" )
            file.write( str(int(round(self.gates[i][0].pos.x))) + " " + str(int(round(self.gates[i][0].pos.y))) + "\n" )

        levelNamesFile = open(const.LEVEL_NAMES_FILE_DIR, "r")
        content = levelNamesFile.read().split()
        if not (self.name in content):
            f = open(const.LEVEL_NAMES_FILE_DIR, "a")
            f.write("\n" + self.name)
            

        print("Level saved successfully")