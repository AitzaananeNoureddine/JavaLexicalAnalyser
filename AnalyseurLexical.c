#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>
#include "rlutil.h" /// biliotheque servant à modifier la couleur du text dans la console


int ident(char c,int* current_state){   // traduction de l'automate définissant les identificateurs en java
    int ascii=c;

    if(*current_state==0){
        if((ascii>=65 && ascii<=90) || (ascii>=97 && ascii<=122) || ascii==36 || ascii==95) return 1;
        else return -1;
    }
    if(*current_state==1){
        if((ascii>=65 && ascii<=90) || (ascii>=97 && ascii<=122) || (ascii>=48 && ascii<=57) ||ascii==36 || ascii==95) return 1;
        else return -1;
    }

}

int comment(char c,int* current_state){ // traduction de l'automate définissant les commentaires en java
    int ascii=c;
    if(*current_state==0){
        if(ascii==47) return 1;
        else return -1;
    }
    else if(*current_state==1){
        if(ascii==47) return 2;
        else if(ascii==42) return 3;
        else return -1;
    }
    else if(*current_state==2){
        if(ascii==10) return -1; // 10 ascii code for new line charachter(\n)
        else return 2;
    }
    else if(*current_state==3){
        if(ascii==42) return 4;
        else if(ascii==10) return 3; // 10 ascii code for new line charachter(\n)
        else return 3;
    }
    else if(*current_state==4){
        if(ascii==47) return 5;
        else return -1;
    }
    else if(*current_state==5){
        return -1;
    }
}

int chaine(char c,int* current_state){  // traduction de l'automate définissant les chaines de caractères en java
    int ascii=c;
    if(*current_state==0){
        if(ascii==34) return 1;
        else return -1;
    }
    if(*current_state==1){
        if(ascii==34) return 2;
        else return 1;
    }
    if(*current_state==2) return -1;
}

int num(char c,int* current_state){ // traduction de l'automate définissant les nombres en java
    int ascii=c;
    if(*current_state==0){
        if(ascii>=48 && ascii<=57) return 1;
        else return -1;
    }
    if(*current_state==1){
        if(ascii>=48 && ascii<=57) return 1;
        else return -1;
    }
}

int logicOp(char c,int* current_state){ // traduction de l'automate définissant les operateurs logiques en java
    int ascii=c;
    if(*current_state==0){
        if(ascii==38) return 1;
        else if(ascii==124) return 2;
        else if(ascii==33) return 3;
        else return -1;
    }
    if(*current_state==1){
        if(ascii==38) return 3;
        else return -1;
    }
    if(*current_state==2){
        if(ascii==124) return 3;
        else return -1;
    }
    if(*current_state==3){
        return -1;
    }
    
}

int sep(char c,int* current_state){ // traduction de l'automate définissant les separateurs en java
    int ascii=c;
    if(*current_state==0){
        if(ascii==40 || ascii==41 || ascii==123 || ascii==125 || ascii==91 || ascii==93 || ascii==59 || ascii==46 || ascii==44) return 1;    
        else return -1;
    }
    if(*current_state==1) return -1;
}

int rel_op(char c,int* current_state){  // traduction de l'automate définissant les operateurs relationnels en java
    int ascii=c;
    if(*current_state==0){
        if(ascii==61 || ascii==33) return 1;
        else if(ascii==60) return 3;
        else if(ascii==62) return 4;
        else return -1;
    }
    if(*current_state==1){
        if(ascii==61) return 2;
        else return -1;
    }
    if(*current_state==2){
        return -1;
    }
    if(*current_state==3){
        if(ascii==61) return 2;
        else return -1;
    }
    if(*current_state==4){
        if(ascii==61) return 2;
        else return -1;
    }
}

int aff_op(char c,int* current_state){  // traduction de l'automate définissant les operateurs d'affectation en java
    int ascii=c;
    if(*current_state==0){
        if(ascii==61) return 1;
        else if(ascii==43) return 2;
        else if(ascii==45) return 3;
        else if(ascii==47) return 4;
        else if(ascii==37) return 5;
        else if(ascii==42) return 6;
        else return -1;
    }
    if(*current_state==2){
        if(ascii==43) return 7;
        else if(ascii==61) return 8;
        else return -1;
    }
    if(*current_state==3 || *current_state==5 || *current_state==4 || *current_state==6){
        if(ascii==61) return 8;
        else return -1;
    }
    if(*current_state==7 || *current_state==8 || *current_state==1) return -1;
}

int numericOp(char c,int* current_state){   // traduction de l'automate définissant les operateurs arithmetiques en java
    int ascii=c;
    if(*current_state==0){
        if(ascii==43 || ascii==45 || ascii==42 || ascii==47 || ascii==37) return 1;    
        else return -1;
    }
    if(*current_state==1) return -1;
}

int escape(char c,int* current_state){ // traduction de l'automate définissant les blancs en java
    int ascii=c;
    if(*current_state==0){
        if(ascii==32 || ascii==9 || ascii==10) return 1;
        else return -1;
    }
    if(*current_state==1){
        if(ascii==32 || ascii==9 || ascii==10) return 1;
        else return -1;
    }
}

int isKeyword(char* lexeme){ /// fonction pour verifier si l'identificateur en entrée est un mot clé en java ou pas
    char keywords[55][100]={"java","int","Exception","abstract","assert","boolean","break","byte","case","catch","char","class","const","continue","default","do","double","else","enum","extends","final","finally","float","for","if","goto","implements","import","instanceof","int","interface","long","native","new","package","private","protected","public","return","short","static","strictfp","super","switch","synchronized","this","throw","throws","transient","try","void","volatile","while","String","null"};
    int i;
    bool b=false;
    for(i=0;i<55;i++){
        if(strcmp(lexeme,keywords[i])==0) b=true;
    }
    return b;
}
int main(){

    char input[200];
    char lexeme[1000],ul[30];
    int ptrDebut=0,ptrFin=0,current=-1,i=0;
    int current_blank=0,current_iden=0,current_num=0,current_com=0,current_ch=0,current_sep=0,current_numop=0,current_lop=0,current_rel=0,current_aff=0;
    int loop,reset,ligne=1;
    char errors[200]=""; /// la taille du tableau errors correspond au nombre de ligne dans le code à compiler

    //// ouverture du fichier contenant le code java à compiler /////
    FILE* file_ptr=fopen("Expression.java","r");
    if(file_ptr==NULL){
        printf("file 'Expression.java' was not found\n");
        exit(0);
    }
    
    for(i=0;i<200;i++) input[i]=0;
    for(i=0;i<1000;i++) lexeme[i]=0;
    while (!feof(file_ptr)){ // tant que la fin du document n'est pas atteint
        fgets(input,200,file_ptr); /// lecture ligne par ligne à partir du fichier .java
        ptrDebut=0;ptrFin=0;
        for(loop=0;loop<sizeof(input)/sizeof(input[0]);loop++){
            i=0;
            /////////// LES ESPACES,TABS,(\n) ///////
            while(escape(input[ptrFin],&current_blank)!=-1 && i<strlen(input)-1){
                for(reset=0;reset<sizeof(lexeme)/sizeof(lexeme[0]);reset++) lexeme[reset]=0;
                lexeme[i]=input[ptrFin];
                current_blank=escape(input[ptrFin],&current_blank);
                ptrFin++;
                i++;
            }
            if(current_blank==1){
                current_blank=0;
                ptrDebut=ptrFin;
            }
            else{
                ptrFin=ptrDebut;
            }
            /////////// LES ESPACES,TABS,(\n) ///////
            i=0;
            /////////// IDENTIFICATEURS //////////////
            while(ident(input[ptrFin],&current_iden)!=-1){
                lexeme[i]=input[ptrFin];
                current_iden=ident(input[ptrFin],&current_iden);
                ptrFin++;
                i++;
            }
            if(current_iden==1){
                current_iden=0;
                ptrDebut=ptrFin;
                if(isKeyword(lexeme)) strcpy(ul,"Mot clé");
                else strcpy(ul,"Identificateur");
                setColor(GREEN); /// changer la couleur du text en vert
                printf("lexeme : ");
                setColor(WHITE); /// reinitializer la couleur en blanc
                printf("%s",lexeme);
                printf("\t");
                setColor(GREEN);
                printf(";ul : ");
                setColor(WHITE);
                printf("%s",ul);
                printf("\n");
                for(reset=0;reset<sizeof(lexeme)/sizeof(lexeme[0]);reset++) lexeme[reset]=0;
            }
            else{
                ptrFin=ptrDebut;
            }
            /////////// IDENTIFICATEURS //////////////
            i=0;
            /////////// NOMBRES ////////////////
            while(num(input[ptrFin],&current_num)!=-1){
                lexeme[i]=input[ptrFin];
                current_num=num(input[ptrFin],&current_num);
                ptrFin++;
                i++;
            }
            if(current_num==1){
                current_num=0;
                ptrDebut=ptrFin;
                strcpy(ul,"Nombre");
                setColor(GREEN);
                printf("lexeme : ");
                setColor(WHITE);
                printf("%s",lexeme);
                printf("\t");
                setColor(GREEN);
                printf(";ul : ");
                setColor(WHITE);
                printf("%s",ul);
                printf("\n");
                for(reset=0;reset<sizeof(lexeme)/sizeof(lexeme[0]);reset++) lexeme[reset]=0;
            }
            else{
                ptrFin=ptrDebut;
            }
            /////////// NOMBRES ////////////////
            i=0;
            /////////// COMMENTAIRES ////////////////
            Roll :
            while(comment(input[ptrFin],&current_com)!=-1 && ptrFin<=sizeof(input)/sizeof(input[0])){
                if((int)input[ptrFin]==10 && current_com==3) goto next;
                if((int)input[ptrFin]==10) input[ptrFin]=' ';
                lexeme[i]=input[ptrFin];
                current_com=comment(input[ptrFin],&current_com);
                ptrFin++;
                i++;
            }
            errors[ligne]=input[ptrFin]; // detection et ajout d'une erreur lexicale
            if(current_com==3 && ptrFin>sizeof(input)/sizeof(input[0])){
                next : 
                for(reset=0;reset<200;reset++) input[reset]=0;
                fgets(input,200,file_ptr);
                ptrDebut=0;
                ptrFin=0;
                ligne++;
                goto Roll;
            }
            if(current_com==2 || current_com==5){
                current_com=0;
                ptrDebut=ptrFin;
                strcpy(ul,"Commentaire");
                setColor(GREEN);
                printf("lexeme : ");
                setColor(WHITE);
                for(reset=0;reset<i;reset++){
                    if((int)lexeme[reset]>0) printf("%c",lexeme[reset]);
                }
                printf("\t");
                setColor(GREEN);
                printf(";ul : ");
                setColor(WHITE);
                printf("%s",ul);
                printf("\n");
                for(reset=0;reset<sizeof(lexeme)/sizeof(lexeme[0]);reset++) lexeme[reset]=0;
            }
            else{
                ptrFin=ptrDebut;
            }
            /////////// COMMENTAIRES ////////////////
            i=0;
            ////////// OPERATEURS RELATIONNELS //////////
            while(rel_op(input[ptrFin],&current_rel)!=-1){
                lexeme[i]=input[ptrFin];
                current_rel=rel_op(input[ptrFin],&current_rel);
                ptrFin++;
                i++;
            }
            if(current_rel==2 || current_rel==3 || current_rel==4){
                current_rel=0;
                ptrDebut=ptrFin;
                strcpy(ul,"Operateur relationnel");
                setColor(GREEN);
                printf("lexeme : ");
                setColor(WHITE);
                printf("%s",lexeme);
                printf("\t");
                setColor(GREEN);
                printf(";ul : ");
                setColor(WHITE);
                printf("%s",ul);
                printf("\n");
                for(reset=0;reset<sizeof(lexeme)/sizeof(lexeme[0]);reset++) lexeme[reset]=0;
            }
            else{

                if(rel_op(input[ptrFin],&current_rel)==-1) current_rel=0;
                ptrFin=ptrDebut;
            }
            ////////// OPERATEURS RELATIONNELS //////////
            i=0;
            ////////// OPERATEURS D AFFECTATION //////////
            while(aff_op(input[ptrFin],&current_aff)!=-1){
                lexeme[i]=input[ptrFin];
                current_aff=aff_op(input[ptrFin],&current_aff);
                ptrFin++;
                i++;
            }
            if(current_aff==7 || current_aff==8 || current_aff==1){
                current_aff=0;
                ptrDebut=ptrFin;
                strcpy(ul,"Operateur d'affectation");
                setColor(GREEN);
                printf("lexeme : ");
                setColor(WHITE);
                printf("%s",lexeme);
                printf("\t");
                setColor(GREEN);
                printf(";ul : ");
                setColor(WHITE);
                printf("%s",ul);
                printf("\n");
                for(reset=0;reset<sizeof(lexeme)/sizeof(lexeme[0]);reset++) lexeme[reset]=0;
            }
            else{
                ptrFin=ptrDebut;
            }
            ////////// OPERATEURS D AFFECTATION //////////
            i=0;
            ////////// OPERATEURS NUMERIQUES //////////
            while(numericOp(input[ptrFin],&current_numop)!=-1){
                for(reset=0;reset<sizeof(lexeme)/sizeof(lexeme[0]);reset++) lexeme[reset]=0;
                lexeme[i]=input[ptrFin];
                current_numop=numericOp(input[ptrFin],&current_numop);
                ptrFin++;
                i++;
            }
            if(current_numop==1){
                current_numop=0;
                ptrDebut=ptrFin;
                strcpy(ul,"Operateur numerique");
                setColor(GREEN);
                printf("lexeme : ");
                setColor(WHITE);
                printf("%s",lexeme);
                printf("\t");
                setColor(GREEN);
                printf(";ul : ");
                setColor(WHITE);
                printf("%s",ul);
                printf("\n");
                for(reset=0;reset<sizeof(lexeme)/sizeof(lexeme[0]);reset++) lexeme[reset]=0;
            }
            else{
                ptrFin=ptrDebut;
            }
            ////////// OPERATEURS NUMERIQUES //////////
            i=0;
            ////////// CHAINES DE CARACTERES ///////
            while(chaine(input[ptrFin],&current_ch)!=-1){
                lexeme[i]=input[ptrFin];
                current_ch=chaine(input[ptrFin],&current_ch);
                ptrFin++;
                i++;
            }
            if(current_ch==2 || current_ch==5){
                current_ch=0;
                ptrDebut=ptrFin;
                strcpy(ul,"Chaine de caractères");
                setColor(GREEN);
                printf("lexeme : ");
                setColor(WHITE);
                printf("%s",lexeme);
                printf("\t");
                setColor(GREEN);
                printf(";ul : ");
                setColor(WHITE);
                printf("%s",ul);
                printf("\n");
                for(reset=0;reset<sizeof(lexeme)/sizeof(lexeme[0]);reset++) lexeme[reset]=0;
            }
            else{
                ptrFin=ptrDebut;
            }
            ////////// CHAINES DE CARACTERES ///////
            i=0;
            ////////// SEPARATEURS //////////
            while(sep(input[ptrFin],&current_sep)!=-1){
                lexeme[i]=input[ptrFin];
                current_sep=sep(input[ptrFin],&current_sep);
                ptrFin++;
                i++;
            }
            if(current_sep==1){
                current_sep=0;
                ptrDebut=ptrFin;
                strcpy(ul,"Separateur");
                setColor(GREEN);
                printf("lexeme : ");
                setColor(WHITE);
                printf("%s",lexeme);
                printf("\t");
                setColor(GREEN);
                printf(";ul : ");
                setColor(WHITE);
                printf("%s",ul);
                printf("\n");
                for(reset=0;reset<sizeof(lexeme)/sizeof(lexeme[0]);reset++) lexeme[reset]=0;
            }
            else{
                ptrFin=ptrDebut;
            }
            ////////// SEPARATEURS //////////
            i=0;
            ////////// OPERATEURS LOGIQUES //////////
            while(logicOp(input[ptrFin],&current_lop)!=-1){
                lexeme[i]=input[ptrFin];
                current_lop=logicOp(input[ptrFin],&current_lop);
                ptrFin++;
                i++;
            }
            if(current_lop==1 || current_lop==2 || current_lop==3){
                current_lop=0;
                ptrDebut=ptrFin;
                strcpy(ul,"Operateur logique");
                setColor(GREEN);
                printf("lexeme : ");
                setColor(WHITE);
                printf("%s",lexeme);
                printf("\t");
                setColor(GREEN);
                printf(";ul : ");
                setColor(WHITE);
                printf("%s",ul);
                printf("\n");
                for(reset=0;reset<sizeof(lexeme)/sizeof(lexeme[0]);reset++) lexeme[reset]=0;
            }
            else{
                ptrFin=ptrDebut;
            }
            ////////// OPERATEURS LOGIQUES //////////
            
        }
        for(loop=0;loop<sizeof(input)/sizeof(input[0]);loop++) input[loop]=0; /// vider la variable pour contenir la ligne suivante
        ligne++;
    }
    fclose(file_ptr);
    ////////// AFFICAHGE DES ERREURS LEXICALES //////////
    for(i=0;i<sizeof(errors)/sizeof(errors[0]);i++){
        if((int)errors[i]!=0 && (int)errors[i]!=10){
            setColor(RED);
            printf("Erreur lexicale ");
            setColor(WHITE);
            printf("[%c]",errors[i]);
            setColor(RED);
            printf(" ligne : ");
            setColor(WHITE);
            printf("%d\n",i);
        }
    }

    return 0;
}