#include <assert.h>

#include <cstdlib>
#include <iostream>

#include "il.hpp"

class Tester {
 public:
  // testing for default constructor is done for you
  void testDefCtor() {
    IntList il;
    assert(il.head == NULL);
    assert(il.tail == NULL);
    assert(il.getSize() == 0);
  }
  // example of another method you might want to write
  void testAddFront() {
    // WRITE ME
    IntList il;
    il.addFront(1);  // il: 1
    assert(il.head != NULL);
    assert(il.tail == il.head);
    assert(il.head->next == NULL);
    assert(il.head->prev == NULL);
    assert(il.getSize() == 1);
    assert(il[0] == 1);

    il.addFront(2);  // il: 21
    assert(il.head == il.head->next->prev);
    assert(il.tail == il.head->next);
    assert(il.head->next->next == NULL);
    assert(il.head->prev == NULL);
    assert(il.getSize() == 2);
    assert(il[0] == 2);
    assert(il[1] == 1);
  }
  // many more tester methods
  void testAddBack() {
    IntList il;
    il.addBack(1);  // il: 1
    assert(il.head != NULL);
    assert(il.tail == il.head);
    assert(il.head->next == NULL);
    assert(il.head->prev == NULL);
    assert(il.getSize() == 1);
    assert(il[0] == 1);

    il.addBack(2);  // il: 12
    assert(il.head == il.head->next->prev);
    assert(il.tail == il.head->next);
    assert(il.head->next->next == NULL);
    assert(il.head->prev == NULL);
    assert(il.getSize() == 2);
    assert(il[0] == 1);
    assert(il[1] == 2);
  }

  void testAssign() {
    IntList l1;  //l1:21
    l1.addBack(1);
    l1.addFront(2);
    IntList l2;  //l2:21
    l2 = l1;
    assert(l2.getSize() == 2);
    assert(l2[0] == 2);
    assert(l2[1] == 1);
    assert(l2.head->next->next == NULL);
    assert(l2.head == l2.head->next->prev);
    assert(l2.tail == l2.head->next);
    assert(l2.head->next->next == NULL);
    assert(l2.head->prev == NULL);
    assert(l1.head != l2.head);
  }
  void testAssign2() {
    IntList l1;  //l1:21
    l1.addBack(1);
    l1.addFront(2);
    IntList l2;  //l2:34
    l2.addBack(3);
    l2.addBack(4);
    l2 = l1;  //l2: 21
  }

  void testCopy() {
    IntList l1;  //l1:21
    l1.addBack(1);
    l1.addFront(2);
    IntList l2(l1);  //l2:21
    assert(l2.getSize() == 2);
    assert(l2[0] == 2);
    assert(l2[1] == 1);
    assert(l2.head->next->next == NULL);
    assert(l2.head == l2.head->next->prev);
    assert(l2.tail == l2.head->next);
    assert(l2.head->next->next == NULL);
    assert(l2.head->prev == NULL);
    assert(l1.head != l2.head);
  }
  void testRemove() {
    IntList l1;  // l1: 224321
    l1.addFront(1);
    l1.addFront(2);
    l1.addFront(3);
    l1.addFront(4);
    l1.addFront(2);
    l1.addFront(2);

    IntList l2;  //l2: 21
    l2.addFront(1);
    l2.addFront(2);

    IntList l3;  //l3: 21
    l3.addFront(1);
    l3.addFront(2);

    IntList l4;  //l4: 1357
    l4.addBack(1);
    l4.addBack(3);
    l4.addBack(5);
    l4.addBack(7);

    IntList l5;  //l5: 137
    l5.addBack(1);
    l5.addBack(3);
    l5.addBack(7);

    //test l1
    assert(l1.getSize() == 6);

    assert(l1.remove(2) == true);  //l1:24321
    assert(l1.getSize() == 5);

    assert(l1[0] == 2 && l1[3] == 2);
    assert(l1.head->data == 2);
    assert(l1.head->next->data == 4);

    assert(l1.remove(10) == false);
    l1.remove(2);  //l1:4321
    assert(l1.head->data == 4);
    l1.remove(2);  //l1: 431
    assert(l1.head->next->next->data == 1);
    assert(l1.tail->data == 1);
    l1.remove(1);  //l1 : 43
    assert(l1.tail->data == 3);

    //test l2
    l2.remove(2);
    l2.remove(1);  //l2: empty
    assert(l2.getSize() == 0 && l2.head == NULL && l2.tail == NULL);

    //test l3
    l3.remove(2);  //l3: 1
    assert(l3.getSize() == 1 && l3.head == l3.tail && l3.head != NULL);
    assert(l3[0] == 1);
    assert(l3.head->next == NULL && l3.head->prev == NULL);
  }
};

int main(void) {
  Tester t;
  t.testDefCtor();
  t.testAddFront();
  // write calls to your other test methods here
  t.testAddBack();
  t.testAssign();
  t.testAssign2();
  t.testCopy();
  t.testRemove();

  return EXIT_SUCCESS;
}