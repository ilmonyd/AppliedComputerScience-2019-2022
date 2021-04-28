from gimpfu import *
from math import *
import sys

def newImage(width, height):
    new_image = pdb.gimp_image_new(width, height, 0)
    pdb.gimp_display_new(new_image)
    new_image.new_layer()
    return new_image

def fillCirc(img, x, y, r, color):
    temp = pdb.gimp_image_get_active_layer(img)
    fg = pdb.gimp_context_get_foreground()
    pdb.gimp_context_set_foreground(color)
    img.new_layer("Circle")
    pdb.gimp_image_select_ellipse(img, 0, x, y, r, r)
    pdb.gimp_edit_fill(pdb.gimp_image_get_active_drawable(img), 0)
    pdb.gimp_layer_set_mode(pdb.gimp_image_get_active_drawable(img), 33)
    pdb.gimp_context_set_foreground(fg)
    pdb.gimp_image_set_active_layer(img, temp)
    pdb.gimp_selection_none(img)

def render(img, fr):
    img.new_layer("Circles")
    bg = pdb.gimp_image_get_active_drawable(img)
    l = pdb.gimp_drawable_width(bg)
    pdb.gimp_context_set_foreground((0, 0, 0, 255))
    pdb.gimp_edit_fill(bg, 0)
    a = l/fr
    r = l/3
    h = (a * sqrt(3))/2
    ctr = l/2
    fillCirc(img, ctr-r/2, ctr-(2*h/3)-r/2, r, (255, 0, 0, 255))
    fillCirc(img, ctr-r/2-a/2, ctr-r/2+(h/3), r, (0, 255, 0, 255))
    fillCirc(img, ctr-r/2+a/2, ctr-r/2+(h/3), r, (0, 0, 255, 255))
