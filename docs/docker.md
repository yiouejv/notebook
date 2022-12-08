
## 安装docker

```
curl -fsSL https://get.docker.com -o get-docker.sh
sudo sh get-docker.sh
```

## 概念

- 镜像（Image): 相当于一个root文件系统。比如官方镜像ubuntu:16.04就包含了一套完整的Ubuntu16.04最小系统的root文件系统
- 容器（Container）: 镜像（Image）和容器的关系，容器是镜像运行的实体
- 仓库 （Repository）：保存镜像

## 配置镜像加速器

```
sudo mkdir -p /etc/docker
sudo tee /etc/docker/daemon.json <<-'EOF'
{
    "registry-mirrors": ["https://docker.mirrors.ustc.edu.cn"]
}
EOF
sudo systemctl daemon-reload
sudo systemctl restart docker
```

## command

- 启动: systemctl start docker
- 停止: systemctl stop docker
- 重启: systemctl restart docker
- 查看状态: systemctl status docker
- 开启自启: systemctl enable docker

## 镜像相关命令

hub.docker.com

- 查看镜像: docker images
- 搜索镜像: docker search redis
- 拉取镜像: docker pull redis[:3.2]
- 删除镜像: docker rmi redis

    docker rmi iamgeID

    docker rmi redis[:版本号]

## 容器相关命令

- 创建容器:

    docker run -it --name=c1 redis:latest /bin/bash

    -i, 保持一直运行

    -t, 分配一个终端

    --name, 给容器起一个名字

    /bin/bash, 进入容器的初始化指令

    --------------------

    docker run -id --name=c1 redis:latest [不加默认也是bash]

    -d, 后台运行一个容器

- 查看容器: docker ps, 查看正在运行的容器

    docker ps -a, 查看所有容器
    docker ps -aq, 查看容器的id

- 进入容器: docker exec -it c1 /bin/bash
- 退出容器: exit
- 启动容器: docker start c1
- 停止容器: docker stop c1
- 删除容器: docker rm c1
- 查看容器信息: docker inspect c1

## 数据卷

- docker容器删除后，在容器中产生的数据还在吗?

    删除后，数据不在了

- docker容器和外部机器可以直接交换文件吗？

    不能直接交换文件

- 容器之间想要进行交换数据

    数据卷

-----------------------

数据卷是宿主机中的一个目录或文件

当容器目录和数据卷目录绑定后，对方的修改会立即同步

一个数据卷可以被多个容器同时挂载

一个容器可以挂载多个数据卷

----------------------------- 

数据卷的作用：

- 容器数据持久化
- 外部机器和容器间接通信
- 容器之间数据交换


### 配置数据卷

创建/启动容器时，使用-v

```
docker run ... -v 宿主机目录(文件):容器内目录(文件) ...
```

注意事项:

- 目录必须是绝对路径
- 如果目录不存在，会自动创建

