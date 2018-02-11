#!/usr/bin/python3

from enum import Enum
import difflib

from PIL import Image
import pytesseract
import argparse
import cv2
import os

ap = argparse.ArgumentParser()
ap.add_argument("-i", "--image", required=True, help="path to input image")
ap.add_argument("-p", "--preprocess", type=str, default="thresh", help="type of preprocessing")
args = vars(ap.parse_args())

airplanes = ['UH8', 'L6R', 'G7C', 'S1P', 'JW3', 'A2X']

image = cv2.imread(args["image"])
gray = cv2.cvtColor(image, cv2.COLOR_BGR2GRAY)

if args["preprocess"] == "thresh":
	gray = cv2.threshold(gray, 0, 255, cv2.THRESH_BINARY | cv2.THRESH_OTSU)[1]
elif args["preprocess"] == "blur":
	gray = cv2.medianBlur(gray, 3)

gray = cv2.resize(gray, (0, 0), fx=2, fy=1)

text = pytesseract.image_to_string(gray)
print('found', text)

poss = difflib.get_close_matches(text, airplanes)

print('possibilities:', poss)
