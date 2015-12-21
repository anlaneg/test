#! /bin/bash
function find_java()
{
    dir="$1"
    find "$dir" -type f -name '*.java' | xargs -i echo {}    
}

function complier_java()
{
    dir="$1"
    class_path="$2"
    java_file="$3"
    echo "javac -d $dir -classpath $class_path $java_file"
    javac -d $dir -classpath $class_path $java_file
}

function need_complier()
{
    java_dir="$1"
    class_dir="$2"
    
    for i in `find_java $java_dir`;
    do
        package_name=`dirname $i | sed -e "s/$java_dir//"`
        java_file_name=`basename $i|cut -d '.' -f 1`
        class_file="$class_dir$package_name/${java_file_name}.class"
        if [ ! -e "$class_file" -o "$i" -nt "$class_file" ];
        then
            echo "$i"
        fi;
    done
}

function get_class_path()
{
    current_dir=`pwd`
    class_path="$current_dir"
    for i in `ls -1 $class_path/tool/lib/`;
    do
        class_path+=":$current_dir/tool/lib/$i"
    done;
    echo ".:./bin:$class_path"
}


function do_complier_java()
{
    src_dir="$1"
    dst_dir="$2"
    class_path="$3"
    files=`need_complier "$src_dir" "$dst_dir"`
    for f in `echo $files`;
    do
        if [ "X$f" != "X" ];
        then
            echo "-$f-"
            complier_java "$dst_dir" "$class_path" "$f" 
        fi;
    done;
}

function complier()
{
    class_path=`get_class_path`
    do_complier_java "src" "bin" "$class_path"
    do_complier_java "test" "bin" "$class_path"
}

function run_test()
{
    class_path=`get_class_path`
    echo "java -classpath $class_path cn.along.xparse.test.XparseStructTest"
    java -classpath $class_path cn.along.xparse.test.XparseStructTest

}

function run()
{
    class_path=`get_class_path`
    echo "java -classpath $class_path cn.along.xparse.Xparse -d . -o ./bin/ -d /usr/bin/"
    java -classpath $class_path cn.along.xparse.Xparse -d . -d ../xparse -O ./bin/ 
}

complier
run
