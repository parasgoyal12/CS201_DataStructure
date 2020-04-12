import random
import re
import numpy as np

li=np.random.choice(2,3200)
f=open('inp.txt','w')
#out=open('output.txt','w')

f.write('1100')
test=[]
a=''
for index,i in enumerate(li):
	
	if index%32==0:
		f.write('\n1 ')
		test.append(a)
	f.write(str(i))
	a=a+str(i)
test.append(a)
test=test[1:]
print(len(test))
f.write('\n')
test2=[]
for i in range(500):
	n=random.randint(1,32)
	l=np.random.choice(2,n)
	f.write('3 ')
	a=''
	for j in l:
		a=a+str(j)
		f.write(str(j))
	f.write('\n')
	test2.append(a)

for i in range(500):
	n=random.randint(1,32)
	l=np.random.choice(3,n)
	f.write('4 ')
	for j in l:
		if str(j) == '2':
			f.write('?')
		else:
			f.write(str(j))
	f.write('\n')

