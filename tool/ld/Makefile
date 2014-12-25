#untouch-update
#此目录用于探索ld控制中,如何在不修改旧代码的前提下,解决程序的自动适配
#dynsymal 使用动态符号方法
#muildefine 使用多定义,默认处理方法
#uncontain 使用wrap方式,限制为必须不在同一个.o文件中,故命名为un contain
DIR=dynsymal muildefine uncontain

all:
	@for i in $(DIR) ; do $(MAKE) -C $$i all ; done;
clean:
	@for i in $(DIR) ; do $(MAKE) -C $$i clean; done;
