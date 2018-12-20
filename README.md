# Environment 
* ubuntu16.04
* open3d-python (python 3.6.7)
* opencv-python (python 3.6.7)
* pcl(1.9)
* opencv(3.3.0)
* ffmpeg - video maker
* totem - video viewer

## Python environment using pyenv virtualenv
```
pyenv install 3.6.7
pyenv virtual env 3.6.7 toyota
pyenv local toyota
pip install --upgrade pip
pip install open3d-python
pip install opencv-python
```

## pcl-1.9 from src

```
sudo apt update
sudo apt install git build-essential linux-libc-dev
sudo apt install cmake cmake-gui 
sudo apt install libusb-1.0-0-dev libusb-dev libudev-dev
sudo apt install mpi-default-dev openmpi-bin openmpi-common  
sudo apt install libflann1.8 libflann-dev
sudo apt install libeigen3-dev
sudo apt install libboost-all-dev
sudo apt install libvtk5.10-qt4 libvtk5.10 libvtk5-dev
sudo apt install libqhull* libgtest-dev
sudo apt install freeglut3-dev pkg-config
sudo apt install libxmu-dev libxi-dev 
sudo apt install mono-complete
sudo apt install qt-sdk openjdk-8-jdk openjdk-8-jre
sudo apt install libproj-dev
git clone https://github.com/PointCloudLibrary/pcl.git
cd pcl
mkdir release
cd release
cmake-gui ../
# set
make -j8
```

## opencv 3.3.0 from src

```
sudo apt-get install cmake libeigen3-dev libgtk-3-dev qt5-default freeglut3-dev libvtk6-qt-dev libtbb-dev ffmpeg libdc1394-22-dev libavcodec-dev libavformat-dev libswscale-dev libjpeg-dev libjasper-dev lib
png++-dev libtiff5-dev libopenexr-dev libwebp-dev libhdf5-dev libpython3.5-dev python3-numpy python3-scipy python3-matplotlib libopenblas-dev liblapacke-dev
mkdir opencv && cd opencv
wget https://github.com/opencv/opencv/archive/3.3.0.tar.gz
tar xvf 3.3.0.tar.gz
mkdir opencv-3.3.0/build && cd opencv-3.3.0/build
cmake -G "Unix Makefiles" --build . -D BUILD_CUDA_STUBS=OFF -D BUILD_DOCS=OFF -D BUILD_EXAMPLES=OFF -D BUILD_JASPER=OFF -D BUILD_JPEG=OFF -D BUILD_OPENEXR=OFF -D BUILD_PACKAGE=ON -D BUILD_PERF_TESTS=OFF -D
BUILD_PNG=OFF -D BUILD_SHARED_LIBS=ON -D BUILD_TBB=OFF -D BUILD_TESTS=OFF -D BUILD_TIFF=OFF -D BUILD_WITH_DEBUG_INFO=ON -D BUILD_ZLIB=OFF -D BUILD_WEBP=OFF -D BUILD_opencv_apps=ON -D BUILD_opencv_calib3d=ON -D B
UILD_opencv_core=ON -D BUILD_opencv_cudaarithm=OFF -D BUILD_opencv_cudabgsegm=OFF -D BUILD_opencv_cudacodec=OFF -D BUILD_opencv_cudafeatures2d=OFF -D BUILD_opencv_cudafilters=OFF -D BUILD_opencv_cudaimgproc=OFF -
D BUILD_opencv_cudalegacy=OFF -D BUILD_opencv_cudaobjdetect=OFF -D BUILD_opencv_cudaoptflow=OFF -D BUILD_opencv_cudastereo=OFF -D BUILD_opencv_cudawarping=OFF -D BUILD_opencv_cudev=OFF -D BUILD_opencv_features2d=
ON -D BUILD_opencv_flann=ON -D BUILD_opencv_highgui=ON -D BUILD_opencv_imgcodecs=ON -D BUILD_opencv_imgproc=ON -D BUILD_opencv_java=OFF -D BUILD_opencv_ml=ON -D BUILD_opencv_objdetect=ON -D BUILD_opencv_photo=ON 
-D BUILD_opencv_python2=OFF -D BUILD_opencv_python3=ON -D BUILD_opencv_shape=ON -D BUILD_opencv_stitching=ON -D BUILD_opencv_superres=ON -D BUILD_opencv_ts=ON -D BUILD_opencv_video=ON -D BUILD_opencv_videoio=ON -
D BUILD_opencv_videostab=ON -D BUILD_opencv_viz=OFF -D BUILD_opencv_world=OFF -D CMAKE_BUILD_TYPE=RELEASE -D WITH_1394=ON -D WITH_CUBLAS=OFF -D WITH_CUDA=OFF -D WITH_CUFFT=OFF -D WITH_EIGEN=ON -D WITH_FFMPEG=ON -
D WITH_GDAL=OFF -D WITH_GPHOTO2=OFF -D WITH_GIGEAPI=ON -D WITH_GSTREAMER=OFF -D WITH_GTK=ON -D WITH_INTELPERC=OFF -D WITH_IPP=ON -D WITH_IPP_A=OFF -D WITH_JASPER=ON -D WITH_JPEG=ON -D WITH_LIBV4L=ON -D WITH_OPENC
L=ON -D WITH_OPENCLAMDBLAS=OFF -D WITH_OPENCLAMDFFT=OFF -D WITH_OPENCL_SVM=OFF -D WITH_OPENEXR=ON -D WITH_OPENGL=ON -D WITH_OPENMP=OFF -D WITH_OPENNI=OFF -D WITH_PNG=ON -D WITH_PTHREADS_PF=OFF -D WITH_PVAPI=OFF -
D WITH_QT=ON -D WITH_TBB=ON -D WITH_TIFF=ON -D WITH_UNICAP=OFF -D WITH_V4L=OFF -D WITH_VTK=OFF -D WITH_WEBP=ON -D WITH_XIMEA=OFF -D WITH_XINE=OFF -D WITH_LAPACKE=ON -D WITH_MATLAB=OFF ..
make -j8
sudo make install
```

