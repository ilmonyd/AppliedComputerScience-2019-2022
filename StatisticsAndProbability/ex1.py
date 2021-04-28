import random

############################################
# podpunkt a

print("*** excercise a ***")
random.seed(a=None)  # random.seed() with argument a = None uses current system time as seed
print(random.uniform(0, 1))  # generating pseudo-random numbers from range (0, 1)

############################################
# podpunkt b

print("\n*** excercise b ***")
colors = ["spades", "hearts", "diamonds", "clubs"]
vals = ["A"] + [(str(num)) for num in range(2, 11)] + ["J", "Q", "K"]


def draw_cards():
    stack = []
    while stack.__len__() != 3:
        num = random.randint(0, 51)
        if num not in stack:
            stack.append(num)
    return stack


counter = 0

for card in draw_cards():
    print(vals[card % len(vals)] + " of " + colors[card % len(colors)])
    if card % len(colors) == 3:
        counter += 1

print(f'Number of clubs in drawn cards: {counter}')

############################################
# podpunkt c

print("\n*** excercise c ***")
prob = 0.413
counter = 0
n = 100000
for i in range(1, n + 1):
    inner_count = 0
    for card in draw_cards():
        if card % len(colors) != 3:
            inner_count += 1
    if inner_count == 3:
        counter += 1
    if abs(prob - (counter / i)) < 0.001:
        print(f'It takes {i} draws to get probability of no clubs in 3 cards drawn equal to {counter / i}')
        break
