/**
* @file WorkersTree.cpp
* @description İç ağacı yani worker agacını oluşturur yazar ve siler. Fonksiyon açıklamaları hppde.
* @course 2. Öğretim B grubu
* @assignment Odev-2
* @date 25.12.2020
* @author BERKECAN AKDEMİR
*/

#include "WorkersTree.h"

WorkersTree::WorkersTree()
{
}

Personel* WorkersTree::Add(Personel* treeRoot,int workTime, vector<string> dismember) 
{
	// Dugum yoksa oluştur
	if (treeRoot == NULL)
		return treeRoot = CreateNode(dismember);

	/**** Agacın verisinden büyük ise sağına ekle ****/ 
	if (treeRoot->time < workTime)
		treeRoot->right = Add(treeRoot->right, workTime, dismember);

	/**** Ağacın verisinde küçük ise soluna ekle ****/
	else if (treeRoot->time >= workTime)
		treeRoot->left = Add(treeRoot->left, workTime, dismember);
	else return treeRoot;

	//üst düğümün yüksekliğini güncelliyorum
	treeRoot->depth = max(Depth(treeRoot->left),Depth(treeRoot->right)) + 1;

	// derinlik farkını getir
	int balance = BalanceWrite(treeRoot);        

	/****** Balance değerine göre(derinlik farkına göre) gerekli rotasyonlar aşağıdaki gibi olur ******/

	// Left-Left  
	if (balance > 1 && workTime < treeRoot->left->time)
		return RotationRight(treeRoot);

	// Right-Right  
	if (balance < -1 && workTime > treeRoot->right->time)
		return RotationLeft(treeRoot);
	// Left-Right
	if (balance > 1 && workTime > treeRoot->left->time) {
		treeRoot->left = RotationLeft(treeRoot->left);
		return RotationRight(treeRoot);
	}
	// Right-Left
	if (balance < -1 && workTime < treeRoot->right->time) {
		treeRoot->right = RotationRight(treeRoot->right);
		return RotationLeft(treeRoot);
	}
	
	return treeRoot;
}
Personel* WorkersTree::CreateNode(vector<string> datas) 
{
	Personel* tree = new Personel();
	tree = new Personel();
	tree->right = NULL;
	tree->left = NULL;
	tree->time = 2020-stoi(datas[2]);
	tree->name = datas[1];
	return tree;
}
void WorkersTree::Delete(Personel* root) 
{
	if (root == NULL)
		return;
	Delete(root->left);
	Delete(root->right);
	delete root;
}

void WorkersTree::Postorder(Personel* rd) 
{
	if (rd == NULL)
		return;
	Postorder(rd->left);
	Postorder(rd->right);
	cout << rd->name + "-" + to_string(2020 - rd->time);
	counter++;
	if (counter < personelNumber)
		cout << " | ";
}

int WorkersTree::Depth(Personel *a)
{
	if (a == NULL)
		return(-1);
	else 
	{
		int LDepth = Depth(a->left);
		int RDepth = Depth(a->right);

		// hangi derinlik daha büyükse ağacın derinliği odur.
		if (LDepth > RDepth) return(LDepth + 1);
		else return(RDepth + 1);	
	}
}

int WorkersTree::Height(Personel* t) {
   int h = 0;
   if (t != NULL) {
      int left_height = Height(t->left);
      int right_height = Height(t->right);
      int max_height = max(left_height, right_height);
      h = max_height + 1;
   }
   return h;
}


int WorkersTree::BalanceWrite(Personel *A)
{
	if (A == NULL) return 0;
	
	return Depth(A->left) - Depth(A->right);
		
}

Personel* WorkersTree::RotationLeft(Personel* x) 
{
	Personel *y = x->right; 
	Personel *T2 = y->left;

	/**** Rotasyonun uygulanması ****/
	// sola rotasyon olurken kökün sağı kök yerine geçer eski kök ise yeninin soluna geçer 
	// T2 istisna durumudur kural gereği eski kökün sağına ekliyoruz.
	// Sağa rotasyonda ise buranın tam tersi işlemleri yapılıyor
	y->left = x; 
	x->right = T2; 

	// Yüksekliğin güncellenmesi
	x->depth = max(Depth(x->left), Depth(x->right)) + 1;
	y->depth = max(Depth(y->left), Depth(y->right)) + 1;

	return y;
}

Personel* WorkersTree::RotationRight(Personel* y) 
{
	// Sola rotasyonun tam tersi işlemler
	Personel *x = y->left;
	Personel *T2 = x->right;
	
	x->right = y;
	y->left = T2;

	y->depth = max(Depth(y->left), Depth(y->right)) + 1;
	x->depth = max(Depth(x->left), Depth(x->right)) + 1;

	return x;
}


WorkersTree::~WorkersTree()
{
	Delete(treeRoot);
}
