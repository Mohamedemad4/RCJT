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

void update_matrix(){
    //call update_matrix();
    int lt=count_tiles(left_us);
    int ct=count_tiles(center_us);
    int rt=count_tiles(right_us);
    DEBUG_RAW("update_matrix() current orintation is: ");
    DEBUG_INT(orintation);
    if (orintation==0){
        append_to_matrix(lt,3);
        append_to_matrix(ct,0);
        append_to_matrix(rt,1)
    }
    if(orintation==1){
        append_to_matrix(lt,0);
        append_to_matrix(ct,1);
        append_to_matrix(rt,2);
    }
    if (orintation==2){
        append_to_matrix(lt,1);
        append_to_matrix(ct,2);
        append_to_matrix(rt,3);
    }
    if (orintation==3){
        append_to_matrix(lt,2);
        append_to_matrix(ct,3);
        append_to_matrix(rt,0);
    }
} 

void append_to_matrix(int Ntiles,int ao){ 
    /*
    ao represents the matrix's internal orintation variable
    since you will want to append to certien directions relative to the start tile 
    it follows the same logic ,0=F,1=R,2=B,3=L 
    */
    DEBUG_RAW("append_to_matrix: ");
    DEBUG_INT(Ntiles);
    DEBUG_INT(ao);
    if(Ntiles==0){
        return;
    }
    if(ao==0){
        for (int i=posX;i<=Ntiles+posX;i++){ 
            grid_matrix[i][posY]=1;
        }
    }
    if(ao==2){
        for (int i=posX;i>=posX-Ntiles;i--){ 
            grid_matrix[i][posY]=1;
        }            
    }   
    
    if(ao==1){
        for (int i=posY;i<=Ntiles+posY;i++){ 
            grid_matrix[posX][i]=1;
        }
    }
    if(ao==3){
        for (int i=posY;i>=posY-Ntiles;i--){ 
            grid_matrix[posX][i]=1;
        }            
    }
}   