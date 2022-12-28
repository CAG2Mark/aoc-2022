# Advent of Code 2022
My Advent of Code 2022 solutions.

# Running
You will need a Unix-like system like Linux, macOS or WSL.

To initialise:
```bash
git clone https://github.com/CAG2Mark/aoc-2022
cd aoc-2022/utils
g++ aocutils.cpp -O2 -c -std=c++17
cd ..
```
To run a certain day, place a file called `input` in the `dayX` folder, and optionally the test input `input.test`. Then:
```bash
cd dayX
```
To run part 1, run `make r1`. For part 2, run `make r2`. If you are on Windows, you can build manually using:
```bash
g++ p1.cpp ../utils/aocutils.o -o p1.exe -O2 -std=c++17
```
# Automatic Input Fetcher
Navigate to the Advent of Code website, log in, then go to Inspect Element -> Network, then refresh the page. Click on the first request, then go to Cookies, then copy your session cookie and paste it into a file called `session` in the root directory. Then, you can run `python3 ./get_input.py X` to auto-fetch the input for day `X`.
