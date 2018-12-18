# coding:utf-8
import json
import numpy as np
import matplotlib.pyplot as plt

if __name__ == "__main__":
    poseTraX = []
    poseTraY = []
    poseTraZ = []
    for i in range(10):
        filename = '../pose/'+str(i)+'_pose.json'
        print("file open : " + filename)
        f = open(filename, 'r')
        jsonData = json.load(f)
        poseTraX.append(jsonData["Pose"]["translation"]["x"])
        poseTraY.append(jsonData["Pose"]["translation"]["y"])
        poseTraZ.append(jsonData["Pose"]["translation"]["z"])
        f.close()
    plt.scatter(poseTraX, poseTraY)
    plt.show()
