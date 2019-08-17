import vector2D
import level
import camera
import pygame
import entity
import textBlock
import toolManager

WINDOW_WIDTH = 800
WINDOW_HEIGHT = 800

WHITE = (255, 255, 255)
BLACK = (0,0,0)

class Point:
    def __init__(self, a = 0):
        self.a = a

    def getA(self):
        return self.a

class LevelEditor:

    def __init__(self, level):
        pygame.init()

        self.level = level
        level.setCamera(camera = camera.Camera(pos = vector2D.Vector2D(int(level.size.x/2), int(level.size.y/2)), size = vector2D.Vector2D(40, 40), windowSize = vector2D.Vector2D(WINDOW_WIDTH, WINDOW_HEIGHT)))
        self.toolMng = toolManager.ToolManager()
        self.running = True 

        self.window = pygame.display.set_mode((WINDOW_WIDTH, WINDOW_HEIGHT))
        pygame.display.set_caption("Level Editor")
        self.clock = pygame.time.Clock()

        self.txtBlock = textBlock.TextBlock(pos = vector2D.Vector2D(10, 10), center = False, size = vector2D.Vector2D(120, 40), borderThickness = 5, text = self.toolMng.currentTool)

    def run(self):

        while self.running:

            for event in pygame.event.get():

                if event.type == pygame.QUIT:
                    self.running = False

                if event.type == pygame.KEYDOWN and event.key == pygame.K_ESCAPE:
                    self.running = False

            pressed = pygame.key.get_pressed()

            if pressed[pygame.K_RIGHT]: self.level.renderer.camera.pos.x += 1
            if pressed[pygame.K_LEFT]: self.level.renderer.camera.pos.x -= 1
            if pressed[pygame.K_UP]: self.level.renderer.camera.pos.y -= 1
            if pressed[pygame.K_DOWN]: self.level.renderer.camera.pos.y += 1

            self.window.fill(BLACK)
            self.level.render(self.window)
            self.txtBlock.render(self.window)
            pygame.display.update()

            self.clock.tick(30)

        pygame.quit()
