#include <iostream>
#include <GLFW/glfw3.h>

using namespace std;

#define APP_NAME "gencylinder"
#define WINDOW_WIDTH 640
#define WINDOW_HEIGHT 512

void key_handler(GLFWwindow *w, int key, int scancode, int action, int mods) {
	if (w == NULL)
		return;

	if (key == GLFW_KEY_ESCAPE) {
		glfwSetWindowShouldClose(w, 1);
	}
}

int main(int argc, char* argv[]) {
  cout << "INFO: gencylinder starts" << endl;

  if (glfwInit() != GLFW_TRUE) {
	  cerr << "ERROR: Unable to init glfw" << endl;
	  exit(1);
  }

  GLFWwindow* w = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, APP_NAME, NULL, NULL);
  glfwSetKeyCallback(w, key_handler);
  
  while (!glfwWindowShouldClose(w)) {

	  glfwPollEvents();
	  glfwSwapBuffers(w);	  
  }


  glfwTerminate();


  return 0;
}
