import random

filename='in2.txt'

def func(file,n,m):
    file.write(f'{n} {m}\n')
    for _ in range(n):
        for _ in range(m):
            e=random.randint(1,9)
            file.write(f'{e} ')
        file.write('\n')

with open(filename,'w') as file:    
    func(file,5,5)

print(filename+' has done.')