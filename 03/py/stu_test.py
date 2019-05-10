class Person:
    name = ""
    sex = ""
    age = 0
    def __init__(self,name,sex,age):
        self.name = name
        self.sex = sex
        self.age = age
    def speak(self):
        print("%s: 我是%s,性别%s,今年%d岁。" % (self.name, self.name, self.sex, self.age))
def sayhi(name):
    print("hi %s" % name)

def introduce(obj):
    print("主持人:这位是%s,%s,今年%d岁,大家欢迎!" % (obj.name, obj.sex, obj.age))

class PersonFactory:
    def getOnePerson(self):
        p = Person("小花","女",1234567)
        return p

#sayhi("xiaoming")
#p = Person("luffy", "male", 123)
#p.speak()
#introduce(p)
#pf = PersonFactory()
#introduce(pf.getOnePerson())
