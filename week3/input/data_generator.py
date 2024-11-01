import random

filename='in2.txt'

def func(file,n):
    file.write(f'{n}\n')
    for _ in range(n):
        x=random.randint(1,7)
        file.write(f'{x}')
        if x==6:
            y=random.randint(0,100)
            file.write(f' {y}')
        file.write('\n')

with open(filename,'w') as file:    
    func(file,50)

print(filename+' has done.')