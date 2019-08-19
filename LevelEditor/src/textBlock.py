import pygame
import vector2D
import const

FONT_SCALE = 0.142

class TextBlock(object):

    def __init__(self, pos, center, size, borderThickness, text):

        if center: self.pos = pos
        else: self.pos = vector2D.Vector2D(pos.x + size.x/2, pos.y + size.y/2)
        self.size = size
        self.bt = borderThickness
        self.setText(text)
        self.color = const.GREY

    def getOrigin(self): return self.pos.getSub( vector2D.Vector2D(self.size.x/2, self.size.y/2) )

    def setText(self, text):
        self.text = text

        fontSize = int(self.size.x * FONT_SCALE)
        arialFont = pygame.font.Font(const.FONT_DIR + "arial.ttf", fontSize)
        self.textSurf = arialFont.render(self.text, True, const.WHITE)
        self.textRect = self.textSurf.get_rect()
        self.textRect.center = self.pos.getTuple()

    def render(self, window):
        pygame.draw.rect(window, const.WHITE, (self.getOrigin().x - self.bt, self.getOrigin().y - self.bt, self.size.x + 2*self.bt, self.size.y + 2*self.bt))
        pygame.draw.rect(window, self.color, (self.getOrigin().x, self.getOrigin().y, self.size.x, self.size.y))
        
        window.blit(self.textSurf, self.textRect)