#include "types.h"
#include "input.h"
#include <iostream>

extern bool fullscreen;
extern bool mirroredDisplay;
extern int width;
extern int height;
extern int swapInterval;
extern GLFWwindow* window;

namespace proj {


void keyCallback(GLFWwindow* a_window, int a_key, int a_scancode, int a_action, int a_mods){
  

    // filter calls that only include a key press
    if (a_action != GLFW_PRESS)
    {
        return;
    }

    // option - exit
    else if ((a_key == GLFW_KEY_ESCAPE) || (a_key == GLFW_KEY_Q))
    {
        glfwSetWindowShouldClose(a_window, GLFW_TRUE);
    }

    // option - toggle fullscreen
    else if (a_key == GLFW_KEY_F)
    {
        // toggle state variable
        fullscreen = !fullscreen;

        // get handle to monitor
        GLFWmonitor* monitor = glfwGetPrimaryMonitor();

        // get information about monitor
        const GLFWvidmode* mode = glfwGetVideoMode(monitor);

        // set fullscreen or window mode
        if (fullscreen)
        {
            glfwSetWindowMonitor(window, monitor, 0, 0, mode->width, mode->height, mode->refreshRate);
            glfwSwapInterval(swapInterval);
        }
        else
        {
            int w = 0.8 * mode->height;
            int h = 0.5 * mode->height;
            int x = 0.5 * (mode->width - w);
            int y = 0.5 * (mode->height - h);
            glfwSetWindowMonitor(window, NULL, x, y, w, h, mode->refreshRate);
            glfwSwapInterval(swapInterval);
        }
    }

    // option - toggle vertical mirroring
    else if (a_key == GLFW_KEY_M)
    {
        mirroredDisplay = !mirroredDisplay;
        camera->setMirrorVertical(mirroredDisplay);
    }


}



void inputHelp(){
  std::cout << std::endl;
  std::cout << "\t\tScott Saunders - Cpsc599.Haptics - Final Project\t\t" << std::endl;
  std::cout << std::endl;
  std::cout << "[esc] - Exit applicatoin" << std::endl;

}

};
