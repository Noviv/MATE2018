#!/usr/bin/env python3

from PIL import Image
from PIL import ImageTk

from tkinter import Label, Entry, Tk, Button
from tkinter.filedialog import askopenfilename
from tkinter import ttk, messagebox
import tkinter as tk

import numpy
import math
import cv2

from enum import Enum
import pytesseract
import difflib

import matplotlib
matplotlib.use("agg")
from matplotlib.backends.backend_tkagg import FigureCanvasTkAgg, NavigationToolbar2TkAgg
from matplotlib.figure import Figure

def center(toplevel):
	toplevel.update_idletasks()
	w = toplevel.winfo_screenwidth()
	h = toplevel.winfo_screenheight()
	size = tuple(int(_) for _ in toplevel.geometry().split('+')[0].split('x'))
	x = w / 2 - size[0] / 2
	y = h / 2 - size[1] / 2
	toplevel.geometry("%dx%d+%d+%d" % (size + (x, y)))

class FlightGUI:
	def __init__(self, master):
		self.master = master

		# take off location
		self.tol_l = Label(master, text="Take-off Location")
		self.tol_l.pack()

		self.tol = Entry(master)
		self.tol.pack()

		# heading
		self.head_l = Label(master, text="Heading (deg)")
		self.head_l.pack()

		self.head = Entry(master)
		self.head.pack()

		# ascent airspeed
		self.aa_l = Label(master, text="Ascent Airspeed (m/s?)")
		self.aa_l.pack()

		self.aa = Entry(master)
		self.aa.pack()

		# ascent rate
		self.ar_l = Label(master, text="Ascent Rate (m/s?)")
		self.ar_l.pack()

		self.ar = Entry(master)
		self.ar.pack()

		# time after takeoff
		self.tat_l = Label(master, text="Time After Takeoff (s)")
		self.tat_l.pack()

		self.tat = Entry(master)
		self.tat.pack()

		# descent airspeed
		self.da_l = Label(master, text="Descent Airspeed (m/s?)")
		self.da_l.pack()

		self.da = Entry(master)
		self.da.pack()

		# descent rate
		self.dr_l = Label(master, text="Descent Rate (m/s?)")
		self.dr_l.pack()

		self.dr = Entry(master)
		self.dr.pack()

		# wind direction
		self.wd_l = Label(master, text="Wind Direction (deg)")
		self.wd_l.pack()

		self.wd = Entry(master)
		self.wd.pack()

		# close
		self.close_b = Button(master, text="Close", command=master.quit)
		self.close_b.pack(side="bottom")

		# calculate
		self.calc_b = Button(master, text="Calculate", command=self.calc)
		self.calc_b.pack(side="bottom")

		# load from file
		self.load_b = Button(master, text="Load File", command=self.load)
		self.load_b.pack(side="bottom")

	def load(self):
		print("Loading from file...")
		filename = askopenfilename()

		if filename:
			print("will load", filename)
			# parse here

	def calc(self):
		print("Calculating...")

		# ascent
		r = float(self.aa.get()) * float(self.tat.get())
		t = 90 - float(self.head.get()) # degrees

		x0 = round(r * math.cos(math.radians(t)), 4)
		y0 = round(r * math.sin(math.radians(t)), 4)

		print('Ascent movement   ', x0, ' meters along X axis')
		print('                  ', y0, ' meters along Y axis')

		# descent
		r = float(self.da.get()) * float(self.tat.get()) * float(self.ar.get()) / float(self.dr.get())
		t = 90 - float(self.head.get())

		x1 = round(r * math.cos(math.radians(t)), 4)
		y1 = round(r * math.sin(math.radians(t)), 4)

		print('Descent movement  ', x1, ' meters along X axis')
		print('                  ', y1, ' meters along Y axis')

		# wind
		r = self.calc_ws(float(self.tat.get()) * float(self.ar.get()) / float(self.dr.get()))
		t = float(self.wd.get()) + 90

		x2 = round(r * math.cos(math.radians(t)), 4)
		y2 = round(r * math.sin(math.radians(t)), 4)

		print('Wind movement     ', x2, ' meters along X axis')
		print('                  ', y2, ' meters along Y axis')

		x = round(x0 + x1 + x2, 4)
		y = round(y0 + y1 + y2, 4)

		print('Total movement    ', x, ' meters along X axis')
		print('                  ', y, ' meters along Y axis')

		r = round(math.sqrt(x * x + y * y), 4)
		t = round(90 - math.degrees(math.atan2(y, x)), 4)

		out = 'Search zone: ' + str(r) + ' meters in direction ' + str(t) + ' degrees from ' + self.tol.get()
		print(out)
		messagebox.showinfo('Calculation', out)

	def calc_ws(self, t):
		return 25 * t - math.pow(t, 3) / 2160

class TidalGUI:
	def __init__(self, master):
		self.master = master

		# number of turbines
		self.n_l = Label(master, text="Number of Turbines")
		self.n_l.pack()

		self.n = Entry(master)
		self.n.pack()

		# density of seawater
		self.p_l = Label(master, text="Seawater Density (kg/m^3)")
		self.p_l.pack()

		self.p = Entry(master)
		self.p.pack()

		# swept area of one rotor
		self.a_l = Label(master, text="Rotor Swept Area (m^2)")
		self.a_l.pack()

		self.a = Entry(master)
		self.a.pack()

		# velocity of water
		self.v_l = Label(master, text="Water Velocity (m/s)")
		self.v_l.pack()

		self.v = Entry(master)
		self.v.pack()

		# efficiency of turbines
		self.cp_l = Label(master, text="Turbine Efficiency")
		self.cp_l.pack()

		self.cp = Entry(master)
		self.cp.pack()

		# close
		self.close_b = Button(master, text="Close", command=master.quit)
		self.close_b.pack(side="bottom")

		# calculate
		self.calc_b = Button(master, text="Calculate", command=self.calc)
		self.calc_b.pack(side="bottom")

		# load from file
		self.load_b = Button(master, text="Load File", command=self.load)
		self.load_b.pack(side="bottom")

	def load(self):
		print("Loading from file...")
		filename = askopenfilename()
		
		if filename:
			print("will load", filename)
			# parse here

	def calc(self):
		print("Calculating...")
		try:
			val = float(self.n.get())
			val *= .5
			val *= float(self.p.get())
			val *= float(self.a.get())
			val *= float(self.v.get()) ** 3
			val *= float(self.cp.get())
			print("P = ", val)
		except:
			print("missing params")

class SeismicGUI:
	def __init__(self, master):
		self.master = master

		# graph
		f = Figure(figsize=(5, 5), dpi=100)
		self.a = f.add_subplot(111)
		self.a.plot([1, 2, 3, 4, 5, 6, 7, 8], [5, 6, 1, 3, 8, 9, 3, 5])

		self.a.set_xlabel('Time (s)')
		self.a.set_ylabel('Amplitude')

		self.canvas = FigureCanvasTkAgg(f, master)
		self.canvas.show()
		self.canvas.get_tk_widget().pack(side="top", fill="both", expand=True)

		# close
		self.close_b = Button(master, text="Close", command=master.quit)
		self.close_b.pack(side="bottom")

		# load from file
		self.load_b = Button(master, text="Load File", command=self.load)
		self.load_b.pack(side="bottom")

		# navigation
		self.toolbar = NavigationToolbar2TkAgg(self.canvas, master)
		self.toolbar.update()
		self.canvas._tkcanvas.pack(side="top", fill="both", expand=True)

	def load(self):
		print("Loading from file...")
		filename = askopenfilename()
		
		if filename:
			print("will load", filename)

		self.a.clear()
		data = numpy.genfromtxt(filename, delimiter=',', skip_header=1, names=['x', 'y'])
		self.a.set_xlabel('Time (s)')
		self.a.set_ylabel('Amplitude')
		self.a.plot(data['x'], data['y'], color='r', label='data')
		self.canvas.draw()

class VideoGUI:
	def __init__(self, master, cap):
		self.master = master
		self.cap = cap

		self.airplanes = ['UH8', 'L6R', 'G7C', 'S1P', 'JW3', 'A2X']

		# set up opencv shit
		self.lmain = Label(master)
		self.lmain.pack()

		# close
		self.close_b = Button(master, text="Close", command=master.quit)
		self.close_b.pack(side="bottom")

		# take picture
		self.calc_b = Button(master, text="Screen Grab", command=self.grab)
		self.calc_b.pack(side="bottom")

		self.show_frame()

	def grab(self):
		_, frame = self.cap.read()

		# convert to grayscale
		gray = cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY)
		_, gray = cv2.threshold(gray, 255, 255, cv2.THRESH_BINARY | cv2.THRESH_OTSU)

		# OCR
		text = pytesseract.image_to_string(gray)
		print('found:', text)
		poss = difflib.get_close_matches(text, self.airplanes)

		if poss:
			idx = self.airplanes.index(poss[0])
			print('Probably plane', chr(ord('A') + idx), 'with ID', poss[0])
		else:
			print('No ID found')

	def show_frame(self):
		_, frame = self.cap.read()
		oframe = cv2.cvtColor(frame, cv2.COLOR_BGR2RGBA)

		img = Image.fromarray(oframe)
		imgtk = ImageTk.PhotoImage(image=img)
		self.lmain.imgtk = imgtk
		self.lmain.configure(image=imgtk)
		self.lmain.after(10, self.show_frame)

root = Tk()
root.geometry('900x700')
root.resizable(False, False)
root.title("UT SAE Underwater GUI")
center(root)

cap = cv2.VideoCapture(0)

# set up notebook
s = ttk.Style()
s.configure('TNotebook', tabposition='n')
n = ttk.Notebook(root)

# set up flight GUI
flight = ttk.Frame(n)
flight_gui = FlightGUI(flight)
n.add(flight, text="Flight")

# set up tidal GUI
tidal = ttk.Frame(n)
tidal_gui = TidalGUI(tidal)
n.add(tidal, text="Tidal")

# set up seismic GUI
seis = ttk.Frame(n)
seis_gui = SeismicGUI(seis)
n.add(seis, text="Seismic")

# set up video GUI
vid = ttk.Frame(n)
vid_gui = VideoGUI(vid, cap)
n.add(vid, text="Video")

# pack
n.pack(fill=tk.BOTH, expand=True)

# loop
root.mainloop()
