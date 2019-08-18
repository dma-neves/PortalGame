import pygame
import vector2D

FONT_DIR = "../../Assets/Fonts/"

GREY = (150, 150, 150)
WHITE = (255, 255, 255)
BLACK = (0,0,0)
RED = (255,0,0)
DARK_GREY=(30,30,30)

FONT_SCALE = 0.142

class TextBlock(object):

    def __init__(self, pos, center, size, borderThickness, text):

        if center: self.pos = pos
        else: self.pos = vector2D.Vector2D(pos.x + size.x/2, pos.y + size.y/2)
        self.size = size
        self.bt = borderThickness
        self.setText(text)
        self.color = GREY

    def getOrigin(self): return self.pos.getSub( vector2D.Vector2D(self.size.x/2, self.size.y/2) )

    def setText(self, text):
        self.text = text

        fontSize = int(self.size.x * FONT_SCALE)
        arialFont = pygame.font.Font(FONT_DIR + "arial.ttf", fontSize)
        self.textSurf = arialFont.render(self.text, True, WHITE)
        self.textRect = self.textSurf.get_rect()
        self.textRect.center = self.pos.getTuple()

    def render(self, window):
        pygame.draw.rect(window, WHITE, (self.getOrigin().x - self.bt, self.getOrigin().y - self.bt, self.size.x + 2*self.bt, self.size.y + 2*self.bt))
        pygame.draw.rect(window, self.color, (self.getOrigin().x, self.getOrigin().y, self.size.x, self.size.y))
        
        window.blit(self.textSurf, self.textRect)