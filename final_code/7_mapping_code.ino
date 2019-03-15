void MappingLoop(){
    /*use turns and drive_one_tile() to move,update_matrix() every time u move*/
    //tell me how u need to interface with the matrix,don't do it directly
/*    if(!isThisWall(center_us)){
        drive_one_tile_f();
        update_matrix();
    }*/
    drive_one_tile_f();
    drive_one_tile_f();
    drive_one_tile_f();
    
    turn(90,1);
    drive_one_tile_f();
    drive_one_tile_f();
    drive_one_tile_f();
    turn(90,0);
    drive_one_tile_f();
    drive_one_tile_f();
    drive_one_tile_f();
    turn(180,0);
    drive_one_tile_f();
    drive_one_tile_f();
    drive_one_tile_f();
    drive_one_tile_f();
    drive_one_tile_f();
    drive_one_tile_f();
    
    grid_matrix[posX][posY]=30;   
}