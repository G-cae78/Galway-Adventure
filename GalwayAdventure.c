/*Chukwuma Anayo-Ezikeoha
        22358526
                22/03/23*/
#include <stdio.h>
#include <string.h>
#include<stdbool.h>
#include<ctype.h>

typedef struct {
    char description[100];
    int n, s, e, w, in, out;
} location;

typedef struct{
    char objdescription[100];//variable to store description of objects
    char name[100];//variable to store name of objects
    int location;
}object;//struct to store data for objects

object objects[30];
location locations[40];
int numLocations = 0;
int numobjects=0;
char locationsFile[] = "/Users/georgea.e/Documents/First Year/C/adventure_locations.txt";//file path of locations
char objfile[]="/Users/georgea.e/Documents/First Year/C/adventure_objects.txt";//file path of locations
char itemtaken[100];
char itemdropped[100];
char examine[100];
char object1[100];
char object2[100];
FILE* openFileForReading(char* filename) {
    FILE* file_ptr = fopen(filename, "r");//reading in file
    if (file_ptr == NULL) 
        printf("Could not open %s\n", filename);//printing error message
    return file_ptr;
}

bool readLocations() {
    FILE* file_ptr = openFileForReading(locationsFile);
    if (file_ptr == NULL)
        return false;

    numLocations = 0;
    int readHeaderLines = 0;
    char line[200];
    while (fgets(line, 99, file_ptr) != NULL) {
        if (readHeaderLines<2)//ignoring first two lines of file
            readHeaderLines++;
        else {
            numLocations++;//counting numbner of locations
            location l;
            int locNum;
            sscanf(line, "%d\t%d\t%d\t%d\t%d\t%d\t%d\t%[^\t]\n", &locNum, &l.n, &l.s, &l.e, &l.w, &l.in, &l.out, l.description);//scanniong in location
            locations[numLocations] = l; // the 1st location is 1 (not 0) so we can use 0 to mean 'nothing' in adventure_locations.txt
        }
    }

    return true;
}

bool readobjects() {
    FILE* fptr = openFileForReading(objfile);
    if (fptr == NULL)
        return false;

    numobjects = 0;
    int readHeader = 0;
    char line[200];
    while (fgets(line, 99, fptr) != NULL) {
        if (readHeader<2)//ignoring first two lines of file
            readHeader++;
        else {
            numobjects++;//counting numbner of locations
            object Obj;
            //int objNum;
            sscanf(line, "%[^\t]\t%d\t%[^\t]\n", &Obj.name, &Obj.location, &Obj.objdescription);//scanniong in objects
            objects[numobjects] = Obj; // the 1st location is 1 (not 0) so we can use 0 to mean 'nothing' in adventure_locations.txt
        }
    }

    return true;
}

 //char droportake[100];
 void take(int userlocation, int objectlocation);//function prototype to pick objects
 void drop(int userlocation, int objectlocation);//function prorotype to drop objects 



int main() {
   
    char userInput[100];
   // char caseInput[100];
    
    int userlocation=1;
   // int USBdrivelocation=1;
   //int Icecreamlocation=2;
    char delim[100]= "nsweinoutlost";
    char delims[100]= "droptake";
    if (readLocations()&& readobjects()) {
        printf("\nSuccessfully read %d locations and %d Objects from file\n", numLocations,numobjects);//telling user how many locations were read in 
         
         
    }
    
   printf("\nWelcome to Galway Adventure. Type 'Lost' if you are stuck.\n\n");
    
    
   

    while(strcmp(userInput,"quit")!=0){
   
     printf(">");
     scanf("%s",userInput);

     //userInput = tolower(caseInput);

    if(strcmp(userInput,"quit")==0){//if user inputs quit end loop
      printf("\nExting game...........\n");
    }

    else if(strcmp(userInput,delim)){
        //while(strcmp(userInput,"quit")!=0){
        
             if(strcmp(userInput,"lost")==0){
                 printf("\nHere are the commands:\nn   s   e   w   in   out   look   lost  take drop  quit\n");//telling user commands to use if lost
            }
             else if(!strcmp(userInput,"n") && locations[userlocation].n!=0){//comparing user input to direction command
                userlocation = locations[userlocation].n;//updating college location
                printf("%s\n\n",locations[userlocation].description);//printing out location to screen
             }

             else if(!strcmp(userInput,"s") && locations[userlocation].s!=0){//comparing user input to direction command
                userlocation = locations[userlocation].s;//updating college location
                printf("%s\n\n",locations[userlocation].description);//printing out location to screen
            }   

            else if(!strcmp(userInput,"in") && locations[userlocation].in!=0){//comparing user input to direction command
                userlocation = locations[userlocation].in;//updating college location
                printf("%s\n\n",locations[userlocation].description);
                //USBdrivelocation=locations[userlocation].in;
                // printf("Usblocation:%d",USBdrivelocation);
               //t printf("objects here: %s\n",objects[USBdrivelocation].name);//printing out location to screen
            }

            else if(!strcmp(userInput,"out") && locations[userlocation].out!=0){//comparing user input to direction command
                userlocation = locations[userlocation].out;//updating college location
                printf("%s\n\n",locations[userlocation].description);//printing out location to screen
            }

            else if(!strcmp(userInput,"e") && locations[userlocation].e!=0){//comparing user input to direction command
                userlocation = locations[userlocation].e;//updating college location
                 printf("%s\n\n",locations[userlocation].description);//printing out location to screen
            }

            else if(strcmp(userInput,"look")==0){//comparing user input to direction command
                printf("%s\n\n",locations[userlocation].description);//printing out location to screen
            }

            else if(strcmp(userInput,"take")==0){
                printf("take what item?\n>");
                scanf(" %[^\n]", itemtaken);//scanning in object user wants to take
    
                    for(int i=0;i<3;i++){//looping through to compare user input to objects in array
                         //printf("%s\n",itemtaken);
                         //printf("%s\n",objects[i].name);

                        if(strcmp(objects[i].name,itemtaken)==0){//comparing userinput to objects in array
                            
                              take(userlocation,objects[i].location);//calling function do pick up item
                              //printf("%d",objects[i].location);
                              //printf("%d",userlocation);
                             }
                     }

            }
            

            else if(strcmp(userInput,"drop")==0){

                printf("What do you want to drop?\n>");
                scanf(" %[^\n]",itemdropped);//scanning in what object user wants to drop
                for(int i=0;i<3;i++){

                     if(strcmp(objects[i].name,itemdropped)==0){//looping through to compare user input to objects in array
                         drop(userlocation,objects[i].location);//callinf function to drop item 
                     }
                // printf("What do you want to drop?");
                // scanf("%s",itemdropped);

                
                // int objHere=0;
                // int newlocation=0;
                //  for(int i=1;i<=numobjects;i++){
                //     if(strcmp(objects[i].name,itemdropped)==0){
                //         newlocation=objects[i].location;
                //         objHere=1;
                //     }
                //  }

                //  if(objHere==1 && userlocation==newlocation){
                //     printf("\n%s dropped at %s",itemdropped,locations[userlocation].description);
                //  }
                //  else{
                //     printf(" %s not in inventory\n",itemdropped);
                //  }
                
            //      if(strcmp(objects[1].name,itemdropped)==0){

            //         strcpy(object1,"");
            //         objects[1].location=userlocation;
            //         printf("%s dropped successfully\n>",objects[1].name);
            //     }
            //     else if(strcmp(objects[2].name,itemdropped)==0){
                }
            }

             else{
                 printf("\nYou might be facing a wall\n");//print invalid command if wrong cammand is inputted

             }

            if(objects[0].location==userlocation){//
                printf("Objects here: %s\n",objects[0].name);//telling user objects available
            }
            if(objects[1].location==userlocation){
                printf("Objects here: %s\n",objects[1].name);//telling user objects available
            }


        }
        
   

}
}



 void take(int userlocation, int objectlocation){

      for(int i = 1; i<=numobjects; i++){
        if(objects[i].location == objectlocation){
            objects[i].location = userlocation;//changing object location to userlocation
            printf("\n%s added to inventory.\n\n", objects[i].name);//adding to inventory
 
}
 }
 }


void drop(int userlocation, int objectlocation){

     for(int i = 1; i<=numobjects; i++){
         if(objects[i].location == userlocation){//comapring object location to user location
         objects[i].location = objectlocation;//removing from inventory
         printf("\n%s removed from inventory.\n\n", objects[i].name);

         }
     }
}


//}
//}