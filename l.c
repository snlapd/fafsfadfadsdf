#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include <string.h>
#include <conio.h>
#include <string.h>

#define loop_space(c)  for(int i=0; i<c; i++ )   printf(" ");
#define CBLUE  "\033[0;36m"
#define CRED  "\033[0;31m"
#define CWHT  "\x1B[37m"
#define CMAG  "\x1B[35m"
#define CWHITE "\033[0;37m"
char colors[5][10] = { "\033[0;36m" , "\033[0;31m"  ,  "\x1B[37m"  , "\033[0;32m",  "\033[0;37m"};



CONSOLE_SCREEN_BUFFER_INFO csbi;

struct LINTER{
	char new_words[20][100];
	char review[20][100];
	char conslidation[20][100];
	char learn_words[20][100];
};

struct USER {

	char first_name[100];
	char last_name[100];
	char user_name[100];
	char pass[12];
	char  phone_number[15];
	char email[30];
	struct LINTER linter_;
	
};

struct ENGLISH_LETTERS {
	char letter[50];
	char dis[150];
    struct ENGLISH_LETTERS* next;
};




void menue();
void singup();
struct USER singin();
void showle();
void forgot_password();
void display();
int find(char* ,char* , struct USER* ,int* );
int check_existing( struct USER , int*);
void show();
void admin_pannel();
void add_word();
void edit_word();
void user_pannel(struct USER*);
void remove_word_l(struct ENGLISH_LETTERS**);
struct ENGLISH_LETTERS* make_linked_word();
struct ENGLISH_LETTERS* set_info(struct ENGLISH_LETTERS* , char* ,char*);
void sort(struct ENGLISH_LETTERS**);
void wtire_in_file(struct ENGLISH_LETTERS*);
void Search_letter (struct USER*);
void other(struct ENGLISH_LETTERS* , char*);
void free_linter_nwords(struct USER*);
void fwrite_to_file(struct USER* );
void linter(struct USER* );
void show_information(struct USER*);
void edit_information(struct USER*);
void write_file_new_info(struct USER*);
void set_new_info(struct USER* ,char *);
void new_words(struct ENGLISH_LETTERS* , struct USER*);
void review(struct ENGLISH_LETTERS*, struct USER*);
void conslidation(struct ENGLISH_LETTERS* , struct USER*);
void learned_words_(struct USER* );
void add_word();
void edit_word();
struct ENGLISH_LETTERS* set_info(struct ENGLISH_LETTERS * head , char* , char* );



//-------------------------------------------------------
int find(char* name,char* phone , struct USER* tmp  ,int* pos){

    struct USER user;
    FILE* fp;
    long p =0;
	printf("      ");
	// fp = fopen()
	fp = fopen("C:\\Users\\RSKALA\\Desktop\\dbuser.bin", "r+b" );

    
    while(fread(&user , sizeof(struct USER) , 1 , fp)){
            if(!strcmp(name ,user.user_name) && !strcmp(phone , user.phone_number))
            {
                    *pos = p;
					fclose(fp);
					// *tmp = user;
					 return 1;
					
            }

            p += sizeof(struct USER);
    }
	printf("\n\nNOT %sFOUND%s THIS %sUSER%s \n\n" ,CRED,CWHITE,CMAG,CWHITE);
	
	return 0;

					

}

// void readAndWriteWords() {
//     FILE *inputFile = fopen("C:\\Users\\RSKALA\\Desktop\\Dictionary.txt", "r");
//     if (inputFile == NULL) {
//         perror("Failed to open input file");
//         return;
//     }

//     FILE *outputFile = fopen("C:\\Users\\RSKALA\\Desktop\\dbletters.bin", "wb");
//     if (outputFile == NULL) {
//         perror("Failed to open output file");
//         fclose(inputFile);
//         return;
//     }

//     char line[2 * 50 + 2];
//    struct ENGLISH_LETTERS word;

//     while (fgets(line, sizeof(line), inputFile)) {
//         // Skip the line number
//         char *start = strchr(line, '-');
//         if (start != NULL) {
//             start += 1; // Move past the '-'
//         } else {
//             // If no '-' is found, skip this line (should not happen if the file format is correct)
//             continue;
//         }

//         // Process the word and translation part
//         char *delimiter = strchr(start, ':');
//         if (delimiter != NULL) {
//             *delimiter = '\0'; // Replace ':' with null terminator
//             strncpy(word.letter, start, 50);
//             word.letter[50 - 1] = '\0'; // Ensure null termination

//             char *transformation = delimiter + 1;
//             // Remove potential "transformation:" prefix and commas
//             char *comma = strchr(transformation, ',');
//             if (comma != NULL) {
//                 *comma = '\0';
//             }
//             strncpy(word.dis, transformation, 50);
//             word.dis[50- 1] = '\0'; // Ensure null termination

//             // Remove newline character from Persian word if present
//             size_t len = strlen(word.dis);
//             if (word.dis[len - 1] == '\n') {
//                 word.dis[len - 1] = '\0';
//             }

//             fwrite(&word, sizeof(struct ENGLISH_LETTERS), 1, outputFile);
//         }
//     }

//     fclose(inputFile);
//     fclose(outputFile);
// // }
// void readAndStoreWords() {
//     // FILE *inputFile = fopen("", "r");
//     FILE *inputFile = fopen("C:\\Users\\RSKALA\\Desktop\\Dictionary.txt", "r");

//     if (inputFile == NULL) {
//         perror("Failed to open input file");
//         return;
//     }

//     char line[4 * 50 + 2];
//     *wordCount = 0;

//     while (fgets(line, sizeof(line), inputFile) && *wordCount < 100) {
//         // Skip the line number
//         char *start = strchr(line, '-');
//         if (start != NULL) {
//             start += 1; // Move past the '-'
//         } else {
//             // If no '-' is found, skip this line (should not happen if the file format is correct)
//             continue;
//         }

//         // Find the position of "word:"
//         char *wordStart = strstr(start, "word:");
//         if (wordStart != NULL) {
//             wordStart += 5; // Move past "word:"
//         } else {
//             continue; // If "word:" is not found, skip this line
//         }

//         // Find the position of "transformation:"
//         char *transStart = strstr(start, "transformation:");
//         if (transStart != NULL) {
//             transStart += 14; // Move past "transformation:"
//         } else {
//             continue; // If "transformation:" is not found, skip this line
//         }

//         // Extract the English word
//         char *endOfWord = strchr(wordStart, ',');
//         if (endOfWord != NULL) {
//             *endOfWord = '\0'; // Replace ',' with null terminator
//         } else {
//             continue; // If no ',' is found, skip this line (should not happen if the file format is correct)
//         }

//         strncpy(words[*wordCount].letter, wordStart, 50);
//         words[*wordCount].letter[50 - 1] = '\0'; // Ensure null termination

//         // Extract the Persian translation
//         char *endOfTrans = strchr(transStart, ',');
//         if (endOfTrans != NULL) {
//             *endOfTrans = '\0'; // Replace ',' with null terminator
//         } else {
//             // Remove newline character if present
//             size_t len = strlen(transStart);
//             if (transStart[len - 1] == '\n') {
//                 transStart[len - 1] = '\0';
//             }
//         }

//         strncpy(words[*wordCount].dis, transStart, 50);
//         words[*wordCount].dis[50- 1] = '\0'; // Ensure null termination

//         (*wordCount)++;
//     }


// #include <stdio.h>
// #include <stdlib.h>
// #include <string.h>

// #define MAX_WORD_LENGTH 50

// typedef struct {
//     char english[MAX_WORD_LENGTH];
//     char persian[MAX_WORD_LENGTH];
// } Word;

// void readAndWriteWords() {
//     // FILE *inputFile = fopen(inputFileName, "r");
//     FILE *inputFile = fopen("C:\\Users\\RSKALA\\Desktop\\Dictionary.txt", "r");

//     if (inputFile == NULL) {
//         perror("Failed to open input file");
//         return;
//     }

//     // FILE *outputFile = fopen(outputFileName, "wb");
//     FILE *outputFile = fopen("C:\\Users\\RSKALA\\Desktop\\dbletters.bin", "wb");

//     if (outputFile == NULL) {
//         perror("Failed to open output file");
//         fclose(inputFile);
//         return;
//     }

//     char line[4 * 50 + 2];
//    struct ENGLISH_LETTERS word;

//     while (fgets(line, sizeof(line), inputFile)) {
//         // Skip the line number
//         char *start = strchr(line, '-');
//         if (start != NULL) {
//             start += 1; // Move past the '-'
//         } else {
//             // If no '-' is found, skip this line (should not happen if the file format is correct)
//             continue;
//         }

//         // Find the position of "word:"
//         char *wordStart = strstr(start, "word:");
//         if (wordStart != NULL) {
//             wordStart += 5; // Move past "word:"
//         } else {
//             continue; // If "word:" is not found, skip this line
//         }

//         // Find the position of "transformation:"
//         char *transStart = strstr(start, "transformation:");
//         if (transStart != NULL) {
//             transStart += 14; // Move past "transformation:"
//         } else {
//             continue; // If "transformation:" is not found, skip this line
//         }

//         // Extract the English word
//         char *endOfWord = strchr(wordStart, ',');
//         if (endOfWord != NULL) {
//             *endOfWord = '\0'; // Replace ',' with null terminator
//         } else {
//             continue; // If no ',' is found, skip this line (should not happen if the file format is correct)
//         }

//         strncpy(word.letter, wordStart, 50);
//         word.letter[50 - 1] = '\0'; // Ensure null termination

//         // Extract the Persian translations
//         // Assuming multiple translations are separated by commas
//         char *token = strtok(transStart, ",");
//         if (token != NULL) {
//             strncpy(word.dis, token, 50);
//             word.dis[50 - 1] = '\0'; // Ensure null termination
//         } else {
//             // If no translation is found, skip this line
//             continue;
//         }

//         // Write the word to the binary file
//         fwrite(&word, sizeof(struct ENGLISH_LETTERS), 1, outputFile);
//     }

//     fclose(inputFile);
//     fclose(outputFile);
// 	showle();
// 	Sleep(20000);
// }

// int main() {
//     readAndWriteWords("words.txt", "words.bin");
//     return 0;
// }




// void readAndWriteWords() {
//     // FILE *inputFile = fopen(inputFileName, "r");
//     FILE *inputFile = fopen("C:\\Users\\RSKALA\\Desktop\\Dictionary.txt", "r");

//     if (inputFile == NULL) {
//         perror("Failed to open input file");
//         return;
//     }

//     // FILE *outputFile = fopen(outputFileName, "wb");
//     FILE *outputFile = fopen("C:\\Users\\RSKALA\\Desktop\\dbletters.bin", "wb");

//     if (outputFile == NULL) {
//         perror("Failed to open output file");
//         fclose(inputFile);
//         return;
//     }

//     char line[2 * 50 + 2];
//     struct ENGLISH_LETTERS  word;

//     while (fgets(line, sizeof(line), inputFile)) {
//         // Skip the line number
//         char *start = strchr(line, '-');
//         if (start != NULL) {
//             start += 1; // Move past the '-'
//         } else {
//             // If no '-' is found, skip this line (should not happen if the file format is correct)
//             continue;
//         }

//         // Process the word and translation part
//         char *delimiter = strchr(start, ':');
//         if (delimiter != NULL) {
//             *delimiter = '\0'; // Replace ':' with null terminator
//             strncpy(word.letter, start, 50);
//             word.letter[50 - 1] = '\0'; // Ensure null termination

//             char *transformation = delimiter + 1;
//             // Remove potential "transformation:" prefix and commas
//             char *comma = strchr(transformation, ',');
//             if (comma != NULL) {
//                 *comma = '\0';
//             }
//             strncpy(word.dis, transformation, 50);
//             word.dis[50 - 1] = '\0'; // Ensure null termination

//             // Remove newline character from Persian word if present
//             size_t len = strlen(word.dis);
//             if (word.dis[len - 1] == '\n') {
//                 word.dis[len - 1] = '\0';
//             }

//             fwrite(&word, sizeof(struct ENGLISH_LETTERS), 1, outputFile);
//         }
//     }

//     fclose(inputFile);
//     fclose(outputFile);
// }





// void readAndWriteWords() {
//     // FILE *inputFile = fopen("words.txt", "r");
//     FILE *inputFile = fopen("C:\\Users\\RSKALA\\Desktop\\Dictionary.txt", "r");

//     if (inputFile == NULL) {
//         perror("Failed to open input file");
//         return;
//     }

//     // FILE *outputFile = fopen("words.bin", "wb");
//     FILE *outputFile = fopen("C:\\Users\\RSKALA\\Desktop\\dbletters.bin", "wb");
    
//     if (outputFile == NULL) {
//         perror("Failed to open output file");
//         fclose(inputFile);
//         return;
//     }

//     char line[4 *50+ 2];
//     struct ENGLISH_LETTERS word;

//     while (fgets(line, sizeof(line), inputFile)) {
//         // Skip the line number
//         char *start = strchr(line, '-');
//         if (start != NULL) {
//             start += 1; // Move past the '-'
//         } else {
//             continue; // If no '-' is found, skip this line
//         }

//         // Find the position of "word:"
//         char *wordStart = strstr(start, "word:");
//         if (wordStart != NULL) {
//             wordStart += 5; // Move past "word:"
//         } else {
//             continue; // If "word:" is not found, skip this line
//         }

//         // Find the position of "transformation:"
//         char *transStart = strstr(start, "transformation:");
//         if (transStart != NULL) {
//             transStart += 14; // Move past "transformation:"
//         } else {
//             continue; // If "transformation:" is not found, skip this line
//         }

//         // Extract the English word
//         char *endOfWord = strchr(wordStart, ',');
//         if (endOfWord != NULL) {
//             *endOfWord = '\0'; // Replace ',' with null terminator
//         } else {
//             continue; // If no ',' is found, skip this line
//         }

//         strncpy(word.letter, wordStart, 50);
//         word.letter[50 - 1] = '\0'; // Ensure null termination

//         // Extract the Persian translations
//         char *endOfTrans = strchr(transStart, '\n');
//         if (endOfTrans != NULL) {
//             *endOfTrans = '\0'; // Replace newline with null terminator
//         }

//         // Join all translations with comma
//         // In this case, we assume all translations are in a single line and separated by commas
//         snprintf(word.dis, sizeof(word.dis), "%s", transStart);

//         // Write the word to the binary file
//         fwrite(&word, sizeof(struct ENGLISH_LETTERS), 1, outputFile);
//     }

//     fclose(inputFile);
//     fclose(outputFile);'

// }
void write_binary_file(struct ENGLISH_LETTERS *entries, int count) {
	int i=0;
    // FILE *file = fopen(filename, "wb");
    FILE *fp = fopen("C:\\Users\\RSKALA\\Desktop\\dbletters.bin", "r");
	if(fp) return ;
	else{

    FILE *fp = fopen("C:\\Users\\RSKALA\\Desktop\\dbletters.bin", "w+b");


    // if (!file) {
    //     perror("Failed to open file for writing");
    //     exit(EXIT_FAILURE);

    // }
	// while(entries[i].letter){
    fwrite(entries, sizeof(struct ENGLISH_LETTERS), count, fp);
    // fclose(fp);
	// entries++;
	// i++;

	}
	fclose(fp);
	showle();
	Sleep(3000);
	printf("-------------\n");
	admin_pannel();
}





void r()
{

//  FILE *file = fopen("dictionary.txt", "r");
    FILE *file = fopen("C:\\Users\\RSKALA\\Desktop\\Dictionary.txt", "r");

    if (!file) {
        perror("Failed to open dictionary file");
        return  ;
    }

    struct ENGLISH_LETTERS entries[200];
    int count = 0;
    char line[256];

    while (fgets(line, sizeof(line), file)) {
        if (strstr(line, "word: ") && strstr(line, "translation: ")) {
            struct ENGLISH_LETTERS entry;
            sscanf(line, "%*d- word: %99[^,], translation: %99[^\n]", entry.letter, entry.dis);
            // Remove leading and trailing spaces from entry.word and entry.translation
            char *word_start = entry.letter;
            while (*word_start == ' ') word_start++;
            char *word_end = word_start + strlen(word_start) - 1;
            while (*word_end == ' ') *word_end-- = '\0';

            char *trans_start = entry.dis;
            while (*trans_start == ' ') trans_start++;
            char *trans_end = trans_start + strlen(trans_start) - 1;
            while (*trans_end == ' ') *trans_end-- = '\0';

            strcpy(entry.letter, word_start);
            strcpy(entry.dis, trans_start);

            entries[count++] = entry;
        }
    }
    fclose(file);

    write_binary_file(entries, count);
    // FILE *outputFile = fopen("C:\\Users\\RSKALA\\Desktop\\dbletters.bin", "wb");
	

    // printf("Dictionary written to dictionary.bin with %d entries.\n", count);
    return ;



	
}



void review(struct ENGLISH_LETTERS* head , struct USER* user){


struct ENGLISH_LETTERS* ptmp = head;

int i=0 ,t=0,r=0, q=0;
char key;
int e=0;
char ans;
while(user->linter_.new_words[e][0]) {
        strcpy(user->linter_.review[e] , user->linter_.new_words[e] );
		e++;
}

	while(user->linter_.review[i][0]){
	     system("cls");
	
		 	printf("%s\t\t" , user->linter_.review[i]); 

			key = _getch();
			 if(key =='\r') { i++; t++ ;continue;}
		
			 if(key == ' '){
				system("cls");

				       
						ptmp = head;
						while(ptmp){
						if(!strcmp(ptmp->letter , user->linter_.review[t])){
								printf("%s            " , ptmp->dis);
								break;
							

						}
						ptmp = ptmp->next;
						}	t++;

		while(1){
			// for(r ; user->linter_.review[r][0] ; r++);
			printf("\n\n1.Know\n\n 2.Did not know\n\n ~ ~ ENTER HERE -> ");
			ans = _getch();
			// if(ans=='2')  {strcpy(user->linter_.review[r] , user->linter_.new_words[i]); for(int j=0;j<100 ; j++) user->linter_.new_words[i][j]='\0';} 
			if(ans=='2') break;
			if(ans == '1') 
			
			{for(q ; user->linter_.conslidation[q][0]; q++);strcpy(user->linter_.conslidation[q] , user->linter_.new_words[i]); for(int j=0 ; j<100 ; j++) user->linter_.review[i][j] ='\0'; q=0; break;}else {printf("enter the correct value !"); Sleep(2000); ("cls"); continue;}
			
		}
			key = _getch();
		   if(key == ' ')   { t--; continue;}
		   else if(key =='\r') { i++; continue;}
			}
			}
			system("cls");
		printf("\n\nfinised ! !");
		Sleep(300);
			system("cls");
		

	fwrite_to_file(user);


	return ;


}






















int find_field(char * word , char n)
{
    struct USER user;
	FILE* fp;
	fp = fopen("C:\\Users\\RSKALA\\Desktop\\dbuser.bin" , "r+b");
    if(!fp)  { printf("\nno user\n"); return 0;}

    switch (n)
    {
    case '3' :
      	while(fread(&user , sizeof(struct USER) ,  1,fp)){
   

            if(!strcmp(word ,user.user_name)){
                    printf("this user-name is exis , enter another ");
                    Sleep(1500);
                    return 0;

            }
		}return 1;    
        break;

    case '5':

    	while(fread(&user , sizeof(struct USER ),  1,fp)){
   

            if(!strcmp(word ,user.phone_number)){
                    printf("this phone-number is exis , enter another ");
                    Sleep(1500);
                    return 0;

            }return 1;

    }
    case '6':

    
    	while(fread(&user , sizeof(struct USER) ,  1,fp)){
            if(!strcmp(word ,user.email)){
                    printf("this email is exis , enter another ");
                    Sleep(1500);
                    return 0;

            }
			
		}return 1;
  
    default:
        break;
    }




}






void show_lin(struct ENGLISH_LETTERS* head){
	struct ENGLISH_LETTERS* ptmp = head;
	// sort(&head);

	while(ptmp){
			printf("\nword : %s\t\t d:%s\n\n" , ptmp->letter , ptmp->dis);
			ptmp = ptmp->next;
	}
	printf("\n\n~ bacck->press %s b %s" , CRED,CWHITE);
// while(1){
// 	char key = _getch();
// 	if(key == 'b') admin_pannel();
// 	else printf("enter the correct value!");
//    }
}




int fnletter(char* letter_){
	struct ENGLISH_LETTERS lch;
	FILE* fp;


	fp = fopen("C:\\Users\\RSKALA\\Desktop\\dbletters.bin" , "r+b");
	if(!fp)
	{
			printf("no letter\n\n");		
			return 0;
	}
	

	while(fread(&lch , sizeof(struct ENGLISH_LETTERS) ,  1,fp))
	{
		if(!strcmp(letter_ , lch.letter)){
		fclose(fp);
				return 1;
		}

	}

	return 0;

	admin_pannel();



}



//-------------------------------

int main()
{

// r();
// showle();
// Sleep(120000);

	int t = 0, i = 0;
	int key;

	// char message[50] = "WELCOME TO SPARATA DICTIONARY ;)";
	// int ret = GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
	// 	int width = csbi.dwSize.X;

	// 	 for (int i = 0; i < width; i=i+3) {
	// 	 printf("%s - " ,colors[t++]);
	// 	 if (t > 4) t = 0;
	//  }
	//   loop_space(width / 3 + 4);
	//  while (message[i]) {
	// 	 printf("%c", message[i]);
	// 		 Sleep(120);

	// 	 i++;

	//  }




// r();
// printf("this is test");
	// r();
	menue(&key);



// if(key ==1)singin();
	// printf("out");
    // readAndWriteWords();
	// printf("out\n");
	// showle();
	// printf("out");



// showle();
// Sleep(40000);
    // singup();
	
	// show();
	// Sleep(2000);
    //  hndl();
	//  readAndWriteWords();
	//  showle();
	//  Sleep(20000);
	// printf("this is test");
	// struct USER user;
	// // linter(&user);

	// // show();

	// user = singin();
	// // admin_pannel();
	// user_pannel(&user);
	// linter(&user);

	// admin_pannel();
	// // Sleep(4000);


    // user = singin();
	// linter(&user);
	// user_pannel(&user);
	// linter(&user);
    // edit_information(&user);

    //  Search_letter(&user);

	// char key;
	// int emtity;
	// show();
	
	// // linter(&user);
	// admin_pannel();
	
      
    // int position =0;
	// admin_pannel();
	// show();
    // find("name-khatar" , "0914123" ,&position );
	// forgot_password();

	// menue(&key);




	
	// printf("%c", key);
		/*while (1) {*/

			// switch (key)
			// {
			// case '1':
			// 	singup();
			// 	break;
			// case'2':
			//    user= singin();
			//    if(!strcmp(user.user_name , "Admin")) admin_pannel();
			//    else    user_pannel(&user);
			// 	break;
			// case '3':
			// 		forgot_password();
			// 		break;
			
			// case '4':
			// 	exit(0);
			// default:

			// printf("ENTER THE CORRECT VALUE! \n\n");
			// Sleep(1200);
			// system("cls");
			// 	break;

			// }


		//}



	return 0;
}




void menue()
{
	struct USER user;
	char option[4][20] = { "1-Sing up" , " 2-Sing in" , "3-Forgot password", "4 - Exit" };
	char key;
	int t = 0, i = 0;
	int ret = GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
		int width = csbi.dwSize.X;

	
	

	 printf("\n\n");

	
	
	 Sleep(700);
	 system("cls");

	 for (int i = 0; i < width; i = i + 3) {
		 printf("%s - ", colors[t++]);
		 if (t > 4) t = 0;
	 }

	 printf("\n\n\n");
	 loop_space(width / 4);
	 

	
	 for (int i = 0; i <= (width / 2)+width/2 +1; i = i + 2) {
		 printf("%s-" , CBLUE);


	 }
	 printf("\n");
	 loop_space(width / 4);
	 printf("|");

	 for (int i = 0; i < (width / 2) + width / 2;  i=i+2) {
		 printf(" ");


	 }
	 printf("\b|\n");

	 loop_space(width / 4);
	 printf("|");

	 for (int i = 0; i < (width / 2) + width / 2 ; i = i + 2) {
		 printf(" ");


	 }
	 printf("\b|\n");
	 
	 loop_space(width / 4 + 1);
	 printf("\b|   ");
	 //printf("1-Sing up 2-Sing in 3-Forgot password 4-Exit");*/
	 t = 0;
	 do {
		 printf("%s", option[t]);
		 loop_space((width / 31));
		 t++;

	 } while (t<4);
	 
	
	 printf("|\n");
	 loop_space(width / 4);

	  printf("|");
	 for (int i = 0; i < (width / 2) + width / 2; i = i + 2) {
		 printf(" ");


	 }
	 printf("\b|\n");

	 loop_space(width / 4);

	 //printf("");
	 for (int i = 0; i <= (width / 2) + width / 2 + 1; i = i + 2) {
		 printf("%s-", CBLUE);


	 }
	 int test;
	 while (1) {
		 printf("\n\n\n\n %s~ ~ ENTER ONE THIS OPTIONS : ", CRED);
		 key = _getch();
		// scanf("%d" , &key);
		
		 if (key>'4'|| key<'1')
		 {
			 printf("\n\n %s ENTER NUMBER BETWEEN 1 TO 4" ,CRED);
			 Sleep(300);
			//system("cls");
			 continue;
		}

	
		break;




	 }

// while(1){
// 	 if(key == 1) singin();
// 	 else if (key==2){   user= singin();  if(!strcmp(user.user_name , "Admin")) admin_pannel();   else  user_pannel(&user);}
// 	 else if(key ==3) forgot_password();
// 	 else if(key == 4) return ;
// 	//  else

// }
	// 		   else    user_pannel(&user);}
		/*while (1) {*/

			switch (key)
			{
			case '1':
				singup();
				break;
			case'2':
			   user= singin();
			   if(!strcmp(user.user_name , "Admin")) admin_pannel();
			   else    user_pannel(&user);
				break;
			case '3':
					forgot_password();
					break;
			
			case '4':
				return ;
			default:

			printf("ENTER THE CORRECT VALUE! \n\n");
			Sleep(1200);
			system("cls");
				break;

			}


		//}



	//  printf("%s\n\n\n\n", colors[4]);

	// //  while(1){
	// 		switch (key)
	// 		{
	// 		case 1:
	// 			singup();
	// 			break;
	// 		case 2:
	// 		   user= singin();
	// 		   if(!strcmp(user.user_name , "Admin")) admin_pannel();
	// 		   else    user_pannel(&user);
	// 			break;
	// 		case 3:
	// 				forgot_password();
	// 				break;
			
	// 		case 4:
	// 			exit(0);
	// 		default:

	// 		printf("ENTER THE CORRECT VALUE! \n\n");
	// 		Sleep(1200);
	// 		system("cls");
	// 			break;

	// 		}
			// menue();
			// printf("what");
			// key = _getch();

	 }






// }







int check_existing( struct USER user , int* fields){

struct USER check_user;
FILE* fp;

// printf("%s\n\nnoew we are in cheking\n\n" , colors[0]);
fp = fopen("C:\\Users\\RSKALA\\Desktop\\dbuser.bin " , "rb");
while(fread(&check_user , sizeof(struct USER)  , 1 , fp ))
	{ 
		if (!strcmp(check_user.user_name , user.user_name))    fields[0]=1;

		if(!strcmp(check_user.phone_number , user.phone_number))  fields[1]=1;
		
		if(!strcmp(check_user.email , user.email))  	fields[2] =1;
	}
		
		for(int i =0 ; i<3 ; i++)
		{
				if(fields[i])
						return 1;

		}
		return 0;
	}



void singup()
{
    int t=0;
	int flag = 0;
	char key;
	int check_fields[3] ={0,0,0};
	// for(int i=0 ; i<3 ;i ++)  printf("fields -> %d  " , check_fields[i]);
     int i=0;
	struct USER user;

	FILE* fp;
	fp = fopen("C:\\Users\\RSKALA\\Desktop\\dbuser.bin", "a+b" );
    if(!fp) fp = fopen("C:\\Users\\RSKALA\\Desktop\\dbuser.bin" , "w+b" );

	printf("\n\nFILL OUT THE BELOW : \n\n");
    


   
	printf("\n%s ENTER YOUR FIRST NAME ->" , colors[t++]);
	scanf("%s",user.first_name );
  
	printf("\n%s ENTER YOUR LAST NAME ->" , colors[t++]);
	scanf("%s", user.last_name);


	printf("\n%s ENTER YOUR USER-NAME ->" , colors[t++]);
	scanf("%s", user.user_name);
 

	printf("\n%s ENTER YOUR PASSWORD->" , colors[t++]);
	scanf("%s", user.pass);
   

    printf("\n%s ENTER YOUR PHONE ->" , colors[t++]);
    scanf("%s" , user.phone_number);


  printf("\n%s ENTER YOUR EMAIL ->" , colors[0]);
    scanf("%s" , user.email);

	
	while(check_existing(user , check_fields)){

	  if(check_fields[0]==0 && !check_fields[1]==0 && !check_fields[2]==0)  break;

	
	//   for(int i=0 ; i<3 ; i++) printf(" %d " , check_fields[i]);
	//   printf("\n");

			if(i==0 && check_fields[i++]  )	{
					printf("\n\n%sENTER THE %s DIFFERENT %sUSER-NAME%s",CWHITE,CBLUE,CMAG,CWHITE);
					printf("\n\n ~ new %suser-name :%s " , CBLUE,CWHITE);
					scanf("%s" , user.user_name);
				
			}check_fields[0]=0; 
			if(i==1 && check_fields[i++] )	
			{
				printf("ENTER THE %sDIFFERENT %sPHONE-NUMBER%s ",CBLUE,CMAG,CWHITE);
					printf("\n\n ~ new %sphone-number :%s " , CBLUE,CWHITE);


					scanf("%s" , user.phone_number);
						
			

			}check_fields[1]=0; 
			if(i==2 && check_fields[i++] )	{

					printf("ENTER THE DIFFERENT EMAIL \n ~ new email :");
					scanf("%s" , user.email);
					
			}check_fields[2]=0; 
			
			flag = 0;
			i=0;
	
		}
		printf("----------------------------------------------------------------------------%ssuccesfully!%s----------------------------------------------------------------------------",CMAG,CWHITE);

		free_linter_nwords(&user);
		fwrite(&user, sizeof(struct USER) , 1 , fp);

		fclose(fp);
		Sleep(1200);
		system("cls");
		int tmp;
		menue(&tmp);


}



void forgot_password()
{

FILE* fp;
int write =0;
	struct USER user, checke ,tmp;
    int position = 0;

	fp = fopen("C:\\Users\\RSKALA\\Desktop\\dbuser.bin", "r+b" );
	if(!fp)
	{
			printf("DB NOT EXIST");
			Sleep(1000);
			system("cls");
			return ;
	}

while(1){
		printf(" %s ~ ~ %s PLEASE ENTER YOUR USER NAME : " , colors[0] , colors[2]);
		scanf("%s" , user.user_name);
		// strcpy(user.user_name , "new");

	   printf("\n %s ~ ~ %s PLEASE ENTER YOUR PHONE-NUMBER  : " , colors[0] , colors[2]);
		scanf("%s" , user.phone_number);
		// strcpy(user.phone_number , "new");


		if(!strcmp(user.user_name , "Admin")){
			printf("\n\nYOU ARE NOT ADMIN\n");
			Sleep(1000);
			system("cls");
			continue;
		}

		char passw[100];
		fclose(fp);
      if(find( user.user_name, user.phone_number , &tmp ,&position )){
		
		// while(fread(checke.user_name , sizeof(struct USER) , 1, fp)){
		// 		if(!strcmp(checke.user_name,user.user_name)){


							 printf("ENTER NEW PASSWORD : ");
		                      scanf("%s" ,tmp.pass);
			// strcpy(tmp.pass , "123412341234");
			
			
    	                     fseek(fp ,position , SEEK_SET);
	                       fwrite(&tmp , sizeof(struct USER) , 1 , fp); 
						   write = 1;
							break;
					
				}

				if(write) break;


		}
		  

	        //  }

        fclose(fp);
         show();
}
	







struct USER singin()
{	
		
	system("cls");

	FILE* fp;
	struct USER user , checker;


	
	while(1){

		
	fp = fopen("C:\\Users\\RSKALA\\Desktop\\dbuser.bin", "r+b" );
	if(!fp) 
	{	
			printf("NO BODY IN DB\n");
			strcpy(user.user_name , " ");
			return user;

	}
		printf(" %s ~ ~ %s PLEASE ENTER YOUR USER NAME : " , colors[0] , colors[2]);
	     scanf("%s" , user.user_name);

	   printf("\n %s ~ ~ %s PLEASE ENTER YOUR PASSWORD : " , colors[0] , colors[2]);
	    scanf("%s" , user.pass);

		if(!strcmp(user.user_name,"Admin") && !strcmp(user.pass,"Admin") ){
			printf("\n\nWELCOM %sADMIN%s TO YOUR DICTIONAR\n\n" , CBLUE , CWHITE);
			fclose(fp);
		
		
		  	 return user;
	
		}


		while(fread(&checker , sizeof(struct USER) , 1 , fp)){
					if(!strcmp(checker.user_name , user.user_name) && !strcmp(checker.pass , user.pass)){

						printf(" WELCOME %s %s %s TO YOUR DICTIONARY\n\n" , CBLUE ,user.user_name , CWHITE);
						fclose(fp);
						// printf("\n\nnow we are in the sing in  func name : %S  family : %s\n\\n" , user.user_name , user.last_name);
						return checker;
						// fclose(fp);

	
					}

				}	

	printf("\n %s! %s WE DO NOT HAVE THIS %s USER %s PLEASE ENTER THE %s correct %s USER-NAME OR %sPASSWORD  %s!%s " , CRED, CWHITE, CMAG ,CWHITE , CBLUE , CMAG , CMAG ,CRED , CWHITE);
		fclose(fp);
		Sleep(1000);
		system("cls");
		


	}
	
	
}




void show()
{
	int i;
	FILE* fp;
	char test[100];
	struct USER user;
	fp = fopen("C:\\Users\\RSKALA\\Desktop\\dbuser.bin", "rb" );

   while(fread(&user , sizeof(struct USER) , 1 , fp)){
	    i=0;
        printf("\n\nname : %s    last-name:%s  user-name :%s  password : %s  phone :%s email: %s " , user.first_name  , user.last_name , user.user_name ,user.pass, user.phone_number,user.email );
		// while(user.linter_.new_words[i++]) printf("nwords= %s  , ");
		// if(user.linter_.new_words[i]) printf("%s" ,user.linter_.new_words[i]);
		strcpy(test,user.linter_.new_words[i++]);
		if(test) printf("nword: %s\n\n" , test);
  
		printf("\n\n");
   }
		 fclose(fp);

}

void admin_pannel(){

	// COORD t;
	
 struct ENGLISH_LETTERS* head = NULL;
   struct ENGLISH_LETTERS* tmp = make_linked_word();

   if(!head) head = tmp;



	
	

char op;
	
	


printf("~ ~ WITCH OPTION : ");
printf("\n\n1.Add word\n\n2.Edit Word \n\n3.Remove Word\n\n4.Read From File\n\n.Suggested Words\n\n6.Show All Words\n\n7.Back");

while(1){
	printf("\n\n ~ ENTER HERE ->");
	op = _getch();
	if(op<'1' || op >'7' )
	{
			printf("\n\n enter the number between 1 to 7\n\n");
			Sleep(1000);

			system("cls");
			continue;

			}
	break;
}


// char oop;
// while (1)
// {
// 	/* code */



switch (op)
{
case '1':
		add_word();
		break;

	case '2': 
			edit_word();
		
			break;
	case '3' :
			remove_word_l(&head);
			wtire_in_file(head);
			show_lin(head);
     		break;

	case '4':
     	r();
	printf(" ");
	break;

	case '5':
	printf(" ");
	break;

	case '6':
		
	   show_lin(head);
		break;

	case '7':
			menue();
	
	
	default:
	printf("enter corrext vakue !");
	Sleep(1200);
	system("cls");
	break;



}
}


// show_lin(head);
	// showle();
// }
// }





void user_pannel(struct USER* user)
{
	system("cls");
	struct ENGLISH_LETTERS* head;

char oop;
	char op;
	printf("CHOOSE ONE :\n\n1.Search\n2.Linter\n\n3.Test\n\n4.Show Information\n\n5.Edit Inforamtion\n\n6.menue");
    while(1){

	printf("\n\n ~ ENTER HERE ->");
	op = _getch();
	if(op<'1' || op >'7' )
	{
			printf("\n\n enter the number between 1 to 7\n\n");
			Sleep(1000);

			system("cls");
			continue;

			}
	break;
}

switch (op)
{
case '1':
		Search_letter(user);
	break;

	case '2': 
			linter (user);
			printf(" ");
		
			break;
	case '3' :
            printf(" ");
     		break;

	case '4':
    show_information(user);
	break;

	case '5':
	edit_information(user);
    // printf("");
	break;

	case '6':
	
			menue();
            break;
	
	
	default:
	break;




}


}


void add_word(){

	
	// showle();
	struct ENGLISH_LETTERS enletter;
	for(int i=0 ; i<100 ; i++)  enletter.dis[i] = '\0';
	FILE*fp ;
	int i=0;
	char meaning[100];
	int res;
	char ans;
	char anss;
	// fp = fopen("C:\\Users\\RSKALA\\Desktop\\dbletters.bin" , "a+");
	// if(!fp)    fp = fopen("C:\\Users\\RSKALA\\Desktop\\dbletters.bin" , "w+");
	while(1){
			printf("\n\nENTER NEW %sWORD%s : " , CBLUE,CWHITE);
			scanf("%s" , enletter.letter);
		
			
			if(fnletter(enletter.letter)){
					printf("\n\n\nthis letter is %sexist%s",CRED,CWHITE);
					Sleep(1200);
					system("cls");
					printf("\n\ndo you want to continiue ? [y/n]");
					anss = _getch();
					if(anss=='y') continue;
					else if(anss =='n') return;
					else {printf("\n\nenter the carrect value!"); Sleep(1000); system("cls") ; continue;}

			}
			break;
	}
		
	fp = fopen("C:\\Users\\RSKALA\\Desktop\\dbletters.bin" , "a+b");
	if(!fp)    fp = fopen("C:\\Users\\RSKALA\\Desktop\\dbletters.bin" , "w+b");
			// strcmp(enletter.letter , let);
			while(1){
			printf("\n\nENTER THE %sMEANING %s: " , CBLUE , CWHITE);
			// char m[100] =" this is m and it is very good";
			// strcpy(enletter.dis , m);
			// scanf("%s" , enletter.dis);
				scanf("%s",meaning);
			for(i; enletter.dis[i] ; i++ );
			for(int t =0 ; meaning[t]; t++) enletter.dis[i++] = meaning[t];
			enletter.dis[i++] =',';


			printf("\n\nadd an other %smeaning %s? [y,n]\n",CBLUE , CWHITE);
			ans = _getch();
	     	if(ans =='y') continue;
		     else break;
			}
			fwrite(&enletter , sizeof(struct ENGLISH_LETTERS) , 1 , fp);
			
			fclose(fp);


			// printf("this is befor \n");
			// // showle();
			// Sleep(10000);

			admin_pannel();
}




void edit_word(){

	char word[100];
	// showle();
	struct ENGLISH_LETTERS enletter;

	struct ENGLISH_LETTERS* head =NULL;
	struct ENGLISH_LETTERS* ptmp = make_linked_word();

	if(!head) head = ptmp;
	int pos;

	printf("ENTER THE %sLETTER%s : " , CMAG,CWHITE);
	scanf("%s" , word);
	while(!ptmp){
			if(!strcmp(ptmp->letter ,word )){
					printf("\nENTER NEW %sMEANING%s : ",CBLUE,CWHITE);
					scanf("%s" , enletter.dis);
					break;



			}




	}
wtire_in_file(head);
admin_pannel();


}


struct ENGLISH_LETTERS* set_info(struct ENGLISH_LETTERS * head , char* word , char* d){
    struct ENGLISH_LETTERS* tmp =head;

	while(tmp && tmp->next) tmp=tmp->next;


		if(tmp){
		tmp->next = (struct ENGLISH_LETTERS*)malloc(sizeof(struct ENGLISH_LETTERS));
		strcpy(tmp->next->letter , word);
		strcpy(tmp->next->dis , d);
		tmp->next->next = NULL;



	}


	if(!tmp){
		tmp = (struct ENGLISH_LETTERS*)malloc(sizeof(struct ENGLISH_LETTERS));
		strcpy(tmp->letter , word);
		strcpy(tmp->dis , d);
		tmp->next = NULL;


	}


return tmp;



}

struct ENGLISH_LETTERS* make_linked_word()
{

    // showle();
    struct ENGLISH_LETTERS * head = NULL , *ptmp , enletter , *pt;

 
    FILE* fp;
	fp = fopen("C:\\Users\\RSKALA\\Desktop\\dbletters.bin" , "r+b");
  
	if(!fp)
		{
				printf("no %sletter%s",CRED,CWHITE);
				Sleep(1000);
				system("cls");
				return head;

		}

	while(fread(&enletter , sizeof(struct ENGLISH_LETTERS) , 1 , fp)){
                // printf("now word : %s\t\t  di:%s\n\n" , enletter.letter , enletter.dis );

                ptmp = set_info(head,enletter.letter, enletter.dis);
                if(!head) head = ptmp;

        

    }
	fclose(fp);

	return head;


}




void remove_word_l(struct ENGLISH_LETTERS** head)
{


	struct ENGLISH_LETTERS* temp = *head;
	struct ENGLISH_LETTERS* pr =NULL;

char word[2]= "m";
	if(temp!= NULL && !strcmp(temp->letter ,word))
	{
			*head = temp->next;
			free(temp);
			return ;


	}

	while(!temp && strcmp(temp->letter , word)){
				pr = temp;
				temp = temp->next;


	}

	if(!temp) return ;	

	pr->next = temp->next;

	free(temp);



}


void sort(struct ENGLISH_LETTERS** head){
		struct ENGLISH_LETTERS* i , *j;
		if(!*head) return ;
		char temp_letter[100];
		char temp_d[100];


		for(i = *head; i->next ; i = i->next){

				for(j=i->next ; j ; j = j->next){
						if(strcpy(i->letter , j->letter)){
								strcpy(temp_letter , i->letter);
								strcpy(temp_d , i->dis);
								
								strcpy(i->letter , j->letter);
								strcpy(i->dis , j->dis);

								strcpy(j->letter , temp_letter);
								strcpy(j->dis , temp_d);

								


						}


				}



		}
		





}




void wtire_in_file(struct ENGLISH_LETTERS* head )
{

	struct ENGLISH_LETTERS* ptemp = head;
	struct ENGLISH_LETTERS enl;


 FILE* fp;
	fp = fopen("C:\\Users\\RSKALA\\Desktop\\dbletters.bin" , "w+");

	while(ptemp){
			fwrite(&enl , sizeof(struct ENGLISH_LETTERS) , 1 ,fp);
			ptemp = ptemp->next;

	}
fclose(fp);

}




void  free_linter_nwords(struct USER *user){
			for(int i=0 ; i<20 ; i++){
				for(int j=0 ; j<100 ; j++)
						user->linter_.new_words[i][j] ='\0';

			}
			for(int i=0 ; i<20 ; i++){
				for(int j=0 ; j<100 ; j++)
						user->linter_.review[i][j] ='\0';

			}

			
			for(int i=0 ; i<20 ; i++){
				for(int j=0 ; j<100 ; j++)
						user->linter_.conslidation[i][j] ='\0';

			}

for(int i=0 ; i<20 ; i++){
				for(int j=0 ; j<100 ; j++)
						user->linter_.learn_words[i][j] ='\0';

			}

			



}


void fwrite_to_file(struct USER* user)
{
int position = 0;
struct USER checker;

 FILE* fp;
fp = fopen("C:\\Users\\RSKALA\\Desktop\\dbuser.bin" , "r+b");
if(!fp) 
    return;
		
		{
		while(fread(&checker , sizeof(struct USER) , 1 , fp)){
        if(!strcmp(checker.user_name , user->user_name)){
            fseek(fp,position,SEEK_SET);
            fwrite(user , sizeof(struct USER) , 1 , fp);
			return ;
        }
            position+=sizeof(struct USER);

        }
		}

		fclose(fp);

		
}				





void other(struct ENGLISH_LETTERS* head , char* word){
		printf(" ");

}

void Search_letter(struct USER* user){
	// free_linter_nwords(user);

	struct ENGLISH_LETTERS* head = NULL;
    struct ENGLISH_LETTERS* ptmp = make_linked_word();

	if(!head) head = ptmp;
	char word[100];
	char goal_word[20][20];
	char w;
	char ans;
	int i=0 , e ,th;
	// printf("\n ENTER THE WORD : %s" , word);
	for(int i=0; i<100; i++) word[i] ='\0';
	while(1)
		{
		// system("cls");
		printf("\n\n ENTER THE %sWORD %s: %s" ,CBLUE,CWHITE ,word);
	// for(int j=0 ; word[j]='\0' ; j++) printf("%c" , word[j]);
		
		w = _getch();
		
		if(w=='+')
		{
			int t =0 , found =0;
			for(t ; t<20 ;t++){
					for(int j=0 ; j<100 ; j++){
						if(!user->linter_.new_words[t][0]){
							found =1;
							break;


						}


					}
					if (found) break;


			}

			strcpy(user->linter_.new_words[t] ,goal_word[0]);
			// return user ;
			break;
				



		}
		strcpy(goal_word[0] , "  ");
		e=0;
		system("cls");
		ptmp = head;
		
				
		word[i++] = w;
		

		//  for(int i=0;  goal_word[i] ; i++) strcpy(goal_word[i] , " ");

		while(ptmp){
		    

			//    if(i>strlen(ptmp->letter)) continue;
				if(!strncmp(word,ptmp->letter,i)){
					//   goal_word[i-1][20] = ptmp->letter;
						printf("\n%sword %s: %s\t\t %smeaning%s : %s \n", CBLUE,CWHITE ,ptmp->letter ,CBLUE,CWHITE,ptmp->dis);

						strcpy(goal_word[e++] , ptmp->letter);


						


		}
		ptmp = ptmp->next;
		}


	}
	while(1){
	printf("\n\n Do WANT TO CONTINIUE ?[y/n] ");
	// scanf("%s" , &ans);
	ans = _getch();
	if(ans == 'y') break;
	else if (ans=='n') {fwrite_to_file(user);   break; }
	else  continue;

	}



	user_pannel(user);

}


void linter(struct USER* user )
{

    struct ENGLISH_LETTERS* ptmp = make_linked_word();

	struct ENGLISH_LETTERS* head = NULL;

	if(!head) head = ptmp;


	printf("\n\nCHOOSE ONE :\n\n1.new word\n\n2.review\n\n3.consolidation\n\n4.learned words\n\n\n\n~ ~ ENTER HERE -> ");
	char op = _getch();

	switch (op)
	{
	case '1':
		new_words(head,user);
		break;

	case '2':
		review(head , user);
		break;
   
	default:
		break;
	}
	
// review(head , user);


user_pannel(user);


						
}

void show_information(struct USER* user)
{
	system("cls");
        printf("\n1.name : %s\n2.last_name : %s\n3.user-name : %s\n4.phone-number:%s\n5.email: %s\n" , user->first_name,user->last_name,user->user_name,user->phone_number,user->email);
		Sleep(5000);

		user_pannel(user);


}



void edit_information(struct USER* user)
{
    struct USER checke ;
    int position = 0;
    char new[100];
	char tmp[100];
    int ar[3];
    char op;
    system("cls");
    printf("WITCH ONE YOU WANT TO CHANGE ?\n\n1.name \n\n2.last_name\n\n3.user-name\n\n4.password\n\n5.phone-number\n\n6.email\n\n7.user-pannel");
     op = _getch();

     FILE* fp;

	strcpy(tmp , user->user_name);

     switch (op)
     {
     case '1':
     printf("ENTER NEW NAME : ");
     scanf("%s" , user->first_name);
       
       break;
       case '2':
       printf("ENTER NEW LAST-NAME : ");
        scanf("%s" , user->last_name);
        break;

        case '3':
        while(1){
          printf("\n\nENTER %sNEW %sUSER-NAME %s: ", CBLUE,CMAG,CWHITE);
            scanf("%s" , new);
			// strcpy(new,"5");
          if(find_field(new ,op )) { strcpy( tmp , user->user_name); strcpy(user->user_name, new); break;}
          else continue;               

        }
        break;


		case '4':
		   printf("\n\nENTER %sNEW %sPASSWORD %s: ", CBLUE,CMAG,CWHITE);
		   scanf("%s" , user->pass);
		   break;


   case '5':
        while(1){
          printf("\n\n ENTER %sNEW%s  PHONE-NUMBER%s " , CBLUE,CMAG,CWHITE);
          scanf("%s" , new);
		  
		// strcpy(new , "350258923");

          if(find_field (new ,op ))
		  { strcpy(user->phone_number , new); break;}
          else continue;               

        }
        break;


   case '6':
        while(1){
          printf("\n\nENTER %sNEW%s  EMAIL%s : " , CBLUE,CMAG,CWHITE);
          scanf("%s" , new);
		// strcpy(new , "350258923");
          if(find_field(new ,op )) {strcpy(user->email , new); break;}
          else continue;               

        }
        break;

	case '7':
		user_pannel(user);


     default:
	 printf("enter correct value !");
	 Sleep(1200);
	 system("cls");
	//  continue;
        break;
     }


set_new_info(user,tmp);

    
     show();
	 Sleep(4000);
	 user_pannel(user);
    //  return ;
}


void set_new_info(struct USER* user , char* nword){


int position = 0;
struct USER checker;
// char tmp = nword;


 FILE* fp;
fp = fopen("C:\\Users\\RSKALA\\Desktop\\dbuser.bin" , "r+b");
if(!fp) 
    return;



		// while(fread(&checker , sizeof(struct USER ),1,fp))
		
		{
		while(fread(&checker , sizeof(struct USER) , 1 , fp)){
        if(!strcmp(checker.user_name, nword)){

            fseek(fp,position,SEEK_SET);
            fwrite(user , sizeof(struct USER) , 1 , fp);
			return ;
        }
            position+=sizeof(struct USER);

        }
		}

		fclose(fp);


		user_pannel(user);






	
}


void new_words(struct ENGLISH_LETTERS* head , struct USER* user)
{

struct ENGLISH_LETTERS* ptmp = head;


	int i=0 ,t=0,e=0;
	char key;
	while(user->linter_.new_words[i][0]){
	// while(user->linter_.new_words[i])
	// {

			// key = _getch();
		//    if(key == '\r') {

	     system("cls");
		// while(user->linter_.new_words[i][0] ){
			// t=0;
		 	printf("%s       " , user->linter_.new_words[i]); 
			key = _getch();
			 if(key =='\r') { i++; t++ ;continue;}
		
			 if(key == ' '){
				system("cls");

				       
						ptmp = head;
						while(ptmp){
						if(!strcmp(ptmp->letter , user->linter_.new_words[t])){
								printf("%s            " , ptmp->dis);
								break;
							

						}
						ptmp = ptmp->next;
					    // if(!ptmp){	if(user->linter_.new_words[t][0]) ptmp=head;   }
						 
						


						}	t++;


			key = _getch();
		   if(key == ' ')   { t--; continue;}
		   else if(key =='\r') { i++; continue;}




			}







			}
			system("cls");
		printf("\n\nfinised ! !");
		Sleep(300);
			system("cls");
		



}

void conslidation(struct ENGLISH_LETTERS* head, struct USER* user){

struct ENGLISH_LETTERS* ptmp = head;
int e=0;
char ans;
while(user->linter_.new_words[e][0]) {
        strcpy(user->linter_.review[e] , user->linter_.new_words[e] );
		e++;
		}



// struct ENGLISH_LETTERS* ptmp = head;


	int i=0 ,t=0,r=0;
	char key;
	while(user->linter_.new_words[i][0]){
	// while(user->linter_.new_words[i])
	// {

			// key = _getch();
		//    if(key == '\r') {

	     system("cls");
		// while(user->linter_.new_words[i][0] ){
			// t=0;
		 	printf("%s       " , user->linter_.new_words[i]); 
			key = _getch();
			//  if(key =='\r') { i++; t++ ;continue;}
		
			 if(key == ' '){
				system("cls");

				       
						ptmp = head;
						while(ptmp){
						if(!strcmp(ptmp->letter , user->linter_.conslidation[t])){
								printf("%s            " , ptmp->dis);
								break;
							

						}
						int t=0;
						ptmp = ptmp->next;
					    // if(!ptmp){	if(user->linter_.new_words[t][0]) ptmp=head;   }
						 
						


						}	t++;

		while(1){
			for(r ; user->linter_.review[r][0] ; r++);
			printf("\n\n1.learned\n\n 2.Did not learn\n\n ~ ~ ENTER HERE -> ");
			ans = _getch();
			if(ans=='2')  {  break;}
			if(ans == '1') {strcpy(user->linter_.learn_words[r] , user->linter_.new_words[i]); break;}
			else{ printf("\n\nenter the correct value"); Sleep(2000); system("cls"); continue;   }
			


		}

		// 	key = _getch();
		// //    if(key == ' ')   { t--; continue;}
        // //5-----------------------------------
		    // if(key =='\r') { i++ ;--t; continue;} 




			}






// 
			// }
			system("cls");
		printf("\n\nfinised ! !");
		Sleep(300);
			system("cls");
		

	fwrite_to_file(user);





	
}
}


			
		


void showle()
{
	
	system("cls");
		struct ENGLISH_LETTERS lch;
	FILE* fp;

	fp = fopen("C:\\Users\\RSKALA\\Desktop\\dbletters.bin" , "r+b");


	while(fread(&lch , sizeof(struct ENGLISH_LETTERS) ,1 , fp))
			printf("\n\nletter :%s \ndiscription : %s\n\n---------------------------------------------\n",lch.letter , lch.dis);


			fclose(fp);



}
// }

void learned_words_(struct USER* user ){

	int counter =1;
	system("cls");

	for(int i=0 ; user->linter_.learn_words[i][0]; i++)  printf("%d - %s\t" , counter++, user->linter_.learn_words[i]);


	Sleep(2000);





}























	

	













