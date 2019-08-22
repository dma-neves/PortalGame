import pygame

class Entity(pygame.sprite.Sprite):

    def __init__(self, pos ,size, textureFile, typ):
        self.pos = pos
        self.size = size
        self.typ = typ

        pygame.sprite.Sprite.__init__(self)
        self.image = pygame.image.load(textureFile)
        self.rect = self.image.get_rect()
