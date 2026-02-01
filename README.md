<div align="center"> 
  <h1 align="center">SpaceOS</h1>
  <h3 align="center">Welcome to the SpaceOS project</h3>
</div>

<div align="center">
  <img src="https://img.shields.io/badge/License-Apache2.0-blue"/>
  <img src="https://img.shields.io/badge/Language-C-orange"/>
  <img src="https://img.shields.io/badge/Hardware-x64-green"/>
  <img src="https://img.shields.io/badge/Firmware-UEFI/Legacy-yellow"/>
</div>

## 项目简介
SpaceOS 是 Uinxed-Kernel 的一个发行版，对 Uinxed-Kernel 新增并优化了一些功能，（此发行版适合**64位架构的低配置古董机**）。

目标：
 
 - 实现SPF解析（我们自制的可执行文件格式）
 - 实现一个简易的SpaceKernel，作为elf运行于现内核上
 - 实现SPFS（实际上未重构前的版本已经实现了）

## 核心特性
### ✅ 已实现功能
- Uinxed-Kernel所有基础功能
- 实现了自定义的OS版本格式（spaceos.h）

### 🚧 开发中/待实现 (TODOS)
- [ ] 自研 SpaceKernel 微内核（目标：实现类鸿蒙 TEE 的安全功能，专注私密信息处理与安全调用）
- [ ] 网络协议栈与基础网络功能实现
- [ ] 自研 SPF 可执行文件格式（逐步替换 ELF）
- [ ] 自研 SPFS 文件系统（支持设备识别、挂载与系统启动）
- [ ] 一个简易的GUI (SPUI)

## 开源协议
本项目的的开源协议是 Apache 2.0。

## 开源依赖
本项目基于以下开源项目进行二次开发：
- Uinxed-Kernel: [https://github.com/ViudiraTech/Uinxed-Kernel](https://github.com/ViudiraTech/Uinxed-Kernel)

## 常见问题 (FAQ)
### Q1: 为何暂未开源 SpaceKernel 内核代码？
A1: 开源了，自己去看，不过很多todos都没开始做

### Q2: SpaceKernel 内核的核心定位是什么？
A2: SpaceKernel 是 GoutouStdio 自研的微内核，设计目标是运行于独立的隔离环境中，核心职责为处理私密信息、响应安全功能调用；未来会根据需求逐步扩展其应用场景。

## 关于开发者
- 开发团队：[GoutouStdio](https://github.com/GoutouStdio-cn)
- 内核开发团队：[ViudiraTech](https://github.com/ViudiraTech)

## Stars
<picture>
  <source media="(prefers-color-scheme: dark)" srcset="https://api.star-history.com/svg?repos=GoutouStdio-cn/SpaceOS-X&type=Date&freq=monthly&theme=dark" />
  <source media="(prefers-color-scheme: light)" srcset="https://api.star-history.com/svg?repos=GoutouStdio-cn/SpaceOS-X&type=Date&freq=monthly" />
  <img alt="SpaceOS-X Star History Chart" src="https://api.star-history.com/svg?repos=GoutouStdio-cn/SpaceOS-X&type=Date&freq=monthly" style="width: 70%; max-width: 400px;"/>
</picture>

 - 感谢你为我们点的Stars
