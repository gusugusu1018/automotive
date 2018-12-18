from open3d import *

if __name__ == "__main__":
    pcd = read_point_cloud("../pcd/1.pcd")
    draw_geometries([pcd])
