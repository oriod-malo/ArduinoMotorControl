# ArduinoMotorControl
A small Arduino Project which controls a Servo Motor through a 4x4 Matrix Keyboard and displays the information in a 16x2 LCD

Servo motors are extremely common in automation and robotics, such as the example you can see [here](https://www.youtube.com/watch?v=jHWhP4bcG60), the Terasic Spider Robot which makes use of 18 servo motors to move its legs.

For this reason, I decided to develop this small basic framework that emulates a controlled servo motor (from a 4x4 matrix keyboard) and will also display status information in a 16x2 LCD screen.



## **Description:**

If we encode the matrix keyboard as follows:<br>
| 1 | 2 | 3 | A |<br>
| 4 | 5 | 6 | B |<br>
| 7 | 8 | 9 | C |<br>
| + | 0 | - | D |<br>
<br>

Then: 
Numbers 1-9 determine the rotation speed of the Servo Motor by setting the delay. Each number sets a n*5ms delay from step to step. This means that the highest speed will be had with 1 and the lowest speed with 9.
Because the delay for "1" is 5ms while the delay for "9" is 45ms.
Pressing "A" will make it sweep from the 180° position to the 0° position (clock direction). It will not move if the servo is in 0°.
Pressing "B" will make it sweep from the 0° position to the 180° position (anticlock direction). It will not move if the servo is in 180°.
Pressing "C" will make it perform a determined number N of automatic dual sweeps 0° -> 180° and then back 180° -> 0°. This number is determined by the three buttons +, 0 and -. 
Pressing "+" will increase the automatic sweeps by 1. Max number (determined arbitrarily) is 12. Analogously "-" Will decrease the number of automatic sweeps. (Can't go below 0).
Pressing "0" will set the number of automatic sweeps to 0. If 0, this nu
Pressing "D" will show the current position in degrees.

While performing sweeps the LCD will display the current sweep and how many sweeps (except this one) are left.

## **Video:**
The video below (linked to my YT channel) shows these features: automatic sweep, speed change, sweeping in directions (and not moving when there) etc.
https://www.youtube.com/watch?v=JffzAquG6DU

## **Components:**
* Arduino UNO
* SG90 Servo Motor
* 4x4 Matrix Keyboard
* 16x2 LCD Display
* Breadboard and Jumper Wires

## **Setup:**
![image](https://user-images.githubusercontent.com/123891760/220959873-f174d6d5-2652-4a58-9986-888d884a49e0.png)
