#include <iostream>
#include <string>
#include <fstream>
#include <time.h>
#include <stdlib.h>
using namespace std;
struct node{   // tek baðlý doðrusal liste
	
	string kelime;
	node* next;
};
node* ekle_liste(node* r, string k){  
	
	if(r==NULL)
	{
		r = new node ;
		r->kelime = k;
		r->next = NULL;
	}
	else{
		node* yrd;
		yrd = r;
			while(yrd->next!=NULL){
				if(k==yrd->kelime)  // daha önce aynýsý eklenmiþse ekleme
				return r;
				yrd = yrd->next;
			}
			
		
		yrd->next = new node;
		yrd->next->kelime = k;
		yrd->next->next = NULL;
		
	}
	return r;
}
long BF(string aranan, int aranan_u, string metin, long metin_u) {  // Brute Force , aranan kelime metinde var mý?
  
int i,j;
long bulunan_kelime_sayisi=0;
   for (i = 0; i <= metin_u - aranan_u; i++) { 
   
      for (j = 0; j < aranan_u && aranan[j] == metin[i + j]; j++); 
      
      
      if (j == aranan_u)
      	bulunan_kelime_sayisi++;
		
   }
   return bulunan_kelime_sayisi;
}
void dosyaya_yaz(string acilacak_dosya, string kelime ,long bulunan_kelime_sayisi, clock_t time1){
	ofstream yaz("sonuclar.txt",ios::app);
	
	yaz<<"# \""<<kelime<<"\" verisi "<<acilacak_dosya<<"'de "<<bulunan_kelime_sayisi<<" tane bulundu, "<<(float)time1 / CLOCKS_PER_SEC<<" saniyede arama gerceklesti."<<endl;
	
	
	yaz.close();
	system("C:\\Users\\Murat\\Desktop\\veri_yapilari_proje\\sonuclar.txt");
}
// Overloading (yaklaþýk sonuç varsa çalýþýr)
void dosyaya_yaz(string acilacak_dosya, string kelime ,long bulunan_kelime_sayisi, clock_t time1, string yaklasik_kelime, long yaklasik_kelime_sayisi, clock_t time2){
	ofstream yaz("sonuclar.txt",ios::app);
	
	yaz<<"# \""<<kelime<<"\" verisi "<<acilacak_dosya<<"'de "<<bulunan_kelime_sayisi<<" tane bulundu, "<<(float)time1 / CLOCKS_PER_SEC<<" saniyede arama gerceklesti."<<endl;
	yaz<<"Bunu mu demek istediniz?: \""<<yaklasik_kelime<<"\" "<<yaklasik_kelime_sayisi<<" tane bulundu, "<<(float)time2 / CLOCKS_PER_SEC<<" saniyede arama gerceklesti."<<endl;
	
	yaz.close();
	system("C:\\Users\\Murat\\Desktop\\veri_yapilari_proje\\sonuclar.txt");
}
int minimum(int a, int b, int c) { // gelen 3 sayýnýn en küçüðünü gönderir
	if (a <= b && a <= c)
		return a;
	if (b <= c && b <= a)
		return b;
	if (c <= a && c <= b)
		return c;

	return 0;
	}
int editDistance(int birinci_u, string birinci_kelime, int ikinci_u, string ikinci_kelime) { // 2 kelime arasýndaki mesafeyi döndürür (0 mesafesi kelimelerin ayný olduðunu gösterir)
	
	if (birinci_u == 0)
		return ikinci_u;
	if (ikinci_u == 0)
		return birinci_u;
	if (birinci_kelime[birinci_u - 1] == ikinci_kelime[ikinci_u - 1])
		return editDistance(birinci_u - 1, birinci_kelime, ikinci_u - 1, ikinci_kelime);

	int durum1 = editDistance(birinci_u - 1, birinci_kelime, ikinci_u - 1, ikinci_kelime); // yer deðiþtirme 
	int durum2 = editDistance(birinci_u - 1, birinci_kelime, ikinci_u, ikinci_kelime); // silme
	int durum3 = editDistance(birinci_u, birinci_kelime, ikinci_u - 1, ikinci_kelime); // ekleme

	return minimum(durum1, durum2, durum3) + 1;
}
int main(){
int cikis;	

	node* root= NULL;
	
	
	string okunan,veri;
	string acilacak_dosya;
	
	
	cout<<"metin.txt dosyasi aciliyor.. Lutfen bekleyin.."<<endl;
	
		acilacak_dosya= "metin.txt";
		ifstream oku("metin.txt");
		if (!oku){
		   	cout<<"Dosya acilamadi."<<endl;
		   	return 0;
		}
  		else {
		  
			while(!oku.eof()){
			
			root = ekle_liste(root,okunan);
			veri+=okunan;
			veri+=" ";
			oku>>okunan;
			}
			oku.close();
			
		}
			
	

do{
	long bulunan_kelime_sayisi=0;
	long yaklasik_kelime_sayisi=0;
	
	string kelime;
	string yaklasik_sonuc;
	string kelimeler_butunu[50];
	
	clock_t time_start, time_stop, time1, time2;
	
	cout<<"aramak istediginiz kelime: ";
	getline(cin>>ws,kelime); 

	
	
	time_start = clock();
	bulunan_kelime_sayisi= BF(kelime,kelime.length(),veri,veri.length());
	time_stop = clock();
	
	time1 = time_stop - time_start;


	
	int kackelime = 1;
	
	for(int i=0; i<kelime.length(); i++){ // aranan veri kaç kelimeden oluþuyor
		if(kelime[i]==' ')
			kackelime++;
	}
	
	for(int i=0,j=0; i<kackelime; i++){  // aranan her kelimeyi diziye aktardýk
		for(j; j<kelime.length(); j++){
			if(kelime[j]==' '){
				j++;
				break;
			}
			else
				kelimeler_butunu[i]+=kelime[j];
		}
	}
	
			
			
			
		node* yrd;
		
		string gecicikelime,listekelime;
		int max_yakinlik;
		
		bool kontrol = true; // ilk yazdýrýlan kelimeden önce boþluk koyulmamasý için kontrol  (false olduðunda yeni kelime " " boþluk koyulduktan sonra yanýna eklenecek)
		
		if(bulunan_kelime_sayisi==0){
			time_start = clock();
		for(int i=0 ; i<kackelime; i++){
			max_yakinlik=1;
			yrd=root;
		gecicikelime = kelimeler_butunu[i]; 
	
		
		while(yrd!=NULL){
			listekelime = yrd->kelime;
			
			if(listekelime == gecicikelime){ // aranan kelime listedeki bir kelime ile aynýysa 
				if(kontrol){
				yaklasik_sonuc += listekelime;
				kontrol = false;
				}
				else
				yaklasik_sonuc+=" "+listekelime;
				
			break;
			}
		
				int yakinlik = editDistance(gecicikelime.length(),gecicikelime, listekelime.length(),listekelime);
				
				if(yakinlik==max_yakinlik){ // max_yakinlik = 1 yoksa max_yakinlik = 2
					if(kontrol){
						yaklasik_sonuc += listekelime;
						kontrol = false;
						break;
					}
					
					else{
						yaklasik_sonuc+=" "+listekelime;
						break;
					}
				}
				
				if(yrd->next==NULL && max_yakinlik!=2){ // arama bitti 1 yakinliginda kelime yoksa 2 yakinliginda bakiliyor
					max_yakinlik = 2;
					yrd->next=NULL;
					delete yrd;
					yrd = root;
					i=0;
					continue;
				}


			yrd = yrd->next;
		}
		
	}	
		time_stop = clock();
	
			time2 = time_stop - time_start;	
		}
			
		
	
			
	if(kelime==yaklasik_sonuc || yaklasik_sonuc == ""){  // aranan veri yaklaþýk sonuca eþitse sadece veri dosyaya yazýlýyor 
		dosyaya_yaz(acilacak_dosya,kelime,bulunan_kelime_sayisi,time1);
	}
	else{	  // deðilse her iki iþlem süresi de dosyaya yazýlýyor 
		time_start = clock();
		yaklasik_kelime_sayisi= BF(yaklasik_sonuc,yaklasik_sonuc.length(),veri,veri.length());
		time_stop = clock();
		
		time2 += time_stop - time_start;
	
		dosyaya_yaz(acilacak_dosya,kelime,bulunan_kelime_sayisi,time1,yaklasik_sonuc,yaklasik_kelime_sayisi,time2);
	}

	cout<<"Cikis yapmak icin 0, devam etmek icin baska bir sayi girin.."<<endl;
	cout<<"|: ";
	cin>>cikis;

}while(cikis!=0);



	
	
	
	return 0;
}
