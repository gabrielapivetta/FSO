#include <stdio.h>
#include <stdlib.h>

int main() {

	int max, min;
	int semente=0, semente_temp;
	int num, *intervalo;
	
	scanf("%d %d", &min, &max);
		
	intervalo = (int*)malloc((max-min+1) * sizeof(int));
	for(int i=0; i<(max-min+1);i++)
		intervalo[i] = min+i;
	
	while(scanf("%d", &num) != EOF){
		for(int x=0;x<(max-min+1);x++){
			if(intervalo[x]==-1)
				continue;
			semente_temp = intervalo[x];
			for(int j=1;j<10000;j++)
      			rand_r(&semente_temp);
			if(num != rand_r(&semente_temp)%256)
				intervalo[x] = -1;
			else{
				semente = min + x;
				intervalo[x] = semente_temp;
			}
		}
	}
	
	printf("%d\n", semente);
	
		
return 0;
}

