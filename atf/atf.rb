#more test, orader
#测试用例
class TestCase

#
def testcase_init()
end

#
def testcase_destroy()
end

end

#测试集
class TestSuite

#每个测试集开始之前调用
def testsuite_init()
end

#执行每个测试用例时调用
def each_testcase()
end

#每个测试集结束之后调用
def testsuite_destroy()
end
end

#工程
class Project

#此函数用于执行project之前调用
def project_init()
end

#此函数用于执行project之后调用
def project_destroy()
end
end

#1.个project中含有多个TestSuite,1个TestSuite含有多个
#TestCase
