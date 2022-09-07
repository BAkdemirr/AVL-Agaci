/**
* @file Main.cpp
* @description CompanyTree(dıştaki ağaç) class ını kullanarak işlemleri başlatır.
* @course 2. Öğretim B grubu
* @assignment Odev-2
* @date 25.12.2020
* @author BERKECAN AKDEMİR
*/

#include <iostream>
#include"CompanyTree.h"

using namespace std;

int main() {
	Company* root = NULL;
	CompanyTree companyTree;
	companyTree.ReadFile(root);
	companyTree.Postorder(root);
	system("pause");
}