import cv2
import numpy as np
from open3d import *

DEPTH_IMG_PATH = "../depth/"
NORMAL_IMG_PATH = "../normal/"
WIDTH = 2048
HEIGHT = 64
LIDAR_HEIGHT = 1.4
NORMAL_THRESH = 192

def display_inlier_outlier(cloud, ind):
    inlier_cloud = select_down_sample(cloud, ind)
    outlier_cloud = select_down_sample(cloud, ind, invert=True)

    print("Showing outliers (red) and inliers (gray): ")
    outlier_cloud.paint_uniform_color([1, 0, 0])
    inlier_cloud.paint_uniform_color([0.8, 0.8, 0.8])
    draw_geometries([inlier_cloud, outlier_cloud])

if __name__ == "__main__":
    picNum = 0
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
    coordinate = create_mesh_coordinate_frame(size = 5.0, origin = [0, 0, 0])
    draw_geometries([pcd, coordinate])
    print("Downsample the point cloud with a voxel of 0.02")
    voxel_down_pcd = voxel_down_sample(pcd, voxel_size = 0.02)
    draw_geometries([voxel_down_pcd, coordinate])
    print("Statistical oulier removal")
    cl,ind = statistical_outlier_removal(voxel_down_pcd, nb_neighbors=20, std_ratio=2.0)
    display_inlier_outlier(voxel_down_pcd, ind)
