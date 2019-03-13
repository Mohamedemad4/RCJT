void MappingLoop(){
    /*use turns and drive_one_tile() to move,update_matrix() every time u move*/
    //tell me how u need to interface with the matrix,don't do it directly
    if(!isThisWall(center_us)){
        drive_one_tile();
        update_matrix();
    }
}