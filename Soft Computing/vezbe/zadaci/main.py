import numpy as np
import cv2
import matplotlib
import matplotlib.pyplot as plt

if __name__ == '__main__':
    img = cv2.imread('images/girl.jpg')
    plt.imshow(img)
    img = cv2.cvtColor(img, cv2.COLOR_BGR2RGB)  # konvertovanje iz BGR u RGB model boja (OpenCV ucita sliku kao BGR)
    plt.imshow(img)