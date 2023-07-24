#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <conio.h>

char cekuser[50], cekpass[50], cekkode[50];
void menu();
void registrasi();
void dataregistrasi(char user[50], char pass[50]);
void login();
void tampilkan();
void update();
void hapusdata();
char *generasikode(char *user, int x) 
{
   char *new = malloc(sizeof(char)*x+1);
   strncpy(new, user, x);
   new[x] = '\0';
   return new;
}

FILE *simpan,*simpantemp;

int main()
{
	menu();
	return 0;
}

void menu(){
	int pilihan;
	system("cls");
	printf(" ================================\n");
	printf(" |------------ MENU ------------|\n");
	printf(" ================================\n");
	printf(" | 1. Registrasi                |\n");
	printf(" | 2. Login                     |\n");
	printf(" | 3. Tampilkan semua data      |\n");
    printf(" | 4. Update                    |\n");
    printf(" | 5. Hapus Data                |\n");
	printf(" | 6. EXIT                      |\n");
	printf(" ================================\n");
	printf("\n PILIH MENU : "); scanf("%d", &pilihan);
	
	switch(pilihan)
	{
	case 1:
		registrasi();
		break;
	case 2:
		login();
		break;
	case 3:
		tampilkan();
		break;
	case 4:
		update();
		break;
    case 5:
        hapusdata();
        break;
    case 6:
        exit(1);
        break;
	default:
		printf("\nPilihan tidak ada !!\n\n");
		break;
	}
}

void registrasi(){
	char user[50], pass[50];
	system("cls");
	
	printf("==============================\n");
    registrasi:
	printf("\nInput Username : "); scanf("%s", user);
	printf("Input Password : "); scanf("%s", pass);

	if(strlen(user)<6){
		printf("Username harus lebih dari 6 karakter\n\n");
		kurang6:
	    printf("Ingin registrasi lagi ? (y/t)");
	    switch(getch())
	    {
	    case 'y':
		    goto registrasi;
		    break;
	    case 't':
		    return menu();
	    default:
		    printf("\nTidak ada pilihan tersebut !");
		    goto kurang6;
		    break;
        }
	}else{
		int x = 0, simbol = 0;
		while(user[x] != '\0'){
			if( !isalpha(user[x] ) && !isdigit(user[x] ) && user[x] != '.'){
				simbol++;
			}
			x++;
		}
		if(simbol >= 1){
			printf("Username tidak boleh ada spesial karakter !\n\n");
            tdkspesial:
	        printf("Ingin registrasi lagi ? (y/t)");
	        switch(getch())
	        {
	        case 'y':
		        goto registrasi;
		        break;
	        case 't':
		        return menu();
	        default:
		        printf("\nTidak ada pilihan tersebut !");
		        goto tdkspesial;
		    break;
        }
		}
	}
	
	if(strlen(pass)<8){
		printf("Password harus lebih dari 8 karakter\n\n");
		kurang8:
	    printf("Ingin registrasi lagi ? (y/t)");
	    switch(getch())
	    {
	    case 'y':
		    goto registrasi;
		    break;
	    case 't':
		    return menu();
	    default:
		    printf("\nTidak ada pilihan tersebut !");
		    goto kurang8;
		    break;
        }
	}else{
		int x = 0, kecil = 0, kapital = 0, krktr = 0, angka = 0;
		while(pass[x] != '\0'){
			if(pass[x] >= '0' && pass[x] <= '9')
				angka++;	
			else if(pass[x] >= 'A' && pass[x] <= 'Z')
				kapital++;
			else if(pass[x] >= 'a' && pass[x] <= 'z')
				kecil++;
			else
				krktr++;
			x++;
		}
		if(kecil == 0 || kapital == 0 || krktr == 0 || angka == 0){
			printf("Password harus terdiri minimal 1 huruf kecil, 1 huruf kapital, 1 angka, dan 1 karakter spesial!\n\n");
			pwkurang:
            printf("Ingin registrasi lagi ? (y/t)");
            switch(getch())
            {
            case 'y':
                goto registrasi;
                break;
            case 't':
                return menu();
            default:
                printf("\nTidak ada pilihan tersebut !");
                goto pwkurang;
                break;
            }
		}else{
			char rev[50];
			strcpy(rev, pass);
			strrev(rev);
			if(strcmp(pass, rev)==0){
				printf("password tidak boleh palindrome!\n\n");
            tdkpali:
            printf("Ingin registrasi lagi ? (y/t)");
            switch(getch())
            {
            case 'y':
                goto registrasi;
                break;
            case 't':
                return menu();
            default:
                printf("\nTidak ada pilihan tersebut !");
                goto tdkpali;
                break;
            }
			}
		}
	}
	dataregistrasi(user, pass);
	lagi:
	printf("Apakah anda ingin registrasi lagi ? (y/t)");
	printf("\n");
	switch(getch())
	{
	case 'y':
		goto registrasi;
		break;
	case 't':
		menu();
	default:
		printf("\nTidak ada pilihan tersebut !\n\n");
		goto lagi;
		break;
	}
}

void dataregistrasi(char user[50], char pass[50]){
	int i = 1;
	simpan = fopen("dataregistrasi.txt", "a+");
	
	while(fscanf(simpan, "%s %s %s", cekuser, cekpass, cekkode) != EOF){
		if(strcmp(cekuser, user) ==0){
			printf("Username sudah ada\n\n");
            usersudahada:
            printf("Ingin registrasi lagi ? (y/t)");
            switch(getch())
            {
            case 'y':
                return registrasi();
                break;
            case 't':
                return menu();
            default:
                printf("\nTidak ada pilihan tersebut !");
                goto usersudahada;
                break;
            }
		}
		i++;
	}
	
	char x[50];
	strcpy(x, generasikode(user, 3));
	strupr(x);
	
	char y[50];
	sprintf(y, "%d", i);
	while(strlen(y) <4){
		strcat(y, "0");
	}
	strrev(y);
	strcat(x, "-");
	strcat(x, y);
	fprintf(simpan, "%s %s %s\n", user, pass, x);
	
	printf("Username berhasil didaftarkan");
	printf("\n Username : %s\n Password : %s\n Kode User : %s\n", user, pass, x);
	fclose(simpan);
}

void login(){
	char user[50], pass[50];
	int x = 0;
	system("cls");
	printf("==============================\n");
	monitor:
	printf("Masukkan Username : "); scanf("%s", user);
	printf("Masukkan Password : "); scanf("%s", pass);
	
	simpan = fopen("dataregistrasi.txt", "r");
	while(fscanf(simpan, "%s %s %s", cekuser, cekpass, cekkode) != EOF)
	{
		if ((strcmp(cekuser, user) == 0) && strcmp(cekpass, pass) == 0){
			x = 1;
			break;
		}
	}
	fclose(simpan);
	if (x == 1){
		printf("Selamat datang %s\n", cekuser);
		printf("===Data Anda===\n");
		printf("Username : %s\n", cekuser);
		printf("Kode User : %s\n\n", cekkode);
	pilihan:
	printf("Ingin kembali ke layar utama ? (y/t)");
	printf("\n");
	switch(getch())
	{
	case 'y':
		menu();
		break;
	case 't':
		exit(1);
	default:
		printf("Tidak ada pilihan tersebut !");
		goto pilihan;
		break;
	}
	}else
	{
		puts("User atau Password anda salah");
		goto monitor;
	}
}

void tampilkan(){
	int x = 1;
	system("cls");
	simpan = fopen("dataregistrasi.txt", "r");
	printf("===LIST DATA===\n");
	while(fscanf(simpan, "%s %s %s", cekuser, cekpass, cekkode) != EOF){
		printf("=== %d ===\n", x);
		printf("Username : %s\n", cekuser);
		printf("Kode User : %s\n", cekkode);
		x++;
	}
	printf("\n");
	fclose(simpan);
	pilihan:
	printf("Ingin kembali ke layar utama ? (y/t)");
	switch(getch())
	{
	case 'y':
		menu();
		break;
	case 't':
		exit(1);
	default:
		printf("\nTidak ada pilihan tersebut !");
		goto pilihan;
		break;
	}
}

void update(){
	FILE *simpan = fopen("dataregistrasi.txt", "r+");
    FILE *simpantemp = fopen("replace.txt", "w");
    char dicari[20], kalimat[100], temp[100], *kata, user[20];
 	update:
	system("cls");
 	printf("\n================= UPDATE ===================\n");
    printf("\nMasukkan user yang ingin di ganti : "); scanf("%s", dicari);
    printf("Masukkan user baru : "); scanf("%s", user);
    if(strlen(user)<6){
		printf("Username harus lebih dari 6 karakter\n\n");
		kurang6a:
	    printf("Ingin update lagi? (y/t)");
	    switch(getch())
	    {
	    case 'y':
		    goto update;
		    break;
	    case 't':
		    menu();
	    default:
		    printf("\nTidak ada pilihan tersebut !");
		    goto kurang6a;
		    break;
        }
	}else{
		int x = 0, simbol = 0;
		while(user[x] != '\0'){
			if( !isalpha(user[x] ) && !isdigit(user[x] ) && user[x] != '.'){
				simbol++;
			}
			x++;
		}
		if(simbol >= 1){
			printf("Username tidak boleh ada spesial karakter !\n\n");
            tidakblhspesial:
	        printf("Ingin update lagi ? (y/t)");
	        switch(getch())
	        {
	        case 'y':
		        goto update;
		        break;
	        case 't':
     	 	 	 menu();
	        default:
		        printf("\nTidak ada pilihan tersebut !");
		        goto tidakblhspesial;
		    break;
        	}
		}
	}

    while (fgets(kalimat, 100, simpan) != NULL)
    {
        strcpy(temp, kalimat);
        kata = strtok(kalimat, " ");
        if (strcmp(kata, dicari) == 0)
        {
            fprintf(simpantemp, "%s %s %s\n", user, cekpass, cekkode);
        }else
        {
            fprintf(simpantemp, temp);
        }
    }

    fclose(simpan);
    fclose(simpantemp);

    remove("dataregistrasi.txt");
    rename("replace.txt", "dataregistrasi.txt");
 	pilihanx:
	printf("Ingin kembali ke layar utama ? (y/t)");
	printf("\n");
	switch(getch())
	{
	case 'y':
		menu();
		break;
	case 't':
		exit(1);
	default:
		printf("Tidak ada pilihan tersebut !");
		printf("\n");
		goto pilihanx;
		break;
	}
}

void hapusdata(){
    
	simpan = fopen("dataregistrasi.txt", "r+");
	simpantemp = fopen("replace.txt", "w");
	
	char kalimat[100], temp[100], *kata, dicari[20];
	system("cls");
	printf("Masukkan user yang ingin dihapus : "); scanf("%s", dicari);
	
	while(fgets(kalimat, 100, simpan) != NULL){
		strcpy(temp, kalimat);
		kata = strtok(kalimat, " ");
		if(strcmp(kata, dicari) != 0){
				fprintf(simpantemp, temp);
 		}
	}

	fclose(simpan);
	fclose(simpantemp);
	
	remove("dataregistrasi.txt");
	rename("replace.txt", "dataregistrasi.txt");
	printf("\nUser %s berhasil dihapus !!\n", dicari);
	pilihan:
	printf("Ingin kembali ke layar utama ? (y/t)");
	printf("\n");
	switch(getch())
	{
	case 'y':
		menu();
		break;
	case 't':
		exit(1);
	default:
		printf("Tidak ada pilihan tersebut !");
		printf("\n");
		goto pilihan;
		break;
	}
}
