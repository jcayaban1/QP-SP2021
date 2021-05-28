# QP-SP2021
Spring 2021 Quarterly Project

NOTE:
1. You must have pyserial and pygame installed to run Cel.
2. Make sure the Arduino program Accelerometer_code.ino is uploaded to your Arduino. You need to have the Adafruit_MMA8451 and Adafruit_Sensor libraries installed on your computer.
3. Game.py line 28 must have the correct name of the serial port that is connected to the Arduino. The name of the port can be found in the Arduino IDE under "tools > Port"


How to run Cel on macOS terminal:
1. Navigate to the Cel directory in your terminal
2. Use the command "python3 main.py" (or other python compiler)
3. Input the number of players to control into the terminal
4. The game will begin after inputting the number of players

The not_using directory contains old code. We save them here just in case we need them again or need to refer to them.

If you do not have the correct hardware to run the game, you can alternatively go to the Cel_Computer_Only directory and follow steps 2-4 to run the game. You can control the players using the arrow keys.

You can quit the game at any time by pressing the ESC key. To restart the game, you must exit and relaunch.

NOTE: The dimensions of the maze can be changed. In each of the Game.py, Player.py, and Maze.py files, change RESOLUTION_WIDTH and RESOLUTION_HEIGHT to whatever dimension you want. Note that these dimensions must be THE SAME across all three files.
