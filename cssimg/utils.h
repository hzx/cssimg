#ifndef CSSIMG_UTILS_H
#define CSSIMG_UTILS_H


#include <string>


using std::string;


bool pathExists(string& filename);
string getExtension(const string& filename);
string loadFile(string& filename);
string base64_encode(unsigned char const* bytes_to_encode, unsigned int in_len);
string base64Encode(const string& value);


#endif /* end of include guard: CSSIMG_UTILS_H */
