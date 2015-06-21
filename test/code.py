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
	
