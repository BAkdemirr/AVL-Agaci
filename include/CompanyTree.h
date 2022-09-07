/**
* @file CompanyTree.h
* @description CompanyTree sınıfının header dosyası. Fonksiyonların açıklamaları burada içinin ayrıntıları cppde
* @course 2. Öğretim B grubu
* @assignment Odev-2
* @date 25.12.2020
* @author BERKECAN AKDEMİR
*/

#include<iostream>
#include<fstream>
#include<string>
#include<vector>
#include<Math.h>
#include<algorithm> 
#include"WorkersTree.h"

using namespace std;


struct Company 
{
	// iç ağaç
	WorkersTree workersTree;
	// firma adı
	string companyName;
	// personel sayısı
	int personels;
	// derinlik
	int depth; 
	// yükseklik
	int height;
	// ana düğümün sol cocuğu
	Company* left; 
	// ana düğümün sağ cocuğu
	Company* right;
};

class CompanyTree
{
private:
	// kök
	Company* treeRoot;
	// ayrıştırma
	vector<string> parsing;
public:

	CompanyTree();
	
	// Ağaca düğüm ekleme
	Company* Add(Company *,int,vector<string>); 
	// yeni düğüm oluştur
	Company* CreateNode(vector<string>);
	// agacı yok eder
	void Delete(Company*); 
	
	
	// Sola dogru rotasyon
	Company* RotationLeft(Company*);
	// Saga dogru rotasyon
	Company* RotationRight(Company*); 


	// dosya okuyucu
	void ReadFile(Company*&); 
	// Gelen stringi ikinci paramteredeki stringe göre parçalar ve vector olarak döndürür
	void StringSplit(string);
	// parent ın parent ını tutuyor
	Company* CompanyParent(Company*, string);
	// Calışan sayısının değişiklik gösteren firmanın düğümünü güncellemeye yarıyor.
	Company* CompanyUpdate(Company*,string, Company*);
	// okunan ve ayrıştırılan satırı ekle düğümü günceller.
	Company* LineProcess();
	// firma arama
	Company* CompanySearch(Company*,string);
	
	
	// ağacın derinliğini döndürür
	int Depth(Company*); 
	// ağacın yüksekliğini döndürür
	int Height(Company*);
	// depthden faydalanarak balance degerini döndürür(derinlik farkını döndürür)
	int BalanceWrite(Company*);
	// Ağacı postorder dolaşarak dugum arar ekrana yazar.
	void Postorder(Company*);
	
	
	~CompanyTree();
};

