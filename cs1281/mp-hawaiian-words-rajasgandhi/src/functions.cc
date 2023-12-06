#include "functions.hpp"

#include <iostream>

/**
 * TODO: Implement this function
 * @param word word to change to lowercase
 * @return result of changing every character in word to lowercase
 */
std::string StringToLower(const std::string& word) {
  // std::cout << "Input to StringToLower() : " << word << std::endl;
  std::string answer;
  for (size_t i = 0; i < word.length(); ++i) {
    answer += tolower(word.at(i));
  }
  return answer;
}

/**
 * TODO: Implement this function
 * @param v1 first character in potential vowel group
 * @param v2 second character in potential vowel group
 * @return true if v1 and v2 form a valid vowel group
 */
bool IsVowelGroup(const char& v1, const char& v2) {
  // std::cout << "Input to IsVowelGroup() : \"" << v1 << "\" \"" << v2 << "\""
  //           << std::endl;

  if (v1 == 'a') {
    if (v2 == 'e' || v2 == 'i' || v2 == 'o' || v2 == 'u') {
      return true;
    }
  }

  if (v1 == 'e') {
    if (v2 == 'i' || v2 == 'u') {
      return true;
    }
  }

  if (v1 == 'i') {
    if (v2 == 'u') {
      return true;
    }
  }

  if (v1 == 'o') {
    if (v2 == 'i' || v2 == 'u') {
      return true;
    }
  }

  if (v1 == 'u') {
    if (v2 == 'i') {
      return true;
    }
  }

  return false;
}

/**
 * TODO: Complete this function
 * @param v potential vowel character
 * @return true if v is a vowel
 */
bool IsVowel(const char& v) {
  // std::cout << "Input to IsVowel() : \"" << v << "\"" << std::endl;
  return (v == 'a' || v == 'e' || v == 'i' || v == 'o' || v == 'u');
}

/**
 * TODO: Complete this function
 * @param c potential consonant character
 * @return true if c is a consonant
 */
bool IsConsonant(const char& c) {
  // std::cout << "Input to IsConsonant() : \"" << c << "\"" << std::endl;
  if (c == '\'' || c == ' ') {
    return false;
  }
  return !IsVowel(c) && IsValidCharacter(c);
}

/**
 * TODO: Implement this function
 * @param c character to check validity of
 * @return true if input c is a valid character in the Hawaiian language, false
 * otherwise
 */
bool IsValidCharacter(const char& c) {
  // std::cout << "Input to IsValidCharacter() : \"" << c << "\"" << std::endl;
  return (IsVowel(c) || (c == 'p') || (c == 'k') || (c == 'h') || (c == 'l') ||
          (c == 'm') || (c == 'n') || (c == 'w') || (c == ' ') || (c == '\''));
}

/**
 * TODO: Implement this function
 * @param word word to check validity of
 * @return true if every character in word is a valid character in the Hawaiian
 * language, false otherwise
 */
bool IsValidWord(const std::string& word) {
  // std::cout << "Input to IsValidWord() : " << word << std::endl;
  for (size_t i = 0; i < word.length(); i++) {
    if (!IsValidCharacter(word.at(i))) {
      return false;
    }
  }
  return true;
}

/**
 * TODO: Implement this function
 * @param c consonant to get pronunciation of
 * @param prev character before c, used for determining w translation
 *    set to null character as default if no value is passed in
 * @return pronunciation of the consonant c as a string
 */
char ConsonantPronunciation(const char& c, const char& prev) {
  // std::cout << "Input to ConsonantPronunciation() : \"" << c << "\" \"" <<
  // prev
  //           << "\"" << std::endl;
  if (c == 'p' || c == 'k' || c == 'h' || c == 'l' || c == 'm' || c == 'n') {
    return c;
  }

  if (c == 'w') {
    if (prev == '\0' || prev == ' ' || prev == 'a' || prev == 'u' ||
        prev == 'o') {
      return c;
    }
    if (prev == 'i' || prev == 'e') {
      return 'v';
    }
  }

  return '\0';
}

/**
 * TODO: Implement this function
 * @param v1 first vowel in a vowel grouping
 * @param v2 second vowel in a vowel grouping
 * @return the pronunciation of the vowel grouping made up of v1 and v2
 * as a string
 */
std::string VowelGroupPronunciation(const char& v1, const char& v2) {
  // std::cout << "Input to VowelGroupPronunciation() : \"" << v1 << "\" \"" <<
  // v2
  //           << "\"" << std::endl;
  if (v1 == 'a') {
    if (v2 == 'i' || v2 == 'e') {
      return "eye";
    }
    if (v2 == 'o' || v2 == 'u') {
      return "ow";
    }
  } else if (v1 == 'e') {
    if (v2 == 'i') {
      return "ay";
    }
    if (v2 == 'u') {
      return "eh-oo";
    }
  } else if (v1 == 'i') {
    if (v2 == 'u') {
      return "ew";
    }
  } else if (v1 == 'o') {
    if (v2 == 'i') {
      return "oy";
    }
    if (v2 == 'u') {
      return "ow";
    }
  } else if (v1 == 'u') {
    if (v2 == 'i') {
      return "ooey";
    }
  }
  return "";
}

/**
 * TODO: Implement this function
 * @param v single vowel to get pronunciation of
 * @return the pronunciation of v as a string
 */
std::string SingleVowelPronunciation(const char& v) {
  // std::cout << "Input to SingleVowelPronunciation() : \"" << v << "\""
  //           << std::endl;
  if (v == 'a') {
    return "ah";
  }
  if (v == 'e') {
    return "eh";
  }
  if (v == 'i') {
    return "ee";
  }
  if (v == 'o') {
    return "oh";
  }
  if (v == 'u') {
    return "oo";
  }
  return "";
}

/**
 * TODO: Implement this function
 * @param prev first character in set of three passed to function
 * @param curr second character in set of three passed to function
 * @param next third character in set of three passed to function
 * @return pronunciation of curr using next and prev as needed to determine
 * result
 */
std::string ProcessCharacter(const char& prev,
                             const char& curr,
                             const char& next) {
  // std::cout << "Input to ProcessCharacter() : \"" << prev << "\" \"" << curr
  //           << "\" \"" << next << "\"" << std::endl;
  std::string processed;
  if (curr == '\'') {
    return "'";
  }
  if (curr == ' ') {
    return " ";
  }
  if (IsVowelGroup(curr, next)) {
    // std::cout << "vowelgroup " << curr << " " << next << std::endl;
    processed += VowelGroupPronunciation(curr, next);
  } else if (IsVowel(curr)) {
    // std::cout << "vowel " << curr << " " << next << std::endl;
    processed += SingleVowelPronunciation(curr);
  } else if (IsConsonant(curr)) {
    // std::cout << "consonant " << curr << " " << next << std::endl;
    processed += ConsonantPronunciation(curr, prev);
  }
  return processed;
}

/**
 * TODO: Implement this function
 * @param word string to get pronunciation of
 * @return pronunciation of word
 */
std::string Pronunciation(const std::string& word) {
  // std::cout << "Input to Pronunciation() : " << word << std::endl;
  std::string pronounciation;

  for (size_t i = 0; i < word.length(); i++) {
    char prev = ' ';
    if (i != 0) {
      prev = word.at(i - 1);
    }
    char curr = word.at(i);
    char next = ' ';
    if (i != word.length() - 1) {
      next = word.at(i + 1);
    }

    if (i == 0) {
      pronounciation += ProcessCharacter(' ', curr, next);
      if ((IsVowelGroup(curr, next) || IsVowel(curr)) && next != '\'' &&
          next != ' ') {
        pronounciation += "-";
      }
    } else if (i == word.length() - 1) {
      pronounciation += ProcessCharacter(prev, curr, ' ');
    } else {
      pronounciation += ProcessCharacter(prev, curr, next);
      if ((IsVowelGroup(curr, next) || IsVowel(curr)) && next != '\'' &&
          next != ' ') {
        pronounciation += "-";
      }
    }
    if (IsVowelGroup(curr, next)) {
      i++;
    }
  }

  if (pronounciation.back() == '-') {
    pronounciation = pronounciation.substr(0, pronounciation.length() - 1);
  }

  return pronounciation;
}

/**
 * TODO: Implement this function
 * @param hawaiian_word word to get pronunciation of
 * @return the pronunciation of hawaiian_word as a string if valid
 *  and throws an invalid_argument error if not valid
 */
std::string GetPronunciation(const std::string& hawaiian_word) {
  // std::cout << "Input to GetPronunciation() : " << hawaiian_word <<
  // std::endl;
  std::string lowered = StringToLower(hawaiian_word);

  if (IsValidWord(lowered)) {
    return Pronunciation(lowered);
  }
  throw std::invalid_argument("Invalid input!");
  return "";
}