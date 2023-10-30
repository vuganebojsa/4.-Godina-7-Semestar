import numpy as np
import cv2
import matplotlib.pyplot as plt
import sys


def load_image(path):
    return cv2.cvtColor(cv2.imread(path), cv2.COLOR_BGR2RGB)


def image_hsv(img):
    return cv2.cvtColor(img, cv2.COLOR_RGB2HSV)


def display_image(img, color=False):
    if color:
        plt.imshow(img)
    else:
        plt.imshow(img, 'gray')


def get_correct_results():
    return [
        ('ditto_v1_notebook.jpg', 7),
        ('ditto_v2_notebook.jpg', 6),
        ('ditto_v3_notebook.jpg', 7),
        ('ditto_v4_notebook.jpg', 10),
        ('ditto_v5_notebook.jpg', 7),
        ('ditto_v6_notebook.jpg', 1),
        ('ditto_v7_notebook.jpg', 8),
        ('ditto_v8_notebook.jpg', 4),
        ('ditto_v9_notebook.jpg', 7),
        ('ditto_v10_notebook.jpg', 9)
    ]


def get_mask_bounds():
    return np.array([120, 50, 86]), np.array([135, 214, 235])


def get_filtered_contours(contours):
    min_area = 3000
    max_area = 130000
    filtered_contours = []
    for contour in contours:
        area = cv2.contourArea(contour)
        if min_area < area < max_area:
            filtered_contours.append(contour)
    return filtered_contours


def get_ditto_count(img):
    hsv = image_hsv(img)

    lower_bound, upper_bound = get_mask_bounds()
    mask = cv2.inRange(hsv, lower_bound, upper_bound)

    # filter contours that fit a certain area
    contours, _ = cv2.findContours(mask, cv2.RETR_EXTERNAL, cv2.CHAIN_APPROX_SIMPLE)
    filtered_contours = get_filtered_contours(contours)

    total_dittos = len(filtered_contours)

    # displaying the image with red contours
    # img_cont = img.copy()
    # cv2.drawContours(img_cont, filtered_contours, -1, (255, 0, 0), 2)
    # display_image(img_cont)

    return total_dittos


if __name__ == '__main__':
    correct_results = get_correct_results()
    total_differences = []
    print('Picture Name-Correct Answer-My Answer')
    pictures_path = 'pictures/'
    if len(sys.argv) >= 2:
        pictures_path = sys.argv[1]

    for (file_name, value) in correct_results:
        image = load_image(pictures_path + file_name)
        # resizing the image so only the things in the notepad are being looked
        image = image[60:980, 284:900]

        count = get_ditto_count(image)
        total_differences.append(abs(count - int(value)))
        print(file_name + '-' + str(value) + '-' + str(count))

    mae = sum(total_differences) / len(total_differences)
    print('\nMean Absolute error(MAE) is: ' + str(mae))
