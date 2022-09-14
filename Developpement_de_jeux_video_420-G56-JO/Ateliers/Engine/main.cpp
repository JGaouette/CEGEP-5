#include "Application.hpp"
#include "Renderer.hpp"

using namespace std;

int main(int argc, char* argv[]) {
  Application application;
  application.addWindow(new Renderer("A"));
  application.addWindow(new Renderer("B"));
  application.start();

  return 0;
}
