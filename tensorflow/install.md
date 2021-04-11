---
sort: 1
---

# install

adaconada:
https://mirrors.tuna.tsinghua.edu.cn/anaconda/archive/

conda config --add channels https://mirrors.tuna.tsinghua.edu.cn/anaconda/pkgs/free/
conda config --add channels https://mirrors.tuna.tsinghua.edu.cn/anaconda/pkgs/main/
conda config --set show_channel_urls yes

conda info

jupytor notebook --generat-config

修改：~/.jupyter/jupyter_notebook_config.py
c.NotebookApp.notebook_dir = 'local dir'


conda install package
conda remove  package
conda update


tensorflow：

conda create --name tensorflow2.0 python=3.7
conda create -n tensorflow2.0 python=3.7


conda env list
activate tensorflow2.0


pip install numpy matplotlib pillow scikit-learn pandas -i https://pypi.tuna.tsinghua.edu.cn/simple
pip3 install
pip install tensorflow==2.0.0-beta

或者
conda install numpy matplotlib PIL scikit-learn pandas
conda install tensorflow==2.0.0-beta


import tensorflow as tf
