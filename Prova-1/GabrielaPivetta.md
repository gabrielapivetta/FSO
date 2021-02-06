Gabriela da Gama Pivetta - 180052845

### T1:

	O processo pai entra na função if e morre quando a função raise é chamada. O filho executa à partir da onde ele foi criado e como não entra na if, o que resta para ser executado é a pause() e o return 0, ou seja, o filho termina logo em seguida.

	Uma solução para garantir que o filho vá esperar por um sinal seria colocar o pause dentro de um loop infinito, como while(1) para que reveba um sinal, assim ele gerará outro filho, morrerá, mas seu filho agora também irá esperar por um sinal.
	
	
### T2:

***Primeiro Cenário:***
	A função fork pode não não funcionar, ou seja, retornará diferente de 0 e diferente de maior que 0. Assim o filho não será criado e não terá como o pai ser acordado pelo sinal que seria enviado pelo filho.
	
***Segundo Cenário:***
	Se o sinal SIGALRM for enviado antes da função trata_SIGALRM ser criada, não terá como o sinal ser tratado.
