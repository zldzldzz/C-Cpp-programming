# h=input("학과:")
# x=input("이름:")
# y=int(input("학년:"))
# print("안양대학교",h, y,"학년",x,"입니다.")
# x="제이름은"
# y=input()
# x=x+y+"입니다."
# print(x)

# even=[2,4,6,8]
# add=[1,3,5,7]
# all=add+even
# print(all*2)

# name=input("이름:")
# year=2024
# age=int(input("출생년:"))

# print("나는 %s이고 나이는 %s입니다." %(name, year-age))

# astring='hello world!'
# print(astring.index("o"))
# print(astring.count("l"))
# print(astring[3:7])
# print(astring[3:7:2])

# print(astring[::-1])
# print(astring.upper())
# print(astring.startswith('hello'))
# a=astring.split(" ")
# print(a)

# print(set("my name is Eric and Eric is my name".split()))
# aset=set(['apple','banana'])
# bset=set(['orinde','apple'])
# cset=aset.union(bset)
# print(cset)
# dset=bset.union(aset)
# print(dset)

# x=2
# print(x==2)
# print(x==3)
# print(x!=3)
# print(x<3)

# name='wefim'
# age=23
# if name =='wefim' and age==23:
#     print("성공")
# if name =='wefim' or name=='ewfjionrepin':
#     print('성공2')

# x=input("값을 입력하세요: ")
# x=2
# y=2
# print(x is y)
# print(not False)

# if x==2:
#     print("x는 2이다")
# else:
#     print("x는 2가 아니다")
# if -1:
#     # 0은 거짓취급
#     print("true")

time=int(input('what time? : '))
m_time = int(input('몇분? : '))
time = time*100+m_time
class_start = 1600
if class_start - time < 10:
    print('지각')
elif class_start < time:
    print('지각')
else:
    money = int(input('얼마냐? : '))
    if money >= 6000 :
        print('taxi')
    else :
        print('뛰어라')