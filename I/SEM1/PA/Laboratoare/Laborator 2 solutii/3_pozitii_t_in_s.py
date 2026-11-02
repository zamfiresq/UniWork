s = input("s = ")
t = input("t = ")
p = s.find(t)
if p == -1:
    print(f"Șirul '{t}' nu apare în șirul '{s}'")
else:
    print(f"Pozitiile pe care incepe sirul '{t}' apare în șirul '{s}':")
    while p != -1:
        print(p, end=" ")
        p = s.find(t, p + len(t))
print()

p = s.index(t)
print(f"Pozitiile pe care incepe sirul '{t}'  în șirul '{s}':")
try:
    while True:
        print(p, end=" ")
        p = s.index(t, p + len(t))
except:
    pass
print()

#varianta cu index - sa afiseze si mesajul  "nu apare in text"
try:
    p = s.index(t)
    print(f"Pozitiile pe care incepe sirul '{t}'  în șirul '{s}':")
    try:
        while True:
            print(p, end=" ")
            p = s.index(t, p + len(t))
    except:
        pass
except:
    print(f"Șirul '{t}' nu apare în șirul '{s}'")
