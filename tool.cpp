
#include "chai3d.h"
#include "CBullet.h"
#include "tool.h"
#include "types.h"

chai3d::cGenericTool* tool;
chai3d::cHapticDeviceHandler* handler;
chai3d::cGenericHapticDevicePtr hapticDevice; 

using namespace chai3d;
using namespace std;
void toolInit(){
   
    //Taken from a bullet example.

    // create a haptic device handler
    handler = new cHapticDeviceHandler();

    // get access to the first available haptic device
    shared_ptr<cGenericHapticDevice> hapticDevice;
    handler->getDevice(hapticDevice, 0);

    // retrieve information about the current haptic device
    cHapticDeviceInfo hapticDeviceInfo = hapticDevice->getSpecifications();

    // emulate button if device has a force gripper
    hapticDevice->setEnableGripperUserSwitch(true);

    // create a 3D tool and add it to the world
    tool = new cToolCursor(bulletWorld);
    bulletWorld->addChild(tool);

    // connect the haptic device to the tool
    tool->setHapticDevice(hapticDevice);

    // initialize tool by connecting to haptic device
    tool->start();

    // map the physical workspace of the haptic device to a larger virtual workspace.
    tool->setWorkspaceRadius(1.3);

    // define a radius for the tool (graphical display)
    double toolRadius = 0.06;
    tool->setRadius(toolRadius, toolRadius);

    // hide the device sphere. only show proxy.
    tool->setShowContactPoints(true, false);

    // enable if objects in the scene are going to rotate of translate
    // or possibly collide against the tool. If the environment
    // is entirely static, you can set this parameter to "false"
    tool->enableDynamicObjects(true);

    // haptic forces are enabled only if small forces are first sent to the device;
    // this mode avoids the force spike that occurs when the application starts when 
    // the tool is located inside an object for instance. 
    tool->setWaitForSmallForce(true);

    // start the haptic tool
    tool->start();
}

void toolHapticA(){
        // compute global reference frames for each object
        bulletWorld->computeGlobalPositions(true);

        // update position and orientation of tool
        tool->updateFromDevice();

        // compute interaction forces
        tool->computeInteractionForces();


            // get pointer to next interaction point of tool
            cHapticPoint* interactionPoint = tool->getHapticPoint(0);

            // check primary contact point if available
            for( int i =0 ; i < interactionPoint->getNumCollisionEvents(); i++)
            {
                cCollisionEvent* collisionEvent = interactionPoint->getCollisionEvent(i);

                // given the mesh object we may be touching, we search for its owner which
                // could be the mesh itself or a multi-mesh object. Once the owner found, we
                // look for the parent that will point to the ODE object itself.
                cGenericObject* object = collisionEvent->m_object->getOwner()->getOwner();

                // cast to Bullet object
                cBulletMesh* bulletobject = dynamic_cast<cBulletMesh*>(object);

                // if ODE object, we apply interaction forces
                if (bulletobject != NULL)
                {
                    bulletobject->addExternalForceAtPoint(-interactionPoint->getLastComputedForce(),
                        collisionEvent->m_globalPos - object->getLocalPos());

                }
            }
        
}

void toolHapticB(){
          // send forces to haptic device
        tool->applyToDevice();
}

