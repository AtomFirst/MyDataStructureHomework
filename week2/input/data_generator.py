import random

filename='in2.txt'

def func(file,n):
    file.write(f'{n}\n')
    list=random.sample(range(1,100),n)
    list.sort(reverse=True)
    for x in list:
        file.write(f'{x} ')
    file.write('\n')

with open(filename,'w') as file:    
    func(file,30)
    func(file,50)

print(filename+' has done.')