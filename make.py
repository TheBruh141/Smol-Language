
# this is not a nessecarry file this is just a script for easy compiling and testing :D
import os


def main():
    os.system("make dev")
    os.system("python tests/tester.py")


if __name__ == '__main__':
    main()
