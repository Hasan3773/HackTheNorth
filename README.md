Inspiration
Our inspiration for Haul-E is to help the elderly and physically impaired be more self reliant as well help lazy people save some effort.

What it does
Haul-E is a trolley bot that helps carry around luggage for you, controlled using just your eyes. Using Adhawk’s MindLink glasses, Non-Euclidean geometry and an electronic trolley, you are able to wirelessly control Haul-E using your blinks. Blink twice while looking at Haul-E to calibrate its location and then you can blink twice while looking at any location around you and Haul-E will travel there.

How we built it
Software: We started by using Adhawk’s MindLink API to pull vergence data on where the user is looking in (x, y, z) format and the IMU data in quaternion format. Then we created a program to check for our desired command, a double blink. This saves the point the user was looking at in 3 dimensions, however if the user is to move their head at all, that makes all the data redundant because we have rotated 3D space. So, we used the gyroscope in the IMU to get the tilt of the user's head in relation to a calibrated origin, then used Non-Euclidean math to apply the rotation to our 3D data, essentially putting all of our data in one space. We then used some basic trigonometry to turn the data into a distance and angle and then send the control information to the ESP32 on the trolley via Socket.

Hardware/Mechanical: In order to prototype the trolley and its all wheel drive system we started with four DC 3V-12V motors connected across two H-bridge L298n motor drivers using a ESP32 WIFI microcontroller. We designed our own chassis and wheels in Fusion 360 and 3D printed them to create a rugged, scaled down version of what we believe the trolley could look like in the future. All the electronics, including the two 9V batteries that operate this system are housed underneath the chassis itself creating a sleak design where heavy objects can easily be placed on a flat surface. In order to increase the friction on the wheels we wrapped each in rubber bands, allowing us to have smoother movement.

Challenges we ran into
One of our main challenges was our math calculations, we were trying to achieve high spatial computations while using very primitive data types and most of the data was abstracted behind the API so it was difficult to access and use all the data we wanted to without breaking a part of the API.

Operating all four motors simultaneously went beyond the capabilities of the library that we were using as we found that every time we would upload our code one motor would not work. After reassessing the variable declarations we discovered the library can only operate three motors at the same time. This caused us to rethink the circuit and redesign our connections within the two H-bridge motor drivers to find a solution that allows all the motors to run at high speeds.
