
void update_matrix(){
    /*
    int lt=count_tiles(left_us);
    int ct=count_tiles(center_us);
    int rt=count_tiles(right_us);
    */
    append_to_matrix(5,0);
    append_to_matrix(5,2);
    append_to_matrix(5,1);
    append_to_matrix(5,3);
} 

void append_to_matrix(int Ntiles,int ao){ 
    DEBUG("loop_through_matrix");
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