#include <stdio.h>
#include <string.h>

#define Total_Keywords 10
char keywords[Total_Keywords][10] = {"int","int[]","return","float","float[]","double","double[]","void","char","char[]"};

int isKeyWord(char word[]);
void checkWord(char word[]);
char* ConstantOrIdentifier(char string[]);

int main(){
    FILE *file = fopen("input.txt","r");
    if(file){
        char word[20];
        while(fscanf(file,"%s",word)!=EOF){
            if(isKeyWord(word)){
                printf("%s -- Keyword\n",word);
            }else{
                checkWord(word);
            }
        }
    }else{
        printf("File not found");
    }
    fclose(file);
    return 0;
}

int isKeyWord(char word[]){
    for(int i=0;i<Total_Keywords;i++){
        if(strcmp(word,keywords[i])==0)
            return 1;
    }
    return 0;
}

char* ConstantOrIdentifier(char string[]){
    int len=strlen(string);
    if(string[0]=='"' && string[len-1]=='"'){
        return "string constant";
    }else if(string[0]=='\'' && string[len-1]=='\''){
        return "character constant";
    }
    int isInt=1;
    for(int i=0;i<len;i++){
        if(string[i]=='.' && isInt){
            isInt=0;
        }else if(47>string[i] || 58<string[i]){
            return "Identifier";
        }
    }
    return isInt ? "integer constant" : "Decimal constant";
}

void checkWord(char word[]){
    int wordlen = strlen(word);
    char var[wordlen];
    strcpy(var,"");
    for(int i=0;i<wordlen;i++){
        switch(word[i]){
            case ';':   if(strcmp(var,"")!=0){
                            char *string = ConstantOrIdentifier(var);
                            printf("%s -- %s\n",var,string);
                        }
                        printf("; -- End of statement\n");
                        strcpy(var,"");
                        break;

            case ',':   if(strcmp(var,"")!=0){
                            char *string = ConstantOrIdentifier(var);
                            printf("%s -- %s\n",var,string);
                        }
                        printf(", -- special symbol\n");
                        strcpy(var,"");            
                        break;

            case '=':   if(strcmp(var,"")!=0){
                            char *string = ConstantOrIdentifier(var);
                            printf("%s -- %s\n",var,string);
                        }
                        printf("= -- assignment operator\n");
                        strcpy(var,"");            
                        break;

            case '{': printf("{ -- opening block\n");
                        strcpy(var,"");            
                        break;

            case '}': printf("} -- closing block\n");
                        strcpy(var,"");
                        break;

            case ')': printf("%s) -- function\n",var);
                        strcpy(var,"");
                        break;

            default: strncat(var,&word[i],1);
        }
    }
    if(strcmp(var,"")!=0)
        printf("%s -- Identifier\n",var);
}