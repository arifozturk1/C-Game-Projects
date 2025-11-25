#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

void rastgeleRenkUret(char* C);
int tahminAl(char* tahmin);
int sonucDegerlendir(char* hedef, char* tahmin, int* dyer, int* yyer);

int main() {
    srand(time(NULL));
    
    char C[5];
    char tahmin[10];
    int hak, dyer, yyer;
    int tut;

    //Oyun Baþlangýcý
    rastgeleRenkUret(C); 
    
	printf("Renkler: R=Red G=Green B=Blue Y=Yellow P=Purple O=Orange\n");
	printf("Bilgisayarin Tuttugu Renk Gorunsun mu?(1:Evet 2:Hayir):");
    scanf("%d", &tut);
    if(tut == 1) printf("Bilgisayarin Tuttugu Renk: %s\n", C);

	printf("\nTahmin Hakki Giriniz:"); //Tahmin Hakký Belirleme
	scanf("%d",&hak);

    //Oyun döngüsü
    while(hak > 0) {
        printf("\nKalan Hak: %d\n", hak);
        
        
        if (!tahminAl(tahmin)) { 
            continue; 
        }

        // Tahmin kontrol
        if (sonucDegerlendir(C, tahmin, &dyer, &yyer)) {
            printf("Bilgisayarin tuttugu renkler:%s\n",C);
            printf("Oyuncu kazandi.");
            return 0;
        }

		else if(dyer==0 && yyer==0){
    		printf("Dogru tahmin yok.\n");
    	} 
		else{
			if (dyer > 0 && yyer > 0)
            	printf("%d rengin yeri dogru, %d rengin yeri yanlis\n",dyer,yyer);
            else if (dyer > 0)
                printf("%d rengin yeri dogru\n",dyer);
            else
                printf("%d rengin yeri yanlis\n",yyer);
    	}

        hak--;
    }

	printf("Tahmin hakkiniz bitti. Bilgisayarin tuttugu renk: %s\n", C);
	return 0;
}

void rastgeleRenkUret(char* C) { //Bilgisayara rastgele 4 renk seçtirme
	int i, color;
    for(i=0; i<4; i++){   
        color = 1 + rand() % 6;
        switch(color){
            case 1: C[i]='R'; break;
            case 2: C[i]='Y'; break;
            case 3: C[i]='G'; break;
            case 4: C[i]='B'; break;
            case 5: C[i]='O'; break;
            case 6: C[i]='P'; break;
        }   
    }
    C[4] = '\0'; 
}

int tahminAl(char* tahmin) {
    printf("Tahmininiz: ");
    scanf("%s", tahmin);
    
	if(strlen(tahmin) != 4) { // Dogru olmayan karakter sayýsý
        printf("Lutfen 4 renk giriniz!\n");
        return 0; 
    }

    for(int i=0; i<4; i++){ //Geçersiz Karakter
        char c = tahmin[i];
        if (c!='R' && c!='G' && c!='B' && c!='Y' && c!='P' && c!='O'){
            printf("Yanlis giris,gecerli renkleri kullanin! (R,G,B,Y,P,O)\n");
            return 0; 
        }
    }

    return 1; 
}

int sonucDegerlendir(char* hedef, char* tahmin, int* dyer, int* yyer) {
    *dyer = 0;
    *yyer = 0;

    int dogruYerde[4] = {0, 0, 0, 0}; 
    int tahminYer[4] = {0, 0, 0, 0};  
    int i, j;
    
    for(i=0; i<4; i++){ //Doðru renk ve doðru yer kontrol 
        if (hedef[i] == tahmin[i]){
            (*dyer)++;
            dogruYerde[i] = 1;
            tahminYer[i] = 1;
        }
    }

    for(i=0; i<4; i++){ // Renk doðru ama yer yanlýþ kontrol
        if (tahminYer[i] == 0){ 
            for (j=0; j<4; j++){
                if (dogruYerde[j] == 0 && tahmin[i] == hedef[j]){
                    (*yyer)++;
                    dogruYerde[j] = 1;
                    break;
                }
            }
        }
    }

    if (*dyer == 4) return 1; // Kazanma
    return 0;
}
