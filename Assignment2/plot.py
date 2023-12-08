import subprocess as sp
import matplotlib.pyplot as plt

NAME = "Solution 1"

plt.figure(figsize=(10, 6))
for i, solution in enumerate(("Euler's", "Improved Euler's", "Runge-Kutta")):
    process = sp.Popen(["./2_2.out"], stdin=sp.PIPE, stdout=sp.PIPE)

    output, _ = process.communicate(f"20 {1 + i}".encode())
    output = output.decode().strip()

    _, _, _, x_str, _, y_str = output.split("\n")
    x, y = list(map(float, x_str.split())), list(map(float, y_str.split()))

    plt.plot(x, y, label=solution)
    plt.title(NAME, fontsize=18)
    plt.xlabel("x", fontsize=14)
    plt.ylabel("y(x)", fontsize=14)

plt.legend(loc="upper right", fontsize=12)
plt.savefig(f"{NAME.lower().replace(' ', '_')}.png")
plt.show()
