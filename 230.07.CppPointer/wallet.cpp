
/***********************************************************************
 * Source:
 *    Angle
 * Summary:
 *    Just call the Wallet unit tests
 * Author:
 *    James Helfrich
 ************************************************************************/

 #include <iostream>
 #include "testWallet.h"
 #include "wallet.h"
 using namespace std;
 

 // Constructor
 Wallet::Wallet()
 {
     accountSam = 0.0;
     accountSue = 0.0;
     pCurrentAccount = &accountSam;
 }

 // Update functions
 void Wallet::updateSam(double amount)
 {
     accountSam += amount;
 }

 void Wallet::updateSue(double amount)
 {
     accountSue += amount;
 }

 void Wallet::updateCurrent(double amount)
 {
     *pCurrentAccount += amount;
 }

 // Account selection functions
 void Wallet::chooseSam()
 {
     pCurrentAccount = &accountSam;
 }

 void Wallet::chooseSue()
 {
     pCurrentAccount = &accountSue;
 }

 void Wallet::chooseCurrent()
 {
     pCurrentAccount = (accountSam > accountSue) ? &accountSam : &accountSue;
 }

 // Getter functions
 double Wallet::getSam()
 {
     return accountSam;
 }

 double Wallet::getSue()
 {
     return accountSue;
 }

 double Wallet::getCurrent()
 {
     return *pCurrentAccount;
 }

/************************************
 * MAIN
 * Simple driver
 ***********************************/
int main()
{
   TestWallet().run();

   return 0;
}
