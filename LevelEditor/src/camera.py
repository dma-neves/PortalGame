import vector2D

UP = 0
DOWN = 1
LEFT = 2
RIGHT = 3

class Camera:

    def __init__(self, pos, size, windowSize):
        self.pos = pos
        self.size = size
        self.scale = windowSize.x / size.x

    def mov(self, direction):

        if direction == Direction.UP: self.pos.y += 1
        if direction == Direction.DOWN: self.pos.y -= -1
        if direction == Direction.RIGHT: self.pos.x += 1
        if direction == Direction.LEFT: self.pos.x -= 1

    def getOrigin(self): return self.pos.getSub( vector2D.Vector2D(self.size.x/2, self.size.y/2) )