import sys, os


def read_lines(filename):
    with open(filename) as file:
        return file.readlines()


def main(filename):
    pass


def get_filename(flag):
    if flag == 1:
        print("Error: FileNotFound. Please enter another filename in the current directory:")
    elif flag == 2:
        print("Please enter a filename to analyze:")
    filename = input()
    while True:
        if filename in os.listdir():
            main(filename)
        else:
            print("Error: FileNotFound. Please enter another filename in the current directory:")
            filename = input()



if __name__ == "__main__":
    if len(sys.argv) < 1:
        get_filename(1)
    elif len(sys.argv) == 1:
        if sys.argv[1] in os.listdir():
            main(sys.argv[1])
        else:
            print("Error: FileNotFound. Please enter another filename:")
            filename = input()