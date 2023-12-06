int Sched_Init(void){
 for(int x=0; x<NT; x++)
  Tasks[x].func = 0;
  /*
  * Also configures
  * interrupt that
  * periodically calls
  * Sched_Schedule().
  */
}

int Sched_Add(void (*f)(void),int d, int p, int x){
//  for(int x=0; x<NT; x++){
  if (!Tasks[x].func) {
    Tasks[x].period = p;
    Tasks[x].delay = d;
    Tasks[x].exec = 0;
    Tasks[x].func = f;
    return x;
  }
//  }
  
 return -1;
}

void Sched_Schedule(void){
  for(int x=0; x<NT; x++) {
    if(Tasks[x].func){
      if(Tasks[x].delay){
        Tasks[x].delay--;
      } 
      else {
        /* Schedule Task */
        Tasks[x].exec++;
        Tasks[x].delay =
        Tasks[x].period-1;
      }
    }
  }
}

void Sched_Dispatch(void){
  int prev_task = cur_task;
  for(int x=0; x<cur_task; x++) {
    if (Tasks[x].exec) {
      Tasks[x].exec=0;
      cur_task = x;
      interrupts(); //enable interrupts
      Tasks[x].func();
      noInterrupts(); //disable unterrupts
      cur_task = prev_task;
      /*Delete if one-shot */
      if (!Tasks[x].period){
        Tasks[x].func = 0;
      }
      //return;
    }
  }
}

ISR(TIMER1_COMPA_vect){//timer1 interrupt
  //go = 1;
  Sched_Schedule();
  Sched_Dispatch();
}