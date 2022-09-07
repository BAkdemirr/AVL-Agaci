/**
* @file WorkersTree.h
* @description WorkersTree sınıfının header dosyası. Fonksiyonların açıklamaları burada içinin ayrıntıları cppde
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

using namespace std;

struct Personel 
{
	// personel ismi
	string name;
	// personelin firmadaki calistigi sure
	int time; 
	// derinlik
	int depth; 
	// yükseklik
	int height;
	// Ana dugumun sol cocugu
	Personel* left; 
	// Ana dugumun sag cocugu
	Personel* right; 
};
class WorkersTree
{	
public:
	WorkersTree();
	// ekrana | atmamızı saglayacaklar
	int personelNumber, counter = 0;
	// agac kökü
	Personel* treeRoot = NULL;
	// Agaca dugumm ekleme
	Personel* Add(Personel*,int, vector<string>); 
	// yeni dugum olusturur
	Personel* CreateNode(vector<string>);
	// agacı yok eder
	void Delete(Personel*); 
	
	
	// Ağacı postorder dolaşarak ekrana basar
	void Postorder(Personel*); 
	// ağacın derinliğini döndürür
	int Depth(Personel*); 
	// ağacın yüksekliğini döndürür.
	int Height(Personel*);
	// depthden faydalanarak balance degerini döndürür(derinlik farkını döndürür)
	int BalanceWrite(Personel*); 
	
	
	// sola dogru rotasyon
	Personel* RotationLeft(Personel*); 
	// sağa dogru Sola rotasyonun tam tersi işlemler yapılır
	Personel* RotationRight(Personel*); 
	
	
	~WorkersTree();
};

