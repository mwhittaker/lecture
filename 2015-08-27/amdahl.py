# To run this script, install python, pip, and virtualenv. Then, run the
# following:
#
#     virtualenv .
#     source bin/activate
#     pip install -r requirements.txt
#     python amdahl.py
#
# This will create two plots:
#
#     1. speedup.pdf
#     2. efficiency.pdf

import matplotlib
import matplotlib.pyplot as plt

def speedup(p, alpha):
    return 1. / (alpha + ((1. - alpha) / p))

def efficiency(p, alpha):
    return speedup(p, alpha) / p

def main():
    # Increase font size
    matplotlib.rc('font', size=18)

    alpha = 0.1
    ps = range(1, 128 + 1)
    ss = [speedup(p, alpha) for p in ps]
    ts = [efficiency(p, alpha) for p in ps]

    plt.figure()
    plt.plot(ps, ss)
    plt.xlabel("Number of Processors ($p$)")
    plt.ylabel("Speedup ($S_p$)")
    plt.grid()
    plt.savefig("speedup.pdf")

    plt.figure()
    plt.plot(ps, ts)
    plt.xlabel("Number of Processors ($p$)")
    plt.ylabel("Parallel Efficiency ($T_p$)")
    plt.grid()
    plt.savefig("efficiency.pdf")

if __name__ == "__main__":
    main()
