/*******************************
 * Andrew Dillon
 * 2382400
 * CPSC 350
 * Assignment Extra Credit
 *******************************/

#include "RBDatabase.h"


 RBDatabase :: RBDatabase()
 {

 }
 RBDatabase :: ~RBDatabase()
 {

 }

 void RBDatabase :: RunDatabase()
 {
   const int NUM_MENU_OPTIONS = 7;
   const string MENU_TEXT = "RED - BLACK TREE\n"
                            " 1 - Insert a value:\n"
                            " 2 - Remove a value:\n"
                            " 3 - Search for a value:\n"
                            " 4 - Print the Tree:\n"
                            " 5 - Find Maximum Value:\n"
                            " 6 - Find Minimum Value:\n"
                            " 7 - Exit Program:\n"
                            "Choice: ";

   int menuChoice;


   do
   {
     menuChoice = GetMenuInput(MENU_TEXT, NUM_MENU_OPTIONS);

     cout << endl << endl;

     switch(menuChoice)
     {
       case 1:
         AddToTree();
         break;
       case 2:
         RemoveFromTree();
         break;
       case 3:
         SearchTree();
         break;
       case 4:
         PrintTree();
         break;
       case 5:
         FindMaxVal();
         break;
       case 6:
         FindMinVal();
         break;
       default:
         break;
     }

      cout << endl << endl;
   } while(menuChoice != NUM_MENU_OPTIONS);

   cout << "Thank you for using my Red - Black Tree";
 }

 int RBDatabase :: GetMenuInput(const string initialMessage, const int numMenuOptions)
 {
   bool valid = false;
   int menuChoice = 0;

   do
   {
     cout << initialMessage;
     cin >> menuChoice;
     if(cin.fail())
     {
       cin.clear();
       cin.ignore(100000000, '\n');
       cout << "\nSorry, please enter numeric input.\n\n";

       valid = false;
     }
     else if(menuChoice > 0 && menuChoice <= numMenuOptions)
     {
       valid = true;
     }
     else
     {
       cout << "\nSorry, please enter a value between 1 and " << numMenuOptions << endl << endl;
       valid = false;
     }

   } while(!valid);
 }

 int RBDatabase :: GetValueFromUser(const string initialMessage)
 {
   bool valid = false;
   int value = 0;

   do
   {
     cout << initialMessage;
     cin >> value;
     if(cin.fail())
     {
       cin.clear();
       cin.ignore(100000000, '\n');
       cout << "\nSorry, please enter numeric input.\n\n";

       valid = false;
     }
     else
     {
       valid = true;
     }

   } while(!valid);

   return value;
 }


 void RBDatabase :: AddToTree()
 {
   int addValue = GetValueFromUser("Please enter the value you would like to add to the tree: ");

   tree.Insert(addValue);

 }
 void RBDatabase :: RemoveFromTree()
 {
   int removeValue = GetValueFromUser("Please enter the value you would like to remove from the tree: ");

   tree.Delete(removeValue);
 }
 void RBDatabase :: SearchTree()
 {
   int searchValue = GetValueFromUser("Please enter the value you would like search for in the tree: ");

   if(tree.SearchNode(searchValue) != nullptr)
   {
     cout << searchValue << " was found in the tree\n\n";
   }
   else
   {
     cout << "Sorry, "<< searchValue << " was not found in the tree\n\n";
   }

 }
 void RBDatabase :: PrintTree()
 {
   const string PRINT_MENU = "How would you like the tree to be printed?\n"
                               " - 1 Preorder:\n"
                               " - 2 Inorder:\n"
                               " - 3 Postorder:\n"
                               " - 4 Print All Traversals:\n"
                               " - 5 Return to Main Menu:\n"
                               "Choice: ";
   const int numMenuOptions = 5;
    int treePrint;


   do
   {

     treePrint = GetValueFromUser(PRINT_MENU);

   } while(treePrint > 0 && treePrint >= numMenuOptions);

   cout << endl << endl;

   if(treePrint == 1)
   {
     tree.PreOrder();
   }
   else if(treePrint == 2)
   {
     tree.InOrder();
   }
   else if(treePrint == 3)
   {
     tree.PostOrder();
   }
   else if(treePrint == 4)
   {
     tree.PrintAllTraversals();
   }
 }
 void RBDatabase :: FindMaxVal()
 {
   cout << "Maximum value is: ";

   try
   {
     cout << tree.GetMax();
   }
   catch(const char* ex)
   {
     cout << ex;
   }

   cout << endl << endl;
 }
 void RBDatabase :: FindMinVal()
 {
   cout << "Minimum value is: ";

   try
   {
     cout << tree.GetMin();
   }
   catch(const char* ex)
   {
     cout << ex;
   }

   cout << endl << endl;
 }
