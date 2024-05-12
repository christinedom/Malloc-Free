import matplotlib.pyplot as plt

def parse_output(file_path):
    sizes = []
    malloc_times = []
    total_times = []
    test_cases = []

    with open(file_path, "r") as file:
        current_test_case = 0
        for line in file:
            if line.startswith("Test Case"):
                current_test_case += 1
                test_cases.append(current_test_case)
            elif line.startswith("Time:"):
                time = float(line.split(":")[1].strip(" seconds\n"))
                total_times.append(time)
            elif line[0].isdigit():
                size, malloc_time = map(float, line.split())
                sizes.append(size)
                malloc_times.append(malloc_time)

    return sizes, malloc_times, total_times, test_cases

def plot_graph(sizes, malloc_times, total_times, test_cases):
    plt.figure(figsize=(12, 8))

    plt.subplot(2, 1, 1)
    plt.bar(range(len(sizes)), malloc_times)
    plt.xlabel("Memory Size (bytes)")
    plt.ylabel("Malloc Time (seconds)")
    plt.title("Actual speeds of tmalloc() with Varying Sizes")
    plt.xticks(range(len(sizes)), sizes, rotation=45, ha="right")
    plt.tight_layout()

    plt.subplot(2, 1, 2)
    plt.bar(test_cases, total_times)
    plt.xlabel("Test Case")
    plt.ylabel("Total Time (seconds)")
    plt.title("Total Time for Each Test Case")
    plt.xticks(test_cases)
    plt.tight_layout()

    plt.savefig("actualspeeds_malloc.png")
    plt.show()

if __name__ == "__main__":
    sizes, malloc_times, total_times, test_cases = parse_output("output.txt")
    plot_graph(sizes, malloc_times, total_times, test_cases)
