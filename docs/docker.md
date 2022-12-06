
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

- 查看镜像: docker images
- 搜索镜像:
- 拉取镜像:
- 删除镜像:
