import random

filename='in4.txt'

def func(file,n):
    file.write(f'{n}\n')
    for _ in range(n):
        file.write(f'{random.randint(1,10000)} ')
    file.write('\n')

with open(filename,'w') as file:    
    func(file,10000)

print(filename+' has done.')