#include<stdio.h>
#define maximum 100
#define infinity 99999

/*declare variables*/
unsigned int nodes;
unsigned int n_butterflies;
int b_place[maximum];
int spider_p;
int adj[maximum][maximum];
int pathes[maximum];
int dists[maximum];

/*declare functions*/
void clearDijkstra(){
    for (int i=0;i<maximum;i++){
        pathes[i] = NULL;
        dists[i] =  NULL;
    }
}

void dijkstra(int G[maximum][maximum],int n,int startnode){
	int cost[maximum][maximum],distance[maximum],pred[maximum];
	int visited[maximum],countt,mindistance,nextnode,i,j;

	//pred[] stores the predecessor of each node
	//countt gives the number of nodes seen so far
	//create the cost matrix
	for(i=0;i<n;i++)
        for(j=0;j<n;j++)
            if(G[i][j]==0)
                cost[i][j]=infinity;
            else
				cost[i][j]=G[i][j];

    //initialize pred[],distance[] and visited[]
	for(i=0;i<n;i++){
		distance[i]=cost[startnode][i];
		pred[i]=startnode;
		visited[i]=0;
	}

	distance[startnode]=0;
	visited[startnode]=1;
	countt=1;

	while(countt<n-1){
		mindistance=infinity;

		//nextnode gives the node at minimum distance
		for(i=0;i<n;i++)
			if(distance[i]<mindistance&&!visited[i])
			{
				mindistance=distance[i];
				nextnode=i;
			}

			//check if a better path exists through nextnode
			visited[nextnode]=1;
			for(i=0;i<n;i++)
				if(!visited[i])
					if(mindistance+cost[nextnode][i]<distance[i])
					{
						distance[i]=mindistance+cost[nextnode][i];
						pred[i]=nextnode;
					}
		countt++;
	}

	//print the path and distance of each node
	int temp;
	for(i=0;i<n;i++)
		if(i!=startnode){
		    if (distance[i] == infinity)
                dists[i] = 0;
            else
                dists[i] = distance[i];

			j=i;
			do{
			    temp = j;
				j=pred[j];
			}while(j!=startnode);
			pathes[i] = temp;
        }
}
 void entries(){

    entry: ;
    int mode;
    printf("choose the statement please:\nfor input adjacency matrix press 1\nto read entries from file press 2\nwhich one? ");
    scanf("%d",&mode);
    printf("\n");

    switch(mode){
    case 1:
    /*get number of nodes from user*/
    printf("\nwarning:the maximum supporting nodes are 10\a\n\n");
    getNODES:
    printf("enter number of the nodes: ");
    scanf("%d",&nodes);

    /*conditions to check if nodes are between 2 to 10(1<nodes=<10) or not*/
    if(nodes>10){
        printf("\nplease enter valid number!\a\n\n");
        goto getNODES;
    }
    else if(nodes<2){
        printf("\nat least two nodes are needed!\a\n\n");
        goto getNODES;
    }

    /*get adjacency matrix from the user*/
    printf("\nenter adj matrix:\n");

    for(int i=0;i<nodes;i++)
    {
        for(int j=0;j<nodes;j++)
        {
            scanf("%d",&adj[i][j]);
        }
    }

    /*get number of the butterflies from user*/
    getBUTTERFLIESnumber:
    printf("\n\nenter the number of butterflies: ");
    scanf("%d",&n_butterflies);

    /*conditions to check that the number of butterflies is nodes-1 or less than it & also its not 0  */
    if(n_butterflies>nodes-1){
        printf("\n\nnumber of butterflies must be less than nodes & more than 0!!!\a");
        goto getBUTTERFLIESnumber;
    }

    else if(n_butterflies==0){
        printf("\n\nnumber of butterflies must be less than nodes & more than 0!!!\a");
        goto getBUTTERFLIESnumber;
    }

    /*get the place of butterflies from user*/
    for(int i=0; i< n_butterflies ;i++){
		printf("\nPlease enter the place of butterflies: ");
		scanf("%d",&b_place[i]);

        /*check the condition to prevent user of entering Repetitious place for butterflies*/
		for(int j=0;j<i;j++){
			if (b_place[j] == b_place[i]){
				printf("You already have entered that place please enter another place");
				i--;
				break;
			}
		}
	}

    /*get spider place from user*/
    getSPIDERplace:
    printf("\nenter the place of spider: ");
    scanf("%d",&spider_p);

    /*check the condition to prevent user of putting spider on butterflies*/
    for(int i=0;i<n_butterflies;i++){
          if(spider_p==b_place[i]){
            printf("you put spider on butterflies!!! choose an other place\n");
            goto getSPIDERplace;
          }
    }
    break;

    case 2: ;
    FILE *mapp ;
    char filename[300];
    getFILE:
    printf("please enter the filename: ");
    scanf("%s",filename);
    mapp = fopen(filename,"r");
    if((mapp = fopen(filename,"r")) == NULL ){
        printf("the entered file name is invalid try again!!!\n");
        goto getFILE;
    }
    fscanf(mapp,"%d",&nodes);
    printf("%d\n",nodes);
    for(int i=0;i<nodes;i++){
        for(int j=0;j<nodes;j++){
            fscanf(mapp,"%d",&adj[i][j]);
        }
    }

    for(int i=0;i<nodes;i++){
        for(int j=0;j<nodes;j++){
            printf("%d ",adj[i][j]);
        }
        puts("\n");
    }

    fscanf(mapp,"%d",&n_butterflies);
    printf("%d\n",n_butterflies);

    for ( int i = 0 ; i < n_butterflies ;i++ ){
        fscanf(mapp,"%d",b_place+i);
        printf("%d ",*(b_place+i) );
    }
    printf("\n");
    fscanf(mapp,"%d",&spider_p);
    printf("%d\n",spider_p);
       break;
    default:
        printf("you just have two choice 1 or 2");
        goto entry;
    }
 }

void butterfly(){
    int i, j = infinity, index, node;

    for (i = 0; i < n_butterflies; i++){
        clearDijkstra();
        dijkstra(adj, nodes, b_place[i]);

        if (dists[spider_p] > 0 && dists[spider_p] < j){

            index = i;
            node = pathes[spider_p];
            j = dists[spider_p];
        }
    }

    printf("Butterfly removed the edge between the nodes %d and %d\n", b_place[index], node);
    adj[b_place[index]][node] = 0;
    adj[node][b_place[index]] = 0;
}

void spider(){
    int i, j = infinity, moveto;
    clearDijkstra();
    dijkstra(adj, nodes, spider_p);
    for (i = 0; i < n_butterflies; i++){
        if (dists[b_place[i]] > 0 && dists[b_place[i]] < j){
            moveto = pathes[b_place[i]];
            j = dists[b_place[i]];
        }
    }

    printf("Spider moved from node %d to %d\n", spider_p, moveto);
    spider_p = moveto;
}

int butterfly_win(){
    int i;
    clearDijkstra();
    dijkstra(adj, nodes, spider_p);

    for (i = 0; i < n_butterflies; i++){
        if (dists[b_place[i]] == 0){
            return 1;
        }
    }
    return 0;
}

int spider_win(){
    int i;
    for (i = 0; i < n_butterflies; i++){
        if (b_place[i] == spider_p){
            return 1;
        }
    }
    return 0;
}

int main(){
    statement: ;
    int mode, i, j;
    printf("choose the statement please:\nif you want to play as butterflies press 1\nif you want to play as spider press 2");
    printf("\nwhich one? ");
    scanf("%d",&mode);
    printf("\n");

    switch(mode){
    case 1://play as butterfly
        entries();
        while (1){
            if (butterfly_win()){
                printf("Butterfly Won");
                return 0;
            }
            spider();

            if (spider_win()){
                printf("Spider Won");
                return 0;
            }
            getEdgeToRemove:
                printf("Enter an edge to be removed -> i j:");
                scanf("%d %d", &i, &j);
                if (adj[i][j] != 1){
                    printf("There is no edge. enter again\n");
                    goto getEdgeToRemove;
                }
                adj[i][j] = 0;
                adj[j][i] = 0;
        }
        break;

    case 2://play as spider
        entries();
        while (1){
            if (butterfly_win()){
                printf("Butterfly Won");
                return 0;
            }

            getNodeToMove:
                printf("Enter a node to move spider to it");
                scanf("%d", &i);
                if (adj[spider_p][i] != 1){
                    printf("there is no edge. enter again\n");
                    goto getNodeToMove;
                }
                spider_p = i;
            if (spider_win()){
                printf("Spider Won");
                return 0;
            }
            butterfly();
        }
        break;
    default:
        printf("you just have two choice 1 or 2 !!!");
        goto statement;
    }
}
