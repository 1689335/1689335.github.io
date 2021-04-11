VBoxManage list hdds
VBoxManage modifyhd 0bc1f930-5460-4e41-ab6c-22c042b7d5ac   --resize 51200


virutalbox 全屏显示
点击【设备】，然后点击【安装增强功能】


df -ah   
fdisk /dev/sda
mkfs ext4 /dev/sda4
blkid

fstab
UUID=   /xxx ext4 defaults 0 0
partprobe

ubuntu安装
sed -i 's/archive.ubuntu.com/mirrors.ustc.edu.cn/g' /etc/apt/sources.list
apt-get install openssh-server
apt-get install vim
sudo apt-get install unity-tweak-tool

