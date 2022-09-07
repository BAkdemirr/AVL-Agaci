/**
* @file CompanyTree.cpp
* @description Dış ağacı yani company ağacını oluşturur. Düğümleri günceller.Ekrana yazar ve siler.
* @course 2. Öğretim B grubu
* @assignment Odev-2
* @date 25.12.2020
* @author BERKECAN AKDEMİR
*/

#include "CompanyTree.h"

CompanyTree::CompanyTree()
{
}


Company* CompanyTree::Add(Company* tree, int workerCount,vector<string> dismember) 
{
	// Düğüm yoksa oluştur
	if (tree == NULL)
		return tree = CreateNode(dismember);
	
	/**** Agacın verisinden büyük ise sağına ekle ****/ 
	if (tree->personels < workerCount)
		tree->right = Add(tree->right, workerCount, dismember);

	/**** Ağacın verisinde küçük ise soluna ekle ****/
	else if (tree->personels >= workerCount)
		tree->left = Add(tree->left, workerCount, dismember);
	else return tree;

	//üst düğümün yüksekliğini güncelliyorum
	tree->depth = max(Depth(tree->left), Depth(tree->right)) + 1;

	// derinlik farkını getir
	int balance = BalanceWrite(tree);

	/****** Balance değerine göre(derinlik farkına göre) gerekli rotasyonlar aşağıdaki gibi olur ******/

	// Left-Left 
	if (balance > 1 && workerCount < tree->left->personels)
		return RotationRight(tree);

	// Right-Right
	if (balance < -1 && workerCount > tree->right->personels)
		return RotationLeft(tree);
	// Left-Right 
	if (balance > 1 && workerCount > tree->left->personels) {
		tree->left = RotationLeft(tree->left);
		return RotationRight(tree);
	}
	// Right-Left
	if (balance < -1 && workerCount < tree->right->personels) {
		tree->right = RotationRight(tree->right);
		return RotationLeft(tree);
	}
	return tree;
}

Company* CompanyTree::CreateNode(vector<string> datas) 
{
	Company* tree = new Company();
	tree->right = NULL;
	tree->left = NULL;
	tree->personels = 1;
	tree->workersTree.personelNumber = 1;
	tree->companyName = datas[0];
	int time = 2020 - stoi(datas[2]);
	tree->workersTree.treeRoot = tree->workersTree.Add(tree->workersTree.treeRoot, time, datas);
	return tree;
}

void CompanyTree::Delete(Company* root) 
{
	if (root == NULL)
		return;
	Delete(root->left);
	Delete(root->right);
	delete root;
}


Company* CompanyTree::RotationLeft(Company* x) 
{
	Company *y = x->right; // gerekli değişkenleri alıyoruz
	Company *T2 = y->left;

	/**** Rotasyonun uygulanması ****/
	// sola rotasyon olurken kökün sağı kök yerine geçer eski kök ise yeninin soluna geçer 
	// T2 istisna durumudur kural gereği eski kökün sağına ekliyoruz.
	// Sağa rotasyonda ise buranın tam tersi işlemleri yapılıyor
	y->left = x; 
	x->right = T2;

	// Yüksekliğin güncellenmesi
	x->depth = max(Depth(x->left), Depth(x->right)) + 1;
	y->depth = max(Depth(y->left), Depth(y->right)) + 1;
	
	// yeni dugumu dondur
	return y;
}


Company* CompanyTree::RotationRight(Company* y) 
{
	// Sola rotasyonun tam tersi işlemler
	Company *x = y->left;
	Company *T2 = x->right;

	x->right = y;
	y->left = T2;

	
	y->depth = max(Depth(y->left), Depth(y->right)) + 1;
	x->depth = max(Depth(x->left), Depth(x->right)) + 1;

	return x;
}

void CompanyTree::ReadFile(Company*& root) 
{
	treeRoot = root;
	ifstream dosyaOku("./doc/Veri.txt");
	string satir = "";
	if (dosyaOku.is_open()) 
	{

		while (getline(dosyaOku, satir)) 
		{
			if (satir != "" && satir != "\n")// boş satırlarda hata vermemesi için
				StringSplit(satir);
			root = LineProcess();
			parsing.clear();
		}
		dosyaOku.close();
	}
	else
		cout << "Dosya acilamadi\n";
}

void CompanyTree::StringSplit(string line) 
{
	std::string delimiter = "#";

	size_t pos = 0;
	std::string token;
	while ((pos = line.find(delimiter)) != std::string::npos) 
	{
		token = line.substr(0, pos);
		line.erase(0, pos + delimiter.length());

		parsing.push_back(token);
	}
	parsing.push_back(line);
}


// iki farklı global değişken kullanıyoruz nedeni biri düğümün parent ını diğeri o parent ın parent ını tutuyor.
// globalde tanımlanmasının nedeni değişkenin değeri sabit kalmıyor.
Company* company = NULL;
Company* parent_parent = NULL;
Company* CompanyTree::CompanyParent(Company* root, string name) 
{
	if (root == NULL)
		return NULL;
	if (root == treeRoot && root->companyName == name)
		parent_parent = root;
	CompanyParent(root->left, name);
	if (root->right != NULL && root->right->companyName == name)
		parent_parent = root;
	else if (root->left != NULL && root->left->companyName == name)
		parent_parent = root;
	CompanyParent(root->right, name);
	return NULL;
}

// Güncelleme gereken düğümünn parent düğümünü alıp öyle işlemleri yapıyoruz
Company* CompanyTree::CompanyUpdate(Company* updateParent,string location, Company* parent_parent) 
{
	
	// Eğer kök düğümse sağdaki düğümü kontrol et
	if (updateParent == treeRoot && location=="root" && updateParent->right!=NULL) 
	{
		// çelişki varsa yer değişme uygula.
		if (updateParent->personels > updateParent->right->personels) 
		{
			// klasik yer değiştirme işlemleri sağı solu yedekleyip işlemi öyle yapıyoruz
			Company* temp = updateParent->right;
			Company* tempRight = temp->right;	
			Company* tempLeft = temp->left;
			
			Company* updateLeft = updateParent->left; 
			
			temp->left = updateLeft;
			temp->right = updateParent; 
			treeRoot = temp; 
			
			updateParent->right = tempRight;
			updateParent->left = tempLeft;
			//yeniden güncelleme gerekirse diye yine yolluyoruz.
			temp = CompanyUpdate(temp,"right", parent_parent);
		}
	}
	// guncellenecek düğüm parent ının sağındaysa
	else if (location == "right" && updateParent->right->right!=NULL) 
	{
		if (updateParent->right->personels > updateParent->right->right->personels) 
		{
			// klasik yer değiştirme işlemleri sağı solu yedekleyip işlemi öyle yapıyoruz
			Company* temp = updateParent->right->right;
			Company* tempRight = temp->right;	
			Company* tempLeft = temp->left;

			Company* updateLeft = updateParent->right->left;

			temp->left = updateLeft;
			temp->right = updateParent->right;
			
			updateParent->right->right = tempRight;
			updateParent->right->left = tempLeft;
			updateParent->right = temp;

			parent_parent->right = temp;
			//yeniden güncelleme gerekirse diye yine yolluyoruz.
			temp= CompanyUpdate(temp, "right", parent_parent);
		}
	}

	else 
	{
		// parent kök ise parent ın solunu güncellememiz gerek.
		if (updateParent == treeRoot) 
		{
			// önce parent yla kontrol ediyoruz.
			// çünkü parant ile uyuşmazlık varsa önce sağdakini kontrol etmenin mânası yok.
			if (updateParent->personels < updateParent->left->personels) 
			{
				Company* temp = updateParent->left;
				Company* tempLeft = temp->left; 
				Company* tempRight = temp->right;

				Company* parent_sag = updateParent->right;

				updateParent->left = tempLeft; 
				updateParent->right = tempRight;
				temp->left = updateParent;
				temp->right = parent_sag;
				treeRoot = temp;
				temp = CompanyUpdate(temp, "root", parent_parent);
			}
			// eğer parantı ile uyuşmazlık yoksa
			else 
			{
				// sağındaki düğümle kontrol ediyoruz.
				if (updateParent->left->right!=NULL && updateParent->left->personels > updateParent->left->right->personels) 
				{
					Company* temp = updateParent->left->right;
					Company* tempRight = temp->right; 
					Company* tempLeft = temp->left;

					Company* parent_sol = updateParent->left->left; 

					updateParent->left->right = tempRight;
					updateParent->left->left = temp->left;
					temp->left = parent_sol;
					temp->right = updateParent->left;

					updateParent->left = temp; 

					temp = CompanyUpdate(temp, "right",parent_parent);
				}
			}
		}
		// parent kök değilse;
		else 
		{
			// parent ı ile kontrol ediyoruz
			if (updateParent->personels < updateParent->left->personels) 
			{
				Company* temp = updateParent->left;
				Company* tempLeft = temp->left; 
				Company* tempRight = temp->right;

				Company* parent_sag = updateParent->right;

				updateParent->left = tempLeft;
				updateParent->right = tempRight;
				temp->left = updateParent;
				temp->right = parent_sag;
				
				// fark burada
				if (parent_parent->left == updateParent)
					parent_parent->left = temp;
				else
					parent_parent->right = temp;
				Company* old_parent_parent = parent_parent;
				CompanyParent(treeRoot, parent_parent->companyName);
				Company* new_parent_parent = parent_parent;
				old_parent_parent = CompanyUpdate(old_parent_parent, "left", new_parent_parent);
			}
			// eğer parent ile uyuşmazlık yoksa sağındakiyle kontrol ediyoruz.
			else 
			{
				// sağdakine göre verisi daha büyükse burada yer değiştirme yapması lazım
				if (updateParent->left->right != NULL && updateParent->left->personels > updateParent->left->right->personels) 
				{
					Company* temp = updateParent->left->right;
					Company* tempRight = temp->right;
					Company* tempLeft = temp->left;

					Company* parent_sol = updateParent->left->left;

					updateParent->left->right = tempRight;
					updateParent->left->left = temp->left;
					temp->left = parent_sol;
					temp->right = updateParent->left;

					updateParent->left = temp;

					temp = CompanyUpdate(temp, "right",updateParent);
				}
			}
		}
		return updateParent;
	}
	return updateParent;
}


Company* CompanyTree::LineProcess() 
{
	// okunan firmanın ağaçta olup olmadığı firma arama fonksiyonu ile bakılır 
	// eğer yoksa eklenir.
	// varsa üzerine eklenir
	Company* result = CompanySearch(treeRoot, parsing[0]);
	if (company == NULL) 
	{
		treeRoot = Add(treeRoot, 1, parsing);
	}
	else 
	{
		int time = 2020 - stoi(parsing[2]);
		// location guncellenmesi gereken düğüm parentinin neresinde olduğunu tutar
		// konumu neredeyse ona göre işlemi yapar.
		string location = "";
		if (company->right != NULL && company->right->companyName == parsing[0]) location = "right";
		else if (company->left != NULL && company->left->companyName == parsing[0]) location = "left";
		else if (company->companyName == parsing[0]) location = "root";
			
		
		if (location == "right") 
		{
			company->right->workersTree.treeRoot = company->right->workersTree.Add(company->right->workersTree.treeRoot, time, parsing);
			company->right->personels++;
			company->right->workersTree.personelNumber++;
		}
		else if (location == "left") 
		{
			company->left->workersTree.treeRoot = company->left->workersTree.Add(company->left->workersTree.treeRoot, time, parsing);
			company->left->personels++;
			company->left->workersTree.personelNumber++;
		}
		else if (location == "root") 
		{
			company->workersTree.treeRoot = company->workersTree.Add(company->workersTree.treeRoot, time, parsing);
			company->personels++;
			company->workersTree.personelNumber++;
		}
		// gerektiğinde parentinin üstünü alıyoruz
		// güncellemeye yolluyoruz
		Company* result_parent = CompanyParent(treeRoot, company->companyName);
		company = CompanyUpdate(company, location, parent_parent);
		company = NULL;
		parent_parent = NULL;
	}
	return treeRoot;
}

Company* CompanyTree::CompanySearch(Company* root,string name) 
{
	if (root == NULL)
		return NULL;	
	if (root == treeRoot && root->companyName == name)
		company = root;
	CompanySearch(root->left,name);
	if (root->right != NULL && root->right->companyName == name)
		company = root;
	else if (root->left != NULL && root->left->companyName == name)
		company = root;
	CompanySearch(root->right,name);
	return NULL;
}

int CompanyTree::Depth(Company *a)
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

int CompanyTree::Height(Company* t) {
   int h = 0;
   if (t != NULL) {
      int left_height = Height(t->left);
      int right_height = Height(t->right);
      int max_height = max(left_height, right_height);
      h = max_height + 1;
   }
   return h;
}


int CompanyTree::BalanceWrite(Company *A)
{
	if (A == NULL)	return 0;
	return Depth(A->left) -
		Depth(A->right);
}

void CompanyTree::Postorder(Company* rd) 
{
		if (rd == NULL)
			return;
		Postorder(rd->left);
		Postorder(rd->right);
		cout << rd->companyName << endl;
		rd->workersTree.Postorder(rd->workersTree.treeRoot);
		cout << endl << endl;
}





CompanyTree::~CompanyTree()
{
	Delete(treeRoot);
}
