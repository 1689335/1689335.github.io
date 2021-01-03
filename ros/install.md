---
sort: 1
---

# install

**更换科大源**
```
sudo sh -c 'echo "deb https://mirrors.ustc.edu.cn/ros/ubuntu $(lsb_release -sc) main" > /etc/apt/sources.list.d/ros-latest.list'

sudo apt-key adv --keyserver 'hkp://keyserver.ubuntu.com:80' --recv-key C1CF6E31E6BADE8868B172B4F42ED6FBAB17C654

sudo apt-get update
sudo apt-get upgrade
sudo apt-get install ros-kinetic-desktop-full
sudo apt-get install python-rosinstall
```

**安装依赖包**
```
sudo rosdep init
rosdep update
```

**科大源**  

<http://mirrors.ustc.edu.cn/help/ros.html?highlight=ros>

**参考**  

<https://zhuanlan.zhihu.com/p/107218921>

