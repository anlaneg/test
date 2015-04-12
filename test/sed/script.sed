#! /bin/sed -f 
1a\
#'1a\'表示在本行后插入多行\
#此为插入的第2行

3i\
#'3i\'表示在本行前加入多行\
#此为加入的第2行

#'{'为在一行情况下组合多条命令
8 {
a\
我们在第8行后加入此行
i\
我们在第8行之前加入此行
=;
}

#'d'为删除
9 {d;}

#'c'为修改
10 { p;i\
#上面为第10行,我们将第10行中的修改为abc
c\
abc
}

#'y'为等价于tr 'abc' '123' 
12 {
y/abcmdif/1234567/
}

#g 将hold space中的内容拷贝到pattern space中，原来pattern space里的内容清除
14{
g;
}
#G：将hold space中的内容append到pattern space\n后
15{
G;
}
#+ g：[address[,address]]g 将hold space中的内容拷贝到pattern space中，原来pattern space里的内容清除

#+ G：[address[,address]]G 将hold space中的内容append到pattern space\n后

#+ h：[address[,address]]h 将pattern space中的内容拷贝到hold space中，原来的hold space里的内容被清除

#+ H：[address[,address]]H 将pattern space中的内容append到hold space\n后

#+ d：[address[,address]]d 删除pattern中的所有行，并读入下一新行到pattern中

#+ D：[address[,address]]D 删除multiline pattern中的第一行，不读入下一行

#PS：不论是使用G、g还是H、h，它们都是将hold space里面的内容“copy”到pattern space中或者将pattern space中的内容“copy”到hold space中。
