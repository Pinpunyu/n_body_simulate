import random

gravitational_constant = 0.01
number_of_bodies = 100
time_step = 50

bodies = []

for i in range(number_of_bodies):
    mass = random.uniform(0.001, 10)  
    position = [random.uniform(-10, 10) for _ in range(3)] 
    velocity = [random.uniform(-1, 1) for _ in range(3)]  
    bodies.append((mass, position, velocity))

with open("n_body_data.txt", "w") as file:
    file.write(f"{gravitational_constant} {number_of_bodies} {time_step}\n")
    for body in bodies:
        mass, position, velocity = body
        file.write(f"{mass}\n")
        file.write(" ".join(map(str, position)) + "\n")
        file.write(" ".join(map(str, velocity)) + "\n")

