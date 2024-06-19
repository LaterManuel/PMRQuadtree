import csv
import matplotlib.pyplot as plt
from PIL import Image


def read_csv(filename):
    with open(filename, 'r') as csvfile:
        reader = csv.reader(csvfile)
        next(reader)  # Skip the header
        data = list(reader)
    return data

def plot_data(data):
    for row in data:
        p1_x, p1_y, p2_x, p2_y = map(float, row)
        plt.plot([p1_x, p2_x], [p1_y, p2_y], color='green', linewidth=0.5)
        plt.scatter([p1_x, p2_x], [p1_y, p2_y], color='blue')

    plt.show()

def main():

    filename = 'datapy.csv'

    # Read data from CSV
    data = read_csv(filename)

    # Plot the data
    plot_data(data)

    # Save plot as PNG
    image_path = 'plot.png'
    plt.savefig(image_path)

    # Close the plot
    plt.close()

    # Open and display the saved image
    img = Image.open(image_path)
    img.show()

if __name__ == "__main__":
    main()