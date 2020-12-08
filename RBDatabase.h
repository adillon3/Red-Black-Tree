/*******************************
 * Andrew Dillon
 * 2382400
 * CPSC 350
 * Assignment Extra Credit
 *******************************/

#ifndef EXTRACREDIT_H_
#define EXTRACREDIT_H_

#include <iostream>
using namespace std;

#include <string>
#include <fstream>

#include "RBtree.h"


class RBDatabase
{
public:
  RBDatabase();
  ~RBDatabase();

  void RunDatabase();
  int GetMenuInput(const string initialMessage, const int numMenuOptions);
  int GetValueFromUser(const string initialMessage);

  void AddToTree();
  void RemoveFromTree();
  void SearchTree();
  void PrintTree();
  void FindMaxVal();
  void FindMinVal();
private:
  RBtree<int> tree;

};





#endif /* EXTRACREDIT_H_ */
