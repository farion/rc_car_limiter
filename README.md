# Arduino sketch to limit the speed of a remote controlled car

Credits to http://www.rc-forum.de/showthread.php?4006290-Fahrtregler-Leistung-drosseln-mit-Arduino&p=5054032&viewfull=1#post5054032, where the idea and the original code is from.

## Hardware

Chassis: Tomiyo 1:10 TT-02R 
Motor: Robitronic Razer 1/10 Brushless Motor 3652 3000kV
Controller: Robotronic Razer 1/10 Brushless Speed Controller 60A 2-3s
Arduino: Arduino Micro
Receiver: Reflex Wheel PRO3 2,4 GHz 

## Circuit

 * Sig from receiver to D2
 * Sig to motor to D9
 * GND / 7,4V

## Behavior

Currently speed is limited by factor 12.
The brake is unlimited.
The backward speed is also limited, but not for the first 6 PWN cycles in order to overcome the threshold

## TODO 
Switch to control and disable Limiter (like the original code does)
