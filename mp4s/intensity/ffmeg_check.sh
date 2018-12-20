#!/bin/sh
for i in 1 2 3 4 5
do
	ffmpeg -r 10 -i $1/$i/intensity/%d_intensity.png -pix_fmt yuv420p intensity_$i.mp4
done
