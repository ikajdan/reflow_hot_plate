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
from csv import writer
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

# Set the matplotlib style
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


class NavigationBar(Gtk.Box):
    def __init__(self, callback_dict):
        Gtk.Box.__init__(self, orientation=Gtk.Orientation.HORIZONTAL, spacing=16)

        self.callback_dict = callback_dict

        buttons_info = [
            ("Profile", "on_profile_clicked"),
            ("Start", "on_start_clicked"),
            ("Save Log", "on_save_clicked"),
            ("About", "on_about_clicked"),
        ]

        for label, callback_name in buttons_info:
            button = Gtk.Button(label=label)
            button.connect("clicked", self.on_button_clicked, callback_name)
            self.pack_start(button, True, True, 0)

    def on_button_clicked(self, widget, callback_name):
        callback = self.callback_dict.get(callback_name)
        if callback:
            callback(widget)


class MainWindow(Gtk.Window):
    def __init__(self):
        Gtk.Window.__init__(self, title="Reflow Hot Plot")
        self.set_default_size(800, 600)
        self.set_border_width(16)

        self.callback_dict = {
            "on_profile_clicked": self.on_profile_clicked,
            "on_start_clicked": self.on_start_clicked,
            "on_save_clicked": self.on_save_clicked,
            "on_about_clicked": self.on_about_clicked,
        }

        self.navigation_bar = NavigationBar(self.callback_dict)

        self.data = {"Time": [], "Temperature": [], "TargetTemperature": []}
        self.fig, self.ax = plt.subplots()
        self.canvas = FigureCanvas(self.fig)

        self.box = Gtk.Box(orientation=Gtk.Orientation.VERTICAL, spacing=48)
        self.box.set_margin_start(8)
        self.box.set_margin_end(8)
        self.box.pack_start(self.navigation_bar, False, False, 0)
        self.box.pack_start(self.canvas, True, True, 0)

        self.add(self.box)

        GLib.timeout_add(100, self.parse_data)

    def parse_data(self):
        received_data = self.read_serial_data()
        if received_data:
            print("Received:", received_data)
            try:
                payload = json.loads(received_data)
                for key, value in payload.items():
                    if key in self.data:
                        self.data[key].append(value)
                self.update_title(payload["State"])
                self.update_plot()
            except json.JSONDecodeError as e:
                print(f"Error decoding JSON: {e}")
        return True

    def read_serial_data(self):
        if serial_port.in_waiting > 0:
            return serial_port.readline().decode("utf-8").strip()
        return None

    def update_plot(self):
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

        plt.tight_layout(pad=1)
        self.canvas.draw()

    def update_title(self, state):
        state_mapping = {
            0: "Idle",
            1: "Preheat",
            2: "Reflow",
            3: "Cooldown",
        }

        state_name = state_mapping.get(state, "Idle")
        self.set_title(f"Reflow Hot Plot — {state_name}")

    def on_profile_clicked(self, widget):
        pass

    def on_start_clicked(self, widget):
        pass

    def on_save_clicked(self, widget):
        dialog = Gtk.FileChooserDialog(
            "Save Data to CSV",
            self,
            Gtk.FileChooserAction.SAVE,
            (
                Gtk.STOCK_CANCEL,
                Gtk.ResponseType.CANCEL,
                Gtk.STOCK_SAVE,
                Gtk.ResponseType.OK,
            ),
        )

        dialog.set_current_name("reflow_log.csv")
        dialog.set_do_overwrite_confirmation(True)

        filter_text = Gtk.FileFilter()
        filter_text.set_name("CSV files")
        filter_text.add_mime_type("text/csv")
        dialog.add_filter(filter_text)

        response = dialog.run()
        if response == Gtk.ResponseType.OK:
            filename = dialog.get_filename()
            self.write_data_to_csv(filename)

        dialog.destroy()

    def on_about_clicked(self, widget):
        dialog = Gtk.MessageDialog(
            self,
            0,
            Gtk.MessageType.INFO,
            Gtk.ButtonsType.OK,
            "Reflow Hot Plot",
        )
        dialog.format_secondary_text("Created by: Ignacy Kajdan\nLicense: MIT")
        dialog.run()
        dialog.destroy()

    def write_data_to_csv(self, filename):
        with open(filename, "w", newline="") as csvfile:
            csv_writer = writer(csvfile)
            csv_writer.writerow(self.data.keys())
            zip_data = zip(*self.data.values())
            csv_writer.writerows(zip_data)


if __name__ == "__main__":
    window = MainWindow()
    window.connect("destroy", Gtk.main_quit)
    window.show_all()
    Gtk.main()
