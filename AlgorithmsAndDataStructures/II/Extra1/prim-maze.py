#!/usr/bin/env python3

import numpy as np
import random


class Maze:
    UNVISITED = 0
    EMPTY = 1
    WALL = 2
    THICKNESS = 5

    CELL_CHARS = {
        UNVISITED: '##', # should not happen
        EMPTY: '  ',
        WALL: '██'
    }

    def __init__(self, width, height):
        self.maze = np.zeros((height, width))

        start_x, start_y = random.randrange(1, width - 1), random.randrange(1, height - 1)
        self.maze[start_y, start_x] = self.EMPTY
        walls = set(self._neighbors(start_y, start_x))

        while walls:
            y, x = random.choice(tuple(walls))
            self.maze[y, x] = self.WALL

            if sum(self.maze[n] == self.EMPTY for n in self._neighbors(y, x)) <= 1:
                self.maze[y, x] = self.EMPTY
                walls |= set(n for n in self._neighbors(y, x) if self.maze[n] != self.EMPTY)

            walls.remove((y, x))

        self.maze = np.where(self.maze == self.UNVISITED, self.WALL, self.maze)
        self.maze = np.pad(self.maze, ((1,1), (1,1)), constant_values=self.WALL)

    def _neighbors(self, y, x):
        for y, x in [(y-1, x), (y+1, x), (y, x-1), (y, x+1)]:
            if 0 <= y < self.maze.shape[0] and 0 <= x < self.maze.shape[1]:
                yield y, x

    def print(self):
        for row in self.maze:
            for cell in row:
                print(self.CELL_CHARS[cell], end='')
            print()

    def render(self):
        from PIL import Image # Pillow imported only if image generation is selected
        out = Image.new("1", (tuple([n * self.THICKNESS for n in self.maze.shape][::-1])))
        pixels = out.load()
        for y in range(self.THICKNESS, (self.maze.shape[0]-1)*self.THICKNESS, self.THICKNESS):
            for x in range(self.THICKNESS, (self.maze.shape[1]-1)*self.THICKNESS, self.THICKNESS):
                for i in range(self.THICKNESS):
                    for j in range(self.THICKNESS):
                        if self.maze[int(y/self.THICKNESS)][int(x/self.THICKNESS)] == self.EMPTY: 
                            out.putpixel((x+j, y+i), 1)
        out.save("maze.png", "png")


if __name__ == '__main__':
    m = Maze(100, 100)
    # m.print()
    m.render()
