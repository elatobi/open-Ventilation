# Open-Ventilation

This is an Arduino sketch to controll an 12V Fan. I use this to ventilate my Printercabinet. 

<img src="https://user-images.githubusercontent.com/74827898/218267789-d42504ba-00f3-40d7-9853-e34cf54e7a7b.jpg" width="403" height="302">

The mainscreen shows the current temperature, material and the dutycicle of the fan.

<img src="https://user-images.githubusercontent.com/74827898/218267807-d876c021-c1a1-4d8f-ba48-8c7f13a479c5.jpg" width="336" height="231">

By pressing the button of the rotaryencoder for 3s, the setup menu gets opend. Ther you can set the different materials.
For now there is PLA, PETG, FLEX, PC and IGLIDUR a material from Igus. 
Each material has its own min and max temp. Between thise temperatures the fan runns with a maped dutycicle, below the min temp the fan is not running.
Abov the max temp the fan runns with 100% dutycicle.

<img src="https://user-images.githubusercontent.com/74827898/218267813-f431670b-728f-423f-8b89-dc367e704677.jpg" width="294" height="197">


In the PCB folder are the files for getting the PCB according to the circuit diagram.

You can finde the CAD-Files for the Housing at my Printables Profile https://www.printables.com/de/model/162908-housing-for-cabinet-ventilation-control

