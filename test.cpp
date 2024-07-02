#include <vector>
#include <iostream>
#include <string>
#include <algorithm>
#include <sstream>  // Include for std::stringstream

int main() {
  std::vector<std::string> words; // Vector to store words

  // Split the sentence into words and store them in the vector
  std::string sentence = "NICK nano USER zafd fdfs dsfds fdsds";
  std::string word;
  std::stringstream ss(sentence);  // Use stringstream

  while (ss >> word) {
    words.push_back(word);
  }

  // Find the iterator pointing to "USER"
  std::vector<std::string>::iterator it = std::find(words.begin(), words.end(), "USER");

  // Remove elements before "USER" if it exists
  if (it != words.end()) {
    words.erase(words.begin(), it);
  }

  // Print the remaining words (using traditional for loop)
  for (int i = 0; i < words.size(); ++i) {
    const std::string& word = words[i];
    std::cout << word << " ";
  }
  std::cout << std::endl;

  return 0;
}
