import const
import entity
import vector2D

class ToolManager:

    def __init__(self):
        self.currentTool = const.STATIC_BLOCK

    def handleActivation(self, level, worldPos):

        if worldPos.x >= 0 and worldPos.x <= level.size.x and worldPos.y >= 0 and worldPos.y <= level.size.y and level.getEntity(worldPos) == None:

            pos = vector2D.Vector2D( round(worldPos.x), round(worldPos.y) )
            size = vector2D.Vector2D(1,1)

            if self.currentTool == const.STATIC_BLOCK: level.addEntity(entity.Entity(pos = pos ,size = size, textureFile = const.TEXTURE_DIR + level.texturePack + "staticBlock.png", typ = self.currentTool))
            elif self.currentTool == const.DYNAMIC_BLOCK: level.addEntity(entity.Entity(pos = pos ,size = size, textureFile = const.TEXTURE_DIR + level.texturePack + "dynamicBlock.png", typ = self.currentTool))
            elif self.currentTool == const.PLAYER:
                pos.y -= 0.5
                size.y = 2
                level.addEntity(entity.Entity(pos = pos ,size = size, textureFile = const.TEXTURE_DIR + level.texturePack + "player.png", typ = self.currentTool))
            elif self.currentTool == const.FINISH_BLOCK: level.addEntity(entity.Entity(pos = pos ,size = size, textureFile = const.TEXTURE_DIR + level.texturePack + "finishBlock.png", typ = self.currentTool))
            elif self.currentTool == const.GATE:
                pos.y -= 0.5
                size.y = 2
                level.addGate(entity.Entity(pos = pos ,size = size, textureFile = const.TEXTURE_DIR + level.texturePack + "gate.png", typ = self.currentTool))
            elif self.currentTool == const.LEVER: level.addLever(entity.Entity(pos = pos ,size = size, textureFile = const.TEXTURE_DIR + level.texturePack + "lever.png", typ = self.currentTool))