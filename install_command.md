# Ubuntu 16.04 / Mint 18 での ROS kinetic の導入  


2018/12/06  
60190091 野村　雅也  


基本は下のサイトの手順で進めると良いです.(kineticより古いindigoなので注意)  
http://bril-tech.blogspot.com/2016/10/ros1-robot-operating-system.html  

※このマニュアルはうろ覚えで書いたものです

---
  
### [ターミナルからkineticフルバージョンのインストール]

> $sudo sh -c 'echo "deb http://packages.ros.org/ros/ubuntu xenial main" > /etc/apt/sources.list.d/ros-latest.list' 

> $wget https://raw.githubusercontent.com/ros/rosdistro/master/ros.key -O - | sudo apt-key add - 

> $sudo apt-get update 

> $sudo apt-get install ros-kinetic-desktop-full

---

### [ROSの初期設定]

> $sudo rosdep init

> $rosdep update

> $echo "source /opt/ros/kinetic/setup.bash" >> ~/.bashrc

---

### [ワークスペースの準備]

> $sudo apt-get update && sudo apt-get install build-essential

> $mkdir -p ~/catkin_ws/src

> $cd catkin_ws/src

> $catkin_init_workspace

> $source /opt/ros/kinetic/setup.bash

> $echo $ROS_PACKAGE_PATH

> $catkin_make

---

### [catkin_makeで”Could not find SDL”のようなエラーが出た時]

> &sudo apt-get install libsdl-dev

---

### [依存している関連パッケージをインストールしたい時(tis_cameraには適用不可)]

> $rosdep update

> $rosdep install --from-paths src --ignore-src --rosdistro=kinetic -y --os=ubuntu:xenial

> ($sudo apt-get update && sudo apt-get install libopenni2-dev)

※　rosdep はcatkin_wsで実行します

---

### [Gazeboがクラッシュする時]

> $sudo apt-get dist-upgrade

> $sudo apt-get update

> $sudo apt-get upgrade

※　このあとcatkin_ws内の”devel”と”build”を削除してからcatkin_makeすることが重要です

---

### [tfツリーの時間がおかしい時(重要)]

> &lt;node name="robot_state_publisher" pkg="robot_state_publisher" type="robot_state_publisher" respawn="false" output="screen" ns="/my_robo"&gt;  
> &nbsp;&nbsp;&nbsp;&nbsp;**&lt;param name="use_tf_static" value="false"/&gt;**  
> &lt;/node&gt;

※　launchファイルでのrobot_state_publisherの呼び出し時にパラメータ”use_tf_static”をfalseにする必要があります
