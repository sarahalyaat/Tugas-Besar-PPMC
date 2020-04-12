#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct node{
	char *word;
	struct node *next;
} node;

typedef struct queue{
	node *front, *rear;
} queue;

//Fungsi mencari value dari key pada text
void searchValue(node **text, queue **key){
	node *currText = *text;		//randomHead(text);
	node *testText;
	node *currKey;
	int found = 0;
	while (found == 0){
		currKey = (*key)->front;
		while(!currKey){
			testText = currText;
			if (strcmp(testText->word,currKey->word)!=0)
				break;
			currKey = currKey->next;
			testText = testText->next;
		}
		if (currKey==NULL){
			found = 1;
		}
		else {
			currText = currText->next;
		}
	}
	printf("%s ",testText->word);
	// dequeue(key);
	// enqueue(key, testText->word);
}