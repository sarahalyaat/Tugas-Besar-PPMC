#include<stdio.h>
#include<stdlib.h>
#include<string.h>


//Test
node* randomHead(node **text,int n){
	int r = (rand() % n) + 1;
	int i = 0;
	node *head = *text;
	printf("%d\n",r);

	for(i = 0; i < r; i++){
		head = head->next;
	}
	return (head);
}

//Fungsi mencari value dari key pada text
void searchValue(node **text, queue **key, int n){
	node *currText = randomHead(text,n);
	node *testText;									
	node *currKey;
	int found = 0;
	while (found == 0){		
		currKey = (*key)->front;
		testText = currText;
		while(currKey!=NULL){
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
	printf("val: %s ",testText->word);
	// dequeue(key);
	// enqueue(key, testText->word);
}



