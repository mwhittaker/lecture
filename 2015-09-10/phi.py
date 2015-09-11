import numpy as np
import matplotlib.pyplot as plt

def main():
    peak_flops = 120e9
    peak_memory = 59e9
    ois = np.arange(0.25, 32, 0.1)
    max_flops = [min(peak_flops, peak_memory * oi) for oi in ois]
    plt.loglog(ois, max_flops)

    plt.xlabel("Operational Intensity")
    plt.ylabel("Attainable FLOP/s")
    plt.grid(True)
    plt.savefig("roofline.pdf")

if __name__ == "__main__":
    main()
