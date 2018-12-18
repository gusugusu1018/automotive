import cv2
import numpy as np
from open3d import *
import matplotlib.pyplot as plt

DEPTH_IMG_PATH = "../depth/"
WIDTH = 2048
HEIGHT = 64

if __name__ == "__main__":
    picNum = 0
    depthFile = DEPTH_IMG_PATH + str(picNum) + "_depth.png"
    print("Open depthImg : " + depthFile)
    depthImg = cv2.imread(depthFile, cv2.IMREAD_ANYDEPTH)
    print("shape : " + str(depthImg.shape) + " size : " +
          str(depthImg.size) + " dtype : " + str(depthImg.dtype))
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
                if r * np.sin(phi) > - 5:
                    xyz[h * WIDTH + w, 0] = r * np.cos(theta) * np.cos(phi)
                    xyz[h * WIDTH + w, 1] = r * np.sin(theta) * np.cos(phi)
                    xyz[h * WIDTH + w, 2] = r * np.sin(phi)
    fig = plt.figure()
    ax = fig.add_subplot(1,1,1)
    ax.hist(xyz[:,2], bins=200)
    fig.show()
    pcd = PointCloud()
    pcd.points = Vector3dVector(xyz)
    draw_geometries([pcd])
