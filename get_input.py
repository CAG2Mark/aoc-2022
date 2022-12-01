import os
import sys

if len(sys.argv) < 2:
    print("Expected 1 arguments.")
    sys.exit()
day = int(sys.argv[1])
session = open("session").read().split("\n")[0]
os.system(f"mkdir -p ./day{day}")
os.system(f"curl https://adventofcode.com/2021/day/{day}/input --cookie \"session={session}\" -o ./day{day}/input")

print("First line of file:")
print(open(f"day{day}/input").readline())

