import cv2
import numpy as np
from open3d import *

DEPTH_IMG_PATH = "../depth/"
NORMAL_IMG_PATH = "../normal/"

if __name__ == "__main__":
    i = 1
    depthFile = DEPTH_IMG_PATH + str(i) + "_depth.png"
    print("Open depthImg : " + depthFile)
    normalFile = NORMAL_IMG_PATH + str(i) + "_normal.png"
    print("Open normalImg : " + normalFile)
    # read a gray scale image
    depthImg = cv2.imread(depthFile, 0)
    normalImg = cv2.imread(normalFile, 1)
    xyz = np.zeros((64 * 2048, 3))
    for h in range(64):
        for w in range(2048):
            if depthImg[h][w] != 0:
                r = depthImg[h][w] * 100 / 256  # or 2^16
                theta = w * 2 * np.pi / 2048
                if h < 32:
                    phi = (2 - h / 3) * np.pi / 180
                else:
                    phi = (- 8.33 - (h-31) / 2) * np.pi / 180
                if normalImg[h][w][0] > 192 and normalImg[h][w][1] < 64 and normalImg[h][w][2] < 64:
                    xyz[h * 2048 + w, 0] = r * np.cos(theta) * np.cos(phi)
                    xyz[h * 2048 + w, 1] = r * np.sin(theta) * np.cos(phi)
                    xyz[h * 2048 + w, 2] = r * np.sin(phi)

    pcd = PointCloud()
    pcd.points = Vector3dVector(xyz)
    draw_geometries([pcd])
