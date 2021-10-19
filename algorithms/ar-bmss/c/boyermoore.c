#include<stdio.h>
#include<string.h>
#include<ctype.h>

int* lastOcurences(char Pattern[]);//generate last ocurences of each character in pattern and not in pattern
int* lastOcurences_version_2(char Pattern[]);

void booyerMoore(char Text[],char Pattern[]);

void main(argc,argv)
	int argc;
	char* argv[];
	{
		if(argc==3){
			booyerMoore(argv[1],argv[2]);
		}
		else{
			fprintf(stderr,"Input Format: booyerMoore.exe \"Text\" \"Pattern\"");
		}
	}

int* lastOcurences(char Pattern[]){
	char alphabet[]={"abcdefghijklmnopqrstuvwxyz"};
	char *P=Pattern,*A=alphabet;

	int i,j,lengthOfPattern;
	if(Pattern[0] != '\0'){
	i,j,lengthOfPattern = strlen(Pattern)-1;
	}
	static int last[26];//we return this array so we need to define it as static

	printf("Last Ocurences Table: |");
	for(i=0;i<26;i++){
		for(j=lengthOfPattern;j>-1;j--){
			if(*(P+j)==*(A+i)){
				last[i]=j;
				break;
			}
			last[i]=-1;
		}
	printf("%d|",last[i]);
	}
	printf("\n");
	return last;
}

//Second version of last ocurences finding method(Efficient one)
int* lastOcurences_version_2(char Pattern[]){
	//char alphabet[]={"abcdefghijklmnopqrstuvwxyz"};
	char *P=Pattern;

	int i,j,k,lengthOfPattern;
    	if(Pattern > 1){
    	i,j,k,lengthOfPattern = strlen(Pattern)-1;
    	}
	static int last[26];
	for(i=0;i<26;i++){//assign every character as -1->T.C=O(sizeof alphabet)
		last[i]=-1;
	}
	for(j=0;j<lengthOfPattern+1;j++){//in pattern we assign each character's place again in that table->T.C=O(sizeof pattern)
		last[*(P+j)-97]=j;
	}
	//print last table
	printf("Last Ocurences Table: ");
	for(k=0;k<26;k++){
		printf("[%d]",last[k]);
	}
	return last;
}

void booyerMoore(char Text[],char Pattern[]){
	printf("Text: %s\nPattern: %s\n",Text,Pattern);

	int i,n,m,s=0;
	if(Text[0] != '\0' && Pattern != '\0'){
	i,n=strlen(Text);
	m=strlen(Pattern);
	}
	int *last=lastOcurences(Pattern);//create a pointer and assign lastOcurences table to it

	char *P=Pattern,*T=Text;//create two char pointers to access Pattern and Text

	for(i=0;i<n-m+1;i++){
		int j=m-1;
		while((*(P+j)==*(T+s+j))&&(j>0)){//loop works until characters match(from right->left) each other
			j--;
		}
		if(j==0){//if loop ends we check whether j came to end of pattern.It means that pattern matched.
			printf("Match At: %d",s);
			exit(0);
		}
		else{//*(P+j)-98 this means we get the mismatched characters position by its asscii value to access our last ocurence table
			//and the code will not work for uppercase letters
			if(*(last+*(P+j)-98)<j){
				s+=j-*(last+*(P+j)-98);
			}
			else if((*(last+*(P+j)-98)>j)||(*(last+*(P+j)-98)==-1)){
				s++;
			}
		}
	}
	printf("No Match!!!");
}
//pre-condition: Before excuting move to folder contain exe file
//Input in cmd: naiveMatch.exe "Text" "Pattern"
