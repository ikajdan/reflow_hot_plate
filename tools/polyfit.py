#!/usr/bin/env python3

import numpy as np
import matplotlib.pyplot as plt
from numpy.polynomial.polynomial import Polynomial
import csv

# Degree of the polynomial to fit
degree = 9

# Read data from the CSV file
data_file = "../data/reflow_profiles/dsp_863.csv"
x_data = []
y_data = []

with open(data_file, "r") as csvfile:
    csvreader = csv.reader(csvfile)
    next(csvreader) # Skip the header
    for row in csvreader:
        x_data.append(float(row[0]))
        y_data.append(float(row[1]))

# Create the polynomial function
coefficients = Polynomial.fit(x_data, y_data, degree).convert().coef
polynomial = Polynomial(coefficients)

# Print the polynomial formula 
print(polynomial)

# Calculate Mean Squared Error
x_mse = np.linspace(min(x_data), max(x_data), len(x_data))
y_fitted = polynomial(x_mse)
mse = np.mean((y_data - y_fitted) ** 2)

# Create points for plotting the polynomial curve
x_plot = np.linspace(min(x_data), max(x_data), 3600)
y_plot = polynomial(x_plot)

# Plot the original data points and the fitted polynomial curve
plt.scatter(x_data, y_data, marker="x", label="Data Points", color="black", s=25)
plt.plot(
    x_plot,
    y_plot,
    "k",
    marker="",
    label=f"Fitted Polynomial (Degree {degree})",
    linewidth=0.5,
)
plt.xlabel("Time (s)")
plt.ylabel("Temperature (°C)")
plt.text(280, 27, f"MSE: {mse:.5f}", fontsize=10, color="gray")
plt.legend()
plt.tick_params(axis="both", which="both", direction="in", top=True, right=True)
plt.grid(True, linestyle="dotted")
plt.show()

