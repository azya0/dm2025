data = {}
counter = 0

with open("../orwell.txt") as file:
    text = file.read()


for char in text:
    counter += 1

    if char not in data:
        data[char] = 0
    
    data[char] += 1


with open("../ascii_letter_chance.azya", "w") as file:
    for key in sorted(data, key=lambda value: data[value])[::-1]:
        file.write(f"{ord(key)} {data[key] / counter:.3}\n")
