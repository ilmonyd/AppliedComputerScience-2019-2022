#!/usr/bin/python
# -*- coding: utf-8 -*-

from gimpfu import *
from math import *
import sys


def saveGif(img, delay=40):
    if pdb.gimp_drawable_is_indexed(pdb.gimp_image_get_active_drawable(img)) == FALSE:
        pdb.gimp_convert_indexed(img, 1, 0, 64, FALSE, FALSE, "")
    pdb.file_gif_save(img, pdb.gimp_image_get_active_drawable(img), "output path", "output path", TRUE, 1, delay, 0)

def newImage(width, height):
    new_image = pdb.gimp_image_new(width, height, 0)
    return new_image

def text(img, str, fr):
    img.new_layer("Background")
    bg = pdb.gimp_image_get_active_drawable(img)
    pdb.gimp_context_set_foreground((0, 0, 0, 255))
    pdb.gimp_edit_fill(bg, 0)
    font_size = img.height * 0.9
    tx_lay = pdb.gimp_text_layer_new(img, str, "Arial", font_size, 0)
    w = tx_lay.width
    img.add_layer(tx_lay, 0)
    tx_lay_trail = pdb.gimp_text_layer_new(img, str, "Arial", font_size, 0)
    img.add_layer(tx_lay_trail, 0)
    pdb.gimp_layer_set_offsets(tx_lay, fr, img.height * 0.05)
    pdb.gimp_layer_set_offsets(tx_lay_trail, fr+w, img.height * 0.05)
    pdb.gimp_text_layer_set_color(tx_lay, (255, 0, 0, 255))
    pdb.gimp_text_layer_set_color(tx_lay_trail, (255, 0, 0, 255))
    for i in range(1, -1, -1):
        pdb.gimp_image_merge_down(img, img.layers[i], 0)
    return w


def render(img, frames, str):
    img.new_layer("Background")
    bg = pdb.gimp_image_get_active_drawable(img)
    h = pdb.gimp_drawable_height(bg)
    pdb.gimp_context_set_foreground((0, 0, 0, 255))
    pdb.gimp_edit_fill(bg, 0)
    w = text(img, str, 0)
    pdb.gimp_image_merge_down(img, img.layers[0], 0)
    fr = w/frames
    for i in range(2, frames + 1):
        text(img, str, -i*fr)

if __name__ == "__main__":
    img = newImage(300, 30)
    render(img, 50, u'Who killed captain Alex? ')
    pdb.gimp_display_new(img)
    saveGif(img, 50)
