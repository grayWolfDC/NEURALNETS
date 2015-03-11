#include <stdio.h>
#include <stdlib.h>
#include "fann.h"

#define MAX_LINE 1024
void printUsage()
{
    printf("PrintConMat <network file> optional:<outputfile>\n");
}

int main (int argc, char** argv)
{
    FILE *fp;
    char* annFile; 
    char * connFile;
    struct fann *ann;
    struct fann_connection *con;  // weight matrix
    unsigned int connum;    // connections number
    unsigned int i = 0;
    unsigned int printOpt=0;
    if (argc == 3)
        printOpt = 1;    
    
    if (argc <2 || argc > 3)
        printUsage();
    
    annFile = argv[1];
    ann = fann_create_from_file(annFile);    

    if (printOpt)
    {
        connFile = argv[2];
        fp = fopen(connFile,"w+");
    }

    /* Begin -- Weight matrix printing bit*/
    
    connum = fann_get_total_connections(ann);
    if (connum == 0) 
    {
        fprintf(stderr,"Error: connections count is 0\n");
        return EXIT_FAILURE;
    }
    con = calloc(connum,sizeof(*con));
    if (con == NULL) {
        fprintf(stderr, "Error: unable to allocate memory\n");
        return EXIT_FAILURE;
    }
    // Get weight matrix
    fann_get_connection_array(ann,con);
    // Print weight matrix
    for (i=0;i<connum;++i) 
    {
        printf("weight from %u to %u: %f\n",con[i].from_neuron,
                con[i].to_neuron,con[i].weight);
        if (printOpt)
            fprintf(fp,"%u,%u,%f\n",con[i].from_neuron,
                con[i].to_neuron,con[i].weight);
    }
    free(con);
    if (printOpt)
        fclose(fp);
    /* End -- Weight matrix printing bit */
}
