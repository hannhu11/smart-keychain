#pragma once
#include <Arduino.h>
#include <vector>
#define LGFX_USE_V1
#include <LovyanGFX.hpp>

class VietnameseRenderer {
public:
  static String cleanLatin(const String& input) {
    String s = input;
    // Lowercase
    s.replace("á", "a"); s.replace("à", "a"); s.replace("ả", "a"); s.replace("ã", "a"); s.replace("ạ", "a");
    s.replace("ă", "a"); s.replace("ắ", "a"); s.replace("ằ", "a"); s.replace("ẳ", "a"); s.replace("ẵ", "a"); s.replace("ặ", "a");
    s.replace("â", "a"); s.replace("ấ", "a"); s.replace("ầ", "a"); s.replace("ẩ", "a"); s.replace("ẫ", "a"); s.replace("ậ", "a");
    s.replace("đ", "d");
    s.replace("é", "e"); s.replace("è", "e"); s.replace("ẻ", "e"); s.replace("ẽ", "e"); s.replace("ẹ", "e");
    s.replace("ê", "e"); s.replace("ế", "e"); s.replace("ề", "e"); s.replace("ể", "e"); s.replace("ễ", "e"); s.replace("ệ", "e");
    s.replace("í", "i"); s.replace("ì", "i"); s.replace("ỉ", "i"); s.replace("ĩ", "i"); s.replace("ị", "i");
    s.replace("ó", "o"); s.replace("ò", "o"); s.replace("ỏ", "o"); s.replace("õ", "o"); s.replace("ọ", "o");
    s.replace("ô", "o"); s.replace("ố", "o"); s.replace("ồ", "o"); s.replace("ổ", "o"); s.replace("ỗ", "o"); s.replace("ộ", "o");
    s.replace("ơ", "o"); s.replace("ớ", "o"); s.replace("ờ", "o"); s.replace("ở", "o"); s.replace("ỡ", "o"); s.replace("ợ", "o");
    s.replace("ú", "u"); s.replace("ù", "u"); s.replace("ủ", "u"); s.replace("ũ", "u"); s.replace("ụ", "u");
    s.replace("ư", "u"); s.replace("ứ", "u"); s.replace("ừ", "u"); s.replace("ử", "u"); s.replace("ữ", "u"); s.replace("ự", "u");
    s.replace("ý", "y"); s.replace("ỳ", "y"); s.replace("ỷ", "y"); s.replace("ỹ", "y"); s.replace("ỵ", "y");

    // Uppercase
    s.replace("Á", "A"); s.replace("À", "A"); s.replace("Ả", "A"); s.replace("Ã", "A"); s.replace("Ạ", "A");
    s.replace("Ă", "A"); s.replace("Ắ", "A"); s.replace("Ằ", "A"); s.replace("Ẳ", "A"); s.replace("Ẵ", "A"); s.replace("Ặ", "A");
    s.replace("Â", "A"); s.replace("Ấ", "A"); s.replace("Ầ", "A"); s.replace("Ẩ", "A"); s.replace("Ẫ", "A"); s.replace("Ậ", "A");
    s.replace("Đ", "D");
    s.replace("É", "E"); s.replace("È", "E"); s.replace("Ẻ", "E"); s.replace("Ẽ", "E"); s.replace("Ẹ", "E");
    s.replace("Ê", "E"); s.replace("Ế", "E"); s.replace("Ề", "E"); s.replace("Ể", "E"); s.replace("Ễ", "E"); s.replace("Ệ", "E");
    s.replace("Í", "I"); s.replace("Ì", "I"); s.replace("Ỉ", "I"); s.replace("Ĩ", "I"); s.replace("Ị", "I");
    s.replace("Ó", "O"); s.replace("Ò", "O"); s.replace("Ỏ", "O"); s.replace("Õ", "O"); s.replace("Ọ", "O");
    s.replace("Ô", "O"); s.replace("Ố", "O"); s.replace("Ồ", "O"); s.replace("Ổ", "O"); s.replace("Ỗ", "O"); s.replace("Ộ", "O");
    s.replace("Ơ", "O"); s.replace("Ớ", "O"); s.replace("Ờ", "O"); s.replace("Ở", "O"); s.replace("Ỡ", "O"); s.replace("Ợ", "O");
    s.replace("Ú", "U"); s.replace("Ù", "U"); s.replace("Ủ", "U"); s.replace("Ũ", "U"); s.replace("Ụ", "U");
    s.replace("Ư", "U"); s.replace("Ứ", "U"); s.replace("Ừ", "U"); s.replace("Ử", "U"); s.replace("Ữ", "U"); s.replace("Ự", "U");
    s.replace("Ý", "Y"); s.replace("Ỳ", "Y"); s.replace("Ỷ", "Y"); s.replace("Ỹ", "Y"); s.replace("Ỵ", "Y");

    return s;
  }

  static void wrapText(const String& text, int maxCharsPerLine, std::vector<String>& lines) {
    lines.clear();
    String currentLine = "";
    String currentWord = "";

    for (size_t i = 0; i < text.length(); i++) {
      char c = text[i];
      if (c == ' ' || c == '\n') {
        if (currentLine.length() + currentWord.length() + 1 <= (size_t)maxCharsPerLine) {
          if (currentLine.length() > 0) currentLine += " ";
          currentLine += currentWord;
        } else {
          if (currentLine.length() > 0) lines.push_back(currentLine);
          currentLine = currentWord;
        }
        currentWord = "";
        if (c == '\n') {
          lines.push_back(currentLine);
          currentLine = "";
        }
      } else {
        currentWord += c;
      }
    }
    if (currentWord.length() > 0) {
      if (currentLine.length() + currentWord.length() + 1 <= (size_t)maxCharsPerLine) {
        if (currentLine.length() > 0) currentLine += " ";
        currentLine += currentWord;
      } else {
        if (currentLine.length() > 0) lines.push_back(currentLine);
        currentLine = currentWord;
      }
    }
    if (currentLine.length() > 0) {
      lines.push_back(currentLine);
    }
  }
};
