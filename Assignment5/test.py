import networkx as nx

import math
import random

number_of_nodes=100
edge_prob=0.05
g=nx.gnp_random_graph(number_of_nodes,edge_prob)


for (u,v) in g.edges():
    g[u][v]['weight2']=random.random()
    g[u][v]['weight']=-math.log10(1-g[u][v]['weight2'])
    g[u][v]['color']=random.randint(0,1)

s=nx.algorithms.simple_paths.all_simple_paths(g,source=0,target=number_of_nodes-1)

def path_prob(g,path,target):
    prob=0.0
    k=0
    for index,i in enumerate(path):
        if(i==target):
            break
        prob=prob + g[i][path[index+1]]['weight']
        k=k+g[i][path[index+1]]['color']
    return (prob,k)

k_count=random.randint(2,10)
m_prob=-math.log10(1-random.random())

flag=0
for path in s:
    pp,pk=path_prob(g,path,number_of_nodes-1)
#     print(pp)
#     print(pk)
    if pp<=m_prob and pk <= k_count:
        flag=1
        break


print(m_prob)
print(k_count)
print(flag)

f=open('input.txt','w')
f.write(str(m_prob)+'\n')
f.write(str(k_count)+'\n')
f.write(str(number_of_nodes)+'\n')
f.write(str(g.number_of_edges())+'\n')
for (u,v) in g.edges():
    f.write(f'{u+1} {v+1} {g[u][v]["weight2"]} {g[u][v]["color"]}\n')
