import textBlock

class Button(textBlock.TextBlock):

    def __init__(self, pos, center, size, borderThickness, text):
        super(Button, self).__init__(pos, center, size, borderThickness, text)
        self.released = True

    def isOverlapping(self, pos):
        return pos.x >= self.pos.x - self.size.x/2 and pos.x <= self.pos.x + self.size.x/2 and pos.y >= self.pos.y - self.size.y/2 and pos.y <= self.pos.y + self.size.y/2


