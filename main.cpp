#include <graphics.h>
#include <stdlib.h>
#include <stdio.h>


// Çizilen karenin komşu olmaması gereken bir kare varsa o kareyi çizdirmez
bool komsu_kontrol(int x,int y,int m ){

    int n=10*m;
    int komsu_renk,komsu_renk1,komsu_renk2; // Çizilecek karenin komsu olmaması gereken karlerin renkleri

    if(m==4){
        komsu_renk=7;
        komsu_renk1=7;
        komsu_renk2=7;
    }
    else if(m==8){
        komsu_renk=7;
        komsu_renk1=2;
        komsu_renk2=7;
    }
    else if(m==16){
        komsu_renk=7;
        komsu_renk1=2;
        komsu_renk2=6;
    }

    // Karenin üstündeki ve altındaki komşuları kontrol eder.Komşu olmaması gereken bir kare varsa "0" döndürür.
    for(int i=x;i<x+n-5;i+=20){
        if(getpixel(i,y-10)==komsu_renk || getpixel(i,y-10)==komsu_renk1 || getpixel(i,y-10)==komsu_renk2 ){
            return 0;
        }
        if(getpixel(i,y+n)==komsu_renk ||getpixel(i,y+n)==komsu_renk1 ||getpixel(i,y+n)==komsu_renk2){
            return 0;
        }
    }

    // Kare sağındaki ve solundaki komşuları kontrol eder.Komşu olmaması gereken bir kare varsa "0" değerini döndürür.
    for(int i=y;i<y+n-5;i+=20){
        if(getpixel(x-10,i)==komsu_renk || getpixel(x-10,i)==komsu_renk1 || getpixel(x-10,i)==komsu_renk2){
            return 0;
        }
        if(getpixel(x+n,i)==komsu_renk || getpixel(x+n,i)==komsu_renk1 || getpixel(x+n,i)==komsu_renk2){
            return 0;
        }
    }

    // Etrafında komşu olmaması gereken bir kare yoksa "1" değerini dödürür.
    return 1;
}

//Çizilen şekli karelere ayırır
int kare_ciz(int m,int kx,int ky,int bx,int by){

    int n=10*m;//çizilecek karenin boyutu
    int renk,kont_renk;//çizilecek karenin rengi ve çizileceği bölgenin rengi
    int cnt=0;//çizilen kare sayısı

    if(m==2){
        renk=2;
        kont_renk=7;
    }
    else if(m==4){
       renk=6;
       kont_renk=2;
    }
    else if(m==8){
       renk=5;
       kont_renk=6;
    }
    else if(m==16){
        renk=4;
        kont_renk=5;
    }


    for(int i=kx+5;i<=by+100;i+=n){
         for(int j=ky+5;j<=by+100;j+=n){
            if((getpixel(i,j)==kont_renk && getpixel(i,j+n-10)==kont_renk )&& (getpixel(i+n-10,j+n-10)==kont_renk && getpixel(i+n-10,j)==kont_renk) && komsu_kontrol(i,j,m)){
                int Kare[]={i-5,j-5,i-5,j+n-5,i+n-5,j+n-5,i+n-5,j-5,i-5,j-5};
                setcolor(0);
                setfillstyle(1,renk);
                fillpoly(5,Kare);
                cnt++;
            }
        }
    }

    for(int i=kx+5;i<=bx+100;i+=n/2){
         for(int j=ky+5;j<=by+100;j+=n/2){
            if((getpixel(i,j)==kont_renk && getpixel(i,j+n-10)==kont_renk )&& (getpixel(i+n-10,j+n-10)==kont_renk && getpixel(i+n-10,j)==kont_renk) && komsu_kontrol(i,j,m)){
                int Kare[]={i-5,j-5,i-5,j+n-5,i+n-5,j+n-5,i+n-5,j-5,i-5,j-5};
                setcolor(0);
                setfillstyle(1,renk);
                fillpoly(5,Kare);
                cnt++;
            }
        }
    }



    return cnt;

}


// Bu işlev, veriyi alır ve bir dizeye kopyalar.
size_t dizicmp(void *contents, size_t size, size_t nmemb, void *userp) {
    size_t total_size = size * nmemb;
    char *data = (char *)userp;

    // Veriyi çıkış dizisine kopyala
    strncpy(data, (char *)contents, total_size);

    return total_size;
}

int main() {

        CURL *xy_url;
        CURLcode xy_veri;

    char url[] ="http://abilgisayar.kocaeli.edu.tr/prolab1/prolab1.txt"; // Veriyi almak istediğiniz URL
    char data[1024]; // Alınan verinin saklanacağı dize

    xy_url = curl_easy_init();//CURL nesnesi oluşturur

    if (xy_url) {

        curl_easy_setopt(xy_url, CURLOPT_URL, url);//CURL nesnesine indirilecek verinin URL'sini ayarlar.
        curl_easy_setopt(xy_url, CURLOPT_WRITEFUNCTION, dizicmp);//CURL nesnesine verinin indirildikten sonra nasıl işleneceğini belirten bir işlevi ayarlar
        curl_easy_setopt(xy_url, CURLOPT_WRITEDATA, data);//

        //CURL nesnesi tarafından tanımlanan URL'den veriyi indirir ve xy_veri değişkenine işlem sonucunu atar. Eğer işlem başarılı olursa, xy_veri değişkeni CURLE_OK ile doldurulur.
        xy_veri = curl_easy_perform(xy_url);

        //Verinin alınıp alınmadığını kontrol eder
        if (xy_veri != CURLE_OK) {
            printf("Veri alinamadi...");
        } else {
            printf("\n%s\n", data);
        }

        curl_easy_cleanup(xy_url);//CURL nesnesini temizler ve kaynakları serbest bırakır. Bu, işlem tamamlandığında bellek sızıntısını önlemek için önemlidir
    }



    int str_no=0; //  koordinatlarin alýnacaðý satýr numarasý
    float sndj=0; // birim sondaj maliyeti
    float pltfrm=0; // birim platform maliyeti



    //kullaanicidan  birim sondaj maliyetini ve birim platform maliyeti deðerlerini alma.
    printf("\nKacinci satirdaki alani cizdirmek istiyorsunuz?\n");
    scanf("%d",&str_no);


    printf("\nBirim sondaj maliyetini giriniz:");

    do{
        printf("(Birim sondaj maliyeti 1 ile 10 arasinda olmalidir...)\n");
        scanf("%f",&sndj);
        }while(sndj<1 || sndj>10);


    printf("Birim platform maliyetini giriniz:\n");
    scanf("%f",&pltfrm);

    //istenilen satırı ayırma
    char *satir=strtok(data,"\n");
    int st=0;
    while(satir != NULL && st<str_no){

        strcpy(data,satir);
        satir = strtok(NULL,"\n");
        st++;
    }


    int koordinat[strlen(data)]={0};//x ve y değerlerinin tutulacağı dizi

    //istenilen satırdaki x ve y değerlerini koordinat dizisine atama
    int koordinat_sayayc = 0;
    char *ptr = data;
    while (*ptr!=NULL) {
        if (*ptr == 'B') {
            ptr++; // 'B' karakterini atlıyoruz
            while (*ptr != 'F') {
                if (*ptr == '(') {
                    int x, y;
                    sscanf(ptr, "(%d,%d)", &x, &y) ;
                    koordinat[koordinat_sayayc] = x;
                    koordinat[koordinat_sayayc+1] = y;
                    koordinat_sayayc+=2;
                }
                ptr++;
            }
        }
        ptr++;
    }



     //dizinin eleman sayısını bulma
     int u=0;//koordinat dizisinin uzunluğu
     for(int i=0;i<strlen(data);i++){
        if(koordinat[i]==NULL){
            u=i;
            break;
        }
     }


    //birim karelere oranlı bir çizim yapabilmek için x ve y değerlerini 10 ile çarpıyoruz
    for(int i=0;i<u;i++){
        koordinat[i]=koordinat[i]*10;
    }


    initwindow(1000,1000);// çizim penceresi açma

    //arka planın rengini beyaz yap
    setbkcolor(15);
    cleardevice();

    // Cizim penceresini  10x10'luk birim karelere ayır
     for (int i = 0; i < 1000; i+=10) {
        for (int j = 0; j < 1000; j+=10) {

            setcolor(8);
            rectangle(i , j , i + 10, j + 10 );

        }
    }

    //verilen koordinatların oluşturduğu şekilleri ekrana çizme
    int sekil_xy[u];
    int ilk_n[2]{koordinat[0],koordinat[1]};//şeklin ilk noktasının koordinatlarının  karşılaştırma yapabilmek için tutulacağı dizi
    int s=0;

    //Bir satırdaki birden fazla şekilleri ayırıp çizer
     for(int i=2;i<=u;i+=2){
        if(ilk_n[0]==koordinat[i] && ilk_n[1]==koordinat[i+1]){

            int t=0;

            for( t=0;t<=i+1-s;t++){
                sekil_xy[t]=koordinat[t+s];//koordinat dizisindeki  her bir sekil icin  x ve y'leri sekil_xy dizisine ata
           }

            s=s+t;//sıradaki şeklin koordinatlarının dizideki başlangıç indisini bulmak için
            //Şekli çiz
            setcolor(15);
            setfillstyle(1,0);
            fillpoly(t/2,sekil_xy);
            //karşılaştırma yapılan noktayı değiştirir
            ilk_n[0]=koordinat[i+2];
            ilk_n[1]=koordinat[i+3];
            i+=2;
        }
    }


    //Çizilen şekilleri birim karelere ayırıp alanı bulma
     int alan=0;

     for (int i = 0; i <= 1000; i++) {
        for (int j = 0; j <= 1000; j++) {

            if(getpixel(i,j)== 0){

                int kx=i-(i%10);
                int ky=j-(j%10);

                int alanKare[]={kx,ky,kx,ky+10,kx+10,ky+10,kx+10,ky,kx,ky};

                setcolor(8);
                setfillstyle(1,7);
                fillpoly(5,alanKare);

                alan++;
            }
        }
    }


    printf("\nalan:%d",alan);


    float kynk_rzrv=10*alan;//kaynak rezerv miktarı

    printf("\nKaynak rezerv miktari : %.2f",kynk_rzrv);


    //ikinci çizime geç
    getch();

   //en küçük x ve y dğerlerini bulma
    int enKucukX,enKucukY,enBuyukX,enBuyukY;//koordinatlar arsındaki en küçük x ve y değerleri

    enKucukX=koordinat[0];
    enKucukY=koordinat[1];
    enBuyukX=koordinat[0];
    enBuyukY=koordinat[1];

    for(int i=0;i<u;i+=2){
        if(koordinat[i]<enKucukX)
            enKucukX=koordinat[i];
        if(koordinat[i+1]<enKucukY)
            enKucukY=koordinat[i+1];
        if(koordinat[i]>enBuyukX)
            enBuyukX=koordinat[i];
        if(koordinat[i+1]>enBuyukY)
            enBuyukY=koordinat[i+1];
    }


    //parsellere ayırma ve platform sayısnı bulma
     int cnt_plt=alan;//kurulacak platform sayısı
     int cnt;
     cnt=kare_ciz(2,enKucukX,enKucukY,enBuyukX,enBuyukY);
     cnt_plt-=cnt*3;
     cnt=kare_ciz(4,enKucukX,enKucukY,enBuyukX,enBuyukY);
     cnt_plt-=cnt*3;
     cnt=kare_ciz(8,enKucukX,enKucukY,enBuyukX,enBuyukY);
     cnt_plt-=cnt*3;
     cnt=kare_ciz(16,enKucukX,enKucukY,enBuyukX,enBuyukY);
     cnt_plt-=cnt*3;



     printf("\n\nplatform sayisi:%d",cnt_plt);
     printf("\n\ntoplam sondaj sayisi: %d",alan);

     float top_plt=pltfrm*cnt_plt;
     printf("\n\nplatform maliyeti: %.2f",top_plt);

     float top_snd=sndj*alan;
     printf("\n\nsondaj maliyeti: %.2f",top_snd);

     float top_maliyet=top_plt+top_snd;
     printf("\n\ntoplam maliyet: %.2f",top_maliyet);

     float kar=kynk_rzrv-top_maliyet;
     printf("\n\ntoplam kar miktari: %.2f",kar);



    //çizim penceresini kapat
    getch();
    closegraph();

    return 0;
}

