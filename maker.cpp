#include <iostream>
#include <cstdlib>
#include <sstream>
#include <string>

int main(int argc, char *argv[]) {

  if (argc < 2) {
    std::cerr << "Uso: thumbnail <video>\n";
    return 1;
  }

  std::string video = argv[1];
  const int frame = 30;

  std::string output = video;
  size_t dotPos = output.find_last_of('.');

  if (dotPos != std::string::npos) {
    output = output.substr(0, dotPos);
  }

  output += "_th.jpg";

  std::ostringstream cmd;

  cmd
    << "ffmpeg -y "
    << "-hide_banner -loglevel error "
    << "-i \"" << video << "\" "
    << "-vf \"select=eq(n\\," << frame << ")\" "
    << "-vsync vfr "
    << "-frames:v 1 "
    << "-q:v 2 "
    << "\"" << output << "\"";

  int result = system(cmd.str().c_str());

  if (result != 0) {
    std::cerr << "Error extrayendo thumbnail\n";
    return 2;
  }

  return 0;
}
