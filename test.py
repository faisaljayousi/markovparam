"""
Test script to test the varCond function.
"""

import sys
import cv2
from markov.main import varCond


if __name__ == '__main__':

    if len(sys.argv) < 4:
        print("HOW TO RUN: python3 test.py image_file")
        sys.exit(1)

    image = cv2.imread(sys.argv[1], cv2.IMREAD_GRAYSCALE)
    dx, dy = sys.argv[2], sys.argv[3]

    result = varCond(image, dx=dx, dy=dy)
    print(f"Parameter value: {result}")
