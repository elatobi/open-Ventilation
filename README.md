# Open-Ventilation

<img src="https://user-images.githubusercontent.com/74827898/218269923-bbefb53c-6b16-4999-8544-78e45443e4aa.jpeg" width="403" height="302">

This is an Arduino sketch to PWM controll a 12V Fan, the PCB files for the PCB and the CAD-Data for my Printercabinet housing. 

The mainscreen shows the current temperature, material and the dutycicle of the fan.

<img src="https://user-images.githubusercontent.com/74827898/218269938-e21277fe-43e8-4590-ba35-f5fb0ce41b7e.jpeg" width="336" height="231">

By pressing the button of the rotaryencoder for 3s, the setup menu gets opend. Ther you can set the different materials.
For now there is PLA, PETG, FLEX, PC and IGLIDUR a material from Igus. 
Each material has its own min and max temp. Between thise temperatures the fan runns with a maped dutycicle, below the min temp the fan is not running.
Abov the max temp the fan runns with 100% dutycicle.

<img src="https://user-images.githubusercontent.com/74827898/218269966-f96a36b7-01b3-446a-84e5-3d0d535cc380.jpeg" width="294" height="197">


In the PCB folder are the files for getting the PCB according to the circuit diagram.

<img src="https://user-images.githubusercontent.com/74827898/218269215-f0da455d-e86e-4aa1-a800-56056abaaff0.png" width="410" height="213">
<img src="https://user-images.githubusercontent.com/74827898/218269218-1ed52f0d-93b7-4f24-bc2f-cc7ed72fb9f3.png" width="410" height="213">
<img src="https://user-images.githubusercontent.com/74827898/218269225-b387a72c-2502-43e5-9086-2c4d5a14c1cf.png" width="244" height="244">

You can finde the CAD-Files for the Housing at my Printables Profile https://www.printables.com/de/model/162908-housing-for-cabinet-ventilation-control

# BOM

1 x Arduino Nano\
1 x 16x2 LCD with i2C backpack\
1 x DS18B2\
1 x Rotaryencoder with button\
1 x IRFZ44N MOSFET\
1 x 1N4007 Diode\
1 x 10 kΩ Resistor\
1 x 4,7 kΩ Resistor\
1 x 220 Ω Resistor\
1 x 12V Fan (2 or 3 Wire)\
1 x 12V powersuply 


