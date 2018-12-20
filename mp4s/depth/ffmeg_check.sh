#!/bin/sh
for i in 1 2 3 4 5
do
	ffmpeg -r 10 -i $1/$i/depth/%d_depth.png -pix_fmt yuv420p depth_$i.mp4
done
