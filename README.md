# EasyFront
EasyFront为我大三期间使用C++语言实现的一个类似Python语言的前端，其只包括**词法分析** **语法分析** **语义分析** **字节码生成** **字节码执行**， 不包括 **代码优化** **虚拟机** 等复杂语言构件，编译器理论知识主要参考《Compilers Principles Techniques & Tools》一书，代码主要参考Python3.2，从某种程度上讲，EasyFront本质上是我读懂Python语言实现逻辑并剥离出其前端部分然后改造成C++的一个玩具项目，其不具使用价值，但对我的成长有很大的帮助。

# 支持平台
该项目只在window下测试通过，原理上linux上也可编译通过

# DOC

该项目的文档最终变为了我的学年论文，见[一个完整的编译器前端.pdf](doc/一个完整的编译器前端.pdf)

# 一个例子程序，打印三位数的水仙花数

```python
# test/water_num.ef
# 打印3位数的水仙花数

a = 1

fun print_water_num(n1,n2,n3):
    val = n1 * 100 + n2 * 10 + n3
    result = n1 * n1 * n1 + n2 * n2 * n2 + n3 * n3 * n3
    #cout("val:",val,"result:",result)
    if val == result:
        cout(val)
                
while a < 10:
    b = 0
    while b < 10:
        c = 0
        while c < 10:
            print_water_num(a,b,c)
            c += 1
            #cout("c:",c)
        b += 1
        #cout("b:",b)
    a += 1
    #cout("a:",a)
```
执行方式：
```
D:\EasyFront\test>EasyFront.exe water_num.ef
153
370
371
407

D:\EasyFront\test>
```
