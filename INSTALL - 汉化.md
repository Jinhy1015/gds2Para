# 通用安装和使用说明
请按照这些说明在 Linux 机器上进行一般部署。 尝试为自己部署此代码时，有许多复杂情况可能会导致失败，但本指南试图规定广泛的措施来避免这些问题。 由于不同操作系统环境的可变性，无法始终针对某些问题提供补救措施。 **purdue\_install.md** 中有一个单独的指南，供在普渡大学工作的用户解决他们的特定挑战。

## 安装和使用
1.通过查看这些类别中的以下每个命令是否有输出，确保机器上安装了以下程序：

    * Selected package manager development tools
* GNU Autoconf: `which autoconf`

**GNU Autoconf是一个在Bourne shell下制作供编译、安装和打包软件的配置脚本的工具[1]。Autoconf并不受程式语言限制，常用于C、C++、Erlang和Objective-C。配置脚本控制了一个软件包在特定系统上的安装。在进行一系列测试后，配置脚本从模板中生成makefile与头文件进而调整软件包，使之适应某一种系统。Autoconf与Automake、Libtool等软件组成了GNU构建系统[2]。Autoconf由戴维·麦肯思于1991年夏天编写用于支持他在自由软件基金会的编程工作[3]。此后，Autoconf包含了多人编写的改进代码并成为了使用最广泛的自由编译配置软件。**
         
* GNU Automake: `which automake`
**GNU Automake是一种编程工具，可以产生供make程序使用的Makefile，用来编译程序。它是自由软件基金会发起的GNU计划的其中一项，作为GNU构建系统的一部分。automake所产生的Makefile符合GNU编程标准。**

* GNU Bison: `which bison`
**GNU bison（Bison意为犎牛；而Yacc与意为牦牛的Yak同音）是一个自由软件，用于自动生成语法分析器程序，实际上可用于所有常见的操作系统。Bison把LALR形式的上下文无关文法描述转换为可做语法分析的C或C++程序。在新近版本中，Bison增加了对GLR语法分析算法的支持。**

* Flex: `which flex`
**fast lexical analyzer generator）是一种词法分析程序。它是lex的开放源代码版本，以BSD许可证发布。通常与GNU bison一同运作，但是它本身不是GNU计划的一部分。**

* GNU Compiler Collection (GCC version 7 or newer): `which gcc`, `which g++`, and `which gfortran`
**编译器**

* GNU Make: `which make`
**编译命令**

* Boost C++ Libraries (Boost version 1.57.0 or newer): `locate "filtering_stream.hpp"`
**加速运行库**
**安装命令
   apt-cache search boost
   apt-get install libboost-all-dev**
    
* CMake (CMake version 3.7.0 or newer): `which cmake` and `cmake --version`
**ubuntu需更新到最新版本**
** 查看版本号 cmake --version 
apt remove cmake**

    * git: `which git`
    * Intel Math Kernel Library (MKL): `locate "mklvars.sh"`
    
    *MKL下载地址
    https://software.intel.com/content/www/us/en/develop/articles/oneapi-standalone-components.html#onemkl
    wget
    chmod u+x *.sh
    ./*.sh
    安装位置/opt/intel/oneapi
    
    * Lemon: `which lemon`
    * OpenMPI (OpenMPI version 4.0.1 or newer): `which mpicc`, `which mpicxx`
    * Zlib (Zlib version 3.13 or newer): `locate "zlib.h"`
    * 如果没有安装这些程序中的任何一个，那么建议具有 root 访问权限的人使用包管理器（大多数程序）或通过从源代码构建（GCC、Boost 和 OpenMPI）来安装缺少的任何程序。
    
2. 使用以下命令将此存储库克隆到您的工作位置 `git clone git@github.com:purdue-onchip/gds2Para.git`
    * 如果克隆失败，通常的原因是无法与服务器建立安全连接。 克隆很重要，以便能够使用 `git` 接收更新。 这些步骤将帮助你开始使用 `git`：
        1. 通过在您的主目录中运行 `ls -lh .ssh` 来检查您是否有任何公钥，例如 **id_rsa.pub**
        2. 如果没有出现公钥，则通过在您的主目录中运行 `ssh-keygen -t rsa -C <email>` 来生成一个，其中 \<email> 是您的工作电子邮件地址（请注意，此实用程序可能不适用于所有机器）
        3. 密钥生成命令将要求您单击“Enter”将公钥放置在默认位置，然后再单击"Enter"两次以放弃额外的密码保护
        4. 在文本编辑器中打开公钥 **id_rsa.pub**； 例如，运行`vim ~/.ssh/id_rsa.pub`
        5. 在您的 GitHub 帐户中，转到 [您帐户设置下的 SSH 和 GPG 密钥](https://github.com/settings/keys) 并单击绿色的“新建 SSH 密钥”按钮
        6. 给这个 SSH 公钥标题，例如"Work Network"
        7. 将在文本编辑器中打开的 **id_rsa.pub** 的内容逐字复制并粘贴到关键字段中
        8. 单击绿色的“添加 SSH 密钥”按钮
        9. 导航回您的工作位置并再次尝试克隆存储库
    * 如果克隆和 SSH 密钥生成失败，请尝试通过单击此存储库代码选项卡上的绿色“克隆或下载”按钮，然后单击"下载 ZIP"来下载文件
        1. 将 zip 存档移动到工作位置
        2. 使用命令 `unzip gds2Para-master.zip` 解压缩档案
        3. 将最近创建的目录从"gds2Para-master"重命名为"gds2Para"
3. 使用 `git clone https://github.com/limbo018/Limbo.git` 将 [Limbo 存储库](https://github.com/limbo018/Limbo) 克隆到您的工作位置
    * 如果克隆失败，请尝试通过单击 Limbo 存储库代码选项卡上的绿色“克隆或下载”按钮，然后单击“下载 ZIP”来下载文件
        1. 将 zip 存档移动到工作位置
        2. 使用“unzip Limbo-master.zip”解压缩存档
        3. 将最近创建的目录从“Limbo-master”重命名为“Limbo”
4. 使用 `git clone https://github.com/OpenTimer/Parser-SPEF.git` 将 [Parser-SPEF 存储库](https://github.com/OpenTimer/Parser-SPEF) 克隆到您的工作位置
    * 如果克隆失败，请尝试通过单击 Parser-SPEF 存储库代码选项卡上的绿色“克隆或下载”按钮，然后单击“下载 ZIP”来下载文件
        1. 将 zip 存档移动到工作位置
        2. 使用“unzip Parser-SPEF-master.zip”解压缩档案
        3. 将最近创建的目录从“Parser-SPEF-master”重命名为“Parser-SPEF”
5. 使用 `git clone https://github.com/eigenteam/eigen-git-mirror 将 [eigen-git-mirror 存储库](https://github.com/eigenteam/eigen-git-mirror) 克隆到您的工作位置
    * 如果克隆失败，请尝试通过单击 eigen-git-mirror 存储库的“代码”选项卡上的绿色“克隆或下载”按钮，然后单击"下载 ZIP"来下载文件
        1. 将 zip 存档移动到工作位置
        2. 使用 `unzip eigen-git-mirror-master.zip`解压缩档案
        3. 将最近创建的目录从"eigen-git-mirror-master"重命名为"eigen-git-mirror"
6. 确保您是具有完全读/写/执行权限的下载文件的所有者
    * 使用命令 `chown -R <username>:<username> <directory>` 修改所有权, 此处 \<username> 为用户名 \<directory> 分别为 "gds2Para/", "Limbo/", "Parser-SPEF/", 或 "eigen-git-mirror/"
    * 修改权限 `chmod -R 744 <directory>`, 此处 \<directory> 分别为 "gds2Para/", "Limbo/", "Parser-SPEF/", 或 "eigen-git-mirror/"
7. 根据 `echo $SHELL` 指示的 shell 修改运行命令文件，将 \<absolute path to C compiler> 替换为 C 语言编译器的有效路径，\<absolute path to C++ compiler> 替换为有效路径C++ 编译器，\<Fortran 编译器的绝对路径> 用于 Fortran 编译器的有效路径，\<OpenMPI 二进制文件的绝对路径> 用于 OpenMPI 二进制文件的有效路径，\<OpenMPI 静态库的绝对路径> 用于有效路径到 OpenMPI 静态库，\<Boost 目录的绝对路径> 为 Boost C++ 头文件目录的有效路径，\<Limbo 目录的绝对路径> 为 Limbo 目录的有效路径，\<Parser-SPEF 的绝对路径directory> 为 Parser_SPEF 目录的有效路径，\<本征目录的绝对路径> 为本征目录的有效路径，\<未来 HYPRE 目录的绝对路径> 为尚未创建的 HYPRE 目录的有效路径，和 \<absolute path to MKL directory> 为 Intel Math Kernal L 的有效路径ibrary (MKL) 目录
    * 对于 Trusted Silicon Stratus 的用户，前面的安装步骤已经为您完成，因此在您的主目录中编辑文件".bashrc"，附加以下内容：
    ```bash
    # Skip rest of file if not interactive
    if [ -z "$PS1" ]; then
        return
    fi

    # User specific aliases and functions
    source /opt/gds2Para_setup.sh
    ```
    * For "bash", edit the file ".bashrc" in your home directory by appending the following:
    ```bash
    # Skip rest of file if not interactive
    if [ -z "$PS1" ]; then
        return
    fi

    # Environment Variables for Compilers
    export CC=<absolute path to C compiler>
    export CXX=<absolute path to C++ compiler>
    export FC=<absolute path to Fortran compiler>

    # Environment Variables for OpenMPI
    export OMPI_CC=$CC
    export OMPI_CXX=$CXX
    export OMPI_FC=$FC
    export PATH=<absolute path to OpenMPI binaries>:$PATH
    export LD_LIBRARY_PATH=<absolute path to OpenMPI static libraries>:$LD_LIBRARY_PATH

    # Environment Variables for GDSII File Handling
    export BOOST_DIR="<absolute path to Boost directory>"
    export LIMBO_DIR="<absolute path to Limbo directory>"
    export PARSER_SPEF_DIR="<absolute path to Parser-SPEF directory>"
    export EIGEN_DIR="<absolute path to Eigen directory>"
    export HYPRE_DIR="<absolute path to future HYPRE directory>"
    export MKL_DIR="<absolute path to MKL directory>"
    ```
    * 对于“tcsh”，通过附加以下内容来编辑主目录中的文件“.cshrc”:
    ```tcsh
    # 如果不交互，则跳过文件的其余部分
    if (! $?prompt) then
        exit 0
    endif

    # 编译器的环境变量
    setenv CC <absolute path to C compiler>
    setenv CXX <absolute path to C++ compiler>
    setenv FC <absolute path to Fortran compiler>

    # OpenMPI 的环境变量
    setenv OMPI_CC ${CC}
    setenv OMPI_CXX ${CXX}
    setenv OMPI_FC ${FC}
    setenv PATH <absolute path to OpenMPI binaries>:${PATH}
    setenv LD_LIBRARY_PATH <absolute path to OpenMPI static libraries>:${LD_LIBRARY_PATH}

    # GDSII 文件处理的环境变量
    setenv BOOST_DIR <absolute path to Boost directory>
    setenv LIMBO_DIR <absolute path to Limbo directory>
    setenv PARSER_SPEF_DIR <absolute path to Parser-SPEF directory>
    setenv EIGEN_DIR <absolute path to Eigen directory>
    setenv HYPRE_DIR <absolute path to future HYPRE directory>
    setenv MKL_DIR <absolute path to MKL directory>
    ```
    * 确保编译器版本支持以下标准：用于 Fortran 的 GNU Fortran（F95 的超集）、用于 C 语言的 C99 和用于 C++ 的 C++17。
    * 用于深度神经网络的英特尔 MKL-DNN **不**与安装兼容，只有常规英特尔 MKL 兼容
8. 在重新登录之前退出shell并终止连接
9. 通过运行 `echo $LIMBO_DIR` 确保正确加载了运行命令文件
    * 如果 "bash" 用户没有任何显示，请在主目录中运行 `cp .bashrc .bash_profile`，退出 shell，重新登录，然后重试
    * 如果“tcsh”用户没有任何显示，请在主目录中运行`cp .cshrc .tcshrc`，退出shell，重新登录，然后重试
    * 对于所有其他错误，请联系主要维护者
10. 从工作位置进入目录“Limbo”
11. 运行 `git reset --hard 3.3.0` 以恢复到早期版本的存储库
    * 只有在引入 CMake 作为构建整个 Limbo 的方式之前，运行 gds2Para 所需的 Limbo 组件的部分安装才可行
    * 仅使用这些说明从 Limbo 构建必要的解析器，想要使用其他 Limbo 功能的用户应遵循该存储库中给出的安装说明
    * （可选）相信 Limbo 的必要组件和大多数其他组件可以按照这些说明使用 Limbo 顶层目录中的 `make` 构建，但这尚未经过测试
12. 按照文件 /Limbo/limbo/thirdparty/lefdef/5.8/lefdefReadme.txt 中的说明安装第三方 LEF 和 DEF 阅读器
13. 编译 Limbo 的解析器
    * Limbo 的 GDSII 解析器：进入目录“/Limbo/limbo/parsers/gdsii/stream”。 在此目录中运行 `make -j 2` 以构建某些 Limbo 库
    * Limbo 的 LEF 解析器：进入目录“/Limbo/limbo/parsers/lef/adapt”。 运行`make -j 2`。
    * Limbo 的 DEF 解析器：进入目录“/Limbo/limbo/parsers/def/adapt”。 运行`make -j 2`。
14. 确保名为 **libgdsparser.a**、**liblefparseradapt.a** 和 **libdefparseradapt.a** 的新静态库存在于目录“/Limbo/lib”中
15. 按照 [HYPRE 设置](#HYPRE-Setup) 中的说明从 HYPRE 准备多重网格方法
    * 在遵循这些说明之前，有必要对主目录中的“.bashrc”和“.cshrc”进行所有更改
    * 根据 Linux 机器的设置，可能需要设置其他环境变量
    * 安装 HYPRE 后继续执行剩余步骤
16. 从工作位置进入目录“gds2Para”
17. （可选）将更多 GDSII 文件添加到工作位置的“examples/”目录中
    * 该软件的某些使用模式可能还需要一个与先前存在的示例格式类似的模拟输入文件（后缀前的文件名必须与“.gds”前的 GDSII 文件的文件名匹配）
    * 默认情况下，软件创建的文件将直接添加到当前工作目录中
    * 可选添加的文件可用于代替其余说明中的示例
18. 在 shell 中运行 `make` 来编译可执行文件 **LayoutAnalyzer**
19. 运行 `LayoutAnalyzer --help` 以获取可执行文件支持的可用控制模式列表
20. 在 shell 中运行 `LayoutAnalyzer -r examples/nand2.gds` 以生成描述 GDSII 文件的终端输出
21. 通过运行 `mpirun LayoutAnalyzer -s examples/SDFFRS_X2.gds examples/SDFFRS_X2.sim_input examples/SDFFRS_X2.cir` 来执行完整的参数提取以读取设计和仿真输入文件，进行所有分析，并将结果返回到 Xyce ( SPICE 兼容）子电路
    * 有必要使用 `mpirun` 来保证软件并行化部分的内存完整性。

## HYPRE 设置
1. 使用 `git clone https://github.com/hypre-space/hypre.git` 将 [HYPRE 存储库](https://github.com/hypre-space/hypre) 克隆到您的工作位置
    * 这需要为安全连接设置 SSH 密钥
2. 从工作位置进入目录“hypre/src/cmbuild”
    * 可以使用`../configure --help`查看配置选项
    * 推荐的安装涉及 CMake 而不是更简单的，可能的安装只使用 make 和包含的 **configure** 工具
<!--3。 运行命令`./configure --enable-shared --enable-complex --with-MPI=/opt/mpich2-gcc/1.4.1p1 --with-MPI-include=/opt/mpich2-gcc/1.4。 1p1/include/ --with-MPI-libs="" --with-MPI-lib-dirs=/opt/mpich2-gcc/1.4.1p1/lib64/ CC=/opt/gcc/7.1.0/bin/ gcc CFLAGS="-g" CXX=/opt/gcc/7.1.0/bin/gcc CXXFLAGS="-g" FC=/opt/gcc/7.1.0/bin/gfortran`-->
3. 运行 `cmake --version` 并确保安装的 CMake 版本至少为 3.7.0
4. 运行 `cmake -LA ..` 并确保 CMake 找到了正确版本的编译器
    * CMake 相当喜怒无常，往往会忽略在系统范围内指定不同编译器的常用方法
    * 检查主目录中的“.bashrc”或“.cshrc”以查看编译器的环境变量是否设置正确
    * 特别是，除非非常仔细地注意这些安装说明，否则在构建 HYPRE 时很难应用 OpenMPI 的设置
5. 运行 `cmake ..` 来生成一个 makefile
6. 从同一位置（工作位置中的“hypre/src/cmbuild”）运行`make install -j 2`以安装头文件
7. 返回工作目录并通过运行`ls -lh hypre/src/hypre/include`确保存在名为**HYPRE.h**的新库文件
