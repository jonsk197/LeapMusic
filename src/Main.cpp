#include <iostream>
#include <string.h>
#include "../include/Leap.h"
#include "Listener.h"
#include "Matte.h"
#include <algorithm>
#include <cmath>

using namespace Leap;

int main(int argc, char** argv) {
  // Create a sample listener and controller
    SampleListener listener;
    Controller controller;
    Menu menu;

  // Have the sample listener receive events from the controller
  controller.addListener(listener);

  if (argc > 1 && strcmp(argv[1], "--bg") == 0)
    controller.setPolicy(Leap::Controller::POLICY_BACKGROUND_FRAMES);

  // Keep this process running until Enter is pressed
  std::cout << "Press Enter to quit..." << std::endl;
  std::cin.get();

  // Remove the sample listener when done
  controller.removeListener(listener);

  return 0;
}
