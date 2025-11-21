// Online C compiler to run C program online
#include <stdio.h>
#include <stdlib.h>

//Display Map

void MarkRestaurant(char grid[36][36]){
    grid[2][3]='B';
    grid[33][28]='B';
    grid[27][31]='B';
    grid[8][8]='B';
    grid[11][13]='B';
    grid[24][24]='B';
    grid[14][19]='B';
    grid[2][16]='P';
    grid[33][8]='P';
    grid[27][23]='P';
    grid[8][2]='P';
    grid[12][26]='P';
    grid[19][11]='P';
    grid[24][14]='P';
    grid[3][8]='N';
    grid[6][34]='N';
    grid[12][23]='N';
    grid[33][21]='N';
    grid[27][14]='N';
    grid[24][26]='N';
    grid[16][1]='N';
    grid[1][13]='A';
    grid[34][1]='A';
    grid[27][7]='A';
    grid[23][18]='A';
    grid[18][33]='A';
    grid[13][7]='A';
    grid[7][21]='A';
    grid[2][22]='S';
    grid[7][13]='S';
    grid[13][3]='S';
    grid[17][9]='S';
    grid[22][31]='S';
    grid[28][18]='S';
    grid[32][26]='S';
    grid[1][27]='Z';
    grid[9][19]='Z';
    grid[12][31]='Z';
    grid[17][24]='Z';
    grid[23][6]='Z';
    grid[28][4]='Z';
    grid[31][11]='Z';
    grid[2][32]='C';
    grid[8][29]='C';
    grid[14][16]='C';
    grid[31][19]='C';
    grid[29][34]='C';
    grid[24][4]='C';
    grid[18][26]='C';
    return;
}

void UnmarkRestaurant(char grid[36][36]){
    grid[2][3]='|';
    grid[33][28]='|';
    grid[27][31]='|';
    grid[8][8]='|';
    grid[11][13]='|';
    grid[24][24]='|';
    grid[14][19]='|';
    grid[2][16]='|';
    grid[33][8]='|';
    grid[27][23]='|';
    grid[8][2]='|';
    grid[12][26]='|';
    grid[19][11]='|';
    grid[24][14]='|';
    grid[3][8]='|';
    grid[6][34]='|';
    grid[12][23]='|';
    grid[33][21]='|';
    grid[27][14]='|';
    grid[24][26]='|';
    grid[16][1]='|';
    grid[1][13]='|';
    grid[34][1]='|';
    grid[27][7]='|';
    grid[23][18]='|';
    grid[18][33]='|';
    grid[13][7]='|';
    grid[7][21]='|';
    grid[2][22]='|';
    grid[7][13]='|';
    grid[13][3]='|';
    grid[17][9]='|';
    grid[22][31]='|';
    grid[28][18]='|';
    grid[32][26]='|';
    grid[1][27]='|';
    grid[9][19]='|';
    grid[12][31]='|';
    grid[17][24]='|';
    grid[23][6]='|';
    grid[28][4]='|';
    grid[31][11]='|';
    grid[2][32]='|';
    grid[8][29]='|';
    grid[14][16]='|';
    grid[31][19]='|';
    grid[29][34]='|';
    grid[24][4]='|';
    grid[18][26]='|';
}


void DispMap(char grid[36][36], int GRID_SIZE) {

    // Populate the grid with spaces and vertical lines
    for (int i = 0; i <= GRID_SIZE; ++i) {
        for (int j = 0; j <= GRID_SIZE; ++j) {
            if (i % 5 == 0 || j % 5 == 0)
                grid[i][j] = '*';
            else
                grid[i][j] = '|'; // Vertical line
        }
    }

    MarkRestaurant(grid);

    // Printing the column indices
    printf("  ");
    for (int i = 0; i <= GRID_SIZE; ++i)
        printf("%2d  ", i);
    printf("\n");

    // Printing the grid
    for (int i = 0; i <= GRID_SIZE; ++i) {
        // Print row index
        printf("%2d ", i);

        // Printing the cells in the row
        for (int j = 0; j <= GRID_SIZE; ++j) {
            printf("%c   ", grid[i][j]); // Print the character stored in the grid
        }
        printf("\n"); // End of row

        // Print horizontal lines between rows
        if (i != GRID_SIZE) {
            printf("    ");
            for (int k = 0; k < GRID_SIZE; ++k) {
                printf("----");
            }
            printf("\n");
        }
    }

    UnmarkRestaurant(grid);



}

int NotOnRestaurant(int x, int y){
    if (x==2 && y==3){
        return 0;
    }
    else if (x==33 && y==28){
        return 0;
    }
    else if (x==27 && y==31){
        return 0;
    }
    else if (x==8 && y==8){
        return 0;
    }
    else if (x==11 && y==13){
        return 0;
    }
    else if (x==24 && y==24){
        return 0;
    }
    else if (x==14 && y==19){
        return 0;
    }
    else if (x==2 && y==16){
        return 0;
    }
    else if (x==33 && y==8){
        return 0;
    }
    else if (x==27 && y==23){
        return 0;
    }
    else if (x==8 && y==2){
        return 0;
    }
    else if (x==12 && y==26){
        return 0;
    }
    else if (x==19 && y==11){
        return 0;
    }
    else if (x==24 && y==14){
        return 0;
    }
    else if (x==3 && y==8){
        return 0;
    }
    else if (x==6 && y==34){
        return 0;
    }
    else if (x==12 && y==23){
        return 0;
    }
    else if (x==33 && y==21){
        return 0;
    }
    else if (x==27 && y==14){
        return 0;
    }
    else if (x==24 && y==26){
        return 0;
    }
    else if (x==16 && y==1){
        return 0;
    }
    else if (x==1 && y==13){
        return 0;
    }
    else if (x==34 && y==1){
        return 0;
    }
    else if (x==27 && y==7){
        return 0;
    }
    else if (x==23 && y==18){
        return 0;
    }
    else if (x==18 && y==33){
        return 0;
    }
    else if (x==13 && y==7){
        return 0;
    }
    else if (x==7 && y==21){
        return 0;
    }
    else if (x==2 && y==22){
        return 0;
    }
    else if (x==7 && y==13){
        return 0;
    }
    else if (x==13 && y==3){
        return 0;
    }
    else if (x==17 && y==9){
        return 0;
    }
    else if (x==22 && y==31){
        return 0;
    }
    else if (x==28 && y==18){
        return 0;
    }
    else if (x==32 && y==26){
        return 0;
    }
    else if (x==1 && y==27){
        return 0;
    }
    else if (x==9 && y==19){
        return 0;
    }
    else if (x==12 && y==31){
        return 0;
    }
    else if (x==17 && y==24){
        return 0;
    }
    else if (x==23 && y==6){
        return 0;
    }
    else if (x==28 && y==4){
        return 0;
    }
    else if (x==31 && y==11){
        return 0;
    }
    else if (x==2 && y==32){
        return 0;
    }
    else if (x==8 && y==29){
        return 0;
    }
    else if (x==14 && y==16){
        return 0;
    }
    else if (x==31 && y==19){
        return 0;
    }
    else if (x==29 && y==34){
        return 0;
    }
    else if (x==24 && y==4){
        return 0;
    }
    else if (x==18 && y==26){
        return 0;
    }
    return 1;
}

int NotOnRoad(int x,int y){
    if (x%5==0 || y%5==0){
        return 0;
    }
    else{
        return 1;
    }
}

typedef struct node{
    int x;
    int y;
    int dist;
}node;

typedef struct route{
    int source_node_x;
    int source_node_y;
    int dest_node_x;
    int dest_node_y;
}route;

route CalcRoute(int source_x, int source_y, int dest_x, int dest_y) {

    // Making Source Nodes
    node source_node1;

    //Path node holds the two node details which lead to shortest path
    route path_node;

    source_node1.x=source_x-(source_x%5);
    source_node1.y=source_y-(source_y%5);
    source_node1.dist=(source_x%5)+(source_y%5);

    node source_node2;

    source_node2.x=source_x-(source_x%5);
    source_node2.y=source_y+(5-(source_y%5));
    source_node2.dist=(source_x%5)+(5-(source_y%5));

    node source_node3;

    source_node3.x=source_x+(5-(source_x%5));
    source_node3.y=source_y-(source_y%5);
    source_node3.dist=(5-(source_x%5))+(source_y%5);

    node source_node4;

    source_node4.x=source_x+(5-(source_x%5));
    source_node4.y=source_y+(5-(source_y%5));
    source_node4.dist=(5-(source_x%5))+(5-(source_y%5));


    //Destination nodes

    node dest_node1;

    dest_node1.x=dest_x-(dest_x%5);
    dest_node1.y=dest_y-(dest_y%5);
    dest_node1.dist=(dest_x%5)+(dest_y%5);

    node dest_node2;

    dest_node2.x=dest_x-(dest_x%5);
    dest_node2.y=dest_y+(5-(dest_y%5));
    dest_node2.dist=(dest_x%5)+(5-(dest_y%5));

    node dest_node3;

    dest_node3.x=dest_x+(5-(dest_x%5));
    dest_node3.y=dest_y-(dest_y%5);
    dest_node3.dist=(5-(dest_x%5))+(dest_y%5);

    node dest_node4;

    dest_node4.x=dest_x+(5-(dest_x%5));
    dest_node4.y=dest_y+(5-(dest_y%5));
    dest_node4.dist=(5-(dest_x%5))+(5-(dest_y%5));

    int min=999;
    node sources[4]={source_node1,source_node2,source_node3,source_node4};
    node dests[4]={dest_node1,dest_node2,dest_node3,dest_node4};

    for (int i=0; i<4; ++i){

         for (int j=0; j<4; ++j){
               int dist;
                dist=abs(sources[i].x-dests[j].x)+abs(sources[i].y-dests[j].y)+sources[i].dist+dests[j].dist;
                if (dist<min) {
                    path_node.source_node_x=sources[i].x;
                    path_node.source_node_y=sources[i].y;
                    path_node.dest_node_x=dests[j].x;
                    path_node.dest_node_y=dests[j].y;
                    min=dist;
                }
            }
        }

    int new_dist=0;

    if (source_node2.x==dest_node1.x && source_node2.y==dest_node1.y){
        min=abs(source_x-dest_x)+abs(source_y-dest_y);
        path_node.source_node_x=0;
        path_node.source_node_y=0;
    }
    else if (source_node1.x==dest_node2.x && source_node1.y==dest_node2.y){
        min=abs(source_x-dest_x)+abs(source_y-dest_y);
        path_node.source_node_x=0;
        path_node.source_node_y=0;
    }
    else if (source_node1.x==dest_node3.x && source_node1.y==dest_node3.y){
        min=abs(source_x-dest_x)+abs(source_y-dest_y);
        path_node.source_node_x=0;
        path_node.source_node_y=0;
    }
    else if (source_node3.x==dest_node1.x && source_node3.y==dest_node1.y){
        min=abs(source_x-dest_x)+abs(source_y-dest_y);
        path_node.source_node_x=0;
        path_node.source_node_y=0;
    }
    else if (source_node1.x==dest_node1.x && source_node1.y==dest_node1.y){
        min=abs(source_x-dest_x)+abs(source_y-dest_y);
        path_node.source_node_x=0;
        path_node.source_node_y=0;
    }


    return path_node;




}

//Plotting x path
void PlotPathX(int source_x,int source_y,int dest_x,char grid[36][36]){
    if (source_x<dest_x){
        int i;
        for (i=source_x;i<=dest_x;i++){
            grid[i][source_y]='@';
        }
    }
    else{
        int i;
        for (i=source_x;i>=dest_x;i--){
            grid[i][source_y]='@';
        }
    }
}

//Plotting y path
void PlotPathY(int source_x,int source_y,int dest_y,char grid[36][36]){
    if (source_y<dest_y){
        int i;
        for (i=source_y;i<=dest_y;i++){
            grid[source_x][i]='@';
        }
    }
    else{
        int i;
        for (i=source_y;i>=dest_y;i--){
            grid[source_x][i]='@';
        }
    }
}

//Display route on map
void DispRoute(int source_x,int source_y,int dest_x,int dest_y,route path,char grid[36][36]){

    if (path.source_node_x==0 && path.source_node_y==0){
        //For node to node
        if (source_x<dest_x){
            int i;
            for (i=source_x;i<=dest_x;i++){
                grid[i][source_y]='@';
            }
        }
        else{
            int i;
            for (i=source_x;i>=dest_x;i--){
                grid[i][source_y]='@';
            }
        }


        if (source_y<dest_y){
            int i;
            for (i=source_y;i<=dest_y;i++){
                grid[dest_x][i]='@';
            }
        }
        else{
            int i;
            for (i=source_y;i>=dest_y;i--){
                grid[dest_x][i]='@';
            }
        }
    }
    else{
        //For source co-ordinates to node
        if (abs(source_x-path.source_node_x)<abs(source_y-path.source_node_y)){
            PlotPathX(source_x,source_y,path.source_node_x,grid);
            PlotPathY(path.source_node_x,source_y,path.source_node_y,grid);
        }
        else{
            PlotPathY(source_x,source_y,path.source_node_y,grid);
            PlotPathX(source_x,path.source_node_y,path.source_node_x,grid);
        }

        //For Dest co-ordinates to node
        if (abs(dest_x-path.dest_node_x)<abs(dest_y-path.dest_node_y)){
            PlotPathX(dest_x,dest_y,path.dest_node_x,grid);
            PlotPathY(path.dest_node_x,dest_y,path.dest_node_y,grid);
        }
        else{
            PlotPathY(dest_x,dest_y,path.dest_node_y,grid);
            PlotPathX(dest_x,path.dest_node_y,path.dest_node_x,grid);
        }



        //For node to node
        if (path.source_node_x<path.dest_node_x){
            int i;
            for (i=path.source_node_x;i<=path.dest_node_x;i++){
                grid[i][path.source_node_y]='@';
            }
        }
        else{
            int i;
            for (i=path.source_node_x;i>=path.dest_node_x;i--){
                grid[i][path.source_node_y]='@';
            }
        }


        if (path.source_node_y<path.dest_node_y){
            int i;
            for (i=path.source_node_y;i<=path.dest_node_y;i++){
                grid[path.dest_node_x][i]='@';
            }
        }
        else{
            int i;
            for (i=path.source_node_y;i>=path.dest_node_y;i--){
                grid[path.dest_node_x][i]='@';
            }
        }


    }



    grid[source_x][source_y]='R';
    grid[dest_x][dest_y]='H';

    int GRID_SIZE=35;

    // Printing the column indices
    printf("  ");
    for (int i = 0; i <= GRID_SIZE; ++i)
        printf("%2d  ", i);
    printf("\n");

    // Printing the grid
    for (int i = 0; i <= GRID_SIZE; ++i) {
        // Print row index
        printf("%2d ", i);

        // Printing the cells in the row
        for (int j = 0; j <= GRID_SIZE; ++j) {
            printf("%c   ", grid[i][j]); // Print the character stored in the grid
        }
        printf("\n"); // End of row

        // Print horizontal lines between rows
        if (i != GRID_SIZE) {
            printf("    ");
            for (int k = 0; k < GRID_SIZE; ++k) {
                printf("----");
            }
            printf("\n");
        }
    }
}


void main() {
    int GRID_SIZE=35;
    char grid[36][36];
    int valid=0;
    int x,y;
    int a,b;
    DispMap(grid, GRID_SIZE);
    while (!(valid)){
        printf("Enter source x and y: ");
        scanf("%d%d",&x,&y);
        if (NotOnRoad(x,y) && NotOnRestaurant(x,y)){
            valid=1;
        }
        else{
            printf("\nInvalid Address\n");
        }
    }

    printf("Enter destination x and y: ");
    scanf("%d%d",&a,&b);
    route path;
    path=CalcRoute(x,y,a,b);
    DispRoute(x,y,a,b,path,grid);
}
