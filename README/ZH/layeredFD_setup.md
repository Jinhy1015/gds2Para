# 如何设置分层有限差分求解器
请按照这些说明在 Linux 系统或 Windows 系统中运行分层 FD 求解器。 请将所有问题、错误报告和问题直接发送给主要维护者：
* [Shuzhan Sun](mailto:sun630@purdue.edu?subject=Inquiry%20for%20gds2Para)，普渡大学ECE学院研究生研究助理

## Linux 系统
头文件“fdtd.hpp”中的宏“SKIP_LAYERED_FD”在layeredFD求解器和V0Vh求解器之间切换。 每个的设置是：
* 案例1: 在 Linux 中运行 V0Vh 求解器
```C++
#define SKIP_LAYERED_FD
```

* 案例2: run layeredFD solver in Linux
```C++
// #define SKIP_LAYERED_FD
```

其他一切都与[V0Vh求解器](https://github.com/purdue-onchip/gds2Para/blob/master/purdue_install.md)相同，包括命令、最终参数和存储样式。

## Windows 系统
目前，Windows 系统仅支持 layeredFD 求解器，以上宏`SKIP_LAYERED_FD`在 Windows 系统中不再改变任何内容。
### 如何在 Visual Studio 中设置（在 Visual Studio 2017 中测试）:
1. 在文件夹 `gds2Para` 旁边创建一个 Visual Studio 项目，并且只在项目中包含这些文件：
```bash
fdtd.hpp
generateStiff.cpp
layeredFdtd.hpp
mapIndex.hpp
matrixTypeDef.hpp
mesh.cpp
pardisoSolver.hpp
sysInfoIO.hpp
```
2. 编辑 Visual Studio 项目的“配置”以包含英特尔 MKL。 一个简单的方法是安装 [Intel Parallel Studio XE](https://software.intel.com/en-us/parallel-studio-xe/choose-download)，它对学生免费。
3. 写一个main函数调用layeredFD求解器，放在VS工程解法（.sln）旁边。 示例主函数是`layeredFD.cpp`：
```C++
#include "gds2Para/src/layeredFdtd.hpp"
int main(void) {
    layeredFdtd();
    return 0;
}
```
### 如何在 Visual Studio 中运行
1. 在 Linux 中运行 layeredFD 求解器（可以用`Ctrl+Z` 停止更早）以在文件夹`gds2Para` 旁边生成一个文件夹`temp_sysInfoIO`。 这一步将结构信息导出到几个txt文件中。 这一步是必须的，因为很多加载gds文件的代码在Windows系统中是无法编译的。
2. 回到 Visual Studio，在 `Debug/Release x64/x86` 模式下，在 VS 中运行 `Local Windows Debugger` 以获取 Z 参数。
