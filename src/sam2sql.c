#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<assert.h>
#define MAX_SAM_COLS 20
/* #define WHERE do { fprintf(stderr,"[DEBUG] JE SUIS %s %d\n",__FILE__,__LINE__);} while(0) */
#define WHERE do { } while(0)

#define CIGAR_COLUMNS 5



int main(int argc,char** argv)
{
int i;
FILE* in = stdin;
char* line = NULL;
size_t line_len=0;
size_t line_buffer=0;
//y a t il qq chose a lire
while(!feof(in))
	{
	int c;
	line_len=0;
	int columns[MAX_SAM_COLS];
	int num_cols=0;
	columns[0]=0;
	//on lit une line
	//tant qu'on peut lire un char != \n et EOF
	while((c=fgetc(in))!=EOF && c!='\n')
		{
		//faut-il reallouer la ligne
		if(line==NULL || line_len+2 >= line_buffer)
			{
			line_buffer+= 2048;
			line= (char*) realloc(line,sizeof(char)*(line_buffer));
			assert(line!=NULL);
			}
		
		if(c=='\t' && num_cols+1< MAX_SAM_COLS)
			{
			c=0;
			++num_cols;
			columns[num_cols]= line_len+1;
			}
		

		//on specifier le line_len-th character
		line[line_len]=c;
		//et on increment la taille de la chaine
		line_len++;
		
		} //fin de ligne ou EOF
	// mettre EOL
	line[line_len]=0;
	
	if(line[0]=='@') continue;
	
	fprintf(stdout,"%s\n",line);
	for(i=0;i< num_cols;++i)
		{
		printf("col[%d]=%s\n",i,&line[columns[i]]);
		}
	fprintf(stdout,"CIGAR=%s\n",&line[columns[CIGAR_COLUMNS]]);
	
	int cigar_len=0;
	while()
		{
		if(issdii(cigar[i]) {
			cigar_len = cigar_len*10+ cigar[i]-'0';
			}
		else //operator M,S
		}
	
	// strol
	}
WHERE;
free(line);
return 0;
}
