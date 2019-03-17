void PrintMatrix()
{
   DEBUG("Printing Matrix On Serial");
   for (int i = 0; i < X_COLS; i++) {
       for (int j = 0; j < Y_COLS; j++) {
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
    DEBUG_RAW("update_matrix() current orientation is: ");
    DEBUG_INT(orientation);
    if (orientation==0){
        append_to_matrix(lt,3);
        append_to_matrix(ct,0);
        append_to_matrix(rt,1);
    }
    if(orientation==1){
        append_to_matrix(lt,0);
        append_to_matrix(ct,1);
        append_to_matrix(rt,2);
    }
    if (orientation==2){
        append_to_matrix(lt,1);
        append_to_matrix(ct,2);
        append_to_matrix(rt,3);
    }
    if (orientation==3){
        append_to_matrix(lt,2);
        append_to_matrix(ct,3);
        append_to_matrix(rt,0);
    }
} 
void update_location(int case_up){
    if (case_up==1){ //the robot moves one tile forward
        if (orientation==0){
            posX=posX+2;//posY=posY+1;
            append_value(posX-1,posY,4); //so the middle tile is also visited
        }
        if(orientation==1){
            posY=posY+2;//posX=posX+1;
            append_value(posX,posY-1,4);
        }
        if(orientation==2){
            posX=posX-2;//posY=posY-1;
            append_value(posX+1,posY,4);
        }
        if(orientation==3){
            posY=posY-2;//posX=posX-1;
            append_value(posX,posY+1,4);
        }
    }
    if(case_up==2){ //the robot moves one tile backwards
        if (orientation==0){
            posX=posX-2;
            append_value(posX+1,posY,4);
        }
        if(orientation==1){
            posY=posY-2;
            append_value(posX,posY+1,4);
        }
        if(orientation==2){
            posX=posX+2;
            append_value(posX-1,posY,4);
        }
        if(orientation==3){
            posY=posY+2;
            append_value(posX,posY-1,4);
        }
    }
    append_value(posX,posY,4);
}


void append_to_matrix(int Ntiles,int ao){ 
    /*
    ao represents the matrix's internal orientation variable
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
            append_value(i,posY,1);
        }
    }
    if(ao==2){
        for (int i=posX;i>=posX-Ntiles;i--){ 
            append_value(i,posY,1);
        }            
    }   
    
    if(ao==1){
        for (int i=posY;i<=Ntiles+posY;i++){ 
            append_value(posX,i,1);
        }
    }
    if(ao==3){
        for (int i=posY;i>=posY-Ntiles;i--){ 
            append_value(posX,i,1);
        }            
    }
}   
