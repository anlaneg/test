/*
*打桩测试memory申请失败错误
*原理,保证应用进程启动时调用
* 本模块提供的内存分配,释放函数
* 这样应用程序的内存使用就被本工具代理
* 有以下几种测试方式
* 1.内存申请失败测试(要求外部支持,依次保证第一次申请失败,第二次申请失败
* .....)
* 2.内存申请释放检查(需要链接本库,并使用本库提供的头文件)
*   可检查:1.多次释放;2.无效释放;3.越界;
* 3.内存当前状态显示(如果链接本库,则可提供较详细的状态情况)
*   可检查:1.哪些内存未被施放. 
*   详细显示时,可检查:
*	1.哪行内存未被释放
* 4.查越界问题(需要占用较大量的内存)
* 5.可考虑提供命令行.
* 思路:实现内存代码即可
*/
