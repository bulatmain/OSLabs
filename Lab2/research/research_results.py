import matplotlib.pyplot as plt

def read_results(filename):
    results = []
    f = open(filename)
    for line in f:
        results.append(int(line))
    return results

def calculate_acceleration(working_time):
    t1 = working_time[0]
    return list(map(lambda t : t1 / t, working_time))

def calculate_efficiency(acceleration):
    return list(map(lambda p: acceleration[p - 1] / p, range(1, len(acceleration) + 1)))

if __name__ == "__main__":
    working_time = read_results("results")

    acceleration = calculate_acceleration(working_time)

    efficienty = calculate_efficiency(acceleration)

    x = range(1, len(working_time) + 1)

    wfig, wx = plt.subplots()
    afig, ax = plt.subplots()
    efig, ex = plt.subplots()

    wx.plot(x, working_time)
    ax.plot(x, acceleration)
    ex.plot(x, efficienty)

    plt.show()





