import random
import numpy as np
import datetime

n=int(input("n="));
li=np.random.choice(2,n,p=[0.0001,0.9999])

f=open("inp.txt","w")
out=open(f"output.txt","w")
f.write(f'{n}\n');
for i in li:
	f.write(str(i))
m=int(input("m="))
f.write(f'\n{m}\n')
for _ in range(m):
	l=random.randrange(start=1,stop=n)
	i=random.randrange(start=1,stop=n-l+1)
	k=random.randrange(start=1,stop=n-l+1)
	if(np.array_equal(li[i-1:i+l],li[k-1:k+l])):
		out.write('1\n')
	else:
		out.write('0\n')
	f.write(f'{i} {i+l} {k} {k+l}\n')
	
f.close()
