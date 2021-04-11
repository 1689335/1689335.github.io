
sudo docker commit 71851cd14c48 ubuntu_test
sudo docker save -o ubuntu_test.img ubuntu_test
root@ubuntu-VirtualBox:~# docker images
REPOSITORY          TAG                 IMAGE ID            CREATED                  SIZE
ubuntu              latest              f63181f19b2f        Less than a second ago   72.9MB
ubuntu_test         latest              e0e4d67ecb06        41 seconds ago           94MB
