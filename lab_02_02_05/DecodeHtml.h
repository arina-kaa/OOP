#pragma once
#include <iostream>
#include <string>
#include <algorithm>
#include <map>

void ProcessEncodedHtml(std::string& encodedStr, std::string::iterator& it, bool& isStarted, std::string& result);

std::string DecodeHtml(std::string& htmlString);
