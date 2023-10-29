import numpy as np
import cv2
import matplotlib.pyplot as plt
import csv

def load_image(path):
    return cv2.cvtColor(cv2.imread(path), cv2.COLOR_BGR2RGB)


def display_image(image, color=False):
    if color:
        plt.imshow(image)
    else:
        plt.imshow(image, 'gray')

def load_csv_data():
    result = []
    with open('ditto_count.csv') as ditto_file:
        reader = csv.reader(ditto_file, delimiter=',')
        first = True
        for row in reader:
            if first:
                first = False
                continue
            result.append((row[0], row[1]))
    return result


def get_ditto_count(img):
    kernel = cv2.getStructuringElement(cv2.MORPH_ELLIPSE, (5, 5))
    # img_open = cv2.dilate(img, kernel, iterations=2)
    # img_ero = cv2.erode(img_open, kernel, iterations=2)
    # display_image(img_ero, color=True)
    hsv = cv2.cvtColor(img, cv2.COLOR_RGB2HSV)

    lower_purple = np.array([120, 50, 50])
    upper_purple = np.array([160, 255, 255])
    mask = cv2.inRange(hsv, lower_purple, upper_purple)

    contours, _ = cv2.findContours(mask, cv2.RETR_EXTERNAL, cv2.CHAIN_APPROX_SIMPLE)

    min_area = 2000
    max_area = 130000
    filtered_contours = []
    for contour in contours:
        area = cv2.contourArea(contour)
        if min_area < area < max_area:
            filtered_contours.append(contour)

    total_dittos = len(filtered_contours)
    img_cont = img.copy()
    cv2.drawContours(img_cont, filtered_contours, -1, (255, 0, 0), 2)

    return total_dittos


if __name__ == '__main__':
    result = load_csv_data()
    total_differences = []
    for (file_name, value) in result:
        img = load_image('pictures/' + file_name)
        img = img[60:980, 284:900]
        guess = get_ditto_count(img)
        total_differences.append(abs(guess - int(value)))
        print(file_name + '-' + str(value) + '-' + str(guess))
    print(sum(total_differences)/ len(total_differences))

