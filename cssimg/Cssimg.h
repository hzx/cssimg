#ifndef CSSIMG_CSSIMG_H
#define CSSIMG_CSSIMG_H


#include <string>
#include <vector>


using std::string;
using std::vector;


const int CSSIMG_ERROR_OK = 0;
const int CSSIMG_ERROR_ARGS = 1;
const int CSSIMG_ERROR_CSS = 2;


class Cssimg {
public:
  Cssimg();
  void addPath(string& path);
  void compile(string& dest, string& src);
  string imgToBase64(string& filename);
  string inlineImages(string& src);
  size_t getUrlPos(string& buf, size_t left, size_t right);
  size_t getPos(string& buf, char c, size_t left, size_t right);
  string getFilename(string& filename);

  vector<string> paths;
  int error;
};


#endif /* end of include guard: CSSIMG_CSSIMG_H */
