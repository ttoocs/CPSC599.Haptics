# The most practical VNC ever.


For those who wish to have a haptic interface for their remote sessions, I offer this, a Haptic-Enabled, VNC Client.

This client offers only some the features that someone would want for a VNC client, for example, there is no identification on the keys what-so-ever. However, the keys will never get dirty, and come in a vibrant Red Indian. They also have a smooth motion, while being affixed to the keyboard, which one can move around in any manner they please.

#Introduction
The goal of this project was to accurately model the haptic interface that people experience on a daily basis while working on computers.

The common issue involved with haptics is that of speed, which is the major issue encountered in this project.

#Methods

This project was mainly accomplished using the chai3d library, with it's bullet module, and the VNC-component was done via libvnc.

The main issue involved is the real time run speed, and the complexity of having so many small objects to that can interact closely packed together. The Bullet Physics engine used here is a 'real time' engine by most standards, as it tends to run at ~60Hz. However, haptics requires 1000Hz, and hence, this was pushing the engine to the limit for this project. Patching chai3d to enable more configuration of the bullet-engine allowed a significant improvement in speed. Furthermore reducing the quality of the models gives significant improvements.

#Results

The end result is a rather impractical VNC client, where one needs haptic-hardware to allow one to interact with it. It's also rather power-hungry for a VNC client. But it does have key input, and can display the VNC server's images, and has decent haptic effects.
In terms of haptics, due to the ability to 'scale' time due to a separated physics engine, it's possible to maintain a high-haptic rate. As Bullet has some level of object-interpolation, this lets the haptic systems still feel realistic and smooth. However, the physics of the objects can be noticeably slowed down in some cases, effectively being in slow-motion.

I do wish I could get a haptic signal/feedback played back through the device to emulate the clicks of the device, however with multiple keys this stops being feasibly, as the mass and momentum become predominantly noticeable when the simulation slows down.



#Intro2
The goal of this project is to simulate the good old touch and feel of a computer, but through a haptic device. To accomplish this, it is a VNC client. Thus, any mundane regular task that could be completed in a few minutes, can now span a few hours of trying to get your input in over the lag of VNC, and a not-so-great keyboard... and a mouse that's just for looks.

As with most things in Haptics, the speed of thie simulation is, in large part, the hardest part. For this particular case with 50 or 75 keys (which is reduced from a normal keyboard), this is a rather taxing set of collisions to perform a thousand times a second. Especially so if one wants more complex interactions, which were simply forgiven due to already taxing the underlying system.

#Methods

The project was mainly accomplished using Chai3d with it's bullet module, and the VNC-lifting done via libvnc. These all doing most of the heavy lifting, the remaining part was to 'simply' assemble it, and watch it barley crawl and the physics to glitch and break.

The majority of the issues encountered were speed related. Through trial-and-error it's possible to find a stable-enough configuration for bullet to run as fast as it can. However, this is still significantly slower than the haptic rate with the 50+ near-proximity object of a keyboard (~30-100Hz). Reducing most models from meshes to simple cubes improved the rate, however loses the fidelity. As chai3d doesn't currently support having 'ghost' collisions while different models are used to render, it is just left as the simple meshes.
 Another significant improvement to the project was patching chai3d to enable bit masks for collision detections. This allows the closely packed keys to ignore each other, and the keyboard, for alternative simpler constrains to be used instead, and partially re-implemented for smoother haptic interaction.
 The springs used for each key are coded in such a manner, leveraging a nearly-5-axis restriction from the bullet library, and leaving the last to be handled by specialized code.

This however requires the Bullet Library to update more frequently than it can actually handle, but as it is a separate system, with a level of interpolation between physics steps, it is possible to slow this down to maintain a reasonable haptic rate, with the expense of everything becoming slow-motion.  To attempt to maximize this, and handle initial system instability, the system dynamically scales the time step with a threshold to stay relatively constant, with whatever the current system can handle.


#Results

The end result is a rather impractical VNC client, but a functional one. The haptic feedback is consistently smooth and stable, and one is able to type on the remote system for whatever purposes they want. Including losing horribly at video games.


