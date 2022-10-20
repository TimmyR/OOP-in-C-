# OOP-in-Cpp

Code written for the Object-Oriented Programming in C++ course at the University of Manchester - Spring 2022.

This repository contains code from several small assignments (cumulative worth 30%) which developed my knowledge of C++, as well 
as a final project (worth 70%) where I built a program to store data from astronomical observations.

The assignments focused on learning the core funcitonality of C++ as well as the main elements of object-oriented programming: 
encapsulation, inheritance and polymorphism.

The project consists of an astronomical catalogue to store data from astronomical observations using the C++ Standard Library. The 
main functionality is being able to store and search the CelestialObject objects stored within the DataContainer class. The Date 
class contains the infrastructure to convert between UT1 and Terrestrial Time (TT) timescales, which is the basis for computing
the positions of celestial objects at any given time. UT1 is also used to calculate the Earth Rotation Angle (ERA) which can be
used to calculate the azimuth and heights of celestial objects given the user's position. The next stage of this project on my 
own time is an expansion into an ephemeris program. 

A more complete description of the final project and the C++ features used can be found in the "Project report.pdf" file.