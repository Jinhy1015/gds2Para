# 如何将 Cadence Allegro BRD 转换为 GDSII

1. 找到 Cadence Allegro PCB 文件（.brd 扩展名）
2. 运行 Cadence DB Doctor（在 Windows 开始菜单中单独安装的程序）将文件更新为已安装的 Cadence Allegro 版本以与 Cadence PCB Editor 兼容
3. 使用省略号选择输入设计以打开带有文件管理器的对话框
4. 使用省略号选择输出设计名称以打开带有文件管理器的对话框（建议使用不同的名称以保留原始文件）
5. 在按“检查”按钮之前，选中“更新所有 DRC（包括批处理）”、“检查形状轮廓”和“重新生成 Xnet”
6. 如果日志显示文件转换成功，则关闭 Cadence DB Doctor
7. 运行 Cadence PCB Editor 以打开 Cadence Allegro 的对话框
8. 选择未选中任何选项的产品“Allegro PCB Designer”，然后按“确定”
9. 右键单击 Allegro PCB Designer 顶部的工具栏，确保分隔符上方的“可见性”、“命令”和“查看”以及“文件”、“编辑”、“查看”（再次）和 启用分隔符下方的“制造”，以便显示这些工具栏
10. 使用菜单选项“文件”&rightarrow; “打开”以加载与 Cadence DB Doctor 一起使用的输出设计名称
11. 在屏幕右侧的“可见性”工具栏上单击“打开”以获得全局可见性，因为所有功能都必须可见才能导出为不同的文件格式
12. 使用菜单选项"setup"&rightarrow; “横截面...”打开横截面编辑器对话框并记录图层属性（如果需要，“导出”菜单允许您将信息导出到 XML 文件）
13. 完成后关闭横截面编辑器对话框
14. 使用菜单选项"制造"&rightarrow; **"Stream Out"**（注意名称）打开Stream Out对话框，这是GDSII文件导出向导
15. 使用省略号选择输出 GDSII 文件名以打开带有文件管理器的对话框
16. 使用省略号选择图层转换文件名以打开带有文件管理器的对话框（此扩展名为 .cnv 的文件名不应已在目标位置使用）
17. 点击图层转换文件名下方的“编辑...”，打开Stream Out Edit Layer Conversion File对话框
18. 使用类过滤器调出以下类和子类进行转换，在调整其框中的地图选定项“图层”编号从1开始并单击“地图”之前，为列出的每个子类选中表中的“已选择”框
    * _Etch_
        1. 与横截面编辑器对话框中给出的图层对应的每个子类（如果可行，建议仅使用从 1 开始的奇数）
        2. 跳过与层不对应的子类（例如，_WIRE_）
    * _Via\_Class_
        1. 与横截面编辑器对话框中给出的图层对应的每个子类（如果可行，建议仅使用从 2 开始的偶数）
        2. 跳过与层不对应的子类（例如，_FILMMASKBOTTOM_、_PASTEMASK\_BOTTOM_ 和 _SOLDERMASK\_TOP_）
    * _Board\_Geometry_
        1. 只有_OUTLINE_子类（对模拟输入文件的未来有用）
19. 返回 Stream Out 对话框，在下拉菜单中选择 GDSII 路径元素的端点样式（例如，_Flush_）
20. 选中“将固定文本添加到层次结构的顶层”并保留其他默认选项
21. 如果日志显示导出成功，请单击“导出”按钮并关闭所有内容而不在 Allegro PCB 编辑器中保存
22. 将生成的 GDSII 文件保存到工作位置，如果外观有问题，使用 [KLayout 层布尔操作](https://www.klayout.de/doc/manual/layer_boolean.html) 操作该文件
23. 在工作位置编写一个模拟输入文件，其中包含来自横截面编辑器对话框的叠加信息和流输出层转换文件的映射（带有 .cnv 扩展名的 ASCII 文件）
