# gds2Para
从 GDSII 设计文件到寄生参数提取的完整集成电路 (IC) 版图分析

该布局分析器是用 C++ 编写的，作为更广泛的 API 的一部分，用于 VLSI IC、封装和电路板设计的电磁设计验证。 代码设计遵循的理念旨在为日益复杂的集成电路、封装和电路板提供最大的可扩展性和最高水平的自动化。 来自图形数据库流 II (GDSII) 文件的设计信息被解析并与模拟输入信息一起存储。

非标准操作模式允许将互连建模平台 (IMP) 文件转换为 GDSII 文件设计。 另一种非标准控制模式将 GDSII 文件设计转换为 [平面直线图](http://mathworld.wolfram.com/PlanarStraightLineDrawing.html)，可用作三角测量软件的输入。

加载设计后，可以将信息写入另一个 GDSII 文件或使用全波仿真进行分析，以提取用户指定端口之间的寄生参数。 寄生参数最好通过 [Xyce](https://xyce.sandia.gov/) 子电路文件（来自桑迪亚国家实验室的 SPICE 衍生物）报告，尽管使用 [标准寄生交换格式 (SPEF)](https://ieeexplore. ieee.org/document/5430852) 文件可以交替输出。 请仔细阅读此 **README.md** 文件以获取概述、依赖项和使用说明。

## 概述
### 模拟 (-s) 模式顶层流程图
<img src="https://github.com/purdue-onchip/gdsii-interface/blob/master/images/gds2Para_mode-s.png" width=600 alt="Simulate (-s) Mode Flowchart">

## Packages
| Packages / Library               | Languages        | Headers                                | Description                                                       |
| -------------------------------- | ---------------- | -------------------------------------- | ----------------------------------------------------------------- |
| C Standard Library               | C                | CCtype, Cerrno, Cmath, Cstdio, Cstlib, Cstring, Ctime     | Utilities for testing character categorization, C language error numbers, basic arithmetic operations, C language input/output, manipulating the char\* data type, and dates and timers |
| C++ Standard Library: Algorithms | C++              | Algorithm                              | Useful algorithms including sorting                               |
| C++ Standard Library: Containers | C++              | Queue, Set, Stack, Unordered\_map, Unordered\_set, Vector | Utilities for handling queues and priority queues, sets and multisets, LIFO stacks, associative data types, dictionary collection types, and collection data types from existing C++ data types  |
| C++ Standard Library: I/O        | C++              | FStream, IOStream                      | Plain text file input/output and command line input/output        |
| C++ Standard Library: Numerics   | C++              | Complex                                | Complex floating point number arithmetic                          |
| C++ Standard Library: Strings    | C++              | String                                 | Utilities for easy string handling                                |
| C++ Standard Library: Utilities  | C++              | Utility                                | General C++ utilities such as pairs and swapping                  |
| [Eigen](http://eigen.tuxfamily.org/index.php?title=Main_Page)                                                             | C++              | Sparse                                 | API for sparse matrix storage                                     |
| [HYPRE](https://computation.llnl.gov/projects/hypre-scalable-linear-solvers-multigrid-methods)                            | Fortran/C/C++    | HYPRE, HYPRE_krylov, HYPRE_parcsr_ls   | LLNL library of preconditioners and multigrid solvers             |
| [Limbo](https://github.com/limbo018/Limbo)                            | C/C++            | GdsReader, GdsWriter                   | API for GDSII file parsing and writing                            |
| [MakeUtils](https://www.gnu.org/software/make/)                                                                           | Makefile         | n/a                                    | Makefile utilities that help find build dependencies              |
| [Math Kernel Library](https://software.intel.com/en-us/mkl)                                                               | Fortran/C/C++    | MKL, Mkl\_spblas                        | Intel libraries for parallel mathematics include BLAS, LAPACK, and Pardiso                         |
| [Open Message Passing Interface](https://www.open-mpi.org/)                                                               | Fortran/C        | n/a                                    | Open MPI compilation and runtime tools for parallel computing     |
| [Parser-SPEF](https://github.com/OpenTimer/Parser-SPEF/)                      | C++              | parser-spef                            | API for SPEF file processing                                      |
| Preprocessor                     | C/C++            | n/a                                    | Inclusion, definitions, and macros such as assertion with message |

请注意，需要支持以下语言标准的现代编译器来生成包依赖项：用于 Fortran 的 GNU Fortran（F95 的超集）、用于 C 语言的 C99 和用于 C++ 的 C++17。

## Custom Classes
| Structure / Class Name   | Header                  | Description                                                       |
| ------------------------ | ----------------------- | ------------------------------------------------------------------|
| AsciiDataBase            | limboint                | 使用文件名、元数据、单位、所有几何单元的数据和导体信息读取/构建完整的 GDSII 设计 |
| GeoCell                  | limboint                | 具有名称、元数据和所有 GDSII 元素的 GDSII 几何单元                   |
| boundary                 | limboint                | 多边形边界的 GDSII 元素                                            |
| path                     | limboint                | 路径的 GDSII 元素                                                  |
| node                     | limboint                | 用于电气节点的 GDSII 元件                                           |
| box                      | limboint                | 框轮廓的 GDSII 元素                                                |
| textbox                  | limboint                | 文本框的 GDSII 元素                                                |
| sref                     | limboint                | 用于结构参考的 GDSII 元素                                           |
| aref                     | limboint                | 用于数组引用的 GDSII 元素                                           |
| strans                   | limboint                | 应用于某些 GDSII 元素的线性变换                                     |
| pslg                     | limboint                | PSLG 的顶点、线段连接和区域列表                                     |
| SolverDataBase           | solnoutclass            | 设计名称、输出文件、布局以外的信息以及参数提取所需的所有模拟结果        |
| SimSettings              | solnoutclass            | 仿真设置，包括单位、设计限制和频率扫描参数                            |
| Layer                    | solnoutclass            | 来自物理堆叠的层信息，包括名称、GDSII 层编号、z 坐标和材料属性         |
| Waveforms                | solnoutclass            | 时域图所需的信息（未实现）          |
| Parasitics               | solnoutclass            | 用于导纳参数的端口和稀疏矩阵的集合                                   |
| Port                     | solnoutclass            | 端口信息包括名称、参考方向、供应和返回坐标，并包含 GDSII 层            |
| Aperture                 | solnoutclass            | Gerber 光绘仪光圈的标准模板细节                                     |
| fdtdMesh                 | fdtd                    | 所有离散化、导体和求解器数据的主类                                   |
| fdtdPatch                | fdtd                    | 单个离散化补丁的信息                                                |
| fdtdBound                | fdtd                    | 单个导体或电介质边界区域的信息                                       |
| fdtdCdt                  | fdtd                    | 所有导体通用的求解器信息                                            |
| fdtdOneCondct            | fdtd                    | 有关单个导体区域的离散化和激励的求解器信息                            |
| fdtdPort                 | fdtd                    | 端口的求解器表示                                                    |

## 开发者
所有软件都在积极开发中，没有任何关于更新性质时间的通知。 欢迎通过分支和[拉取请求](https://github.com/purdue-onchip/gds2Para/pulls)做出贡献。 请将与此存储库相关的所有问题、错误报告和问题直接发送给主要维护者：
* [Michael Hayashi](mailto:mhayashi@purdue.edu?subject=Inquiry%20for%20gdsii-interface)，普渡大学ECE学院研究生研究助理

开发者:
* Michael Hayashi，普渡大学 ECE 学院研究生研究助理
* 李雪，普渡大学ECE学院研究生研究助理
* Shuzhan Sun，普渡大学 ECE 学院研究生研究助理

非常感谢项目发起人使该软件的开发成为可能：

| <img src="https://github.com/purdue-onchip/gdsii-interface/blob/master/images/purdue.png" width=100 alt="Purdue University"> | <img src="https://github.com/purdue-onchip/gdsii-interface/blob/master/images/DARPA.png" width=100 alt="DARPA ERI"> |
| :---: | :---: |

## 安装和使用
按照 **INSTALL.md** 中给出的说明安装此软件并从命令行运行它。 普渡大学的用户应该阅读 **purdue\_install.md** 针对他们环境的特定步骤。

## 仿真输入文件 (.sim_input) 语法
每个 GDSII 文件都需要有一个模拟输入文件，并为其创建扩展名为 .sim\_input 的文件。 本节底部给出了模拟输入文件的自定义语法。 重要的是，所有大写字母的标题下方的块中的信息按给定的顺序出现。 注释以“#”开头，并在该行的其余部分继续。 只要行内注释前面有一个空格，注释几乎可以出现在文件中的任何位置。 以下是占位符、尖括号和中间的单词，必须根据设计填充：
* \<六个设计范围>：包围设计的最小直角棱柱的六个坐标，隐含单位的顺序为 xmin（设计中最小的 x 坐标）、xmax、ymin、ymax、zmin 和 zmax（设计中的最小 x 坐标） 设计中最大的 z 坐标）。
     * 小写的“e”可用于科学记数法。
    * 例如, `30.00 +149. -47.0 +120. 0.00 +7.53`。
* \<长度单位lengthUnit>：所有给定和报告的长度（例如，设计的总尺寸、层坐标和高度以及端口坐标）必须乘以以转换为米的单位。 小写的“e”可用于科学记数法。 例如，`1e-6`。
* \<freqUnit>: 所有给定和报告的时间频率必须相乘以转换为赫兹的单位。 小写的“e”可用于科学记数法。 例如，`1.0e+6`。
* \<freqStart>: 带有隐含单位的频率扫描中的最小频率。 例如，`1000.0`。
* \<freqEnd>: 带有隐含单位的频率扫描中的最大频率。 例如，`3000.0`。
* \<nfreq>: 要包含在扫描中的频率总数。 `1` 的值意味着 \<freqEnd> 必须等于 \<freqStart>。 `2` 的值意味着只包含 \<freqStart> 和 \<freqEnd>。 任何更大的整数都需要插值。
* \<freqScale>: 表示频率插值比例的整数。 对于对数间距，推荐值为“0”。 值“1”用于线性间距。
* \<numLayer>: 此设计中的总层数。 此处的整数必须与文件中此行之后的活动 \<layer entry> 行数相匹配。
* \<layer entry>: 代表单个图层的整条线。
    * 必须按顺序包含的四项信息是行首的图层名称、图层底部的 z 坐标（在带有隐含单位的长度之前用 'z = ' 指定）、图层的高度 层（在带有隐含单位的长度之前用“h =”指定），以及构成该层绝缘部分的电介质的相对介电常数（在大于或等于无单位浮点数之前用“e =”指定） 统一）。
    * 小写的“e”可用于科学记数法。
    * 为了保持与 GDSII 文件中使用的层编号的对应关系，层名称必须是纯整数（推荐）或者是在层编号前带有大写“M”的字母数字字符串。
    * 每个层条目的可选规范包括该层中导体的电导率（在以 S/m 为单位的非负浮点数之前指定为 'sigma = '）和介电损耗正切（在非负浮点数之前指定为 'TanD = ' ，无单位浮点数）。
    * 建议在最底部的 GDSII 层下方添加一层，在最顶部的 GDSII 层上方添加第二层，作为完美电导体 (PEC) 的平面，代表设计在测试环境中的表现。
    * 例如, `ILDM2 z = 1.316 h = 0.12 e = 8.0`.
* \<numPorts>: 此设计中的端口总数。 此处的整数必须与文件中此行之后的活动 \<port entry> 行数相匹配。
* \<port entry>: 代表单个端口激励的整条线。
    * 必须按顺序包含的八项信息是端口名称、端口供应点的 x 坐标、端口供应点的 y 坐标、端口供应点的 z 坐标。 端口，端口返回点的x坐标，端口返回点的y坐标，端口返回点的z坐标，端口的方向性。
    * 共享相同名称的端口条目将被转换为具有多个激励的单个端口。
    * 小写的“e”可用于科学记数法。
    * 端口的方向性对于输入端口为“+1”，对于输出端口为“-1”，或者对于双向端口或具有不确定功率流的端口为“0”。
    * 应该为器件的每个输入/输出引脚添加一个端口。 设计中的每个晶体管或其他有源器件都需要额外的端口。 对于印刷电路板 (PCB)，填充布局上的每个组件至少需要一个端口。
    * 例如, `port1 +146. -16.0 4.53 +146. +6.00 4.53 -1`.

```
TOTAL SIZE
<six design extents>
lengthUnit = <lengthUnit>

FREQUENCY
freqUnit = <freqUnit>
freqStart = <freqStart>
freqEnd = <freqEnd>
# Block-interrupting comment
nfreq = <nfreq>
freqScale = <freqScale>

DIELECTRIC STACK
numStack = <numLayer>
<layer entry> # In-line comment
<...>
<layer entry> # In-line comment
# Post-block comment

PORT
numPorts = <numPorts>
<port entry> # In-line comment
<...>
<port entry> # In-line comment
# Post-block comment
```

## 致谢
* 示例文件
    * [Purdue On-Chip Electromagnetics Laboratory](https://engineering.purdue.edu/~djiao/) for **singleStrip.imp** (single stripline)
    * [Yuan Ze University Design Automation library](http://yzuda.org/download/_GDSII_examples.html) for **inv.gds** (inverter logic gate), **nand2.gds** (2-input NAND gate), and **xor.gds** (XOR gate)
    * [NanGate Open Cell Library FreePDK45](https://www.cs.upc.edu/%7Ejpetit/CellRouting/nangate/Front_End/Doc/Databook/Cells/SDFFRS_X2_NangateOpenCellLibrary_typical_typical.html) for **SDFFRS\_X2.gds** (scan D flip-flop with reset/set)
    * [Peter Monta](https://github.com/pmonta/FPGA-netlist-tools/tree/master/masks/4004) and the [Tuva Design Intel 4004 Anniversary Project](http://4004.com/) for **4004.gds** (Intel 4004 processor from 1971)
    * [Open Compute Project](https://www.opencompute.org/wiki/Networking/SpecsAndDesigns#Facebook_Wedge_100_-_32x100G) for original Gerber files for Facebook Wedge 100 that led to **WEDGE100_REV01.gds** (100G Ethernet Switch board)
* Prof. Dan Jiao of the Purdue On-Chip Electromagnetics Laboratory for her guidance of the project
* The staff of the Defense Advanced Research Projects Agency (DARPA) Microsystems Technology Office (MTO) for their sponsorship, feedback, and support of this endeavor
* Prof. C.J. Richard Shi and the students of the [University of Washington RAIL](https://sites.google.com/uw.edu/ssrl/people?authuser=0) research group for [supplying designs](https://github.com/rail-posh) and validating solver results against commercial tools
* The other contributors of the [Intelligent Design of Electronic Assets (IDEA)](https://github.com/aolofsson/IDEA) team and the [Posh Open Source Hardware (POSH)](https://github.com/aolofsson/POSH) team within the DARPA Electronics Resurgence Initiative (ERI)

## 许可
GNU Public License v2.0 (see **LICENSE**)
