/* recursion */
int factorial(int i) {
  if(i == 1) {
      return 1;
  } else {
      return factorial(i - 1);
  }
}

 /* iteration */
 int factorial(int i) {   //i = a0;    factorial:add t1, a0, x0                   #利用t1存结果
    int result; //result = a0;              loop:beq a0, 1, result #返回值
    for(j = i; j > 1; j--) {  //                 mul t1, t1, a0
        result *= j; //
              //                                 addi a0, a0, -1  #a0 = a0 - 1
                                                 j loop
    }         //                         result: # add a0, t1, x0 #将结果送入a0
                                                 # jr ra #返回main函数
    return result;
 }
