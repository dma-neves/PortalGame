import pygame
import camera
import vector2D
import const

class LevelRenderer:

    def __init__(self):
        self.camera = None
        self.sprites = pygame.sprite.Group()

    def addSprite(self, entity):
        self.sprites.add(entity)

    def removeSprite(self, entity):
        self.sprites.remove(entity)

    def render(self, window):

        for sprite in self.sprites:

            drawSize  = sprite.size.copy()
            drawSize.scale(self.camera.scale)

            drawPos = sprite.pos.getSub( self.camera.getOrigin() )
            drawPos.scale( self.camera.scale )

            sprite.image = pygame.transform.scale(sprite.image, drawSize.getTuple())
            sprite.rect = sprite.image.get_rect()
            sprite.rect.center = drawPos.getTuple()

        self.sprites.draw(window)

    def getWorldPos(self, pos):

        aux = pos.getSub(vector2D.Vector2D(const.WINDOW_WIDTH/2, const.WINDOW_HEIGHT/2))
        aux.scale(1.0/self.camera.scale)
    
        return self.camera.pos.getAdd(aux)