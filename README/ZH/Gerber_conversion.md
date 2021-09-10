# 如何将 Cadence Allegro BRD 转换为 GDSII

1. 从源代码下载完整的印刷电路板设计
2. 解压设计并导航到电气方面的 Gerber 文件
    * Gerber 文件可能有任何文件扩展名，但 [典型的](https://www.pcbway.com/blog/help_center/Gerber_File_Extention_from_Different_Software.html) 包括 .pcb、.art、.gbr 或 .ger、.top 或 .bot , 和 .gtl 或 .gbl
    * Excellon NC 钻孔文件同样可以具有任何文件扩展名，但典型的文件扩展名包括 .txt、.drl、.exc、.xln、.drd 和 .tap
    * 不幸的是，无论设计软件设置什么测量系统，大多数钻孔文件都使用美国惯用单位而不是 SI 单位，因此通常需要按以下方式进行缩放
3. 使用 [gerbv](http://gerbv.geda-project.org/)，这是 [gEDA 项目](http://www.geda- project.org/)，从每个铜层中删除机械绘图标题栏（如果存在）
4. 使用[KLayout](https://github.com/KLayout/klayout)导入每个_N_层的Gerber文件和_电镀通孔_的钻孔文件，_blind vias_的所有深度，以及_buried vias_的所有间隔 到单个 GDSII 文件（导入工具的一部分）
5. 将 _N - 1_ 通孔层按 2.54 厘米/英寸缩放。 并小心地重新定位它们，使它们与 _N_ 金属层完美对齐
6. 将生成的 GDSII 文件保存到工作位置，去除重叠金属并丢弃旧 GDSII 文件格式不支持但从 Gerber 文件导入的信息
7. 使用来自设计原理图的叠层信息在工作位置编写一个仿真输入文件
