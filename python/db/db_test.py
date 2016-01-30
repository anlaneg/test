# coding:utf-8
from sqlalchemy.orm import mapper, sessionmaker
import sqlalchemy as sa
#from sqlalchemy import create_engine, Table, Column, Integer, String, MetaData
#from sqlalchemy.sql.expression import Cast
#from sqlalchemy.ext.compiler import compiles
from sqlalchemy.dialects.mysql import \
        BIGINT, BINARY, BIT, BLOB, BOOLEAN, CHAR, DATE, \
        DATETIME, DECIMAL, DECIMAL, DOUBLE, ENUM, FLOAT, INTEGER, \
        LONGBLOB, LONGTEXT, MEDIUMBLOB, MEDIUMINT, MEDIUMTEXT, NCHAR, \
        NUMERIC, NVARCHAR, REAL, SET, SMALLINT, TEXT, TIME, TIMESTAMP, \
        TINYBLOB, TINYINT, TINYTEXT, VARBINARY, VARCHAR, YEAR

#表的属性描述对象
metadata = sa.MetaData()
userTable = sa.Table(
    "user",metadata,
    sa.Column('user_id', sa.Integer, primary_key=True),
    sa.Column('user_name', VARCHAR(50), unique=True, nullable=False),
    sa.Column('password', VARCHAR(40), nullable=True)
)
#创建数据库连接,MySQLdb连接方式
mysql_db = sa.create_engine('mysql://root:root@localhost:3306/along')
#创建数据库连接，使用 mysql-connector-python连接方式
#mysql_db = create_engine("mysql+mysqlconnector://root:root@localhost:3306/along")
#生成表
#metadata.create_all(mysql_db)


#创建一个映射类
class User(object):
    pass
#把表映射到类
mapper(User, userTable)

def get_session():
    #创建了一个自定义了的 Session类
    Session = sessionmaker()
    #将创建的数据库连接关联到这个session
    Session.configure(bind=mysql_db)
    session = Session(autocommit=True)
    return session
   

def insert_value(session,username):
    u = User()
    u.user_name=username
    u.password='password'
    session.add(u)
def subtransaction_insert(session,username):
    with session.begin(subtransactions=True):
        insert_value(session,username)

def transaction_query(session,username):
    with session.begin(subtransactions=True):
        u = session.query(User).filter_by(user_name=username).first()
        if u:
            print(u.password)
        else:
            print("not found")

def transaction_test(session1,session2):
    with session1.begin(subtransactions=True):
        user_name="9baxh83"
        insert_value(session1,user_name)

        print("----not found")
        transaction_query(session2,user_name)#not found
        print("----")

        transaction_query(session1,user_name)#found
       
        subtransaction_insert(session1,user_name + "-1")
        print("----not found")
        transaction_query(session2,user_name + "-1") #not found
        print("----")
        

def main():
    #session1=get_session()
    #session2=get_session()
    
    #transaction_test(session1,session2)
    #session1.close()
    #session2.close()

    session1=get_session()
    #直接用sql查询
    #result = session1.execute("select * from user");
    #直接用sql查询,并传参
    #result = session1.execute("select * from user where user_id = :user_id",{'user_id':1})
    #采用neutron中常见方式(返回的为User对象)
    #result = session1.query(User).all()
    #result = session1.query(User).first()
    
    #采用常见的filter
    #result=session1.query(User).filter(User.user_id == 1).all()
    #result=session1.query(User).filter(User.user_id >= 1, User.user_name != 'a').all()
    for r in result if isinstance(result,list) else [result]:
        print(r)
#def main():
#    u = User()
#    #给映射类添加以下必要的属性,因为上面创建表指定这个字段不能为空,且唯一
#    u.user_name='tan9le测试'
#    #按照上面创建表的相关代码，这个字段允许为空
#    u.password='123456'
#    #在session中添加内容
#    session.add(u)
#    #保存数据
#    session.flush()
#    #数据库事务的提交,sisson自动过期而不需要关闭
#    session.commit()
#
#    #query() 简单的理解就是select() 的支持 ORM 的替代方法,可以接受任意组合的 class/column 表达式
#    query = session.query(User)
#    #列出所有user
#    print list(query)
#    #根据主键显示
#    print query.get(1)
#    #类似于SQL的where,打印其中的第一个
#    print query.filter_by(user_name='tan9le测试').first()
#    u = query.filter_by(user_name='tan9le测试').first()
#    #修改其密码字段
#    u.password = '654321'
#    #提交事务
#    session.commit()
#    #打印会出现新密码
#    print query.get(1).password
#    #根据id字段排序,打印其中的用户名和密码
#    for instance in session.query(User).order_by(User.user_id):
#        print instance.user_name, instance.password
#    #释放资源
#    session.close()
#


if __name__ == '__main__':
    main()
