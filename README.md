# C++ implementation to transfer normals from one pointcloud/mesh to another

## What is in this repository?
This repository contains a script that transfer normals from an input ply file to another using KNN

## Dependencies

### Standard dev tools
On Ubuntu, you need to install the following packages:
```bash
sudo apt-get update
sudo apt-get install git build-essential cmake libx11-dev mesa-common-dev libgl1-mesa-dev libglu1-mesa-dev libxrandr-dev libxi-dev libxmu-dev libblas-dev libxinerama-dev libxcursor-dev libeigen3-dev
```

### Specific dependencies
1. [Eigen](https://eigen.tuxfamily.org/) (downloaded through sudo apt-get install)

## Installation instruction

To build, type into the console:
```bash
git clone https://github.com/rFalque/normals_transfer.git
cd normals_transfer
mkdir build
cd build
cmake ..
make
```

## Run the code

To run the code:
```bash
./normals_transfer path_to_file_with_normals.ply path_to_file_without_normals.ply output_file.ply
```
