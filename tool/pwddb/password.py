def openfile(db,f='/media/samsung/6AEE703BEE70019D/backup/demon.txt'):
    fd = open(f)
    for i in fd.readlines():
        #i.split(' # ')
        #print("username:",i[0],"password:",i[1],"email:",i[2])
        #print(i)
        split=' # '
        username,_,right=i.partition(split)
        password,_,email=right.partition(split)
        #print("username:",username,"password:",password,"email:",email)
        passdb(db,password)

def passdb(db,password):
    mydb=db
    for i in password:
        if i not in mydb:
            mydb[i]={'count':1,'child':{}}
        else:
            mydb[i]['count'] += 1
            mydb =mydb[i]['child']
def display(db):
    pass
if __name__ =="__main__":
    db={}
    openfile(db)
    print(db)
