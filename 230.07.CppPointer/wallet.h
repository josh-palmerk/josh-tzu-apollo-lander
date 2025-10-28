/*************************************************************
 * 1. Name:
 *      Josh Palmer & Tzu
 * 2. Module
 *      WALLET
 * 3. Assignment Description:
 *      A class to represent an wallet with multiple credit cards
 **************************************************************/

#pragma once

#include <cassert>

class TestWallet;

 /************************************
  * WALLET
  ************************************/
class Wallet
{
   friend TestWallet;
public:
	Wallet();
	void updateSam(double amount);
	void updateSue(double amount);
	void updateCurrent(double amount);
	void chooseSam();
	void chooseSue();
	void chooseCurrent();
	double getSam();
	double getSue();
	double getCurrent();

private:
	double accountSam;
	double accountSue;
	double* pCurrentAccount;
};

