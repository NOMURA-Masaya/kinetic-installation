# Ubuntu 16.04 / Mint 18 での ROS kinetic の導入  

<br />

2018/12/06  
60190091 野村　雅也  

<br />

※このマニュアルはうろ覚えで書いたものです

<br />

---

### [ターミナルからkineticフルバージョンのインストール]

ROSのダウンロード先の登録
> $sudo sh -c 'echo "deb http://packages.ros.org/ros/ubuntu xenial main" > /etc/apt/sources.list.d/ros-latest.list' 

公開鍵の取得
> $wget https://raw.githubusercontent.com/ros/rosdistro/master/ros.key -O - | sudo apt-key add - 

フルバージョンのROSのインストール
> $sudo apt-get update 

> $sudo apt-get install ros-kinetic-desktop-full  

---

### [ROSの初期設定]

パッケージの依存関係の初期化
> $sudo rosdep init

> $rosdep update

ターミナル用の環境変数の設定
> $cd

> $echo "source /opt/ros/kinetic/setup.bash" >> ~/.bashrc  

> $source ~/.bashrc

---

### [ワークスペースの準備]

> ~~$sudo apt-get update && sudo apt-get install build-essential~~

ROSのワークスペースの作成
> $mkdir -p ~/catkin_ws/src

> $cd catkin_ws/src

> $catkin_init_workspace  

ワークスペースをインストール環境に登録する
> $echo "source ~/catkin_ws/devel/setup.bash" >> ~/.bashrc

> $source ~/.bashrc

メイク **(ソースコードを変更するたびに実行する)**
> $cd ~/catkin_ws/

> $catkin_make

---

### [rosinstallの準備]

> $sudo apt-get install python-rosinstall



### [マスターの登録]

自分のPCを中心にROSを動かす場合
> $echo "export ROS_MASTER_URI=http://localhost:11311" >> ~/.bashrc

> $source ~/.bashrc

他のPCを中心にROSを動かす場合(マスターを動かすマシンのIPアドレスを書く)
> $echo "export ROS_MASTER_URI=http://192.168.X.XXX:11311" >> ~/.bashrc

> $source ~/.bashrc

---

### [Gazebo 7.14 ~ を利用する準備]

Gazeboのバージョンアップ（7.14以降になると成功）
> $sudo sh -c 'echo "deb http://packages.osrfoundation.org/gazebo/ubuntu-stable `lsb_release -cs` main" > /etc/apt/sources.list.d/gazebo-stable.list'

> $cd /tmp/

> $wget http://packages.osrfoundation.org/gazebo.key

> $sudo apt-key add gazebo.key

> $sudo apt-get update

> $sudo apt-get install gazebo7

> $sudo apt-get update

> $sudo apt-get upgrade

> $sudo reboot

バージョン確認
> $gazebo -v

GazeboとROSを連携するプラグインをインストール
> $sudo apt-get install -y ros-kinetic-gazebo-ros-control
> $sudo apt-get install -y ros-kinetic-ros-control ros-kinetic-ros-controllers


<br />
<br />
<br />



  
### 以下,トラブルシューティング  

---  

### [catkin_makeで”Could not find SDL”のようなエラーが出た時]

> $sudo apt-get install libsdl-dev

---

### [catkin_makeで.cfg関連のエラーが出た時]

> $cd catkin_ws/src

> $sudo find ./ -name "*.cfg" | xargs chmod 777

---

### [依存している関連パッケージをインストールしたい時(tis_cameraには適用不可)]

> $rosdep update

> $rosdep install --from-paths src --ignore-src --rosdistro=kinetic -y --os=ubuntu:xenial

> ~~$sudo apt-get update && sudo apt-get install libopenni2-dev~~

※　rosdep は~/catkin_wsで実行します

---

### [tfツリーの時間がおかしい時(重要)]

> &lt;node name="robot_state_publisher" pkg="robot_state_publisher" type="robot_state_publisher" respawn="false" output="screen" ns="/my_robo"&gt;  
> &nbsp;&nbsp;&nbsp;&nbsp;**&lt;param name="use_tf_static" value="false"/&gt;**  
> &lt;/node&gt;

※　launchファイルでのrobot_state_publisherの呼び出し時にパラメータ”use_tf_static”をfalseにする必要があります

---

### [Gazeboがクラッシュする時]

> $sudo apt-get dist-upgrade

> $sudo apt-get update

> $sudo apt-get upgrade

※　このあとcatkin_ws内の”devel”と”build”を削除してからcatkin_makeすることが重要です

---

