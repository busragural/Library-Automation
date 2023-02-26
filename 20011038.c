#include<stdio.h>
#include<stdlib.h>
#include<string.h>


typedef struct Ogrenci { 
	char ogrID[9]; 
	char ad[30]; 
	char soyad[30]; 
	int puan; 
	struct Ogrenci *next; 
	struct Ogrenci *prev;
}Ogrenci;

typedef struct Yazar { 
	int yazarID; 
	char yazarAd[30]; 
	char yazarSoyad[30]; 
	struct Yazar *next;
}Yazar;

typedef struct KitapOrnek { 
	char EtiketNo[20]; 
	char Durum[8]; 
	struct KitapOrnek *next;
}KitapOrnek;

typedef struct Kitap {
	char kitapAdi[30]; 
	char ISBN[13]; 
	int adet;
	struct Kitap *next; 
	struct KitapOrnek *head;
}Kitap;

typedef struct KitapYazar{ 
	char ISBN[13]; 
	int YazarID;
}KitapYazar;

typedef struct Tarih{ 
	unsigned int gun:5; 
	unsigned int ay:4; 
	unsigned int yil:12;
}Tarih;

typedef struct KitapOdunc{ 
	char EtiketNo[20]; 
	char ogrID[9]; 
	unsigned int islemTipi:1; 
	struct Tarih islemTarihi;
}KitapOdunc;

//KULLANýLAN TUM FONKSIYONLAR

//YAZAR
Yazar *yazarEkle(Yazar *head, char* yazarAd, char* yazarSoyad, int* yazarID);
Yazar* yazarBul(Yazar *head, char* arananYazarAdi, char*arananYazarSoyad);
Yazar* yazarSil(Yazar*(*fpYazarBul)(Yazar *head, char* arananYazarAdi, char* arananYazarSoyad), Yazar *head, char* silinenYazarAdi, char* silinenYazarSoyadi, KitapYazar **database, int databaseCount);
Yazar* guncelleYazar(Yazar*(*fpYazarBul)(Yazar *head, char* arananYazarAdi, char* arananYazarSoyad),Yazar *head, char* guncYazarAdi, char* guncYazarSoyad );
void yazarGoruntule(Yazar*(*fpYazarBul)(Yazar *head, char* arananYazarAdi, char* arananYazarSoyad), Yazar *head, char* gorYazarAdi, char* gorYazarSoyadi, KitapYazar**database,int databaseCount, Kitap* node);
Yazar *dosyaOkuYazar(Yazar* head, int *yazarID);
void dosyaYazYazar(Yazar *head);
//OGRENCI
Ogrenci* ogrenciEkle(Ogrenci *root, char* ogrenciAd, char* ogrenciSoyad, char* ogrenciID, int puan);
void ogrencileriListele(Ogrenci *node);
Ogrenci *ogrenciBul(Ogrenci *root, char* arananOgrenciAdi, char* arananOgrenciSoyad);
Ogrenci* ogrenciSil(Ogrenci*(fpOgrenciBul)(Ogrenci *root, char* arananOgrenciAdi, char* arananOgrenciSoyad), Ogrenci *root, char* silinenOgrAdi, char* silinenOgrSoyad);
Ogrenci* guncelleOgrenci(Ogrenci*(fpOgrenciBul)(Ogrenci *root, char* arananOgrenciAdi, char* arananOgrenciSoyad), Ogrenci *root, char* guncOgrAdi, char* guncOgrSoyad);
void ogrBilgisi(Ogrenci*(fpOgrenciBul)(Ogrenci *root, char* arananOgrenciAdi, char* arananOgrenciSoyad), Ogrenci* root, char *ogrAd, char *ogrSoyad, KitapOdunc **databaseOdunc, int databaseCount);
void ogrenciIDara(Ogrenci *root, char *ID, KitapOdunc **database, int databaseCount);
Ogrenci *dosyaOkuOgrenci(Ogrenci *head );
void dosyaYazOgrenci(Ogrenci *head);
Ogrenci* ogrenciIDKontrol(Ogrenci *root, char *ogrID);
void cezaliListele(Ogrenci *node);
void teslimEtmemisler(KitapOdunc **database, int databaseCount);
//KITAP
Kitap *kitapEkle(Kitap *node, char* kitapAdi, char* ISBN, int* adet );
Kitap* kitapBul(Kitap *node, char* arananKitap);
Kitap* kitapSil(Kitap*(*fpKitapBul)(Kitap *node, char* arananKitap), Kitap *node, char *silinenKitap);
Kitap* guncelleKitap(Kitap*(*fpKitapBul)(Kitap* node, char* arananKitap), Kitap* node, char* guncKitap);
void raftakiKitaplar(Kitap *node);
void kitapGoruntule(Kitap*(*fpKitapBul)(Kitap *node, char* arananKitap), Kitap *node, char *gorKitap, Yazar* head, KitapYazar **database, int databaseCount);
void teslimEdilmeyenler(KitapOdunc **database, int databaseCount);
KitapOrnek* ornekEkle(char* ISBN, int adet);
KitapYazar* kitabinYazari(char *ISBN, int yazarID);
void guncelYazar(Kitap*(*fpKitapBul)(Kitap *node, char* arananKitap), Kitap *node, char *gorKitap, KitapYazar **database, Yazar*(*fpYazarBul)(Yazar *head, char* arananYazarAdi, char* arananYazarSoyad),Yazar*head, char* guncYazarAdi, char* guncYazarSoyad);
Kitap *dosyaOkuKitap(Kitap *head);
void dosyaYazKitap(Kitap *head);
KitapYazar **dosyaOkuKitapYazar(KitapYazar **database, int *databaseCount);
void dosyaYazKitapYazar(KitapYazar **database, int *databaseCount);
KitapOdunc *odunc(Kitap *node, char *kitapAdi, Ogrenci *root, char *ogrID, Tarih *tarihBilgisi);
KitapOdunc *teslim(Kitap *node, char *kitapAdi, Ogrenci *root, char *ogrID, Tarih *tarihBilgisi);
void dosyaYazKitapOdunc(KitapOdunc **database, int *databaseCount);


int main(){
	
	int islem,op,secim;
	int menu = 1;
	int okay;
	
	int yazarID=0; 
	char *yazarAd = (char*)malloc(30*sizeof(char));
	
	if(yazarAd == NULL) { 
   		printf("Bellek yetersiz.\n");
    	exit(1);
  	}
	char *yazarSoyad = (char*)malloc(30*sizeof(char));
	if(yazarSoyad == NULL) { 
   		printf("Bellek yetersiz.\n");
    	exit(1);
  	}
	Yazar *head = NULL;
	
	head = dosyaOkuYazar(head, &yazarID); 
	
	char *ogrID = (char*)malloc(9*sizeof(char));
	if(ogrID == NULL) { 
   		printf("Bellek yetersiz.\n");
    	exit(1);
  	}
	char *ad = (char*)malloc(30*sizeof(char));
	if(ad == NULL) { 
   		printf("Bellek yetersiz.\n");
    	exit(1);
  	}
	char *soyad = (char*)malloc(30*sizeof(char));
	if(soyad == NULL) { 
   		printf("Bellek yetersiz.\n");
    	exit(1);
  	}
	int puan = 100;
	Ogrenci *root = NULL;
	root = dosyaOkuOgrenci(root);
	
	char *kitapAdi = (char*)malloc(30*sizeof(char));
	if(kitapAdi == NULL) { 
   		printf("Bellek yetersiz.\n");
    	exit(1);
  	}
	char *ISBN = (char*)malloc(13*sizeof(char));
	if(ISBN == NULL) { 
   		printf("Bellek yetersiz.\n");
    	exit(1);
  	}
	int adet;
	Kitap *node = NULL;
	node = dosyaOkuKitap(node);
	KitapYazar **database = (KitapYazar**)malloc(sizeof(KitapYazar*));
	int databaseCount=0;
	database = dosyaOkuKitapYazar(database, &databaseCount);
	KitapOdunc **databaseOdunc = (KitapOdunc**)malloc(sizeof(KitapOdunc));
	int databaseSayac = 0;
	
	int tmp;
	Tarih *tarihBilgisi = (Tarih*)malloc(sizeof(Tarih));
		if(ad == NULL) { 
   		printf("Bellek yetersiz.\n");
    	exit(1);
  	}
	int tarih_hesap;
	int i,j;

	printf("------------------------------------------------\n\n");
	printf("*** KUTUPHANE OTOMASYONUNA HOSGELDINIZ! ***\n\n");
	printf("------------------------------------------------");

	while(menu == 1){
		
		
		printf("\n\nYapmak istediginiz islemi seciniz.\n\n1-Ogrenci Islemleri\n2-KitapIslemleri\n3-Yazar Islemleri\n4-Cikis");
		printf("\nSECIM:");
		scanf("%d", &islem);
		

		if(islem == 1){
			printf("\n* OGRENCI ISLEMLERI *\n");
			
			printf("\nYapmak istediginiz islemi seciniz.\n\n1-Ekle\n2-Sil\n3-Guncelle\n4-Ogrenci Bilgisi Goruntule\n5-Kitap Teslim Etmemis Ogrencileri Listele\n6-Cezali Ogrencileri Listele\n7-Tum Ogrencileri Listele\n8-Kitap Odunc Al\n9-Kitap Teslim Et\n10-Geri Don\n11-Cikis\n");
			printf("\nSECIM:");
			scanf("%d", &op);
			getchar();
			
			switch(op){
				
				case 1:	
					printf("Eklemek istediginiz ogrencinin adini giriniz:");			
					gets(ad);
									
					printf("Soyadini giriniz:");			
					gets(soyad);
					
					printf("ID giriniz:");			
					gets(ogrID);

					Ogrenci *kontrol_icin = ogrenciIDKontrol(root, ogrID);
					strcpy(ogrID, kontrol_icin->ogrID);
					
					root = ogrenciEkle(root, ad, soyad, ogrID, puan);
					dosyaYazOgrenci(root);
					break;
					
				case 2:
					printf("Silmek istediginiz ogrencinin adini giriniz:");
					gets(ad);
					
					printf("Soyadini giriniz:");
					gets(soyad);
					
					root = ogrenciSil(ogrenciBul, root, ad, soyad);

					break;
				
				case 3:
					printf("Guncellemek istediginiz ogrencinin eski adini giriniz:");
					gets(ad);
					printf("Soyadini giriniz:");
					gets(soyad);
					
					guncelleOgrenci(ogrenciBul, root, ad, soyad);

					break;
				
				case 4:	
				
					printf("\nBilgilerini goruntulemek istediginiz ogreniyi AD-SOYAD ile aramak icin 1'e, ID ile aramak icin 2'ye basin.\nSECIM: ");
					scanf("%d", &secim);
					getchar();
					
					if(secim == 1){
						printf("\nOgrencinin adini giriniz:");
						gets(ad);
						
						printf("\nSoyadini giriniz:");
						gets(soyad);
						
						ogrBilgisi(ogrenciBul, root, ad, soyad, databaseOdunc, databaseSayac);	
					}
					else if(secim==2){
						printf("\nID giriniz:");
						gets(ogrID);
						
						ogrenciIDara(root, ogrID, databaseOdunc, databaseSayac);
					}
					else{
						printf("\n***HATALI SECIM!");
					}
	
					break;
				
				case 5:
					teslimEtmemisler(databaseOdunc, databaseSayac);
					
					break;
				
				case 6:
					cezaliListele(root);	
					
					break;
				
				case 7:
					
					ogrencileriListele(root);
					break;
				
				case 8:
					printf("\nID giriniz:");
					gets(ogrID);
					
					printf("\nKitap ismi:");
					gets(kitapAdi);
						
					printf("Gun giriniz:");
					scanf("%d", &tmp);
					tarihBilgisi->gun = tmp;
					printf("Ay giriniz:");
					scanf("%d", &tmp);
					tarihBilgisi->ay = tmp;
					printf("Yil giriniz:");
					scanf("%d", &tmp);
					tarihBilgisi->yil = tmp;
					
					
					Kitap *hafiza = node;
					while(strcmp(hafiza->kitapAdi, kitapAdi) != 0 ){
						hafiza = hafiza->next;
					}

					KitapOrnek *temp = hafiza->head;
					
					
					while( temp !=NULL && strcmp(temp->Durum, "RAFTA") != 0 ){
						temp = temp->next;
					}
					
					if(temp != NULL){
						Ogrenci *iter = root;
						
					
						while( iter != NULL && strcmp(iter->ogrID, ogrID) != 0){
							iter=iter->next;
									
						}
							
						if(iter != NULL){
									
							if( iter->puan < 0){
								printf("\nPuaniniz yetmedigi icin kitap alamazsiniz.\n");
									
							}
							else{														
								databaseOdunc = (KitapOdunc**)realloc(databaseOdunc,(databaseSayac+1)*sizeof(KitapOdunc*));
								databaseOdunc[databaseSayac] = odunc(node, kitapAdi, root, ogrID, tarihBilgisi);
									
								databaseSayac++;
								dosyaYazKitapOdunc(databaseOdunc, &databaseSayac);
		
								}
							}else{
								
								printf("\nSistemde boyle bir ogrenci yok.\n");
							}
								
						
					}
					else{
						printf("\n***ISLEM BASARISIZ.\n");
					}

					break;
				
				case 9:
					
					printf("\nID giriniz:");
					gets(ogrID);
					
					printf("\nKitap ismi:");
					gets(kitapAdi);
						
					printf("Gun giriniz:");
					scanf("%d", &tmp);
					tarihBilgisi->gun = tmp;
					printf("Ay giriniz:");
					scanf("%d", &tmp);
					tarihBilgisi->ay = tmp;
					printf("Yil giriniz:");
					scanf("%d", &tmp);
					tarihBilgisi->yil = tmp;
					
					databaseOdunc = (KitapOdunc**)realloc(databaseOdunc,(databaseSayac+1)*sizeof(KitapOdunc*));
					databaseOdunc[databaseSayac] = teslim(node, kitapAdi, root, ogrID, tarihBilgisi);
					j=0;
				
					while(strcmp(databaseOdunc[databaseSayac]->EtiketNo, databaseOdunc[j]->EtiketNo) != 0 || strcmp(databaseOdunc[databaseSayac]->ogrID, databaseOdunc[j]->ogrID) != 0){
						j++;	
					}
					
					tarih_hesap = ((databaseOdunc[databaseSayac]->islemTarihi.ay) - (databaseOdunc[j]->islemTarihi.ay))*30 + ((databaseOdunc[databaseSayac]->islemTarihi.yil) - (databaseOdunc[j]->islemTarihi.yil))*365 + ((databaseOdunc[databaseSayac]->islemTarihi.gun) - (databaseOdunc[j]->islemTarihi.gun));
					printf("GUN SAYISI: %d", tarih_hesap);
	
					if(tarih_hesap>15){
							
						Ogrenci *iter = root;
						while(strcmp(databaseOdunc[databaseSayac]->ogrID,iter->ogrID )!=0 ){
							iter = iter->next;
						}
						iter->puan -=10;
	
					}
	
						databaseSayac++;
						dosyaYazKitapOdunc(databaseOdunc, &databaseSayac);
		
					break;
					
				case 10:
					break;
					
				case 11:
					menu = 0;
					break;
				default:
					printf("Hatali giris. Tekrar deneyiniz.\n\n");
					break;		
			}
			
		}	
		else if(islem == 2){
			
			printf("\n* KITAP ISLEMLERI *\n");
			printf("\nYapmak istediginiz islemi seciniz.\n\n1-Ekle\n2-Sil\n3-Guncelle\n4-Kitap Bilgisi Goruntule\n5-Raftaki Kitaplari Listele\n6-Zamaninda Teslim Edilmeyen Kitaplari Listele\n7-Kitap-Yazar Eslestir\n8-Kitabin Yazarini Guncelle\n9-Geri Don\n10-Cikis\n");
			printf("\nSECIM:");
			scanf("%d", &op);
			getchar();
			switch(op){
				
				case 1:
					printf("\nEklemek istediginiz kitabin adi: ");
					gets(kitapAdi);
					printf("\nEklemek istediginiz kitabin adedi: ");
					scanf("%d", &adet);
					getchar();
					printf("\nEklemek istediginiz kitabin ISBN numarasi: ");
					gets(ISBN);
	
					
					Kitap* kontrol;
					Kitap *sonISBN;
					okay = 1;
					if(node!=NULL){
						while(okay == 1 ){
							if(strcmp(node->ISBN, ISBN) == 0){
								printf("\nSistemde ayni ISBN'e sahip kitap var. Lutfen yeni deger giriniz.\n");
								gets(ISBN);
							}
							else{
								kontrol = node;
								while(kontrol->next != NULL && strcmp(kontrol->ISBN, ISBN) != 0){
									kontrol = kontrol->next;
								}
								if(strcmp(kontrol->ISBN, ISBN) == 0){
									printf("\nSistemde ayni ISBN'e sahip kitap var. Lutfen yeni deger giriniz.\n");
									gets(ISBN);
								}
								else{
									okay = 0;
								}
							}
						}
					}
					else{
						okay = 0;
					}
					
					node = kitapEkle(node, kitapAdi, ISBN, &adet);
					
					break;
					
				case 2:
					printf("\nSilmek istediginiz kitabin adi: ");
					gets(kitapAdi);
					
					node = kitapSil(kitapBul, node, kitapAdi);

					break;
				
				case 3:
					printf("\nBilgilerini guncellemek istediginiz kitap: ");
					gets(kitapAdi);
					
					guncelleKitap(kitapBul, node, kitapAdi);

					break;
				
				case 4:
					
					printf("\nBilgilerini goruntulemek istediginiz kitap: ");
					gets(kitapAdi);

					kitapGoruntule(kitapBul, node, kitapAdi, head, database, databaseCount);

					break;
				
				case 5:
					raftakiKitaplar(node);
					break;
				
				case 6:
					
					
					teslimEdilmeyenler(databaseOdunc, databaseSayac);
					break;
				
				case 7:

					printf("\nEslestirmek istediginiz kitabin adini giriniz: ");
					gets(kitapAdi);
					
					printf("Yazarin adini giriniz:");				
					gets(yazarAd);
					
					printf("Soyadini giriniz:");					
					gets(yazarSoyad);
					
					Kitap* arananKit = kitapBul(node, kitapAdi);
					Yazar* arananYaz = yazarBul(head, yazarAd, yazarSoyad);
					
					if(arananKit == NULL){
						printf("\n\n***Sistemde boyle bir kitap bulunmamaktadir.\n");
					}
					else if(arananYaz == NULL){
						printf("\n\n***Sistemde boyle bir yazar bulunmamaktadir.\n");
					}
					else{

						database = (KitapYazar**)realloc(database,(databaseCount+1)*sizeof(KitapYazar*));
						database[databaseCount] = kitabinYazari(arananKit->ISBN, arananYaz->yazarID);
						
						databaseCount++;	
						printf("\n\nEslesme basarili.");
					
					}

					dosyaYazKitapYazar(database, &databaseCount);

					break;
				
				case 8:
					printf("\nKitabin yazarini guncelle: ");
					
					printf("\nKitabin adi: ");
					gets(kitapAdi);
					
					printf("\nGuncel yazarin adini giriniz:");				
					gets(yazarAd);
					
					printf("\nGuncel soyadini giriniz:");					
					gets(yazarSoyad);
					
					guncelYazar(kitapBul, node, kitapAdi, database, yazarBul, head, yazarAd, yazarSoyad);
					dosyaYazKitapYazar(database, &databaseCount);
					
					break;
					
				case 9:
				
					break;
					
				case 10:
					menu = 0;
					break;	
				
				default:
					printf("Hatali giris. Tekrar deneyiniz.\n\n");
					break;		
			}
			
			
		}
		else if(islem == 3){
			
			printf("\n* YAZAR ISLEMLERI *\n");
			
			printf("\nYapmak istediginiz islemi seciniz.\n\n1-Ekle\n2-Sil\n3-Guncelle\n4-Yazar Bilgisi Goruntule\n5-Geri Don\n6-Cikis\n");
			printf("\nSECIM:");
			scanf("%d", &op);
			getchar();
			
			switch(op){
				
				case 1:
					printf("Eklemek istediginiz yazarin adini giriniz:");				
					gets(yazarAd);
					
					printf("Soyadini giriniz:");					
					gets(yazarSoyad);
				
					head = yazarEkle(head, yazarAd, yazarSoyad,&yazarID);

					break;
					
				case 2:			
					printf("Silmek istediginiz yazarin adini giriniz:");
					gets(yazarAd);
					
					printf("Soyadini giriniz:");
					gets(yazarSoyad);
					
					head = yazarSil(yazarBul, head, yazarAd, yazarSoyad, database, databaseCount);
					dosyaYazKitapYazar(database, &databaseCount);
					
					
					break;
					
				case 3:	
					printf("Guncellemek istediginiz yazarin eski adini giriniz:");
					gets(yazarAd);
					
					printf("Soyadini giriniz:");
					gets(yazarSoyad);

					guncelleYazar(yazarBul, head, yazarAd, yazarSoyad );
					
					break;
					
				case 4:
	
					printf("\nBilgilerini goruntulemek istediginiz yazarin adini giriniz:");
					gets(yazarAd);
					
					printf("Soyadini giriniz:");
					gets(yazarSoyad);
					
					Yazar* arananYaz = yazarBul(head, yazarAd, yazarSoyad);
					if(arananYaz == NULL){
						printf("\n\n***Sistemde boyle bir yazar bulunmamaktadir.\n");
					}
					else{
						yazarGoruntule(yazarBul, head, yazarAd, yazarSoyad, database,databaseCount, node);
					}

					break;
					
				case 5:			
					break;
					
				case 6:
					menu = 0;
					break;	
					
				default:
					printf("Hatali giris. Tekrar deneyiniz.\n\n");
					break;
				
			}
			
		}
		else if(islem == 4){
			menu = 0;
			
			free(yazarAd);
			free(yazarSoyad);
			free(ogrID);
			free(ad);
			free(soyad);
			free(kitapAdi);
			free(ISBN);
			free(tarihBilgisi);
			for(i=0; i<databaseCount; i++){
				free(database[i]);
			}
			free(database);
			for(i=0; i<databaseSayac; i++){
				free(databaseOdunc[i]);
			}
			free(databaseOdunc);	
			
		}
		else{
			printf("Hatali giris. Tekrar deneyiniz.\n\n");
		}	
	}

	return 0;
}


void teslimEdilmeyenler(KitapOdunc **database, int databaseCount){
	int i,j;

	for(i=0; i<databaseCount; i++){
		if(database[i]->islemTipi == 0){
			j = i+1;
			while(j < databaseCount && strcmp(database[i]->EtiketNo,database[j]->EtiketNo ) !=0){	
				j++;
			}
			if(j == databaseCount){
				printf("ETIKET NO: %s\n", database[i]->EtiketNo);
			}	
		}
	}	
}


KitapOdunc *odunc(Kitap *node, char *kitapAdi, Ogrenci *root, char *ogrID, Tarih *tarihBilgisi){
	
	KitapOdunc *oduncKitap = (KitapOdunc*)malloc(sizeof(KitapOdunc));
	if(oduncKitap == NULL){ 
    	printf("Bellek yetersiz!\n");
    	exit(1);
  	}


	Ogrenci *arananOgr = root;
	Ogrenci *iter;
	
	while( arananOgr != NULL && strcmp(arananOgr->ogrID, ogrID) != 0){
		arananOgr= arananOgr->next;
	}
	
	if(arananOgr == NULL){
		printf("\n\nSistemde boyle bir ogrenci yok.");
		return 0;
	}
	else{
		
		Kitap *istenenKitap = kitapBul(node, kitapAdi);	
		
		if(istenenKitap == NULL){
			printf("\n***Sistemde boyle bir kitap bulunmamaktadir.");
			
		}
		else{
			
			Kitap *current = istenenKitap;
					
			while(strcmp(current->head->Durum, "RAFTA") != 0){
				current->head = current->head->next;
					
			}
		
			if(current->head->next != NULL){
				
			
				printf("\n%s etiketli kitap veriliyor.\n" , current->head->EtiketNo);
				strcpy(current->head->Durum, arananOgr->ogrID);
				strcpy(oduncKitap->EtiketNo, current->head->EtiketNo);
				strcpy(oduncKitap->ogrID, arananOgr->ogrID);
				oduncKitap->islemTipi = 0;
				oduncKitap->islemTarihi = *tarihBilgisi;	
				return oduncKitap;
			}
			else{
				printf("\n***Islem basarisiz.");
				
			}

		}
	}	

}

//KITAP ISLEMLERININ OLDUGU FONKSIYONLAR

KitapOdunc *teslim(Kitap *node, char *kitapAdi, Ogrenci *root, char *ogrID, Tarih *tarihBilgisi){
	
	KitapOdunc *teslimKitap = (KitapOdunc*)malloc(sizeof(KitapOdunc));
	if(teslimKitap == NULL){ 
    	printf("Bellek yetersiz!\n");
    	exit(1);
  	}

	Ogrenci *arananOgr = root;
	
	while( strcmp(arananOgr->ogrID, ogrID) != 0){
		arananOgr= arananOgr->next;
	}
	
	if(arananOgr == NULL){
		printf("Boyle bir ogrenci yok.");
	}
	else{
	
		Kitap *verilenKitap = kitapBul(node, kitapAdi);	
		
		if(arananOgr == NULL){
			printf("Boyle bir kitap yok.");
		}
		
		else{
			while(strcmp(verilenKitap->head->Durum,ogrID) != 0){
				verilenKitap->head = verilenKitap->head->next;
			}
			
			printf("\n%s etiketli kitap teslim edilebilir.\n" , verilenKitap->head->EtiketNo);
			strcpy(verilenKitap->head->Durum, "RAFTA");
			
			strcpy(teslimKitap->EtiketNo, verilenKitap->head->EtiketNo);
			strcpy(teslimKitap->ogrID, arananOgr->ogrID);
			teslimKitap->islemTipi = 1;
			teslimKitap->islemTarihi = *tarihBilgisi;
		}
	}
	return teslimKitap;
}


void guncelYazar(Kitap*(*fpKitapBul)(Kitap *node, char* arananKitap), Kitap *node, char *gorKitap, KitapYazar **database, Yazar*(*fpYazarBul)(Yazar *head, char* arananYazarAdi, char* arananYazarSoyad),Yazar*head, char* guncYazarAdi, char* guncYazarSoyad){
	
	Kitap *kitap = fpKitapBul(node, gorKitap);
	KitapYazar **tmp = database;
	int databaseCount = 0;
	
	Yazar *guncellenecekYazar;

	if(kitap == NULL){
		printf("Sistemde boyle bir kitap bulunmamaktadir.\n");
	}	
	else{
		while(strcmp(kitap->ISBN, tmp[databaseCount]->ISBN ) != 0){
			databaseCount++;
		}
		
		guncellenecekYazar = fpYazarBul(head, guncYazarAdi, guncYazarSoyad);
		
		if(guncellenecekYazar == NULL){
			
			printf("Sistemde boyle bir yazar bulunmamaktadir.\n");
		}	
		else{
			
			tmp[databaseCount]->YazarID = guncellenecekYazar->yazarID;
		}

	}

}

void kitapGoruntule(Kitap*(*fpKitapBul)(Kitap *node, char* arananKitap), Kitap *node, char *gorKitap, Yazar* head, KitapYazar **database, int databaseCount){

	int i, j;
	int count = 0;
	Kitap *goruntuleKitap = fpKitapBul(node, gorKitap);
	KitapYazar** tmp = database;
	Yazar *curr;
	
	if(goruntuleKitap == NULL){
		printf("\n****Sistemde boyle bir kitap bulunmamaktadir.\n");
	}
	else{
		
		printf("\nISBN: %s\nAD: %s\nADET: %d\n", goruntuleKitap->ISBN, goruntuleKitap->kitapAdi, goruntuleKitap->adet);

		for(i=0; i<databaseCount; i++){
			
			if(strcmp(goruntuleKitap->ISBN, tmp[i]->ISBN) == 0){
					
					curr= head;
					
					while(tmp[i]->YazarID != curr->yazarID){
						curr = curr->next;
					}
					printf("\nKitabin Yazari: %s %s\n", curr->yazarAd, curr->yazarSoyad);
			}
		}
		for(i=0; i<goruntuleKitap->adet; i++){
				printf("\nETIKET NO: %s\nDURUM:%s\n", goruntuleKitap->head->EtiketNo, goruntuleKitap->head->Durum);		
				goruntuleKitap->head = goruntuleKitap->head->next;
		}
	}
}


KitapYazar* kitabinYazari(char *ISBN, int yazarID){
													
	KitapYazar *yeniEslesme;

	yeniEslesme = (KitapYazar*)malloc(sizeof(KitapYazar));
	if(yeniEslesme == NULL){ 
    	printf("Bellek yetersiz!\n");
    	exit(1);
  	}
	strcpy(yeniEslesme->ISBN, ISBN);
	yeniEslesme->YazarID = yazarID;		
	
	return yeniEslesme;
}



KitapOrnek* ornekEkle(char* ISBN, int adet){
	
	KitapOrnek *head = (KitapOrnek*)malloc(sizeof(KitapOrnek));
	if(head == NULL){ 
    	printf("Bellek yetersiz!\n");
    	exit(1);
  	}
	KitapOrnek *iter = head;
	int i;
	for(i=1; i<=adet; i++){
		
		strcpy(iter->EtiketNo, ISBN);
		strcpy(&(iter->EtiketNo[13]), "_");
		sprintf(&(iter->EtiketNo[14]), "%d\0", i);
		strcpy(iter->Durum, "RAFTA");
		
		iter->next = (KitapOrnek*)malloc(sizeof(KitapOrnek));
		iter = iter->next;
	}
	iter = NULL;

	return head;
}

void raftakiKitaplar(Kitap *node){
	Kitap *iter1 = node;
	KitapOrnek *iter2;
	while (iter1 != NULL){
		iter2 = iter1->head;
		printf("ISBN: %s\nAD: %s\nADET: %d\n", iter1->ISBN, iter1->kitapAdi, iter1->adet);
		while(iter2 != NULL){
			if(strcmp (iter2->Durum, "RAFTA") == 0){
				printf("\tETIKET NO: %s\n", iter2->EtiketNo);
			}
			printf("\n");
			iter2 = iter2->next;
		}
	
    iter1 = iter1->next;
  	}
}


Kitap *kitapEkle(Kitap *node, char* kitapAdi, char* ISBN ,int* adet ){
	Kitap* iter;
	
	Kitap* yeniKitap = (Kitap*)malloc(sizeof(Kitap));
	if(yeniKitap == NULL){ 
    	printf("Bellek yetersiz!\n");
    	exit(1);
  	}
	strcpy(yeniKitap->kitapAdi, kitapAdi);
	strcpy(yeniKitap->ISBN, ISBN);
	yeniKitap->adet = *adet;
	
	yeniKitap->next = NULL;
	yeniKitap->head = ornekEkle(ISBN, *adet);
	
	if(node == NULL){
		node = yeniKitap;
	}	
	else{
		iter = node;
		
		while(iter->next != NULL){
			iter = iter->next;
		}
		
		iter->next = yeniKitap;
	}

	dosyaYazKitap(node);


	return node;
}


Kitap* kitapBul(Kitap *node, char* arananKitap){
	
	Kitap *current = node;
	
	while(current != NULL){
		if(strcmp(current->kitapAdi, arananKitap) == 0){
			return current;
		}
		current = current->next;
	}
	return NULL;
}

Kitap* kitapSil(Kitap*(*fpKitapBul)(Kitap *node, char* arananKitap), Kitap *node, char *silinenKitap){
	
	Kitap *iter;
	Kitap *silinecekKitap = fpKitapBul(node, silinenKitap);
	
	if(silinecekKitap == NULL){
		printf("Sistemde böyle bir kitap bulunmamaktadir.\n");
	}
	else{
		if(node == silinecekKitap){
			node = silinecekKitap->next;
			free(silinecekKitap);
		}
		else{
			iter = node;
			while(iter->next != silinecekKitap){
				iter = iter->next;
			}
			iter->next = iter->next->next;
		}
		dosyaYazKitap(node);
		printf("Kitap silindi.\n");
	}
	return node;
}

Kitap* guncelleKitap(Kitap*(*fpKitapBul)(Kitap* node, char* arananKitap), Kitap* node, char* guncKitap){
	
	Kitap *iter;
	Kitap *guncellenecekKitap = fpKitapBul(node, guncKitap);
	
	if(guncellenecekKitap == NULL){
		printf("Sistemde böyle bir kitap bulunmamaktadir.\n");
	}
	else{
		iter = node;
		while(iter != guncellenecekKitap){
				iter = iter->next;
		}
			
		printf("Guncel kitap adini giriniz:");
		gets(iter->kitapAdi);
	}
	dosyaYazKitap(node);
	return node;
}

//YAZAR ISLEMLERININ OLDUGU FONKSIYONLAR

void yazarGoruntule(Yazar*(*fpYazarBul)(Yazar *head, char* arananYazarAdi, char* arananYazarSoyad), Yazar *head, char* gorYazarAdi, char* gorYazarSoyadi, KitapYazar**database,int databaseCount, Kitap* node){
	
	Yazar *iter;
	Yazar *goruntuleYazar = fpYazarBul(head, gorYazarAdi, gorYazarSoyadi);
	KitapYazar **tmp = database;
	int i = 0;
	Kitap *tmpKitap;
	
	int ID = goruntuleYazar->yazarID;
	
	if(goruntuleYazar == NULL){
		printf("Sistemde boyle bir yazar bulunmamaktadir.\n");
	}
	
	else{
		printf("\nID: %d\nAD: %s\nSOYAD: %s\n", goruntuleYazar->yazarID, goruntuleYazar->yazarAd, goruntuleYazar->yazarSoyad);
		
		while( i<databaseCount && ID != tmp[i]->YazarID){
			
			i++;
		}
		
		if(ID == tmp[i]->YazarID){
			while(strcmp(tmp[i]->ISBN, node->ISBN) != 0){
				node = node->next;
			}
			printf("Yazarin kitaplari:\n");
			printf("ISBN: %s\nAD: %s\nADET: %d\n", node->ISBN, node->kitapAdi, node->adet);
			
		}
		else{
			printf("\nYazarin kitabi bulunmamaktadir.");
		}

	}
}

Yazar *yazarEkle(Yazar *head, char* yazarAd, char* yazarSoyad, int* yazarID){
	
	Yazar* iter;
	Yazar* yeniYazar = (Yazar*)malloc(sizeof(Yazar));
	if(yeniYazar == NULL){ 
    	printf("Bellek yetersiz!\n");
    	exit(1);
  	}
	strcpy(yeniYazar->yazarAd, yazarAd);
	strcpy(yeniYazar->yazarSoyad, yazarSoyad);
	yeniYazar->yazarID = ++(*yazarID);
	
	yeniYazar->next = NULL;
	
	if(head == NULL){
		head = yeniYazar;	
	}
	else{
		iter = head;
		
		while(iter->next != NULL){
			iter = iter->next;
		}
		
		iter->next = yeniYazar;
	}
	dosyaYazYazar(head);
	return head;	
}

Yazar* yazarBul(Yazar *head, char* arananYazarAdi, char*arananYazarSoyad){
	
	Yazar *current = head;

	while (current != NULL){
		if(strcmp(current->yazarAd, arananYazarAdi) == 0 && strcmp(current->yazarSoyad, arananYazarSoyad) == 0){	
			return current;
		}
		current = current->next;
	}
	
	return NULL;
}

Yazar* yazarSil(Yazar*(*fpYazarBul)(Yazar *head, char* arananYazarAdi, char* arananYazarSoyad), Yazar *head, char* silinenYazarAdi, char* silinenYazarSoyadi, KitapYazar **database, int databaseCount){
	
	Yazar *iter;
	Yazar *silinecekYazar = fpYazarBul(head, silinenYazarAdi, silinenYazarSoyadi);
	int i;

	if(silinecekYazar == NULL){
		printf("Sistemde boyle bir yazar bulunmamaktadir.\n");
	}
	else{
		if(head == silinecekYazar){ 
			head = silinecekYazar->next; 
			free(silinecekYazar);	
		}
		else{
			iter = head; 

			while(iter->next != silinecekYazar){
				iter = iter->next;
			}
			
			iter->next =  iter->next->next;
		}
		dosyaYazYazar(head);
		
		for(i=0; i<databaseCount; i++){
			if(database[i]->YazarID == silinecekYazar->yazarID){
				database[i]->YazarID  = -1;
			}
		}
		
		printf("Yazar  silindi.\n");	
	}

	return head;
}

Yazar* guncelleYazar(Yazar*(*fpYazarBul)(Yazar *head, char* arananYazarAdi, char* arananYazarSoyad),Yazar *head, char* guncYazarAdi, char* guncYazarSoyad ){
	
	Yazar *iter;
	Yazar *guncellenecekYazar = fpYazarBul(head, guncYazarAdi, guncYazarSoyad);
	
	if(guncellenecekYazar == NULL){
		printf("Sistemde boyle bir yazar bulunmamaktadir.\n");
	}	
	else{
		
		iter = head; 
		while(iter != guncellenecekYazar){
			iter = iter->next;
		}
		printf("Guncel adi giriniz:");
		gets(iter->yazarAd);
		printf("Guncel soyadi giriniz:");
		gets(iter->yazarSoyad);
		
		dosyaYazYazar(head);
	}
	
	return head; 
}

//OGRENCI ISLEMLERININ OLDUGU FONKSIYONLAR

void cezaliListele(Ogrenci *node){
	
	if(node != NULL){
		while(node != NULL){
			if(node->puan < 0){
				printf("ID: %s\nAD: %s\nSOYAD: %s\nPUAN: %d\n", node->ogrID, node->ad, node->soyad, node->puan);
			}
			node = node->next;
		}
	}
}

void teslimEtmemisler(KitapOdunc **database, int databaseCount){
	
	int i,j;

	if(databaseCount != 0){
		for(i=0; i<databaseCount; i++){
			
			if(database[i]->islemTipi == 0){
			
				j = i+1;
				
				while(j < databaseCount && strcmp(database[i]->EtiketNo,database[j]->EtiketNo ) !=0){
					
					j++;
				}
				
				if(j == databaseCount){
					printf("ID: %s\n", database[i]->ogrID);
				}	
			}
		}		
		
	}
	else{
		printf("\n\n***Ogrenci listesi bos.\n\n");
	}

}

Ogrenci* ogrenciEkle(Ogrenci *root, char* ogrenciAd, char* ogrenciSoyad, char* ogrenciID, int puan){
	
	Ogrenci* iter;
	
	Ogrenci *yeniOgrenci = (Ogrenci*)malloc(sizeof(Ogrenci));
	if(yeniOgrenci == NULL){ 
    	printf("Bellek yetersiz!\n");
    	exit(1);
  	}
	strcpy(yeniOgrenci->ad, ogrenciAd);
	strcpy(yeniOgrenci->soyad, ogrenciSoyad);
	strcpy(yeniOgrenci->ogrID, ogrenciID);
	yeniOgrenci->puan = puan;
	
	yeniOgrenci->next = NULL;
	
	if(root == NULL){
		root = yeniOgrenci;
		root->prev = NULL;
	}
	else{
		iter = root;
		while(iter->next != NULL){
			iter = iter->next;
			
		}
		yeniOgrenci->prev = iter;
		iter->next = yeniOgrenci;
	}

	return root;

}

void ogrencileriListele(Ogrenci *node){
	
  while (node != NULL){
     printf("\n\nID: %s\nAD: %s\nSOYAD: %s\nPUAN: %d\n", node->ogrID, node->ad, node->soyad, node->puan);
     node = node->next;
  }
}

Ogrenci *ogrenciBul(Ogrenci *root, char* arananOgrenciAdi, char* arananOgrenciSoyad){
	
	Ogrenci *current = root; 
	
	while(current != NULL){
		if(strcmp(current->ad, arananOgrenciAdi) == 0 && strcmp(current->soyad, arananOgrenciSoyad) == 0){
			return current;
		}
		current = current->next;
	}

	return NULL;
}

Ogrenci* ogrenciSil(Ogrenci*(fpOgrenciBul)(Ogrenci *root, char* arananOgrenciAdi, char* arananOgrenciSoyad), Ogrenci *root, char* silinenOgrAdi, char* silinenOgrSoyad){
	
	Ogrenci *iter;
	Ogrenci *silinecekOgrenci = fpOgrenciBul(root, silinenOgrAdi, silinenOgrSoyad);
	
	if(silinecekOgrenci == NULL){
		printf("Sistemde boyle bir ogrenci bulunmamaktadir.\n");
	}
	else{
		
		if((silinecekOgrenci->prev == NULL) && (silinecekOgrenci->next == NULL)){
				
				root = NULL;
			} 
			else if(silinecekOgrenci->prev == NULL){
		
				root = silinecekOgrenci->next;
				root->prev = NULL;
			} 
			else if(silinecekOgrenci->next == NULL){
				
				silinecekOgrenci->prev->next = NULL;
			} 
			else{
				
				silinecekOgrenci->prev->next = silinecekOgrenci->next;
				silinecekOgrenci->next->prev = silinecekOgrenci->prev;
			}
			
			free(silinecekOgrenci);
			printf("Ogrenci  silindi.\n");
	}
			
			dosyaYazOgrenci(root);	
			
			return root;
	}


Ogrenci* guncelleOgrenci(Ogrenci*(fpOgrenciBul)(Ogrenci *root, char* arananOgrenciAdi, char* arananOgrenciSoyad), Ogrenci *root, char* guncOgrAdi, char* guncOgrSoyad){
	
	Ogrenci *iter;
	Ogrenci *guncellenecekOgrenci = fpOgrenciBul(root, guncOgrAdi, guncOgrSoyad);
	
	if(guncellenecekOgrenci == NULL){
		printf("Sistemde boyle bir ogrenci bulunmamaktadir.\n");
	}
	else{
		iter = root;
		while(iter != guncellenecekOgrenci){
			iter = iter->next;
		}
		printf("Guncel adi giriniz:");
		gets(iter->ad);
		printf("Guncel soyadi giriniz:");
		gets(iter->soyad);
		printf("Guncel ID giriniz:");
		gets(iter->ogrID);
		dosyaYazOgrenci(root);
	}
	
	return root;
}

void ogrBilgisi(Ogrenci*(fpOgrenciBul)(Ogrenci *root, char* arananOgrenciAdi, char* arananOgrenciSoyad), Ogrenci* root, char *ogrAd, char *ogrSoyad, KitapOdunc **databaseOdunc, int databaseCount){
	
	Ogrenci *iter;
	int i;
	Ogrenci *arananOgrenci = fpOgrenciBul(root, ogrAd, ogrSoyad);
	
	if(arananOgrenci == NULL){
		printf("\nSistemde boyle bir ogrenci bulunmamaktadir.\n");
	}
	else{
		
		iter = root;
		while(strcmp(iter->ad, arananOgrenci->ad) != 0 && strcmp(iter->soyad, arananOgrenci->soyad) != 0){
			iter = iter->next;	
		}
			
		printf("\n\nAD: %s\nSOYAD: %s\nID: %s\nPuan: %d\n", iter->ad, iter->soyad, iter->ogrID, iter->puan);

		for(i<0; i<databaseCount; i++){
			
			if(strcmp(databaseOdunc[i]->ogrID, arananOgrenci->ogrID) == 0){
				
				if(databaseOdunc[i]->islemTipi == 0){
					printf("\nOdunc alinan kitabin etiket numarasi: %s", databaseOdunc[i]->EtiketNo);
					printf("\nIslem tarihi: Gun: %d Ay: %d Yil: %d", databaseOdunc[i]->islemTarihi.gun,databaseOdunc[i]->islemTarihi.ay,databaseOdunc[i]->islemTarihi.yil );
					
				}
				
				if(databaseOdunc[i]->islemTipi == 1){
					printf("\nTeslim edilen kitabin etiket numarasi: %s", databaseOdunc[i]->EtiketNo);
					printf("\nIslem tarihi: Gun: %d Ay: %d Yil: %d", databaseOdunc[i]->islemTarihi.gun,databaseOdunc[i]->islemTarihi.ay,databaseOdunc[i]->islemTarihi.yil );
					
				}
					
			}
	
		}
		
	}

}

void ogrenciIDara(Ogrenci *root, char *ID, KitapOdunc **databaseOdunc, int databaseCount){
	
	Ogrenci* iter = root;
	int i;
	
	while(strcmp(iter->ogrID, ID) != 0){
		iter = iter->next;
	}
	if(iter->next == NULL){
		printf("Ogrenci yok.");
	}
	else{
		printf("\n\nAD: %s\nSOYAD: %s\nID: %s\nPuan: %d\n", iter->ad, iter->soyad, iter->ogrID, iter->puan);
		
			
		for(i<0; i<databaseCount; i++){
			
			if(strcmp(databaseOdunc[i]->ogrID, iter->ogrID) == 0){
				
				if(databaseOdunc[i]->islemTipi == 0){
					printf("\nOdunc alinan kitabin etiket numarasi: %s", databaseOdunc[i]->EtiketNo);
					printf("\nIslem tarihi: Gun: %d Ay: %d Yil: %d", databaseOdunc[i]->islemTarihi.gun,databaseOdunc[i]->islemTarihi.ay,databaseOdunc[i]->islemTarihi.yil );
					
				}
				
				if(databaseOdunc[i]->islemTipi == 1){
					printf("\nTeslim edilen kitabin etiket numarasi: %s", databaseOdunc[i]->EtiketNo);
					printf("\nIslem tarihi: Gun: %d Ay: %d Yil: %d", databaseOdunc[i]->islemTarihi.gun,databaseOdunc[i]->islemTarihi.ay,databaseOdunc[i]->islemTarihi.yil );
					
				}
					
			}
			
			
		}
		
	}
	
}


Ogrenci* ogrenciIDKontrol(Ogrenci *root, char *ogrID){
	
	Ogrenci *kontrol;
	Ogrenci *sonID = (Ogrenci*)malloc(sizeof(Ogrenci));
	if(sonID == NULL){ 
    	printf("Bellek yetersiz!\n");
    	exit(1);
  	}
	int okay = 1;
					
	if(root != NULL){
		while(okay == 1){
			if(strcmp(root->ogrID, ogrID) == 0){
				printf("\nSistemde ayni ID'ye sahip biri var. Lutfen yeni ID giriniz:\n");
					gets(ogrID);
			}
			else{
				kontrol = root;
				while(kontrol->next != NULL && strcmp(kontrol->ogrID, ogrID) != 0){
					kontrol = kontrol->next;
				}
				if(strcmp(kontrol->ogrID, ogrID) == 0){
					printf("\nSistemde ayni ID'ye sahip biri var. Lutfen yeni ID giriniz:\n");
					gets(ogrID);
				}
				else{
					okay = 0;
				}
			}
		}
	}
	else{
		okay = 0;
	}
	strcpy(sonID->ogrID,ogrID);
	
	return sonID;
}

//DOSYA ISLEMLERI


Yazar *dosyaOkuYazar(Yazar *head, int *yazarID){
	
	char *satir= (char*)malloc(80*sizeof(char));
	if(satir == NULL){ 
    	printf("Bellek yetersiz!\n");
    	exit(1);
  	}
	char *yazarAdi = (char*)malloc(30*sizeof(char));
	if(yazarAdi == NULL){ 
    	printf("Bellek yetersiz!\n");
    	exit(1);
  	}
	char *yazarSoyadi = (char*)malloc(30*sizeof(char));
	if(yazarSoyadi == NULL){ 
    	printf("Bellek yetersiz!\n");
    	exit(1);
  	}

	FILE *fpYazar = fopen("Yazarlar.csv", "r");
	
	if(fpYazar == NULL){
		
		exit(1);
	}
	
	while(fgets(satir, 80, fpYazar) != NULL){
		
		strtok(satir, ",");
		yazarAdi = strtok(NULL, ",");
		yazarSoyadi = strtok(NULL, "\n");
		head = yazarEkle(head, yazarAdi, yazarSoyadi, yazarID);
	}
	
	fclose(fpYazar);
	return head;
}

void dosyaYazYazar(Yazar *head){
	
	FILE *fpYazar = fopen("Yazarlar.csv", "w");
	
	if(fpYazar == NULL){
		exit(1);
	}
	
	Yazar *iter = head;
	
	while(iter->next != NULL){
						
		fprintf(fpYazar, "%d,%s,%s\n", iter->yazarID, iter->yazarAd, iter->yazarSoyad);
		iter = iter->next;
	}
	fprintf(fpYazar, "%d,%s,%s", iter->yazarID, iter->yazarAd, iter->yazarSoyad);		
	
	fclose(fpYazar);
}
		

Ogrenci *dosyaOkuOgrenci(Ogrenci *head ){

	char *satir= (char*)malloc(80*sizeof(char));
	if(satir == NULL){ 
    	printf("Bellek yetersiz!\n");
    	exit(1);
  	}
	char *ogrAdi = (char*)malloc(30*sizeof(char));
	if(ogrAdi == NULL){ 
    	printf("Bellek yetersiz!\n");
    	exit(1);
  	}
	char *ogrSoyadi = (char*)malloc(30*sizeof(char));
	if(ogrSoyadi == NULL){ 
    	printf("Bellek yetersiz!\n");
    	exit(1);
  	}
	char *ogrID = (char*)malloc(20*sizeof(char));
	if(ogrID == NULL){ 
    	printf("Bellek yetersiz!\n");
    	exit(1);
  	}
	int puan;

	FILE *fpOgrenci = fopen("Ogrenciler.csv", "r");
	
	if(fpOgrenci == NULL){
		
		exit(1);
	}
	
	while(fgets(satir, 80, fpOgrenci) != NULL){
		
		ogrID = strtok(satir, ",");
		ogrAdi = strtok(NULL, ",");
		ogrSoyadi = strtok(NULL, ",");
		puan = atoi(strtok(NULL,"\n"));
		
		head = ogrenciEkle(head, ogrAdi, ogrSoyadi, ogrID, puan);
	}
	
	fclose(fpOgrenci);
	return head;
}

void dosyaYazOgrenci(Ogrenci *head){
	
	FILE *fpOgrenci = fopen("Ogrenciler.csv", "w");
	
	if (fpOgrenci == NULL) {
		printf("\nDosya acilamadi.\n");
		exit(1);
	}
	
	Ogrenci *iter = head;
	
	
	while(iter->next != NULL){
						
		fprintf(fpOgrenci, "%s,%s,%s,%d\n",iter->ogrID, iter->ad, iter->soyad,iter->puan );
		iter = iter->next;
	}
	fprintf(fpOgrenci, "%s,%s,%s,%d",iter->ogrID, iter->ad, iter->soyad,iter->puan );		
	
	fclose(fpOgrenci);
}

Kitap *dosyaOkuKitap(Kitap *head){

	char *satir= (char*)malloc(80*sizeof(char));
	if(satir == NULL){ 
    	printf("Bellek yetersiz!\n");
    	exit(1);
  	}
	char *kitapAdi = (char*)malloc(30*sizeof(char));
	if(kitapAdi == NULL){ 
    	printf("Bellek yetersiz!\n");
    	exit(1);
  	}
	char *ISBN = (char*)malloc(30*sizeof(char));
	if(ISBN == NULL){ 
    	printf("Bellek yetersiz!\n");
    	exit(1);
  	}
	int adet;

	FILE *fpKitap = fopen("Kitaplar.csv", "r");
	
	if(fpKitap == NULL){
		
		exit(1);
	}
	
	while(fgets(satir, 80, fpKitap) != NULL){
		
		kitapAdi = strtok(satir, ",");
		ISBN = strtok(NULL, ",");
		adet = atoi(strtok(NULL, "\n"));
		head = kitapEkle(head, kitapAdi, ISBN, &adet);
	}
	
	fclose(fpKitap);
	
	return head;
}


void dosyaYazKitap(Kitap *head){
	
	FILE *fpKitap = fopen("Kitaplar.csv", "w");
	
	if (fpKitap == NULL) {
		printf("\nDosya acilamadi.\n");
		exit(1);
	}
	
	Kitap *iter = head;
	
	while(iter->next != NULL){
						
		fprintf(fpKitap, "%s,%s,%d\n", iter->kitapAdi, iter->ISBN, iter->adet);
		iter = iter->next;
	}
	fprintf(fpKitap, "%s,%s,%d", iter->kitapAdi, iter->ISBN, iter->adet);	
	
	fclose(fpKitap);
}


KitapYazar **dosyaOkuKitapYazar(KitapYazar **database, int *databaseCount){

	char *satir= (char*)malloc(40*sizeof(char));
	if(satir == NULL){ 
    	printf("Bellek yetersiz!\n");
    	exit(1);
  	}
	char *kitapISBN = (char*)malloc(30*sizeof(char));
	if(kitapISBN == NULL){ 
    	printf("Bellek yetersiz!\n");
    	exit(1);
  	}
	int yazarID;

	FILE *fpKitap = fopen("KitapYazar.csv", "r");
	if (fpKitap == NULL) {
		printf("\nDosya acilamadi.\n");
	exit(1);
	}
	
	while(fgets(satir, 40, fpKitap) != NULL){
		
		kitapISBN = strtok(satir, ",");
		yazarID = atoi(strtok(NULL, "\n"));
		database = (KitapYazar**)realloc(database,(*databaseCount+1)*sizeof(KitapYazar*));
		database[*databaseCount] = kitabinYazari(kitapISBN,yazarID);
		(*databaseCount)++;
	}
	
	fclose(fpKitap);
	
	return database;
}

void dosyaYazKitapYazar(KitapYazar **database, int *databaseCount){
	
	FILE *fpKitap = fopen("KitapYazar.csv", "w");
	
	if (fpKitap == NULL) {
		printf("\nDosya acilamadi.\n");
		exit(1);
	}

	int i;
	
	
	for(i=0 ; i<(*databaseCount)-1; i++){
		fprintf(fpKitap, "%s,%d\n", database[i]->ISBN, database[i]->YazarID);

	}
	
	fprintf(fpKitap, "%s,%d", database[i]->ISBN, database[i]->YazarID);	
	
	fclose(fpKitap);
}

void dosyaYazKitapOdunc(KitapOdunc **database, int *databaseCount){
	
	FILE *fpKitap = fopen("KitapOdunc.csv", "w");
	
	if (fpKitap == NULL) {
		printf("\nDosya acilamadi.\n");
		exit(1);
	}
	
	int i;

	for(i=0 ; i<(*databaseCount)-1; i++){
		fprintf(fpKitap, "%s,%s,%d,%d.%d.%d\n", database[i]->EtiketNo , database[i]->ogrID, database[i]->islemTipi,database[i]->islemTarihi.gun,database[i]->islemTarihi.ay,database[i]->islemTarihi.yil);

	}
		fprintf(fpKitap, "%s,%s,%d,%d.%d.%d\n", database[i]->EtiketNo , database[i]->ogrID, database[i]->islemTipi,database[i]->islemTarihi.gun,database[i]->islemTarihi.ay,database[i]->islemTarihi.yil);
	
	fclose(fpKitap);
}


