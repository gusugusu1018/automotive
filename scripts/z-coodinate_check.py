import cv2
import numpy as np
from open3d import *

VISION_IMG_PATH = "../depth/"

if __name__ == "__main__":
    i = 1
    filename = VISION_IMG_PATH + str(i) + "_depth.png"
    print("Open img : " + filename)
    # read a gray scale image
    img = cv2.imread(filename, 0)
    print("shape : " + str(img.shape) + " size : " +
          str(img.size) + " dtype : " + str(img.dtype))
    xyz = np.zeros((64 * 2048, 3))
    for h in range(64):
        for w in range(2048):
            if img[h][w] != 0:
                r = img[h][w] * 100 / 256  # or 2^16
                theta = w * 2 * np.pi / 2048
                if h < 32:
                    phi = (2 - h / 3) * np.pi / 180
                else:
                    phi = (- 8.33 - (h-31) / 2) * np.pi / 180
                xyz[h * 2048 + w, 0] = r * np.cos(theta) * np.cos(phi)
                xyz[h * 2048 + w, 1] = r * np.sin(theta) * np.cos(phi)
                xyz[h * 2048 + w, 2] = r * np.sin(phi)
                if xyz[h * 2048 + w, 2] < -5:
                    print("z coodinate is under -5!")
                    print("coodinate : (" + str(xyz[h*2048+w, 0]) + ", " + str(xyz[h*2048+w, 1]) + ", " + str(xyz[h*2048+w, 2]) + ")")
                    print("pixel : (h, w) = (" + str(h) + ", " + str(w) + ")")
    pcd = PointCloud()
    pcd.points = Vector3dVector(xyz)
    draw_geometries([pcd])
