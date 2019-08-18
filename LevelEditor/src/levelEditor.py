import vector2D
import level
import camera
import pygame
import entity
import textBlock
import button
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

        blockSize = vector2D.Vector2D(WINDOW_WIDTH / 10, WINDOW_WIDTH / 30)
        thickness = WINDOW_WIDTH / 150
        dist = blockSize.x + thickness * 4
        aux = thickness*4

        self.txtBlock = textBlock.TextBlock(pos = vector2D.Vector2D(aux, thickness*4), center = False, size = blockSize, borderThickness = thickness, text = self.toolMng.currentTool); aux += dist
        self.buttons = []
        self.buttons.append(button.Button(pos = vector2D.Vector2D(aux, thickness*4), center = False, size = blockSize, borderThickness = thickness, text = toolManager.STATIC_BLOCK)); aux += dist
        self.buttons.append(button.Button(pos = vector2D.Vector2D(aux, thickness*4), center = False, size = blockSize, borderThickness = thickness, text = toolManager.DYNAMIC_BLOCK)); aux += dist
        self.buttons.append(button.Button(pos = vector2D.Vector2D(aux, thickness*4), center = False, size = blockSize, borderThickness = thickness, text = toolManager.PLAYER)); aux += dist
        self.buttons.append(button.Button(pos = vector2D.Vector2D(aux, thickness*4), center = False, size = blockSize, borderThickness = thickness, text = toolManager.FINISH_BLOCK)); aux += dist
        self.buttons.append(button.Button(pos = vector2D.Vector2D(aux, thickness*4), center = False, size = blockSize, borderThickness = thickness, text = toolManager.GATE)); aux += dist
        self.buttons.append(button.Button(pos = vector2D.Vector2D(aux, thickness*4), center = False, size = blockSize, borderThickness = thickness, text = toolManager.LEVER))

    def run(self):

        while self.running:

            self.handleEvents()
            self.render()
            self.clock.tick(30)

        pygame.quit()

    def handleEvents(self):
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

        mx, my = pygame.mouse.get_pos()
  
        for button in self.buttons:
            if button.isOverlapping(vector2D.Vector2D(mx, my)): 
                button.color = textBlock.RED
                if pygame.mouse.get_pressed()[0]:
                    self.toolMng.currentTool = button.text
                    self.txtBlock.setText(self.toolMng.currentTool)

            else: button.color = textBlock.DARK_GREY



    def render(self):
        self.window.fill(BLACK)

        self.level.render(self.window)
        self.txtBlock.render(self.window)
        for button in self.buttons: button.render(self.window)

        pygame.display.update()