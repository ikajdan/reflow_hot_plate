#!/usr/bin/env python3

"""
Data logger and visualizer for the reflow hot plate.
"""

import gi

gi.require_version("Gtk", "3.0")
from gi.repository import Gtk, GLib

import sys
import serial
import json
import matplotlib.pyplot as plt
import matplotlib.style as mpl_style
from matplotlib.ticker import MaxNLocator
from matplotlib.backends.backend_gtk3agg import FigureCanvasGTK3Agg as FigureCanvas

if len(sys.argv) < 2:
    print("Usage: python reflow_hot_plot.py <serial_port>")
    sys.exit(1)

serial_path = sys.argv[1]
serial_port = serial.Serial(serial_path, baudrate=9600, timeout=0)

# Force the theme to Adwaita Dark
settings = Gtk.Settings.get_default()
settings.set_property("gtk-theme-name", "adw-gtk3-dark")
settings.set_property("gtk-application-prefer-dark-theme", True)


class ReflowHotPlot(Gtk.Window):
    def __init__(self):
        Gtk.Window.__init__(self, title="Reflow Hot Plot")
        self.set_default_size(800, 600)
        self.set_border_width(16)

        native_theme = {
            "text.color": "#1A1A19",
            "xtick.color": "#1A1A19",
            "ytick.color": "#1A1A19",
            "grid.color": "#999997",
            "axes.facecolor": "#F6F5F4",
            "axes.edgecolor": "#F6F5F4",
            "axes.labelcolor": "#1A1A19",
            "figure.facecolor": "#F6F5F4",
            "figure.edgecolor": "#F6F5F4",
            "grid.linestyle": "--",
        }

        native_theme_dark = {
            "text.color": "#807A7A",
            "xtick.color": "#807A7A",
            "ytick.color": "#807A7A",
            "grid.color": "#454242",
            "axes.facecolor": "#242424",
            "axes.edgecolor": "#242424",
            "axes.labelcolor": "#807A7A",
            "figure.facecolor": "#242424",
            "figure.edgecolor": "#242424",
            "grid.linestyle": "--",
        }

        mpl_style.use(native_theme_dark)

        self.data = {"Time": [], "Temperature": [], "TargetTemperature": []}
        self.fig, self.ax = plt.subplots()
        self.canvas = FigureCanvas(self.fig)
        self.add(self.canvas)

        GLib.timeout_add(100, self.read_data)

    def read_data(self):
        received_data = self.read_serial_data()
        if received_data:
            print("Received:", received_data)
            try:
                payload = json.loads(received_data)
                self.update_plot(payload)
            except json.JSONDecodeError as e:
                print(f"Error decoding JSON: {e}")
        return True

    def read_serial_data(self):
        if serial_port.in_waiting > 0:
            return serial_port.readline().decode("utf-8").strip()
        return None

    def update_plot(self, payload):
        for key, value in payload.items():
            if key in self.data:
                self.data[key].append(value)

        self.ax.clear()
        self.ax.grid(axis="y")
        self.ax.set_xlabel("Time [s]", labelpad=16)
        self.ax.set_ylabel("Temperature [°C]", labelpad=16)
        self.ax.set_ylim(-1, 251)
        # Show only integer values
        self.ax.xaxis.set_major_locator(MaxNLocator(integer=True))
        self.ax.plot(
            self.data["Time"],
            self.data["Temperature"],
            label="Temperature",
            color="#F66151",
        )
        self.ax.plot(
            self.data["Time"],
            self.data["TargetTemperature"],
            label="TargetTemperature",
            color="#F8E45C",
        )

        self.canvas.draw()


if __name__ == "__main__":
    window = ReflowHotPlot()
    window.connect("destroy", Gtk.main_quit)
    window.show_all()
    Gtk.main()
