#include <graphics.h>
#include <conio.h>
#include <stdio.h>
#include <string.h>
// Global Degiskenler
void envanter();
void personel();
int selected = 0;

// Structure Yapilari
struct KullaniciBilgileri // Sistemde öncesinde kayýt edilmiþ olan kullanýcý verisi
{
    char kullaniciAdi[20];
    char sifre[20];
};

struct Dogrulama // Giris ekranina girilen verinin kayit edildigi alan
{
    char dosyaKullaniciAdi[20];
    char dosyaSifre[20];
};

struct silahEnvanter 
{
    char silahAdi[30];
    char silahKodu[30];
    char silahSayi[10];
};
struct personelSayisi
{
    char personalAdi[30];
    char personelSoyadi[30];
    char personelBolge[30];
};
struct KullaniciBilgileri giris[10];
struct Dogrulama list[10];
struct silahEnvanter bilgi[10];
struct silahEnvanter envanterListesi[10];
struct personelSayisi personelListesi[10];

// Fonksiyonlar
void gosterBilgi() // uygulama icerisinde aktif kullanicinin kim oldugunu gosterir
{
    char gosterStr[50];
    char gosterStr1[50];
    sprintf(gosterStr, "%s", giris[0].kullaniciAdi);
    outtextxy(300, 350, gosterStr);
}
void menuCiz(int selected) // selected renk degistirme parametresidir. bu giris ekranindan sonraki menuyu cizer
{
    setcolor(WHITE);
    setfillstyle(WIDE_DOT_FILL, GREEN);
    bar(0, 0, getmaxx(), getmaxy());

    if (selected == 1)
        setfillstyle(XHATCH_FILL, RED);
    else
        setfillstyle(XHATCH_FILL, LIGHTGREEN);
    bar(50, 40, 581, 100);
    setcolor(WHITE);
    rectangle(50, 40, 581, 100);
    settextstyle(BOLD_FONT, HORIZ_DIR, 1);
    outtextxy(110, 60, "MEVO   TECH  ASKERÝ VERÝ SÝSTEMÝ");

    if (selected == 2)
        setfillstyle(XHATCH_FILL, RED);
    else
        setfillstyle(XHATCH_FILL, LIGHTMAGENTA);
    bar(50, 150, 300, 250);
    setcolor(WHITE);
    rectangle(50, 150, 300, 250);
    outtextxy(120, 175, "  SÝLAH  ");
    outtextxy(100, 200, "ENVANTERÝ");

    if (selected == 3)
        setfillstyle(XHATCH_FILL, RED);
    else
        setfillstyle(XHATCH_FILL, LIGHTBLUE);
    bar(331, 150, 581, 250);
    setcolor(WHITE);
    rectangle(331, 150, 581, 250);
    outtextxy(380, 175, "PERSONEL");
    outtextxy(380, 200, "BÝLGÝLERÝ");

    if (selected == 4)
        setfillstyle(XHATCH_FILL, RED);
    else
        setfillstyle(XHATCH_FILL, LIGHTCYAN);
    bar(50, 300, 581, 400);
    setcolor(WHITE);
    rectangle(50, 300, 581, 400);
    ellipse(90, 340, 0, 360, 20, 20);
    pieslice(90, 390, 0, 180, 30);
    outtextxy(150, 320, "Aktif Oturum");
    outtextxy(150, 350, "Kullanýcý Adý:");
    gosterBilgi();
}

void girdiAl(char *girdiBuffer, int bufferUzunlugu, int x, int y)
// metin girdisi alýr *girdiBuffer olarak bir metin dizisi gonderikir.
{
    int i = 0;
    char ch;
    while (1)
    {
        ch = getch();
        if (ch == 13)
        {
            girdiBuffer[i] = '\0';
            break;
        }
        else if (ch == 8)
        {
            if (i > 0)
            {
                i--;
                girdiBuffer[i] = '\0';
                setfillstyle(SOLID_FILL, BLACK);
                bar(x + i * 10, y, x + (i + 1) * 10, y + 20);
            }
        }
        else if (i < bufferUzunlugu - 1)
        {
            girdiBuffer[i] = ch;
            char tempStr[2] = {ch, '\0'};
            strset(tempStr, '*');
            outtextxy(x + i * 10, y, tempStr);
            i++;
        }
    }
}

void girdiAlEkle(char *girdiBuffer, int bufferUzunlugu, int x, int y)
{
    int i = 0;
    char ch;
    while (1)
    {
        ch = getch();
        if (ch == 13)
        {
            girdiBuffer[i] = '\0';
            break;
        }
        else if (ch == 8)
        {
            if (i > 0)
            {
                i--;
                girdiBuffer[i] = '\0';
                setfillstyle(SOLID_FILL, 5);
                bar(x + i * 10, y, x + (i + 1) * 10, y + 20);
            }
        }
        else if (i < bufferUzunlugu - 1)
        {
            girdiBuffer[i] = ch;
            char tempStr[2] = {ch, '\0'};
            outtextxy(x + i * 10, y, tempStr);
            i++;
        }
    }
}

void dosyayaYaz(struct KullaniciBilgileri open)
{
    FILE *gecici = fopen("girisLogKayitlari.txt", "a");
    if (gecici == NULL)
    {
        printf("Dosya açilamadi.\n");
    }
    else
    {
        fprintf(gecici, "%s %s\n", open.kullaniciAdi, open.sifre);
        fclose(gecici);
        printf("Bilgiler dosyaya yazildi.\n");
    }
}
void goster()
{
    char gosterStr[50];
    char gosterStr1[50];
    sprintf(gosterStr, "%s     ", giris[0].kullaniciAdi);
    outtextxy(212, 195, gosterStr);
    sprintf(gosterStr1, "%s     ", giris[0].sifre);
    outtextxy(212, 265, gosterStr1);
}

void girisTasarimi()
{
    setfillstyle(XHATCH_FILL, LIGHTGREEN);
    bar(0, 0, getmaxx(), getmaxy());

    setfillstyle(WIDE_DOT_FILL, GREEN);
    bar(200, 120, 466, 350);
    rectangle(204, 124, 460, 344);
    outtextxy(207, 130, "MevoTech Askeri Veri Sistemi");
    outtextxy(207, 165, "Kullanici Adi:");
    rectangle(207, 185, 455, 215);
    outtextxy(207, 235, "Sifre:");
    rectangle(207, 255, 455, 285);

    setfillstyle(SOLID_FILL, BLACK);
    bar(207, 300, 307, 330);
    setcolor(WHITE);
    rectangle(207, 300, 307, 330);
    outtextxy(214, 310, "GIRIS YAP");

    bar(320, 300, 450, 330);
    rectangle(320, 300, 455, 330);
    outtextxy(327, 310, "SIFRE GOSTER");

    setfillstyle(WIDE_DOT_FILL, GREEN);
    bar(80, 360, 600, 420);
    outtextxy(315, 365, "UYARI!");

    outtextxy(85, 390, "Kullanici adi ve Sifrenizi girdikten sonra Enter'a Basin");
    girdiAl(giris[0].kullaniciAdi, 25, 215, 195);
    girdiAl(giris[0].sifre, 25, 215, 265);
}
void sistemeGiris()
{
    FILE *sabitVeri = fopen("kayitlikisi.txt", "r");
    if (sabitVeri == NULL)
    {
        outtextxy(getmaxx() / 2, getmaxy() / 2, "Dosya Okunamadi");
    }

    int found = 0, i=0;
    
    while (fscanf(sabitVeri, "%s %s", list[i].dosyaKullaniciAdi, list[i].dosyaSifre) != EOF)
    {
        if (strcmp(giris[i].kullaniciAdi, list[i].dosyaKullaniciAdi) == 0 && strcmp(giris[i].sifre, list[i].dosyaSifre) == 0)
        {
            found = 1;
            break;
        }
        i++;
    }
    fclose(sabitVeri);

    if (found)
    {
        outtextxy(getmaxx() / 2, getmaxy() / 2, "Tebrikler");

        while (1)
        {
            menuCiz(selected);

            int x, y;
            if (ismouseclick(WM_LBUTTONDOWN))
            {
                getmouseclick(WM_LBUTTONDOWN, x, y);
                if (x >= 50 && x < 581 && y >= 40 && y < 100)
                {
                    selected = 1;
                }
                else if (x >= 50 && x < 300 && y >= 150 && y < 250)
                {
                    selected = 2;
                    envanter();
                }
                else if (x >= 331 && x < 581 && y >= 150 && y < 250)
                {
                    selected = 3;
                    personel();
                }
                else if (x >= 50 && x < 581 && y >= 300 && y < 400)
                {
                    selected = 4;
                }
                else
                {
                    selected = 0;
                }
            }

            delay(250);
        }
    }
    else
    {
        outtextxy(150, 100, "Giris Bilgileri Hatali. Tekrar Deneyiniz!");
        delay(2000);
        girisTasarimi();
        dosyayaYaz(*giris);
    }
}

void ekle()
{
    closegraph();
    int gd = DETECT, gm;
    initgraph(&gd, &gm, "");
    int a = 0;

    while (1)
    {
        setfillstyle(XHATCH_FILL, GREEN);
        bar(0, 0, getmaxx(), getmaxy());

        settextstyle(GOTHIC_FONT, HORIZ_DIR, 2);
        outtextxy(150, 20, "Silah Ekleme Ekrani");

        settextstyle(DEFAULT_FONT, HORIZ_DIR, 1);
        outtextxy(20, 100, "Silah Adi:");
        girdiAlEkle(bilgi[a].silahAdi, 30, 20, 120);
        outtextxy(20, 150, "Silah Kodu:");
        girdiAlEkle(bilgi[a].silahKodu, 30, 20, 170);
        outtextxy(20, 200, "Silah Sayisi:");
        girdiAlEkle(bilgi[a].silahSayi, 10, 20, 220);

        FILE *gecici = fopen("silahEnvanteri.txt", "a+");
        if (gecici == NULL)
        {
            printf("Dosya açilamadi.\n");
        }
        else
        {
            fprintf(gecici, "%s %s %s\n", bilgi[a].silahAdi, bilgi[a].silahKodu, bilgi[a].silahSayi);
            fclose(gecici);
            outtextxy(20, 270, "Bilgiler kaydedildi. Devam Etmek Istiyor Musunuz?");
            setfillstyle(USER_FILL, LIGHTGREEN);
            bar(20, 290, 140, 330);
            bar(160, 290, 280, 330);
            settextstyle(COMPLEX_FONT, HORIZ_DIR, 2);
            outtextxy(30, 300, "EVET");
            outtextxy(170, 300, "ANA MENU");

            delay(3000);

            int x, y;
            getmouseclick(WM_LBUTTONDOWN, x, y);
            if (x > 20 && x < 140 && y > 290 && y < 330)
            {
                a++;
            }
            else if (x > 160 && x < 280 && y > 290 && y < 330)
            {
                closegraph();
                int gd = DETECT, gm;
                initgraph(&gd, &gm, "");
                envanter();
            }
        }
    }
}
void tabloCiz(struct silahEnvanter *envanterListesi, int silahSayisi)
{
    int x = 50, y = 200;
    setfillstyle(XHATCH_FILL, WHITE);
    bar(0, 0, getmaxx(), getmaxy());

    int gen = ((441 - textwidth("ASKERI SILAH ENVANTERI")) / 2), yuk = ((80 - textheight("ASKERI SILAH ENVANTERI")) / 2);

    setfillstyle(LTBKSLASH_FILL, DARKGRAY);
    bar(100, 20, 541, 100);

    settextstyle(GOTHIC_FONT, HORIZ_DIR, 2);
    outtextxy(gen - 5, yuk + 15, "ASKERÝ SÝLAH ENVANTERÝ");

    bar(100, 105, 190, 125);
    bar(195, 105, 285, 125);
    bar(290, 105, 380, 125);
    settextstyle(DEFAULT_FONT, HORIZ_DIR, 1);
    outtextxy(102, 105, "Ana Sayfa");
    outtextxy(200, 105, "Ekle");
    outtextxy(300, 105, "Sil");
    // setcolor(BLACK);
    rectangle(40, 170, getmaxx() - 40, y + (silahSayisi + 1) * 30);

    // Baslik
    // setcolor(WHITE);
    setfillstyle(SOLID_FILL, DARKGRAY);
    bar(40, 170, getmaxx() - 40, 200);
    // setcolor(BLACK);
    settextstyle(DEFAULT_FONT, HORIZ_DIR, 1);
    outtextxy(50, 180, "Silah Adi");
    outtextxy(250, 180, "Silah Kodu");
    outtextxy(450, 180, "Silah Sayisi");

    // Içerik
    for (int i = 0; i < silahSayisi; i++)
    {
        // setcolor(BLACK);
        setfillstyle(SOLID_FILL, LIGHTGRAY);
        bar(40, y + (i * 30), getmaxx() - 40, y + ((i + 1) * 30));
        // setcolor(BLACK);
        rectangle(40, y + (i * 30), getmaxx() - 40, y + ((i + 1) * 30));

        outtextxy(50, y + (i * 30) + 5, envanterListesi[i].silahAdi);
        outtextxy(250, y + (i * 30) + 5, envanterListesi[i].silahKodu);
        outtextxy(450, y + (i * 30) + 5, envanterListesi[i].silahSayi);
    }
}
void envanter()
{
    delay(1000);
    closegraph();
    int gd = DETECT, gm;
    initgraph(&gd, &gm, "");

    int silahSayisi = 0;

    FILE *gecici = fopen("silahEnvanteri.txt", "r");
    if (gecici == NULL)
    {
        printf("Dosya açilamadi.\n");
    }
    else
    {
        while (fscanf(gecici, "%s %s %s", envanterListesi[silahSayisi].silahAdi, envanterListesi[silahSayisi].silahKodu, envanterListesi[silahSayisi].silahSayi) != EOF)
        {
            silahSayisi++;
        }
        fclose(gecici);
    }

    tabloCiz(envanterListesi, silahSayisi);

    while (1)
    {
        delay(5);
        if (ismouseclick(WM_LBUTTONDOWN))
        {
            int x, y;
            getmouseclick(WM_LBUTTONDOWN, x, y);
            if (x > 100 && x < 190 && y > 105 && y < 125)
            {
                closegraph();
                int gd = DETECT, gm;
                initgraph(&gd, &gm, "");
                setcolor(WHITE);
                menuCiz(selected);
                sistemeGiris();
            }
            else if (x > 195 && x < 285 && y > 105 && y < 125)
            {
                ekle();
            }
            else if(x > 290 && x < 380 && y > 105 && y < 125)
            {
            outtextxy(100,145,"Bu Fonksiyon Suan Devre Dýþýdýr.");	
			}
        }
        setcolor(WHITE);
    }

    getch();
    closegraph();
}

void ekle2()
{
    closegraph();
    int gd = DETECT, gm;
    initgraph(&gd, &gm, "");
    int a = 0;

    while (1)
    {
        setfillstyle(XHATCH_FILL, GREEN);
        bar(0, 0, getmaxx(), getmaxy());

        settextstyle(GOTHIC_FONT, HORIZ_DIR, 2);
        outtextxy(150, 20, "Personel Ekleme Ekrani");

        settextstyle(DEFAULT_FONT, HORIZ_DIR, 1);
        outtextxy(20, 100, "Personel Adý:");
        girdiAlEkle(personelListesi[a].personalAdi, 30, 20, 120);
        outtextxy(20, 150, "Personel Soyadý:");
        girdiAlEkle(personelListesi[a].personelSoyadi, 30, 20, 170);
        outtextxy(20, 200, "Personel Bölgesi:");
        girdiAlEkle(personelListesi[a].personelBolge, 10, 20, 220);

        FILE *gecici = fopen("personelListesi.txt", "a+");
        if (gecici == NULL)
        {
            printf("Dosya açilamadi.\n");
        }
        else
        {
            fprintf(gecici, "%s %s %s\n", personelListesi[a].personalAdi, personelListesi[a].personelSoyadi, personelListesi[a].personelBolge);
            fclose(gecici);
            outtextxy(20, 270, "Bilgiler kaydedildi. Devam Etmek Istiyor Musunuz?");
            setfillstyle(USER_FILL, LIGHTGREEN);
            bar(20, 290, 140, 330);
            bar(160, 290, 280, 330);
            settextstyle(COMPLEX_FONT, HORIZ_DIR, 2);
            outtextxy(30, 300, "EVET");
            outtextxy(170, 300, "ANA MENU");

            delay(3000);

            int x, y;
            getmouseclick(WM_LBUTTONDOWN, x, y);
            if (x > 20 && x < 140 && y > 290 && y < 330)
            {
                a++;
            }
            else if (x > 160 && x < 280 && y > 290 && y < 330)
            {
                closegraph();
                int gd = DETECT, gm;
                initgraph(&gd, &gm, "");
                personel();
            }
        }
    }
}
void tabloCiz2(personelSayisi *personelListesi, int personelSayisi)
{

    int x = 50, y = 200;
    setfillstyle(XHATCH_FILL, WHITE);
    bar(0, 0, getmaxx(), getmaxy());

    int gen = ((441 - textwidth("ASKERÝ PERSONEL LÝSTESÝ")) / 2), yuk = ((80 - textheight("ASKERÝ PERSONEL LÝSTESÝ")) / 2);
    // setfillstyle(LTSLASH_FILL, LIGHTGREEN);
    // bar(0, 0, getmaxx(), getmaxy());

    // setfillstyle(INTERLEAVE_FILL, BLACK);

    setfillstyle(USER_FILL, BLACK);
    bar(100, 20, 541, 100);
    settextstyle(GOTHIC_FONT, HORIZ_DIR, 2);
    outtextxy(gen - 5, yuk + 15, "ASKERÝ PERSONEL LÝSTESÝ");
    // setcolor(BLACK);
    bar(100, 105, 190, 125);
    bar(195, 105, 285, 125);
    bar(290, 105, 380, 125);
    settextstyle(DEFAULT_FONT, HORIZ_DIR, 1);
    outtextxy(102, 105, "Ana Sayfa");
    outtextxy(200, 105, "Ekle");
    outtextxy(300, 105, "Sil");

    rectangle(40, 170, getmaxx() - 40, y + (personelSayisi + 1) * 30);

    // Baslik
    // setcolor(WHITE);
    setfillstyle(SOLID_FILL, DARKGRAY);
    bar(40, 170, getmaxx() - 40, 200);
    // setcolor(BLACK);
    settextstyle(DEFAULT_FONT, HORIZ_DIR, 1);
    outtextxy(50, 180, "Personel Adý");
    outtextxy(250, 180, "Personel Soyadý");
    outtextxy(450, 180, "Personel Bölgesi");

    // Içerik
    for (int i = 0; i < personelSayisi; i++)
    {
        // setcolor(BLACK);
        setfillstyle(SOLID_FILL, LIGHTGRAY);
        bar(40, y + (i * 30), getmaxx() - 40, y + ((i + 1) * 30));
        // setcolor(BLACK);
        rectangle(40, y + (i * 30), getmaxx() - 40, y + ((i + 1) * 30));

        outtextxy(50, y + (i * 30) + 5, personelListesi[i].personalAdi);
        outtextxy(250, y + (i * 30) + 5, personelListesi[i].personelSoyadi);
        outtextxy(450, y + (i * 30) + 5, personelListesi[i].personelBolge);
    }
}
void personel()
{
    delay(1000);
    closegraph();
    int gd = DETECT, gm;
    initgraph(&gd, &gm, "");

    int personelSayisi = 0;

    FILE *gecici = fopen("personelListesi.txt", "r+");
    if (gecici == NULL)
    {
        printf("Dosya açilamadi.\n");
    }
    else
    {
        while (fscanf(gecici, "%s %s %s", personelListesi[personelSayisi].personalAdi, personelListesi[personelSayisi].personelSoyadi, personelListesi[personelSayisi].personelBolge) != EOF)
        {
            personelSayisi++;
        }
        fclose(gecici);
    }

    tabloCiz2(personelListesi, personelSayisi);

    while (1)
    {
        delay(5);
        if (ismouseclick(WM_LBUTTONDOWN))
        {
            int x, y;
            getmouseclick(WM_LBUTTONDOWN, x, y);
            if (x > 100 && x < 190 && y > 105 && y < 125)
            {
                closegraph();
                int gd = DETECT, gm;
                initgraph(&gd, &gm, "");
                setcolor(WHITE);
                menuCiz(selected);
                sistemeGiris();
            }
            else if (x > 195 && x < 285 && y > 105 && y < 125)
            {
                ekle2();
            }
            else if(x > 290 && x < 380 && y > 105 && y < 125)
            {
            outtextxy(100,145,"Bu Fonksiyon Suan Devre Dýþýdýr.");	
			}
        }
    }
    setcolor(WHITE);
    getch();
    closegraph();
}

// Giris
void mouseKontrol()
{
    int x, y;
    while (1)
    {
        delay(10);
        if (ismouseclick(WM_LBUTTONDOWN))
        {
            getmouseclick(WM_LBUTTONDOWN, x, y);
            if (x > 207 && x < 307 && y > 300 && y < 330)
            {
                sistemeGiris();
            }
            else if (x > 320 && x < 460 && y > 300 && y < 330)
            {
                goster();
            }
        }
    }
}

// Ana Fonksiyon
int main()
{
    int gd = DETECT, gm;
    initgraph(&gd, &gm, "");
    printf("X: %d   Y:%d\n", getmaxx(), getmaxy());
    girisTasarimi();
    dosyayaYaz(*giris);
    mouseKontrol();

    getch();
    closegraph();

    return 0;
}
