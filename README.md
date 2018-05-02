# Ball_Shooter

The project is divided into two subsections. The First subsection deals with the control of the shooting device and the second deals with face detection using a webcam.

We controlled the shooting device using a Arduino Mega microcontroller. The controls were basically just motion of the shooter in all four directions, as well as rotation. The shooting method was developed using a friction based shooting mechanism, consisting of two wheels mounted parallel to each other.

The face detection algorithm uses the cascade classifier to identify faces in a given captured image from a webcam and using the OpenKinect software, extracted depth from a Kinect sensor to identify the locatin of the face in three dimensions and configure the shooter to point at the face
