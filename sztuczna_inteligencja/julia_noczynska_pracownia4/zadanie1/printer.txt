from turtle import *


class Printer:
    def __init__(self, size: int = 8):
        self.length = 50
        self.sx = -100
        self.sy = 0
        self.size = size

    def print_square(self, x: int, y: int, col: str) -> None:
        tracer(0, 1)
        fillcolor(col)
        pu()
        goto(self.sx + x * self.length, self.sy + y * self.length)
        pd()
        begin_fill()
        for _ in range(4):
            fd(self.length)
            rt(90)
        end_fill()
        update()

    def print_circle(self, x: int, y: int, col: str) -> None:
        tracer(0, 1)
        fillcolor(col)
        pu()
        goto(self.sx + x * self.length + self.length / 2, self.sy + y * self.length - self.length)
        pd()
        begin_fill()
        circle(self.length / 2)
        end_fill()
        update()
