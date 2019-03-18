int get_longest_unvisted_direction(){
    DEBUG_INT(Count_unvisted_tiles(north)); 
    /*
    Count_unvisted_tiles(east);
    Count_unvisted_tiles(south);
    Count_unvisted_tiles(west);*/
    return 0;
}

int Count_unvisted_tiles(int ao){
    int tile_status;
    int N_tiles;
    if(ao==north){
        while(tile_status==1 || tile_status==6 || tile_status==2){ //if unvisited victim or unknown
            N_tiles++;
            tile_status=grid_matrix[posX+N_tiles][posY];
        }   
    }
    if(ao==east){
        while(tile_status==1 || tile_status==6 || tile_status==2){ //if unvisited victim or unknown
            N_tiles++;
            tile_status=grid_matrix[posX][posY-N_tiles];
        }   
    }
    if(ao==south){
        while(tile_status==1 || tile_status==6 || tile_status==2){ //if unvisited victim or unknown
            N_tiles++;
            tile_status=grid_matrix[posX+N_tiles][posY];
        }   
    }
    if(ao==west){
        while(tile_status==1 || tile_status==6 || tile_status==2){ //if unvisited victim or unknown
            N_tiles++;
            tile_status=grid_matrix[posX][posY-N_tiles];
        }   
    }
    return N_tiles;
}

void MappingLoop(){
    /*use turns and drive_one_tile() to move,update_matrix() every time u move*/
    //tell me how u need to interface with the matrix,don't do it directly
    //get_unvisited_dir=get_longest_unvisted_direction(); //gives the location of the largest N- unvisited tiles relative to the current orientation 
    DEBUG("MappingLoop");
}