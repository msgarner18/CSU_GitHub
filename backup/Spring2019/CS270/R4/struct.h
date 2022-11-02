/* CS270 - R4
 *
 * Author: Your name here
 * Date:   2/7/2017
 */
 
/********** STRUCTURE DEFINITION **********************************************/

// Structure that represents a student
typedef struct
{
  char firstName[80];
  float qualityPoints;
  int numCredits;
  
} Student;

//Structure that represents a student
typedef struct
{
  int numStudents;
  Student** students;


} ClassRoster;


// Structure that represents a class roster
// TODO: Declare this structure

/********** FUNCTION PROTOTYPES ***********************************************/

void readStudentAndEnroll(Student **slot);

void displayStudent(Student s);
