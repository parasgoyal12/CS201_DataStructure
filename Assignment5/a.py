import networkx as nx
import math
import random

f=open('test_case_6','r')
m_prob=float(f.readline())
k_count=int(f.readline())

number_of_nodes=int(f.readline())

number_of_edges=int(f.readline())

g=nx.Graph()

for i in range(number_of_edges):
	l=f.readline().split()
	g.add_edge(int(l[0]),int(l[1]))
	g[int(l[0])][int(l[1])]['weight']=-math.log10(1-float(l[2]))
	g[int(l[0])][int(l[1])]['color']=int(l[3])

s=nx.algorithms.simple_paths.all_simple_paths(g,source=1,target=number_of_nodes)

def path_prob(g,path,target):
    prob=0.0
    k=0
    for index,i in enumerate(path):
        if(i==target):
            break
        prob=prob + g[i][path[index+1]]['weight']
        k=k+g[i][path[index+1]]['color']
    return (prob,k)

flag=0
for path in s:
    pp,pk=path_prob(g,path,number_of_nodes)
    if pp<=m_prob and pk <= k_count:
        flag=1
        break


print(m_prob)
print(k_count)
print(flag)

