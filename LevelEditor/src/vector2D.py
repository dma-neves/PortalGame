class Vector2D:

    def __init__(self, x = 0, y = 0):
        self.x = x
        self.y = y

    def scale(self, scaler):
        self.x *= scaler
        self.y *= scaler
        return self

    def getSub(self, vec): return Vector2D(self.x - vec.x, self.y - vec.y)
    def getTuple(self): return (self.x, self.y)

    def copy(self): return Vector2D(self.x, self.y)