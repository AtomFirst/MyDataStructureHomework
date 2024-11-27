import random

filename='in2.txt'

def func(file,n,m):
    file.write(f'{n} {m}\n')
    e=set()
    for _ in range(m):
        while True:
            a,b=random.randint(1,n),random.randint(1,n)
            if a!=b and (a,b) not in e:
                c= random.randint(1,100)
                file.write(f'{a} {b} {c}\n')
                e.add((a,b))
                e.add((b,a))
                break

with open(filename,'w') as file:    
    func(file,150,500)

print(filename+' has done.')