import argparse
import time

cells = [0 for _ in range(65535)]
pointer = 0
stack = []

def interpreter(filename: str):
    global cells, pointer, stack
    comment = 0
    with open(filename, 'r') as f:
        code = '\0'
        while code != '':
            code = f.read(1)
            # print("code: %s, pointer: %s" % (code, pointer))
            if code == '>':
                pointer += 1
            elif code == '<':
                pointer -= 1
            elif code == '+':
                cells[pointer] += 1
            elif code == '-':
                cells[pointer] -= 1
            elif code == '.':
                print(cells[pointer])
            elif code == ',':
                cells[pointer] = input()
            elif code == '[':
                stack.append(f.tell() - 1)
            elif code == ']':
                goto = stack.pop()
                if cells[pointer] != 0:
                    f.seek(goto)
            elif code == '/':
                comment += 1
                if comment == 2:
                    comment = 0
                    while(f.read(1) != '\n' and f.read(1) != ''):
                        pass


if __name__ == '__main__':
    parser = argparse.ArgumentParser()
    parser.add_argument('INPUT', type=str, help='any brainfuck source code like hello.b or hello.bf')
    args = parser.parse_args()
    filename = args.INPUT
    interpreter(filename)