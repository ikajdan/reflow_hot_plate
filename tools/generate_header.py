#!/usr/bin/env python3

import sys
import numpy as np
import matplotlib.pyplot as plt
from numpy.polynomial.polynomial import Polynomial

if len(sys.argv) < 2:
    print("Usage: generate_header.py <profile>")
    sys.exit(1)

# Profile name
profile_name = sys.argv[1]

# Degree of the polynomial to fit
degree = 8

# Plot the polynomial
plot_polynomial = False

# Reflow profile data file
data_file = "../data/reflow_profiles/" + profile_name + ".csv"

# Output header file
header_file = "../firmware/Components/PROFILES/Inc/" + profile_name + ".h"

# Load the data
data = np.genfromtxt(data_file, delimiter=",", skip_header=1, dtype=int)
time_data, temperature_data, stage_data = data[:, 0], data[:, 1], data[:, 2]

# Derive the polynomial from the data
coefficients = Polynomial.fit(time_data, temperature_data, degree).convert().coef
polynomial = Polynomial(coefficients)

# Calculate Mean Squared Error
temperature_fitted = polynomial(time_data)
mse = np.mean((temperature_data - temperature_fitted) ** 2)

# Calculate the temperatures
x_data = np.arange(time_data[-1])
y_data = polynomial(x_data)
y_data = np.round(y_data).astype(int)  # Round to the nearest integer

x_plot = np.linspace(min(time_data), max(time_data), 100)
y_plot = polynomial(x_plot)

# Extract stages
stages = [0]
for num in range(2, 5):
    found_stage = np.where(stage_data == num)[0]
    stages.append(time_data[found_stage[0]])

# Generate the header file
header_file_content = f"""#ifndef __{profile_name.upper()}_HEADER_H__
#define __{profile_name.upper()}_HEADER_H__

#define {profile_name.upper()}_SIZE {y_data.size}

int {profile_name}_stages[] = {{{', '.join(map(str, stages))}}};
int {profile_name}[] = {{{', '.join(map(str, y_data))}}};

#endif /* __{profile_name.upper()}_HEADER_H__ */
"""

with open(header_file, "w") as header_file:
    header_file.write(header_file_content)

# Plot the data
plt.scatter(
    time_data, temperature_data, marker="x", label="Data Points", color="black", s=25
)
if plot_polynomial:
    plt.plot(
        x_plot,
        y_plot,
        "k",
        marker="",
        label=f"Fitted Polynomial (Degree: {degree})",
        linewidth=0.5,
    )
if not plot_polynomial:
    plt.scatter(
        x_data,
        y_data,
        marker=".",
        label="Interpolated & quantized curve",
        color="red",
        s=5,
    )
plt.xlabel("Time (s)")
plt.ylabel("Temperature (°C)")
plt.text(280, 27, f"MSE: {mse:.5f}", fontsize=10, color="gray")
plt.legend()
plt.tick_params(axis="both", which="both", direction="in", top=True, right=True)
plt.grid(True, linestyle="dotted")
plt.show()
