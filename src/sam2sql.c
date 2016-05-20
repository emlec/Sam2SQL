#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <errno.h>
#include <unistd.h>

#define MAX_SAM_COLS 20
/* #define WHERE do { fprintf(stderr,"[DEBUG] JE SUIS %s %d\n",__FILE__,__LINE__);} while(0) */
#define WHERE do { } while(0)

#define CIGAR_COLUMNS 5




int main(int argc,char** argv)
{
    int opt;
    int i;
    char* filename_inputFile = NULL;
    char* filename_outputFile = NULL;
    FILE* inputFile;
    FILE* outputFile; 
    char* line = NULL;
    size_t line_len=0;
    size_t line_buffer=0;
   /* char* read_name; 
    char* well_position[5]; */


//////////////////////////////////////////////////////////////////
//Parsing arguments using getopt
    while ((opt = getopt(argc, argv, "i:o:")) != -1) {
        switch (opt) {
            case 'i':
                filename_inputFile = optarg;
                break;
            case 'o':
                filename_outputFile = optarg;
                break;
            default: 
                fprintf(stderr, "error %s\n", argv[0]); 
                exit(EXIT_FAILURE);
           }
        }
    if (filename_inputFile==NULL){
        fprintf(stderr, "Error undefined samFile input, don't forget -i");
        return EXIT_FAILURE;
    }
    
    if (filename_outputFile==NULL){
        fprintf(stderr, "Error undefined output file, don't forget -o");
        return EXIT_FAILURE;
    }
    
    inputFile = fopen(filename_inputFile, "r");
    if (inputFile==NULL){
        fprintf(stderr,"[%s:%d] Error opening file %s : %s.\n", __FILE__, __LINE__, filename_inputFile, strerror(errno));
        return (EXIT_FAILURE);
    }
    
    outputFile = fopen(filename_outputFile, "w");
    if (inputFile==NULL){
        fprintf(stderr,"[%s:%d] Error opening file %s : %s.\n", __FILE__, __LINE__, filename_outputFile, strerror(errno));
        return (EXIT_FAILURE);
    }
    fprintf(outputFile, "ref_name\tread_name\twell_it\tposition\ttype_mut\tbase_ref\tbase_alt\n");
        
        
//////////////////////////////////////////////////////////////////////////////////        
    //y a t il qq chose a lire
    while(!feof(inputFile))
        {
        int c;
        line_len=0;
        int columns[MAX_SAM_COLS];
        int num_cols=0;
        columns[0]=0;
        
       
        // Pour chaque ligne 
        
        //tant qu'on peut lire un char != \n et EOF
        
        while((c=fgetc(inputFile))!=EOF && c!='\n')
            {
            //faut-il reallouer la ligne
            if(line==NULL || line_len+2 >= line_buffer)
                {
                line_buffer+= 2048;
                line= (char*) realloc(line,sizeof(char)*(line_buffer));
                if(line==NULL) {
                    fprintf(stderr,"[%s:%d] OUT OF MEMORY", __FILE__,__LINE__); 
                    exit(EXIT_FAILURE);
                }
                assert(line!=NULL);
                }
            // à la fin d'un élément 
            if(c=='\t' && num_cols+1< MAX_SAM_COLS)
                {
                c=0;
                ++num_cols;
                columns[num_cols]= line_len+1;   // stockage du nombre de caractère de chaque élément
                }
            

            //on remplit la tableau line caractère par caractère
            line[line_len]=c;
            //et on increment la taille de la chaine
            line_len++;
            
            } //fin de ligne ou EOF
        // mettre EOL
        
        // à la fin de la ligne ajouter 0
        line[line_len]=0;
        
        
        
        if(line[0]=='@') continue;    //pourquoi??
        
        
        fprintf(stdout,"%s\n",line);
        for(i=0; i<num_cols;++i)
            {
            printf("col[%d]=%s\n",i,&line[columns[i]]);   // pas compris
            }
        fprintf(stdout,"CIGAR=%s\n",&line[columns[CIGAR_COLUMNS]]);

        int cigar_len=strlen(&line[columns[CIGAR_COLUMNS]]);
        
        fprintf(stdout, "CIGAR_LEN = %d\n", cigar_len);
        
   /*     // Extract read_name and well_position 
        fprintf(stderr, "read_name :\n");
        read_name = malloc(sizeof(char)*(strlen(&line[columns[0]])));
        for (i=0; i<strlen(&line[columns[0]]);i++){
            while(line[i]!="/"){
                read_name[i]=line[i];
            }
            if(line[i]=="/") {i++; while(line[i]!="/"){well_position
            
        }*/
        fprintf(stderr, "\n");
        
        /*while(i<cigar_len)
            {
            if (isdigit(&line[columns[CIGAR_COLUMNS]])){
            //if(issdii(cigar[i]) {
                cigar_len = cigar_len*10+ cigar[i]-'0';
                }
            else //operator M,S
            }
        i++;
        // strol
        }*/
        
    WHERE;

    free(line);
    
    }
    
    fclose(inputFile);
    fclose(outputFile);
    return 0;
}

