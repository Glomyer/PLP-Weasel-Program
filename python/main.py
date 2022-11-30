import random

weasel = "METHINKS IT IS LIKE A WEASEL"
letters = "ABCDEFGHIJKLMNOPQRSTUVWXYZ "
base_string = ""


def score(string): # calculates string score, from 0 to 28
  score = 0
  for i in range(len(weasel)):
    if string[i] == weasel[i]:
      score += 1
  return score

# generates a new random string
for j in range(len(weasel)):
  base_string += random.choice(letters)
print(f"String base:  {base_string} \t Score:{score(base_string)}")

iteration = 0
while base_string != weasel:
  iteration += 1
  string_list = []

  for string in range(100):
    string_list.append(base_string)

  for i in range(len(string_list)):
    listAux = list(string_list[i])

    for j in range(len(listAux)):
      if(random.random() >= 0.95): # 5% chance
        listAux[j] = random.choice(letters)
    stringAux = "".join(listAux)
        
    if score(stringAux) > score(base_string):
      base_string = stringAux
  
  print(f"Iteration {str(iteration).zfill(2)}: {base_string} \t Score:{score(base_string)}")


