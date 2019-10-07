# -*- coding: utf-8 -*-
"""
Created on Sun Oct  6 18:27:47 2019

@author: Reet Barik
"""

import os
os.chdir("D:/Coursework/PACCAR/VarroaPOP/Beepop/Simulations/")

import numpy as np
import pandas as pd
from datetime import datetime
import math
import json
from VarroaPy.VarroaPy.RunVarroaPop import VarroaPop

def photoperiod(latitude, date):
    day = datetime.strptime(str(date), "%Y-%m-%d %H:%M:%S")
    J = day.timetuple().tm_yday
    
    P = math.asin(0.39795 * math.cos(0.2163108 + 2 * math.atan(0.9671396 * math.tan(0.00860 * (J - 186)))))
    D = 24 - (24 / math.pi) * math.acos((math.sin(0.833 * math.pi / 180) + (math.sin(latitude * math.pi / 180) * math.sin(P))) / (math.cos(latitude * math.pi / 180) * math.cos(P)))
    return D
    

obsHist = False
modHist = False
rcp = True

weatherFile = ""
Location = 'Omak'

if Location == 'Omak':
    weatherFile = 'data_48.40625_-119.53125'
if Location == 'Wenatchee':
    weatherFile = 'data_47.40625_-120.34375'
if Location == 'Richland':
    weatherFile = 'data_46.28125_-119.34375'
if Location == 'WallaWalla':
    weatherFile = 'data_46.03125_-118.34375'
    
if obsHist:    
    dt = np.dtype([('PPT', 'ushort'), ('TMAX', 'short'), ('TMIN', 'short'), ('WIND', 'short'), ('SPH', 'short'), ('SRAD', 'short'), ('RMAX', 'short'), ('RMIN', 'short')])
    data = np.fromfile('ObservedHistoricalBinary/' + weatherFile, dtype=dt)
if modHist:    
    dt = np.dtype([('PPT', 'ushort'), ('TMAX', 'short'), ('TMIN', 'short'), ('WIND', 'short')])
    data = np.fromfile('ModeledHistoricalBinary/' + weatherFile, dtype=dt)
if rcp:    
    dt = np.dtype([('PPT', 'ushort'), ('TMAX', 'short'), ('TMIN', 'short'), ('WIND', 'short')])
    data = np.fromfile('Rcp85Binary/' + weatherFile, dtype=dt)
    

df = pd.DataFrame(data)

if obsHist:
    df['PPT'] = df['PPT'] / 40
    df['TMAX'] = df['TMAX'] / 100
    df['TMIN'] = df['TMIN'] / 100
    df['WIND'] = df['WIND'] / 100
    df['SPH'] = df['SPH'] / 1000
    df['SRAD'] = df['SRAD'] /40
    df['RMAX'] = df['RMAX'] / 100
    df['RMIN'] = df['RMIN'] /100
else:
    df['PPT'] = df['PPT'] / 40
    df['TMAX'] = df['TMAX'] / 100
    df['TMIN'] = df['TMIN'] / 100
    df['WIND'] = df['WIND'] / 100


columns = ['Date', 'Max', 'Min', 'Ave', 'Wind', 'Rain']

weather = pd.DataFrame(columns=columns)

if obsHist:
    weather['Date'] = pd.date_range(start='1/1/1979', periods=len(df), freq='D')
if modHist:
    weather['Date'] = pd.date_range(start='1/1/1950', periods=len(df), freq='D')
if rcp:
    weather['Date'] = pd.date_range(start='1/1/2006', periods=len(df), freq='D')

weather['Max'] = df['TMAX']
weather['Min'] = df['TMIN']
weather['Ave'] = (weather['Max'] + weather['Min']) / 2
weather['Wind'] = df['WIND']
weather['Rain'] = df['PPT']

latitude = float(weatherFile.split('_')[1])

weather['Hrs light'] = weather['Date'].apply(lambda x: photoperiod(latitude, x))

f = open("VarroaPy/VarroaPy/files/weather/" + weatherFile + ".wth","w") 
f.write("WEATHER_FILE\n")
f.write("Temperature Scale . . . . . . . . .  = C\n")
f.write("Weather File Name . . . . . . . . .  = " +  weatherFile + ".wth\n")
f.write("Format of the Weather File  . . . .  = MINMAX\n")
f.write("Begin Time of the Weather . . . . .  = 12:00\n")
f.write("Begin Date of the Weather . . . . .  = " + weather['Date'][0].strftime("%#m/%#d/%y") + "\n")
f.write("Ending Time of the Weather  . . . .  = 12:00\n")
f.write("Ending Date of the Weather  . . . .  = " + weather['Date'][len(weather) - 1].strftime("%#m/%#d/%y") + "\n")
f.write("Start Time of the Simulation  . . .  = 12:00\n")
f.write("Start Date of the Simulation  . . .  = " + weather['Date'][0].strftime("%#m/%#d/%y") + "\n")
f.write("Column # of the Temperature . . . .  = 4\n")
f.write("Column # of the Max Temperature . .  = 2\n")
f.write("Column # of the Min Temperature . .  = 3\n")
f.write("Column # of the Daylight . . . . . . = 7\n")
f.write("Column # of the Wind Speed  . . . .  = 5\n")
f.write("Column # of the Rain  . . . . . . .  = 6\n")
f.write("Interval Between Readings . . . . .  = 1440\n")
f.write("----------begin---------\n")

weather['Date'] = weather['Date'].apply(lambda x: x.strftime("%#m/%#d/%Y"))
weather = weather.set_index('Date')
f.write(weather.to_string())       
f.close()

with open('parameters.json', 'r') as f:
    params = json.load(f)
    
    
vp = VarroaPop(parameters = params, weather_file = "VarroaPy/VarroaPy/files/weather/" + weatherFile + ".wth")
output = vp.run_model()
output = output.drop(output.index[0])