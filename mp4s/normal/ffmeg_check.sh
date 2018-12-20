#!/bin/sh
for i in 1 2 3 4 5
do
	ffmpeg -r 10 -i $1/$i/normal/%d_normal.png -pix_fmt yuv420p normal_$i.mp4
done
