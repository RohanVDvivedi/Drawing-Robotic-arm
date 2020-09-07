# Drawing Robotic arm

This repository contains source code for building a robotic arm that writes and draws by mimicking the movement of mouse position on the laptop screen.

The robot is made from corrugated plastic sheet, It is in the shape of an arm of a human being as if s/he is writing.
There are 2 servo motors used for controlling the position of the pen on the board.
2 servos move two link to reach out different position on the drawing board

Aim:- To make a Robotic Drawing Arm that mimics the motion of a finger on touchpad or a mouse.

Hardware used:-
2 – 5 kg-cm torque servos
1 – Micro Servo
1 – 31 cm * 3 cm corrugated plastic sheet
1 – 31 cm * 8 cm corrugated plastic sheet
2 – Regular sized castor wheel for support
1 – Arduino board
1 – External 5v power supply

Details:- The Structure of this Draw-arm is similar to the arm of a person posed for drawing/writing things up. A laptop was used for most of the processing and the Arduino was only used to control the servo motors. A Cpp code took the mouse co-ordinates as input and scaled them to the 31cm * 40cm drawing board. The scaled input was then used to change the angles of the servo motors to reach the particular point in the drawing board. This information of the angle of the servo motor was relayed to the Arduino using serial communication over USB.

Videos:- The Video can be found here : https://youtu.be/kQPi9CGzyg4
