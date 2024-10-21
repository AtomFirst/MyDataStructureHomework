import random

n=200

with open('in2.txt','w') as file:
    file.write(f'{n}\n')
    for _ in range(200):
        file.write(f'{random.randint(1,100)} ')

print('done')