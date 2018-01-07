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

void mouse_handler(GLFWwindow *w, int button, int action, int mods) {

	if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_RELEASE) {
		double xpos, ypos;
		glfwGetCursorPos(w, &xpos, &ypos);

		int width, height;
		glfwGetWindowSize(w, &width, &height);

		double ndc_w = xpos / (double)width;
		double ndc_h = 1.0 - (ypos / (double)height);
		cout << "MousePos (ndc) = [" << ndc_w << " ," << ndc_h << "]" << endl;
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
  glfwSetMouseButtonCallback(w, mouse_handler);
  
  while (!glfwWindowShouldClose(w)) {

	  glfwPollEvents();
	  glfwSwapBuffers(w);	  
  }


  glfwTerminate();


  return 0;
}
