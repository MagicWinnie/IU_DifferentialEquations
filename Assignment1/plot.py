import subprocess as sp
import matplotlib.pyplot as plt


for task in ("Solutions", "Local Errors", "Global Errors"):
    plt.figure(figsize=(10, 6))
    for i, solution in enumerate(("Exact", "Euler's", "Improved Euler's", "Runge-Kutta")):
        if task != "Solutions" and solution == "Exact":
            continue

        process = sp.Popen(["./1_2.out"], stdin=sp.PIPE, stdout=sp.PIPE)

        if task == "Solutions":
            output, _ = process.communicate(f"20 20 40 {1 + i}".encode())
        elif task == "Local Errors":
            output, _ = process.communicate(f"20 20 40 {5 + i - 1}".encode())
        elif task == "Global Errors":
            output, _ = process.communicate(f"20 20 40 {8 + i - 1}".encode())
        output = output.decode().strip()

        _, x_str, _, y_str = output.split("\n")
        x, y = list(map(float, x_str.split())), list(map(float, y_str.split()))

        plt.plot(x, y, label=solution)
        plt.title(task, fontsize=18)
        plt.xlabel("x", fontsize=14)

        if task == "Solutions":
            plt.ylabel("y(x)", fontsize=14)
        elif task == "Local Errors":
            plt.ylabel("LE(x)", fontsize=14)
        elif task == "Global Errors":
            plt.ylabel("GE(x)", fontsize=14)

    plt.legend(loc="upper left", fontsize=12)
    plt.savefig(f"{task.lower().replace(' ', '_')}.png")
    plt.show()
