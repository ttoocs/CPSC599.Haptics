
#include "chai3d.h"
#include "CBullet.h"
#include "tool.h"
#include "types.h"
#include "sim.h"
#include "obj.h"

chai3d::cGenericTool* tool;
chai3d::cHapticDeviceHandler* handler;
chai3d::cGenericHapticDevicePtr hapticDevice; 
double toolRadius = 0.006;

int moveCnt = 0;
vec3 ws_mgmt_dir;

bool forceFeedbackMove = true;

using namespace chai3d;
using namespace std;


proj::myObj * graspObject = NULL;
cVector3d graspPos;
cShapeLine* graspLine;
bool graspActive = false;

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


    //grasper:
    graspLine = new cShapeLine(cVector3d(0,0,0), cVector3d(0,0,0));
    bulletWorld->addChild(graspLine);
    graspLine->m_colorPointA.setRed();
    graspLine->m_colorPointB.setRed();
    graspLine->setShowEnabled(false);

}

void graspUpdate(){
      //Basically taken from bullet example 02.
        if (graspActive)
        {
            // check if button pressed
            if (tool->getUserSwitch(0))
            {
                // position grasp point in world coordinates
                //cVector3d posA = graspObject->getLocalTransform() * graspPos;
                cVector3d posA = graspObject->getLocalTransform() * graspPos;

                // position of tool
                cVector3d posB = tool->getHapticPoint(0)->getGlobalPosGoal();
                
                // update line
                graspLine->m_pointA = posA;
                graspLine->m_pointB = posB;
                graspLine->setShowEnabled(true);

                // compute force
                cVector3d force = 5.0 * (posB - posA);

                // apply force
                graspObject->addExternalForceAtPoint(force, posA - graspObject->getLocalPos());

                // apply reaction force to haptic device
                tool->addDeviceGlobalForce(-force);
            }
            else
            {
                graspLine->setShowEnabled(false);
                graspActive = false;
                graspObject = NULL;
            }
        }
        else
        {
            // get pointer to next interaction point of tool
            cHapticPoint* interactionPoint = tool->getHapticPoint(0);

            // check primary contact point if available
            if (interactionPoint->getNumCollisionEvents() > 0)
            {
                cCollisionEvent* collisionEvent = interactionPoint->getCollisionEvent(0);

                // given the mesh object we may be touching, we search for its owner which
                // could be the mesh itself or a multi-mesh object. Once the owner found, we
                // look for the parent that will point to the ODE object itself.
                cGenericObject* object = collisionEvent->m_object->getOwner()->getOwner();

                // cast to Bullet object
//                cBulletGenericObject*  bulletobject = dynamic_cast<cBulletGenericObject*>(object);

                // if ODE object, we apply interaction forces
                if (object != NULL)
                {

                    // check if button pressed
                    if (tool->getUserSwitch(0))
                    {
                        graspObject = proj::myObj::findObj(object);
                        if(graspObject != NULL){
                          graspPos = collisionEvent->m_localPos;
                          graspActive = true;
                        }
                    }
                }
            }
        }


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
        if(interactionPoint->getNumCollisionEvents() == 0){
          moveCnt++;
          if(moveCnt > 100)
            moveCnt = 100;
        }
            
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

                  if(moveCnt > 0){
                    moveCnt --;
                  }else{
                    ws_mgmt_dir -= chai3d::cProject( ws_mgmt_dir,  collisionEvent->m_localNormal);
                  }
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
            graspUpdate();        
}

void toolHapticB(){
        if(forceFeedbackMove){
          vec3 addForce = -ws_mgmt_dir * 10000;
          tool->addDeviceLocalForce(addForce);
        }
        tool->setLocalPos(tool->getLocalPos() + ws_mgmt_dir);

        if(tool->getUserSwitch(1)){
          tool->setLocalPos(0,0,0.3);
        }

        ws_mgmt_dir = 0;
          // send forces to haptic device
        tool->applyToDevice();
}

