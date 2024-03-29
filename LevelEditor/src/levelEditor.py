import vector2D
import level
import camera
import pygame
import entity
import textBlock
import button
import toolManager
import const

class Point:
    def __init__(self, a = 0):
        self.a = a

    def getA(self):
        return self.a

class LevelEditor:

    def __init__(self, level):
        pygame.init()

        self.level = level
        cameraSize = vector2D.Vector2D(const.WINDOW_WIDTH/20, const.WINDOW_HEIGHT/20)
        level.setCamera(camera = camera.Camera(pos = vector2D.Vector2D(int(level.size.x/2), int(level.size.y/2)), size = cameraSize, windowSize = vector2D.Vector2D(const.WINDOW_WIDTH, const.WINDOW_HEIGHT)))
        self.toolMng = toolManager.ToolManager()
        self.running = True 

        self.window = pygame.display.set_mode((const.WINDOW_WIDTH, const.WINDOW_HEIGHT))
        pygame.display.set_caption("Level Editor")
        self.clock = pygame.time.Clock()

        blockSize = vector2D.Vector2D(const.WINDOW_WIDTH / 10, const.WINDOW_WIDTH / 30)
        thickness = const.WINDOW_WIDTH / 150
        dist = blockSize.x + thickness * 3.5
        aux = thickness*4

        self.txtBlock = textBlock.TextBlock(pos = vector2D.Vector2D(aux, thickness*4), center = False, size = blockSize, borderThickness = thickness, text = self.toolMng.currentTool); aux += dist
        self.buttons = []
        self.buttons.append(button.Button(pos = vector2D.Vector2D(aux, thickness*4), center = False, size = blockSize, borderThickness = thickness, text = const.STATIC_BLOCK)); aux += dist
        self.buttons.append(button.Button(pos = vector2D.Vector2D(aux, thickness*4), center = False, size = blockSize, borderThickness = thickness, text = const.DYNAMIC_BLOCK)); aux += dist
        self.buttons.append(button.Button(pos = vector2D.Vector2D(aux, thickness*4), center = False, size = blockSize, borderThickness = thickness, text = const.PLAYER)); aux += dist
        self.buttons.append(button.Button(pos = vector2D.Vector2D(aux, thickness*4), center = False, size = blockSize, borderThickness = thickness, text = const.FINISH_BLOCK)); aux += dist
        self.buttons.append(button.Button(pos = vector2D.Vector2D(aux, thickness*4), center = False, size = blockSize, borderThickness = thickness, text = const.GATE)); aux += dist
        self.buttons.append(button.Button(pos = vector2D.Vector2D(aux, thickness*4), center = False, size = blockSize, borderThickness = thickness, text = const.LEVER)); aux += dist
        self.buttons.append(button.Button(pos = vector2D.Vector2D(aux, thickness*4), center = False, size = blockSize, borderThickness = thickness, text = const.SAVE))

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

        if pressed[pygame.K_d]: self.level.renderer.camera.pos.x += 1
        if pressed[pygame.K_a]: self.level.renderer.camera.pos.x -= 1
        if pressed[pygame.K_w]: self.level.renderer.camera.pos.y -= 1
        if pressed[pygame.K_s]: self.level.renderer.camera.pos.y += 1

        mx, my = pygame.mouse.get_pos()
        worldPos = self.level.renderer.getWorldPos(vector2D.Vector2D(mx, my))
        buttonPressed = False

        if not pygame.mouse.get_pressed()[0]:
            for button in self.buttons: button.released = True
  
        for button in self.buttons:
            if button.isOverlapping(vector2D.Vector2D(mx, my)):
                buttonPressed = True
                button.color = const.RED
                if pygame.mouse.get_pressed()[0]:

                    if button.text == const.SAVE:
                        if button.released:
                            self.level.save()
                            button.released = False
                    
                    else:

                        self.toolMng.currentTool = button.text
                        self.txtBlock.setText(self.toolMng.currentTool)

            else: button.color = const.DARK_GREY

        if not buttonPressed and pygame.mouse.get_pressed()[0]: self.toolMng.handleActivation(self.level, worldPos)

        if pygame.mouse.get_pressed()[2]:
            entity = self.level.getEntity(worldPos)
            if entity != None: self.level.removeEntity(entity)



    def render(self):
        self.window.fill(const.BLACK)

        self.level.render(self.window)
        self.txtBlock.render(self.window)
        for button in self.buttons: button.render(self.window)

        pygame.display.update()