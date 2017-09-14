#include <stdio.h>

struct employee{
  int empid;
  char name [20];
  float salary;
};

//prototypes
void addEmployee(int ID, FILE * fileName);

void main(void){
  const int dummyID = -1;
  const float dummySalary = -1;
  const char dummyName [] = "                      ";

  FILE * fp;
  fp = fopen("emp_db.bin", "r+");

  //Initializing 100 empty records
  for(int i = 0; i < 100; i ++){
    //empid
    fwrite((const void *) &dummyID, 1, sizeof(int), fp);

    //name
    fwrite((const void *) &dummyName, 1, sizeof(dummyName), fp);

    //salary
    fwrite((const void *) &dummySalary, 1, sizeof(float), fp);
  }

  int tempID;
  //Input the data by asking the user
  printf("Please enter employee id: ");
  scanf("%d\n", &tempID);

  while(tempID != -1){
    //addEmployee(int ID)
  }
}

void addEmployee(int ID, FILE * fileName){
  char tempNAME[20];
  float tempSalary;

  printf("Please enter employee name: ");
  scanf("%c\n", &tempNAME);

  printf("Please enter employee salary: ");
  scanf("%f\n", &tempSalary);

  //calculate the area to write to

}
