import levelRenderer
import vector2D
import entity
import const

class Level:

    def __init__(self, file = None, texturePack = None, size = None):

        self.file = file
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

    def render(self, window):
        self.renderer.render(window)

    def getEntity(self, pos):
        
        for entity in self.entities:
            if pos.x <= entity.pos.x+entity.size.x/2.0 and pos.x >= entity.pos.x-entity.size.x/2.0 and pos.y <= entity.pos.y+entity.size.y/2.0 and pos.y >= entity.pos.y-entity.size.y/2.0: return entity

        return None

    def addLever(self, entity):
        self.addEntity(entity)

        for pair in self.gates:
            if pair[1] != None: 
                pair[1] = entity
                return None

        self.gates.append( [entity, None] )

    def addGate(self, entity):
        self.addEntity(entity)
        added = False

        for pair in self.gates:
            if pair[0] != None: 
                pair[0] = entity
                return None

        self.gates.append( [None, entity] )

    def save(self):
        file = const.LEVEL_DIR + self.file
        file = open(file,"w")