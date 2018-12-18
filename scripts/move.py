# coding:utf-8
import json
from open3d import *

if __name__ == "__main__":
    i = 1
    prev_pcdFile = "../pcd/" + str(i) + ".pcd"
    prev_pcd = read_point_cloud(prev_pcdFile)
    prev_poseFile = '../pose/'+str(i)+'_pose.json'
    print("file open : " + prev_poseFile)
    f = open(prev_poseFile, 'r')
    prev_jsonData = json.load(f)
    f.close()
    i = 2
    pcdFile = "../pcd/" + str(i) + ".pcd"
    pcd = read_point_cloud(pcdFile)
    poseFile = '../pose/'+str(i)+'_pose.json'
    print("file open : " + poseFile)
    f = open(poseFile, 'r')
    jsonData = json.load(f)
    f.close()
    x = float(jsonData["Pose"]["translation"]["x"]) - float(prev_jsonData["Pose"]["translation"]["x"])
    y = float(jsonData["Pose"]["translation"]["y"]) - float(prev_jsonData["Pose"]["translation"]["y"])
    z = float(jsonData["Pose"]["translation"]["z"]) - float(prev_jsonData["Pose"]["translation"]["z"])
    print(str(x))
    print(str(y))
    print(str(z))
    #draw_geometries([pcd])
