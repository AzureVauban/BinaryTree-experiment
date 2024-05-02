#include "LinkedList.h"
#include <cassert>
#include <cstddef>
#include <cstdlib>
#include <random>
#include <vector>

const int TESTCASES = 1000;

// The 'randomBetween' function generates a random integer between two given
// integers 'a' and 'b'. It uses the Mersenne Twister algorithm for random
// number generation.
int randomBetween(int a, int b) {
  std::random_device rd;  // obtain a random number from hardware
  std::mt19937 gen(rd()); // seed the generator
  std::uniform_int_distribution<> distr(a, b); // define the range

  return distr(gen); // generate numbers
}

// The 'PRINTDEBUGLIST' function prints the size, maximum index, and elements of
// a given linked list 'List'. It is used for debugging purposes.
template <typename T> void PRINTDEBUGLIST(LINKEDLIST::Linked_List<T> &List) {
  std::cout << "SIZE: " << List.size() << std::endl;
  std::cout << "MAX INDEX: " << List.size() - 1 << std::endl;

  List.print_list(true);
  std::cout << std::endl;
}

// The 'CreateList' function generates a linked list of unique random integers.
// The size of the list is determined by the 'capacity' parameter.
LINKEDLIST::Linked_List<int> CreateList(const size_t capacity = 100) {
  std::vector<int> values;
  LINKEDLIST::Linked_List<int> intArray;
  for (int i = 0; i < capacity; i++) {
    int chosen_value = randomBetween(0, 100);
    bool isduplicate = false;
    for (int j = 0; j < values.size(); j++) {
      if (values.at(j) == chosen_value) {
        isduplicate = true;
        break;
      }
      if (!isduplicate) {
        values.emplace_back(chosen_value);
        intArray.insert(chosen_value);
      }
    }
  }
  return intArray;
}
// This 'test_peek' function tests the 'peek' operation of a linked list by
// comparing the first element of the list with an expected value. It returns
// 'true' if the test passes and 'false' otherwise.
template <typename T> bool test_peek(LINKEDLIST::Linked_List<T> &List) {
  std::vector<T> expectedList;
  for (int i = 0; i < List.size(); i++) {
    expectedList.emplace_back(List[i]);
  }
  return List[0] == expectedList[0];
}

// This 'test_infunction' function tests the insertion and duplicate value
// checking operations of a linked list.It returns 'true' if a duplicate value
// is found and 'false' otherwise.
template <typename T> bool test_infunction(LINKEDLIST::Linked_List<T> &List) {
  const size_t ListSize = List.size();

  int targetvalue = List[randomBetween(0, ListSize - 1)];
  std::cout << "CHECKING TO SEE IF [" << targetvalue << "] IS A PRESENT VALUE"
            << std::endl;
  return List.in(targetvalue);
}

// The 'test_swap' function tests the 'swap' operation of a linked
// list.It swaps two randomly chosen indices and verifies if the swap was
// successful.The function returns 'true' if the test passes and
// 'false' otherwise.
template <typename T> bool test_swap(LINKEDLIST::Linked_List<T> &List) {

  if (List.size() == 1) {
    std::cout << "SKIPPING TEST BECAUSE LIST ONLY HAS 1 VALUE" << std::endl;
    return true;
  }
  std::vector<T> expectedList;
  const size_t ListSize = List.size();
  for (int i = 0; i < ListSize; i++) {
    expectedList.emplace_back(List[i]);
  }
  // random choosen two swap indicies
  int left = randomBetween(0, (ListSize / 2) - 1);
  int right = randomBetween(left, ListSize - 1);
  std::cout << "SWAPPING INDEX " << left << ":" << right << std::endl;
  List.print_list(true);
  List.swap(left, right);
  List.print_list(true);
  return List[left] == expectedList[right] && List[right] == expectedList[left];
}

// The test_remove function is a template function that removes a randomly
// chosen element from a given linked list. It then checks and returns whether
// the value at the chosen index has changed, indicating successful removal.
template <typename T> bool test_remove(LINKEDLIST::Linked_List<T> &List) {
  if (List.size() == 1) {
    List.remove();
    return List.isempty();
  }
  size_t chosen_index = randomBetween(0, List.size() - 1),
         preremovalsize = List.size();
  T chosen_value = List[chosen_index];
  std::cout << "REMOVING " << chosen_value << " AT " << chosen_index
            << std::endl;
  List.remove(chosen_index);
  List.print_list(true);
  // check if the value at the chosen index is the same as the chosen value
  int index_to_check = chosen_index - 1;
  if (index_to_check < 0) {
    index_to_check = 0;
  }
  return List[index_to_check] != chosen_value &&
         preremovalsize == List.size() + 1;
}

// This function is intended to test the equality operator for a linked list.
// Currently, it is not implemented.
template <typename T>
bool test_operatorEQUAL(const LINKEDLIST::Linked_List<T> &List) {
  std::cout << "TEST NOT IMPLEMENTED, SKIPPING" << std::endl;
  return true;
}

// This function is intended to test the addition operator for a linked list.
// Currently, it is not implemented.
template <typename T>
bool test_operatorADDITION(const LINKEDLIST::Linked_List<T> &List) {
  std::cout << "TEST NOT IMPLEMENTED, SKIPPING" << std::endl;
  return true;
}

// This function is intended to test the combined equality and addition
// operators for a linked list. Currently, it is not implemented.
template <typename T>
bool test_operatorEQUALADDITION(const LINKEDLIST::Linked_List<T> &List) {
  std::cout << "TEST NOT IMPLEMENTED, SKIPPING" << std::endl;
  return true;
}

// This function is intended to test the subtraction operator for a linked list.
// Currently, it is not implemented.
template <typename T>
bool test_operatorSUBTRACTION(const LINKEDLIST::Linked_List<T> &List) {
  std::cout << "TEST NOT IMPLEMENTED, SKIPPING" << std::endl;
  return true;
}

// This function is intended to test the combined equality and subtraction
// operators for a linked list. Currently, it is not implemented.
template <typename T>
bool test_operatorEQUALSUBTRACTION(const LINKEDLIST::Linked_List<T> &List) {
  std::cout << "TEST NOT IMPLEMENTED, SKIPPING" << std::endl;
  return true;
}

int main() {
  for (size_t t = 0; t <= TESTCASES; t++) {
    std::cout << "TESTCASE: " << t << std::endl;
    for (int i = 0; i != 80; i++) {
      std::cout << '=';
    }
    LINKEDLIST::Linked_List<int> List;
    const int TESTSIZE = randomBetween(1, 100);
    // List = CreateList(TESTSIZE);
    for (int j = 0; j < TESTSIZE; j++) {
      int chosen_value = randomBetween(0, 100);
      if (!List.in(chosen_value)) {
        List.insert(chosen_value);
      }
    }
    std::cout << std::endl;
    PRINTDEBUGLIST(List);
    assert(test_peek(List));
    assert(test_infunction(List));
    std::cout << std::endl;
    assert(test_swap(List));
    assert(test_remove(List));
    assert(test_operatorEQUAL(List));
    assert(test_operatorADDITION(List));
    assert(test_operatorEQUALADDITION(List));
    assert(test_operatorSUBTRACTION(List));
    assert(test_operatorEQUALSUBTRACTION(List));
  }
  std::cout << "TERMINATING PROCESS" << std::endl;
  return 0;
}
