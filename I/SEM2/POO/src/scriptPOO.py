import os.path
import subprocess

print("\n------------------------QUIZ POO------------------------")
nr = 0

while(nr != -1):
    print("\nALEGE O PROBLEMA SAU -1 PENTRU A INCHIDE:")
    nr = int(input())
    
    if(nr != -1):
        pbpath = f"{str(nr)}.cpp"
        problema = open(pbpath)
        print("\nPROBLEMA " + str(nr) + ":\n")
        for i in problema :
            print(i, end=' ')
        
        print("\n\nAPASA ENTER PENTRU A AFISA REZOLVAREA\n")
        x = input()

        # compilare fisier C++
        compile_command = "g++ " + pbpath + " -o " + pbpath[:-4]
        result = subprocess.run(compile_command, shell=True, capture_output=True, text=True)
        executable_path = pbpath[:-4]
        
        if result.returncode == 0:
            print("PROBLEMA COMPILEAZA\n")

            # rulare fisier executabil
            run_command = f"{executable_path}"
            run_result = subprocess.run(run_command, shell=True, capture_output=True, text=True)
            print(run_result.stdout)
        else:
            print("PROBLEMA NU COMPILEAZA\n")
            print(result.stderr)

        
        # stergere fisier executabil
        if os.path.exists(f"{nr}.out"):
            os.remove(f"{nr}.out")