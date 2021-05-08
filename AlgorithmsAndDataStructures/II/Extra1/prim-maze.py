#!/usr/bin/env python3

#
#   Created by Oleg Semenov
#   Maze generating script using Prim's algorithm
#

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

    def __init__(self, width, height, thickness):
        self.dims = (width, height)
        self.maze = np.zeros((height, width))
        self.THICKNESS = thickness
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
        out = Image.new("RGB", (tuple([n * self.THICKNESS for n in self.maze.shape][::-1])))
        pixels = out.load()
        for y in range(self.THICKNESS, (self.maze.shape[0]-1)*self.THICKNESS, self.THICKNESS):
            for x in range(self.THICKNESS, (self.maze.shape[1]-1)*self.THICKNESS, self.THICKNESS):
                for i in range(self.THICKNESS):
                    for j in range(self.THICKNESS):
                        if self.maze[int(y/self.THICKNESS)][int(x/self.THICKNESS)] == self.EMPTY: 
                            out.putpixel((x+j, y+i), (255, 255, 255))
        out.save("maze.png", "png")
        return out

    def solve(self, start, end, gif=False):
        from PIL import Image
        if gif:
            import os, glob
            if not os.path.exists("gif_temp"): 
                os.mkdir("gif_temp")
            else:
                files = glob.glob('gif_temp/*')
                for f in files:
                    os.remove(f)
        img = self.render()
        pix = img.load()
        arr = np.array(img)
        isFound = False
        current = start
        iteration = 0
        path = []
        intersects = []
        arr[start] = (255, 0, 255)
        arr[end] = (255, 0, 0)
        while not isFound:
            iteration += 1
            possible = []
            surr = [
                (current[0]-1, current[1]),
                (current[0]+1, current[1]),
                (current[0], current[1]-1),
                (current[0], current[1]+1),
            ]
            for move in surr:
                if move == end:
                    isFound = True
                if pix[move] >= (200, 200, 200) and pix[move] != (255, 255, 0) and move != start:
                    possible.append(move)
            
            if len(possible) >= 2:
                if current not in intersects:
                    intersects.append(current)
            if len(possible) == 0:
                intersects_reversed = intersects[::-1]
                for i in intersects_reversed:
                    if i != current:
                        current = i
                        intersects.pop(intersects.index(i)) 
                        break
                path = path[:path.index(current)]

            else:
                current = random.choice(possible)
            
            path.append(current)
            arr[current[1], current[0]] = (255, 255, 0)
            img = Image.fromarray(arr)
            pix = img.load()
            if gif:
                img.resize((300, 300),Image.BOX).save("gif_temp\\"+str(iteration).zfill(4)+".png", "png")
        for p in path:
            arr[p[1], p[0]] = (0, 255, 0)
            if gif:
                img = Image.fromarray(arr)
                img = img.resize((300, 300),Image.BOX)
                img.save("gif_temp\\"+str(iteration).zfill(4)+".png", "png")
            iteration += 1
        img = Image.fromarray(arr)
        img.save("solution.png", "png")
        if gif:
            images = []
            files = sorted(glob.glob('gif_temp/*'))
            for f in files:
                images.append(Image.open(f))

            images[0].save('anim.gif',
                        save_all=True, append_images=images[1:], optimize=False, duration=20, loop=0)
            files = glob.glob('gif_temp/*')
            for f in files:
                os.remove(f)
            os.rmdir("gif_temp")


if __name__ == '__main__':
    w, h = 30, 30
    m = Maze(w, h, 1)
    m.solve((1, 1), (w, h), True)
