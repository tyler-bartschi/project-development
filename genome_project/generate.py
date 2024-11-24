import random


def write_lines(filename, content):
    with open(filename, "w") as file:
        file.writelines(content)


def generate_genome(filename):
    genome = []
    base_pairs = ["A", "T", "C", "G"]
    for i in range(1000):
        line = ""
        for i in range(50):
            selection = random.choice(base_pairs)
            line += selection
        genome.append(line)

    write_lines(filename, genome)


if __name__ == "__main__":
    generate_genome("genome.txt")
