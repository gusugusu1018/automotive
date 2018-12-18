import cv2
import numpy as np
from open3d import *

DEPTH_IMG_PATH = "../depth/"
NORMAL_IMG_PATH = "../normal/"
WIDTH = 2048
HEIGHT = 63 #64
LIDAR_HEIGHT = 1.4
NORMAL_THRESH = 192

if __name__ == "__main__":
    for picNum in range(50):
        depthFile = DEPTH_IMG_PATH + str(picNum) + "_depth.png"
        normalFile = NORMAL_IMG_PATH + str(picNum) + "_normal.png"
        depthImg = cv2.imread(depthFile, cv2.IMREAD_ANYDEPTH)
        normalImg = cv2.imread(normalFile, 1)
        xyz = np.zeros((HEIGHT * WIDTH, 3))
        for h in range(HEIGHT):
            for w in range(WIDTH):
                if depthImg[h][w] != 0:
                    r = depthImg[h][w] * 100 / 65536
                    theta = w * 2 * np.pi / WIDTH
                    if h < 32:
                        phi = (2 - h / 3) * np.pi / 180
                    else:
                        phi = (- 8.33 - (h-31) / 2) * np.pi / 180
                    if r * np.sin(phi) > - LIDAR_HEIGHT and normalImg[h][w][0] < NORMAL_THRESH:
                        xyz[h * WIDTH + w, 0] = r * np.cos(theta) * np.cos(phi)
                        xyz[h * WIDTH + w, 1] = r * np.sin(theta) * np.cos(phi)
                        xyz[h * WIDTH + w, 2] = r * np.sin(phi)
        pcd = PointCloud()
        pcd.points = Vector3dVector(xyz)
        pcdFile = "../pcd/" + str(i) + ".pcd"
        print("Write PCD : " + pcdFile)
        write_point_cloud(pcdFile, pcd)
