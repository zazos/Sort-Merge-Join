#include <stdio.h>
#include <time.h>
#include <string.h>
#include "../include/getColumn.h"
#include "../include/initArray.h"
#include "../include/reorderedColumn.h"
#include "../include/quicksort.h"
#include "../include/splitBucket.h"
#include "../include/result.h"
#include "../include/sortMergeJoin.h"
#include "../include/processRelation.h"
#include "../include/intervening.h"
#include "../include/work.h"
#include "../include/execute_query.h"


int main(int argc, char const *argv[])
{

    metadata * md;

    uint64_t * ptr;

    md = Read_Init_Binary("workloads/small/small.init");

    for (size_t i = 0; i < 14; i++)
    {
        printf("%lu) tuples = %lu\tcolumns = %lu\t----> ",i,  md[i].num_tuples, md[i].num_columns);

        for (size_t j = 0; j < md[i].num_columns; j++)
        {
            ptr = md[i].array[j];
            printf("%lu|",*(ptr));
        }
        printf("\n");
    }

    printf("\n\n\n");

    //Read_Work("workloads/small/small.work");



    // 3 0 1|0.2=1.0&0.1=2.0&0.2>3499|1.2 0.1


    // r3.2

    relation * relation_A;// = &struct_A;// = &struct_A;


    relation_A = Create_Relation(md,0,0);
    //Print_Relation_2(relation_A);
    printf("Edw\n");
    relation_A = Radix_Sort(relation_A);
    //Print_Relation_2(relation_A);


    relation * relation_B;// = &struct_A;
    relation_B = Create_Relation(md,1,0);


    relation_B = Radix_Sort(relation_B);


//    Print_Relation_2(relation_B);


    intervening * interv_final = interveningInit();
    Join_v2(interv_final, relation_A, relation_B, 0, 1);

    //Print_Relation_2(interv_final -> final_rel);

    relation * relation_C;// = &struct_A;
    relation_C = Create_Relation(md,2,1);

    relation_C = Radix_Sort(relation_C);


    Update_Relation_Keys(md,0,0,interv_final ->final_rel,0);


    interv_final ->final_rel = Radix_Sort(interv_final ->final_rel);
    Join_v2(interv_final, interv_final -> final_rel, relation_C, 0, 2);

    uint64_t x = CheckSum(md,0,0,interv_final->final_rel,0);
    printf("%lu\n",x );
    //
    //Print_Relation_2(interv_final -> final_rel);
    //printf("%lu\n", interv_final -> final_rel -> num_tuples);
    //  intervening * interv_final = interveningInit();
    // Join_v2(interv_final, relation_A[0], relation_A[1], 3, 0);
    // Print_Relation_2(interv_final->final_rel);
    // for (size_t i = 0; i < 4; i++)
    // {
    //     /* code */
    //     relation ** relation_A;
    //     relation_A = (relation **)malloc(sizeof(relation *)*2);
    //     relation_A[0] = Create_Relation(md,3,1);
    //     relation_A[1] = Create_Relation(md,3,2);
    //
    //
    //
    //     relation_A[0] = Radix_Sort(relation_A[0]);
    //
    //     //Create_Relation(md,3,2,relation_A[1]);
    //
    //
    //     relation_A[1] = Radix_Sort(relation_A[1]);
    //
    //
    // //    Print_Relation_2(relation_A[0]);
    // }

    //  relation_A[0] = &struct_A[0];
    // relation_A[1] = &struct_A[1];

    // relation ** relation_B[2];
    // relation_B[0] = &struct_B;
    // Create_Relation(md,3,2,relation_A[0]);
    //
    // // Radix sort to r3.2
    // // relation struct_A_final;
    // // relation * relation_A_final = &struct_A_final;
    // relation_A[0] = Radix_Sort(relation_A[0]);
    // //
    // // // 0.2>3499
    // // relation_A = Filter(relation_A, 3499, '>');
    // //
    // Print_Relation_2(relation_A[0]);
    //
    // // // r0.0
    // relation struct_B;
    // relation * relation_B = &struct_B;
    // Create_Relation(md,0,0,relation_A[3],1);
    // //
    // // // Radix Sort to r0.0
    // relation struct_B_final;
    // relation * relation_B_final = &struct_B_final;
    // relation_A[3] = Radix_Sort(relation_A[3], relation_A[4]);
    // // //
    // //
    //  Print_Relation_2(relation_A[1]);
    //
    // // // // 0.2 = 1.0
    //  intervening * interv_final = interveningInit();
    // Join_v2(interv_final, relation_A[0], relation_A[1], 3, 0);
    // Print_Relation_2(interv_final->final_rel);
    // // // 0.1
    // Update_Relation_Keys(md,3,1,interv_final->final_rel,0);
    // //
    // relation struct_D_final;
    // relation * relation_D_final = &struct_D_final;
    // interv_final -> final_rel = Radix_Sort(interv_final->final_rel, relation_D_final);
    // //
    // Print_Relation_2(interv_final->final_rel);
    // //
    // // // r0.0
    // relation struct_C;
    // relation * relation_C = &struct_C;
    // Create_Relation(md,1,0,relation_C);
    // //
    // // // Radix Sort to r0.0
    // relation struct_C_final;
    // relation * relation_C_final = &struct_C_final;
    // relation_C = Radix_Sort(relation_C, relation_C_final);
    // //
    // Join_v2(interv_final, interv_final->final_rel, relation_C, 3, 1);
    //
    // Print_Relation_2(interv_final->final_rel);
    // //
    // CheckSum(md,0,2,interv_final->final_rel,1);
    // CheckSum(md,3,1,interv_final->final_rel,0);
    // printf("\n");
    // for (size_t i = 0; i < interv_final->position; i++)
    // {
    //         printf("r%lu|",interv_final->rowId[i]);
    // }
//     printf("\n");
    work_line * wl_ptr;
    wl_ptr = Read_Work("workloads/small/small.work");
//    Print_Work(wl_ptr);


    Execute_Queries(md, wl_ptr);




    // Update_Tuple_Payload(md,relation_A,1560,99999999,9999);
    // Update_Tuple_Payload(md,relation_A,1560,99999999,789);
    // Update_Tuple_Payload(md,relation_A,1560,99999999,32);
    // Update_Tuple_Payload(md,relation_A,1560,99999999,450);
    //
    // Update_Tuple_Payload(md,relation_A,1560,99999999,72);
    // Update_Tuple_Payload(md,relation_A,1560,99999999,65);
    //
    // Update_Tuple_Payload(md,relation_A,1559,8888888,72);
    // Update_Tuple_Payload(md,relation_A,1559,8888888,65);
    // Update_Tuple_Payload(md,relation_A,1559,8888888,72);
    // Update_Tuple_Payload(md,relation_A,1558,7777777,78);



    // relation struct_B;
    // relation * relation_B = &struct_B;
    //
    // // r2.0
    // Create_Relation(md,2,0,relation_B);
    //
    // // Update_Tuple_Payload(md,relation_B,66,8888888,99);
    // // Update_Tuple_Payload(md,relation_B,20,7777777,23);
    //
    // relation struct_B_final;
    // relation * relation_B_final = &struct_B_final;
    // Radix_Sort(relation_B, relation_B_final);
    //
    // // r1.1 = r2.0
    //
    // intervening * interv_final = interveningInit();
    //
    // Join_v2(interv_final, relation_A_final, relation_B_final, 2, 3);
    // Print_Relation_2(interv_final -> final_rel);
    //
    // uint64_t counter = Join_v2(interv_final, interv_final->final_rel, relation_B_final, 2, 3);
    //
    // relation struct_A_B;
    // relation * rel_final = &struct_A_B;
    // Print_Relation_2(interv_final->final_rel);
    // interv_final->final_rel = Filter(interv_final->final_rel, 2903, '=');
    //
    // //Print_Relation_2(interv_final -> final_rel);
    // Print_Relation_2(interv_final->final_rel);
    //
    // printf("results = %lu\n",counter);
    //
    // Update_Relation_Keys(md,1,0,interv_final->final_rel,0);
    //
    //     Print_Relation_2(interv_final->final_rel);
    // if(FindRowID(interv_final,2))
    // {
    //     printf("Found\n");
    // }
    // else
    // {
    //     printf("Not found\n");
    // }
    // Update_Tuple_Payload(md,relation_A,1560,99999999,9999);
    // Update_Tuple_Payload(md,relation_A,1560,99999999,789);
    // Update_Tuple_Payload(md,relation_A,1560,99999999,32);
    // Update_Tuple_Payload(md,relation_A,1560,99999999,450);

    // Update_Tuple_Payload(md,relation_A,1560,99999999,72);
    // Update_Tuple_Payload(md,relation_A,1560,99999999,65);

    // Update_Tuple_Payload(md,relation_A,1559,8888888,72);
    // Update_Tuple_Payload(md,relation_A,1559,8888888,65);
    // Update_Tuple_Payload(md,relation_A,1559,8888888,72);
    // Update_Tuple_Payload(md,relation_A,1558,7777777,65);

    // Print_Relation_2(relation_A);

    // relation struct_A_final;
    // relation * relation_A_final = &struct_A_final;
    // Radix_Sort(relation_A, relation_A_final);
    // //
    //  Print_Relation_2(relation_A_final);

    // printf("%lu\n", relation_A_final -> num_tuples);



//----------------------------------------------------------------------------------------------------------------------




    return 0;
}
