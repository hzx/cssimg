#include <cstring>
#include <sstream>
#include <fstream>
#include "utils.h"
#include "Cssimg.h"


const string URL_OPEN = "url(";


Cssimg::Cssimg()
    : error(CSSIMG_ERROR_OK) {
}


void Cssimg::addPath(string& path) {
  paths.push_back(path);
}


void Cssimg::compile(string& dest, string& src) {
  if (!pathExists(src)) {
    error = CSSIMG_ERROR_CSS;
    return;
  }

  std::ostringstream buf;
  std::ifstream inp(src);

  buf << inp.rdbuf();
  string srcContent = buf.str();

  string content = inlineImages(srcContent);

  std::ofstream out(dest);
  out << content;
}


string Cssimg::imgToBase64(string& filename) {
  std::ostringstream buf;
  std::ifstream inp(filename);

  buf << inp.rdbuf();
  string content = buf.str();

  return "data:image/" + getExtension(filename) + ";charset=utf-8;base64," +
      base64Encode(content);
}


string Cssimg::inlineImages(string& src) {
  std::ostringstream buf;
  size_t left = 0;
  size_t right = src.length();
  size_t urlPos;
  size_t urlEnd;

  for (;;) {
    // find url(urlPos
    urlPos = getUrlPos(src, left, right);
    // write all before and with url( or to the end
    buf.write(&src[left], urlPos - left);

    if (urlPos == right) break;

    // skip quoted filename
    if (src[urlPos] != '"' and urlPos != right) {
      // find url close bracket
      urlEnd = getPos(src, ')', urlPos, right);

      // convert filename to base64 content and copy to buf
      if (urlEnd != right and (urlEnd - urlPos) > 0) {
        string filename = src.substr(urlPos, urlEnd - urlPos);
        string full = getFilename(filename);
        if (full.length() > 0) buf << imgToBase64(full);
        else buf << filename; // TODO: report file not found
      }

      left = urlEnd; // move left to ) position
    } else {
      left = urlPos;
    }
  }

  return buf.str();
}


size_t Cssimg::getUrlPos(string& buf, size_t left, size_t right) {
  for (size_t i = left; i < right; ++i) {
    if (buf[i] == 'u') {
      if (std::memcmp(&buf[i], URL_OPEN.data(), URL_OPEN.length()) == 0) {
        return i + URL_OPEN.length();
      }
    }
  }

  return right;
}


size_t Cssimg::getPos(string& buf, char c, size_t left, size_t right) {
  for (size_t i = left; i < right; ++i) {
    if (buf[i] == c) return i;
  }

  return right;
}


string Cssimg::getFilename(string& filename) {
  for (auto path: paths) {
    string full = path + "/" + filename;
    if (pathExists(full)) {
      return full;
    }
  }

  return "";
}
