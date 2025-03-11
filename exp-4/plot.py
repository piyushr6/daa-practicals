import matplotlib.pyplot as plt

sizes, prim_times, kruskal_times = [], [], []

# Read execution times from the file
with open("mst_times.txt", "r") as file:
    for line in file:
        size, prim_time, kruskal_time = line.split()
        sizes.append(int(size))
        prim_times.append(float(prim_time))
        kruskal_times.append(float(kruskal_time))

# Plot the results
plt.plot(sizes, prim_times, marker='o', label="Prim's Algorithm")
plt.plot(sizes, kruskal_times, marker='s', label="Kruskal's Algorithm")
plt.xlabel("Number of Vertices")
plt.ylabel("Time (seconds)")
plt.title("Execution Time of Prim's and Kruskal's Algorithms")
plt.legend()
plt.grid()
plt.show()
