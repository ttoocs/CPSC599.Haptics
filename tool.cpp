
#include "chai3d.h"
#include "CBullet.h"
#include "tool.h"
#include "types.h"
#include "sim.h"

chai3d::cGenericTool* tool;
chai3d::cHapticDeviceHandler* handler;
chai3d::cGenericHapticDevicePtr hapticDevice; 
double toolRadius = 0.006;

vec3 ws_mgmt_dir;

bool forceFeedbackMove = true;

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
    //tool->setWorkspaceRadius(0.8);

    // define a radius for the tool (graphical display)
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
  
    //addForce = vec3(0,0,0);
    ws_mgmt_dir = vec3(0,0,0);
    
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

        //WorkSpace Mgmt:
//        if(interactionPoint->getNumCollisionEvents() == 0)
        {
          //Get workspace radius of tool:

          double rad = hapticDevice->getSpecifications().m_workspaceRadius;
          rad*=.15; //Take half of it

          rad = 0.025; //Say screw it and set it to this as the above seems garbage now?
      
          vec3 tpos = tool->getDeviceLocalPos();
          double tlen = tpos.length();
//          std::cout << "len:" <<  tlen << std::endl;
          if(tlen > rad){
            vec3 dir = cNormalize( tpos);
            vec3 offset = dir*0.001;
            offset *= (tlen-rad)*30;
            ws_mgmt_dir = offset;
            //tool->setLocalPos(tool->getLocalPos() + offset);;
//            std::cout << "In: " << ws_mgmt_dir << std::endl;
          }

        }

            // check primary contact point if available
//            /*
            for( int i =0 ; i < interactionPoint->getNumCollisionEvents(); i++)
            {
                cCollisionEvent* collisionEvent = interactionPoint->getCollisionEvent(i);
                
                //Fix workspace mgmt vectors aganst the one we just hit.
                //Subtract the projection along the normal (ie, no moment along normal)
                if((collisionEvent->m_localNormal.x() != 0) || (collisionEvent->m_localNormal.y() != 0) || (collisionEvent->m_localNormal.z() != 0)){
                  ws_mgmt_dir -= chai3d::cProject( ws_mgmt_dir,  collisionEvent->m_localNormal);
                }else{
                  std::cout << "No normal: " << collisionEvent->m_localNormal << std::endl;
                }

                // given the mesh object we may be touching, we search for its owner which
                // could be the mesh itself or a multi-mesh object. Once the owner found, we
                // look for the parent that will point to the ODE object itself.
                cGenericObject* object = collisionEvent->m_object->getOwner()->getOwner();
                
                // cast to Bullet object //(EXCEPT, THE GENERIC, NOT SOME RANDOM MESH >.<
                cBulletGenericObject* bulletobject = dynamic_cast<cBulletGenericObject*>(object);

                // if ODE object, we apply interaction forces
                if (bulletobject != NULL)
                {
                                    
                    double simScale = 1;
//                    if(sim::haptic_cnt != 0)
//                      simScale /= sim::haptic_cnt;
                    bulletobject->addExternalForceAtPoint(
                      -interactionPoint->getLastComputedForce()*simScale,
                      collisionEvent->m_globalPos - object->getLocalPos());

                }else{
                }
            } // */
        
}

void toolHapticB(){
        if(forceFeedbackMove){
          vec3 addForce = -ws_mgmt_dir * 10000;
          tool->addDeviceLocalForce(addForce);
        }
        tool->setLocalPos(tool->getLocalPos() + ws_mgmt_dir);

        ws_mgmt_dir = 0;
          // send forces to haptic device
        tool->applyToDevice();
}

