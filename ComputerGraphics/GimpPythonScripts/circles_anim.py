from gimpfu import *
from math import *
from time import sleep
import sys


def saveGif(img, delay=40):
    if pdb.gimp_drawable_is_indexed(pdb.gimp_image_get_active_drawable(img)) == FALSE:
        pdb.gimp_convert_indexed(img, 1, 0, 64, FALSE, FALSE, "")
    pdb.file_gif_save(img, pdb.gimp_image_get_active_drawable(img), "output path", "output path", TRUE, 1, delay, 0)

def newImage(width, height):
    new_image = pdb.gimp_image_new(width, height, 0)
    return new_image

def animCirc(img, frames):
    pdb.gimp_image_undo_disable(img)
    for i in range(frames/2):
        render(img, i+5)
        for n in range(2, -1, -1):
            pdb.gimp_image_merge_down(img, img.layers[n], 0)
    for i in range(frames/2, -1, -1):
        render(img, i+5)
        for n in range(2, -1, -1):
            pdb.gimp_image_merge_down(img, img.layers[n], 0)
    pdb.gimp_image_undo_enable(img)

def animRotate(img):
    pdb.gimp_image_undo_disable(img)
    frames = len(img.layers)
    x,y = img.width/2, img.height/2
    angle = 2 * pi / (frames)
    for i in range(frames):
        pdb.gimp_drawable_transform_rotate_default(img.layers[frames-1-i], (frames-i)*angle, TRUE, x, y, TRUE, 1)
    pdb.gimp_image_undo_enable(img)

if __name__ == "__main__":
    img = newImage(500, 500)
    execfile("path to circles.py")
    pdb.gimp_display_new(img)
    animCirc(img, 40)
    animRotate(img)
    saveGif(img)
