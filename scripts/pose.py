# coding:utf-8
import json
import numpy as np
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D

if __name__ == "__main__":
    posePX = []
    posePY = []
    posePZ = []
    #poseQX = []
    #poseQY = []
    #poseQZ = []
    #poseQW = []
    for i in range(50):
        filename = '../dataset/dataset1/bike_bicycle[5]/1/pose/'+str(i)+'_pose.json'
        print("file open : " + filename)
        f = open(filename, 'r')
        jsonData = json.load(f)
        posePX.append(jsonData["Pose"]["translation"]["x"])
        posePY.append(jsonData["Pose"]["translation"]["y"])
        posePZ.append(jsonData["Pose"]["translation"]["z"])
        #poseQX.append(jsonData["Pose"]["unit_quaternion"]["x"])
        #poseQY.append(jsonData["Pose"]["unit_quaternion"]["y"])
        #poseQZ.append(jsonData["Pose"]["unit_quaternion"]["z"])
        #poseQW.append(jsonData["Pose"]["unit_quaternion"]["w"])
        f.close()
    #fig = plt.figure()
    #ax = Axes3D(fig)
    #ax.set_xlabel("X-axis")
    #ax.set_ylabel("Y-axis")
    #ax.set_zlabel("Z-axis")
    #ax.set_xlim(4, 8)
    #ax.set_ylim(2, 5)
    #ax.set_zlim(1, 8)
    #ax.plot(posePX, posePY, posePZ, "o", color="#cccccc", ms=4, mew=0.5)
    #ax.plot(posePX, posePY, posePZ)
    plt.scatter(posePX,posePY)
    plt.show()
