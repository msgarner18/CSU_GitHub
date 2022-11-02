/* CS270 - R4
 *
 * Author: Mark Garner
 * Date:   9/12/2018
 */

#include <stdlib.h>
#include "struct.h"
#include <stdio.h>

int main(int argc, const char **argv)
{
  int studNum;
  scanf("%d", &studNum);

  ClassRoster roster;
  roster.numStudents = studNum;
  //dynamic array initialized with 0's/null
  roster.students =(Student**)calloc(roster.numStudents, Student**);

  for(int i = 0; i < studNum; i++)
  {
    readStudentAndEnroll(&(roster.students[i]));
  }
  for(int i = 0; i < studNum; i++)
  {
    displayStudent(*(roster.students[i]));
    free(roster.students[i]);
  }  
  free(roster.students);
  return 0;
}
