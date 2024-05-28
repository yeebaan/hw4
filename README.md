# Steps to reproduce

Powershell:

```shell
mkdir C:/Users/user/ee6470
cd C:/Users/user/ee6470
git clone http://gitlab.larc-nthu.net/ee6470_TA/docker-images.git
cd C:/Users/user/ee6470/docker-images
docker build -f EE6470/Dockerfile.x86-64 -t ee6470/ubuntu-ee6470:latest ./EE6470
docker run -h ubuntu --rm --cap-add SYS_ADMIN -it -v "C:\\Users\\user:/home/user" ee6470/ubuntu-ee6470:latest
```

bash:

```shell
mkdir ~/ee6470
cd ~/ee6470
git clone http://gitlab.larc-nthu.net/ee6470_TA/docker-images.git
cd ~/ee6470/docker-images
docker build -f EE6470/Dockerfile.x86-64 -t ee6470/ubuntu-ee6470:latest ./EE6470
docker run -h ubuntu --rm --cap-add SYS_ADMIN -it -e LOCAL_USER_ID=$(id -u $USER) -v $HOME:/home/user ee6470/ubuntu-ee6470:latest
```

```shell
entrypoint.sh
source ~/ee6470/docker-images/EE6470/bashrc
cd ~/ee6470
git clone https://github.com/agra-uni-bremen/riscv-vp.git
cd ~/ee6470/riscv-vp
git submodule update --init --recursive
cd ~/ee6470
git clone https://gitlab.larc-nthu.net/ee6470_TA/sobel_riscv_vp.git
cp -r ~/ee6470/sobel_riscv_vp/riscv-vp/vp/src/platform/* ~/ee6470/riscv-vp/vp/src/platform
cp -r ~/ee6470/sobel_riscv_vp/riscv-vp/sw/* ~/ee6470/riscv-vp/sw
cd ~/ee6470
git clone https://github.com/yeebaan/hw4.git
cp -r ~/ee6470/hw4/vp/src/platform/* ~/ee6470/riscv-vp/vp/src/platform
cp -r ~/ee6470/hw4/sw/* ~/ee6470/riscv-vp/sw
mkdir ~/ee6470/riscv-vp/vp/build
cd ~/ee6470/riscv-vp/vp/build
cmake ..
make
cd ~/ee6470/riscv-vp/sw/basic-sobel
# make
make sim
```

after editing vp:

```shell
cp -r ~/ee6470/sobel_riscv_vp/riscv-vp/vp/src/platform/* ~/ee6470/riscv-vp/vp/src/platform && \
cp -r ~/ee6470/sobel_riscv_vp/riscv-vp/sw/* ~/ee6470/riscv-vp/sw && \
cp -r ~/ee6470/hw4/vp/src/platform/* ~/ee6470/riscv-vp/vp/src/platform && \
cp -r ~/ee6470/hw4/sw/* ~/ee6470/riscv-vp/sw && \
cd ~/ee6470/riscv-vp/vp/build && \
make && \
cd ~/ee6470/riscv-vp/sw/basic-sobel && \
make sim
```

after editing sw:

```shell
cp -r ~/ee6470/sobel_riscv_vp/riscv-vp/vp/src/platform/* ~/ee6470/riscv-vp/vp/src/platform && \
cp -r ~/ee6470/sobel_riscv_vp/riscv-vp/sw/* ~/ee6470/riscv-vp/sw && \
cp -r ~/ee6470/hw4/vp/src/platform/* ~/ee6470/riscv-vp/vp/src/platform && \
cp -r ~/ee6470/hw4/sw/* ~/ee6470/riscv-vp/sw && \
# cd ~/ee6470/riscv-vp/vp/build && \
# make && \
cd ~/ee6470/riscv-vp/sw/basic-sobel && \
make sim
```
