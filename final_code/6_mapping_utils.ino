int count_tiles(NewPing Sonar){
    //doesn't count the tile we are on
    int distance=GetDist(Sonar);
    int i=0;
    for (;distance<=30;i++){
        distance=distance-30;
    }
    DEBUG_RAW("Tiles on Sonar are: ");
    if(isThisWall(Sonar)){
        DEBUG_INT(0);
        return 0;
    }
    if (distance<7){
        DEBUG_INT(i);
        return i;
    }
    DEBUG_INT(i+1);
    return i+1;
}

void adjust_orient(int pos){
    //pos=1 right   
    if (orientatation==0 && pos==1){
        orientatation=1; 
    }
    if (orientatation==0 && pos==0){
        orientatation=2;
    }
    if(orientatation==1 && pos==1){
        orientatation=2;
    }
    if(orientatation==1 && pos==0){
        orientatation=0;
    }

    if(orientatation==2 && pos==0){
        orientatation=3;
    }
    if(orientatation==2 && pos==1){
        orientatation=1;
    }

    if(orientatation==3 && pos==0){
        orientatation=2;
    }
    if(orientatation==3 && pos==1){
        orientatation=0;
    }
    DEBUG_RAW("CURRENT orientatation is: ");
    DEBUG_INT(orientatation);
}

void PrintMatrix()
{
   DEBUG("Printing Matrix On Serial");
   for (int i = 0; i < 40; i++) {
       for (int j = 0; j < 40; j++) {
           Serial.print("  ");Serial.print(grid_matrix[i][j], DEC);
       }
       Serial.println();
   }
   Serial.println();
}