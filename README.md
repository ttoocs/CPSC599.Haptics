# The most practical VNC ever.


For those who wish to have a haptic interface for their remote sessions, I offer this, a Haptic-Enabled, VNC Client.

This client offers only some the features that someone would want for a VNC client, for example, there is no identification on the keys what-so-ever. However, the keys will never get dirty, and come in a viberant Red Indian. They also have a smooth motion, while being afixed to the keyboard, which one can move around in any manner they please.

#Introduction
The goal of this project was to accuratly model the haptic interface that people experience on a daily basis while working on computers.

The common issue involved with haptics is that of speed, which is the major issue encountered in this project.

#Methods

This project was mainly accomplished using the chai3d library, with it's bullet module, and the VNC-component was done via libvnc.

The main issue involved is the realtime run speed, and the complexity of having so many small objects to that can interact closely packed togeather. The BulletPhysics engine used here is a 'realtime' engine by most standards, as it tends to run at ~60Hz. However, haptics requires 1000Hz, and hence, this was pushing the engine to the limit for this project. Patching chai3d to enable more configuration of the bullet-engine allowed a signifigant improvment in speed. Furthermore reducing the quality of the models gives signifigant improvments.

#Results

The end result is a rather impractical VNC client, where one needs haptic-hardware to allow one to interact with it. It's also rather power-hungry for a VNC client. But it does have key input, and can display the vnc server's images, and has decent haptic effects.
In terms of haptics, due to the ability to 'scale' time due to a seperated physics engine, it's possible to maintain a high-haptic rate. As Bullet has some level of object-interpolation, this lets the haptic systems still feel realistic and smooth. However, the physics of the objects can be noticibly slowed down in some cases, effectivly being in slow-motion.

I do wish I could get a haptic signal/feedback played back through the device to emulate the clicks of the device, however with multiple keys this stops being feasable, as the mass and momentum become predominantly noticble when the simulation slows down.

