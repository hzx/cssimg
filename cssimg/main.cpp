#include <iostream>
#include "CommandOptions.h"
#include "Cssimg.h"


int main(int argc, const char *argv[]) {
  CommandOptions options;
  options.parse(argc, argv);

  if (options.error or options.paths.size() == 0 or
      options.dest.length() == 0 or options.src.length() == 0) {
    std::cout << "cssimg options error" << std::endl;
    return -1;
  }

  Cssimg ci;
  for (auto path: options.paths)
    ci.addPath(path);
  ci.compile(options.dest, options.src);
  return ci.error;
}
