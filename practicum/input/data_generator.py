import random

filename='data9.txt'

L,R=1,1_000_000_000

def func(file,n):
    file.write(f'{n}\n')
    for _ in range(n):
        file.write(f'{random.randint(L,R)} ')
    file.write('\n')

with open(filename,'w') as file:   
    file.write('10\n')
    
    N=100_000

    a=[random.randint(L,R) for _ in range(N)]
    a.sort()
    
    file.write(f'{N}\n')
    for x in a:
        file.write(f'{x} ')
    file.write('\n')

    a=[random.randint(L,R) for _ in range(N)]
    a.sort(reverse=True)
    
    file.write(f'{N}\n')
    for x in a:
        file.write(f'{x} ')
    file.write('\n')

    a=[random.randint(L,R) for _ in range(N)]

    file.write(f'{N}\n')
    for x in a:
        file.write(f'{x%10_000} ')
    file.write('\n')
    
    for _ in range(4,11): 
        func(file,N)

print(filename+' has done.')