#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include<unistd.h>

void loading(void){
	int i;
	printf("\nPlease wait Loading ...\n");
	for(i=0; i<50; ++i){
		sleep(76);
		printf("%c", 219);
		}
	}

// deklarasi circular linked list
typedef struct node{ 
    char *word;
    struct node *next;
}node;

// deklarasi queue
typedef struct queue{
 node *front, *rear;
} queue;

void aboutUs(){
    //Prosedur untuk menampilkan judul program dan credits
    puts("");
    puts("----------------------------------------------------------------------------");
    puts(" _____         _    ______                _                 _              ");
    puts("|_   _|       | |   | ___ \\              | |               (_)             ");
    puts("  | | _____  _| |_  | |_/ /__ _ _ __   __| | ___  _ __ ___  _ _______ _ __ ");
    puts("  | |/ _ \\ \\/ / __| |    // _` | '_ \\ / _` |/ _ \\| '_ ` _ \\| |_  / _ \\ '__|");
    puts("  | |  __/>  <| |_  | |\\ \\ (_| | | | | (_| | (_) | | | | | | |/ /  __/ |   ");
    puts("  \\_/\\___/_/\\_\\__| \\_| \\_\\__,_|_| |_|\\__,_|\\___/|_| |_| |_|_/___\\___|_|   ");
    puts("----------------------------------------------------------------------------");
    puts("");
    puts("\t\t\t\tCreated by:\n");
    puts("\t\t Dhanurangga Al-Fadh             (13218005)");
    puts("\t\t Ivan Giovanni                   (13218006)");
    puts("\t\t Sarah Alyaa Tsaabitah           (13218011)");
    puts("\t\t Christian Dinata                (13218024)");
    puts("\t\t Zulfikar Nima Arifuzzaki        (13218029)");
    puts("");
    puts("\t\t\t   Press Enter To Continue");
    while(getchar() != '\n');
    // loading();
    system("cls");
}

void enqueue(queue *Q, char *text){
    //Membuat node baru dan meletakkan datanya
    node *newnode = (node*)malloc(sizeof(node));
    newnode->word = (char*)malloc(sizeof(char));
    strcpy(newnode->word,text);

    //Kasus queue masih kosong
    if(Q->rear == NULL){
        newnode->next = newnode;
        Q->rear= newnode;
        Q->front= newnode;
        return;
    }

    //Kasus queue sudah terisi
    Q->rear->next = newnode;
    newnode->next = NULL;
    Q->rear = newnode;
    return;
}

void dequeue(queue *Q){
    //Membuat pointer node sementara;
    node *temp;

    //Kasus queue kosong
    if(Q->front == NULL){
        printf("Queue kosong!\n");
        return;
    }

    //Kasus tersisa node terakhir
    //kasus ini gatau kenapa gabisa
    else if(Q->front == Q->rear){
        temp = Q->front;
        Q->front = NULL;
        Q->rear = NULL;
        free(temp);
        return;
    }

    //Kasus terdapat lebih dari 1 node
    temp = Q->front;
    Q->front = Q->front->next;
    free(temp);
    return;
}

// fungsi menambahkan node pada ujung akhir list
void addNode (char *kata, node **rear){
   
    node *temp = (node*)malloc(sizeof(node));   // deklarasi node baru
    temp->word = (char*)malloc(sizeof(char));   // alokasikan memori untuk word
    strcpy(temp->word,kata);                    // isi word dengan kata

    /* untuk menangani list kosong */
    if (*rear == NULL){
        *rear = temp;
        (*rear)->next = (*rear);
        return ;
    }
    
    /* untuk menangani list yang tidak kosong */
        
    temp->next = (*rear)->next;    // tambahkan node di ujung akhir list dan circular
    (*rear)->next = temp;          // pastikan temp berada pada ujung akhir dengan pointer rear sebelumnya mengarah ke temp
    (*rear) = temp;                // deklarasi rear baru pada temp
    
    return;
}

int fileHandling(char* filename, node **rear){
    //Fungsi untuk memuat data dari file txt ke node dan menghitung jumlah kata
    //Input: nama file (string)
    //Output: jumlah kata

    char *word = (char*)malloc(sizeof(char));
    char line[1024];
    char *newFilename = (char*)malloc(sizeof(char));
    int n;
    FILE *fp;

    n = 0;
    fp = fopen(filename,"r");
    
    //Jika file tidak ditemukan
    while (!fp){
        puts("File Not Found!");
        puts("Masukkan nama file kembali! : ");
        scanf("%s", newFilename);
        fp = fopen(newFilename, "r");
    }
    
    free(newFilename);
    //Jika pembacaan belum mencapai EOF
    while(fgets(line, 1024, fp)){

        line[strcspn(line, "\n")] = 0;                      //Menghilangkan \n
        word = strtok(line, " ");                           //Memisahkan kata dengan spasi

        //Menambahkan kata ke node
        while(word){
            //printf("%s | ",word); //for test only
            addNode(word, rear);
            n++;                                            //Menghitung jumlah kata
            word = strtok(NULL, " ");
        }
    }
    free(word);
    fclose(fp);
    return n;
}

// fungsi untuk mendapatkan posisi rear secara acak dari list
node *randRear (node *rear, int total){
    int rand_int;
    int i;
    rand_int = (rand() % (total)); // generate random integer from 0 to total
    i = rand_int;
    rear = rear->next;             // move rear to the first node of list (usually head)

    /* randomize new position of rear */
    while (i != 0){ 
        rear = rear->next;
        i--;
    }

    return rear;
}

//Fungsi ngerandom node awal di text
node* randomHead(node **text,int textLength){
 int r = (rand() % textLength) + 1; //Batas atas = jumlah kata pada text (textLength)
 int i = 0;
 node *head = *text;

 //Mencari node ke-r
 for(i = 0; i < r; i++){
  head = head->next;
 }

 return (head);
}

//Fungsi mencari value dari key pada text
void searchValue(node **text, queue **key, int textLength){
	node *currText = randRear(*text,textLength);
	node *testText;
	node *currKey;
	int found = 0;

	while (found == 0){
		currKey = (*key)->front;
		testText = currText;

	while(currKey != NULL){
		//Kasus kata tidak sama
		if (strcmp(testText->word,currKey->word)!= 0)
			break;
		//Kasus kata sama
		currKey = currKey->next;
		testText = testText->next;
		}

	//Jika key ditemukan pada text
	if (currKey == NULL){
		found = 1;
	}
	else {
		currText = currText->next;
		}
	}
	//Print the value
	printf("%s ",testText->word);

	//Editing the key linked list
	dequeue(*key);
	enqueue(*key, testText->word);
}

//Fungsi membuat text baru
void generateText(node *text, int textLength, int word_count, int n_grams){
	//inisialisasi key
	queue *key = (queue*)malloc(sizeof(queue));
	key->front = NULL;
	key->rear = NULL;
	node *test = (node*)malloc(sizeof(test));
	test = randRear(text, textLength);
	int i;
 
	//Generate Key dengan jumlah kata = n_gram
	for (i = 0; i < n_grams; i++){
		enqueue(key, test->word);
		test = test->next;
	}//sampai disini didapat key = n
 
	//Generate Text dengan jumlah kata = word_count
	printf("... ");
	for (i = 0; i < word_count; ++i){
		searchValue(&text, &key, textLength);
		printf("ok");
	}
	printf("... \n");
	
	free(key);
}

int menux(){
	int output;
	printf("\nPilihan menu: \n");
	printf("1. Input File Eksternal\n");
	printf("2. Cetak kata random\n");
	printf("3. Exit\n");
	printf("Pilihan menu: ");
	scanf("%d", &output);
	return(output);
	}

void freeList(struct node* head)
{
   struct node* tmp;

   while (head != NULL)
    {
       tmp = head;
       head = head->next;
       free(tmp);
    }

}

int main(){
	srand(time(0));
	
	node* linkedList = (node*)malloc(sizeof(char));
	linkedList = NULL;
     
	int textLength = 0;
	int n_gram;
	int random;
	int menu;
     
	aboutUs();
	
	printf("SELAMAT DATANG DI N-PROGRAM\n");
	printf("Program memiiliki tiga menu, yaitu input text eksternal, cetak kata-kata random dari n-gram, dan exit\n");

	menu = menux();
	while(menu != 3){
		if (menu == 1){//input file eksternal
			printf("Masukkan nama file : ");
			char* filename = (char*)malloc(sizeof(char));
			scanf("%s", filename);
			textLength = fileHandling(filename, &linkedList);
			free(filename);
			printf("%d\n",textLength);
			menu = menux();
			}
		else if(menu == 2){//mencetak kata-kata dari key n_gram
			if(textLength == 0){
				printf("File eksternal belum diinput, silakan input terlebih dahulu!\n");
				menu = 1;
				}
			else{
				printf("Masukkan banyaknya n pada n-gram: ");
				scanf("%d", &n_gram);
				while(n_gram < 2){
					printf("n harus bernilai sama dengan dua atau lebih\n");
					scanf("%d", &n_gram);}
				printf("Masukkan jumlah kata random yang akan dicetak: ");
				scanf("%d", &random);
				generateText(linkedList, textLength, random, n_gram);
				printf("\nyay!");
				menu = menux();
				}
			}
		else if(menu == 3){//keluar
			printf("Terima kasih telah menggunakan program kami!\n");
			freeList(linkedList);
			exit(1);
			}
		else{//pilihan salah
			printf("Masukkan input salah! Silakan input kembali");
			menu = menux();
			}
		}
	return(0);
 }
