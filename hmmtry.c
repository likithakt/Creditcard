#include<stdio.h>
#include<stdlib.h>
#include<math.h>

main(){
	int n,m,i,j,t;
	float a[100][100],b[100][100],pi[100];
	printf("enter the  number of states for the model\n");
	scanf("%d",&n);
	printf("enter the  number of distinct observations symbols per state, i.e. the discrete alphabet size\n");
	scanf("%d",&m);
	printf("enter the NxN state transition probability distribution given in the form of a matrix A = {aij}\n");
	for(i=0;i<n;i++){
		for(j=0;j<n;j++){
			scanf("%f",&a[i][j]);
		}
	}
	printf("enter the NxM observation symbol probability distribution given in the form of a matrix B = {bij}\n");
	for(i=0;i<n;i++){
		for(j=0;j<m;j++){
			scanf("%f",&b[i][j]);
		}
	}
	printf("enter the initial state distribution vector π = {πi}\n");
	for(i=0;i<n;i++){
		scanf("%f",&pi[i]);
	}
//FORWARD ALGORITHM

	printf("\n***************************************FORWARD ALGORITHM*************************************************\n");
	//initialisation
	float alpha[100][100],sum=0,probability=0;
	for(i=0;i<n;i++){
		alpha[0][i]=pi[i]*b[i][0];
	}
	//induction
	
	for(i=0;i<n;i++){	
		for(t=1;t<m;t++){
			for(j=0;j<n;j++){
				sum = sum + alpha[t-1][i]*a[i][j];
			}
		}
	}
	//scaling
	
	for(t=1;t<m;t++){
		for(j=0;j<n;j++){
			alpha[t][j] = sum *b[j][t];
		}
	}
	
	//termination
	
	//probability of hmm from given observation
	printf("alpha variables: \n");
	for(i=0;i<n;i++){
		probability = probability + alpha[m-1][i];
		printf(" %f \t",alpha[m-1][i]);
	}
	printf("\n EVALUATION PHASE:probability of hmm model from given observation sequence: %f",probability);
	printf("\n");
	
//VITERBI ALGORITHM

	printf("\n***************************************VITERBI ALGORITHM*************************************************\n");
	//initialisation
	
	float delta[100][100],max=0,count,temp;
	int l,si[100];
	for(i=0;i<n;i++){
		delta[0][i]=pi[i]*b[i][0];
	}
	
	//recursion
	
	for(i=0;i<n;i++){	
		for(t=1;t<m;t++){
			for(j=0;j<n;j++){
				count = delta[t-1][j]*a[i][j];
				if(max < count){
					max = count;
					si[l]=i;
					l++;
				}
			}
		}
	}
	
	//scaling
	
		for(t=1;t<m;t++){
				for(j=0;j<n;j++){
					delta[t][j] = max * b[j][t];
				}
		}

	//maximum likelihood state tracking
	printf("delta variables :\n");
	for(i=0;i<n;i++){
		printf(" %f \t",delta[m-1][i]);
	}

/*
	for(i=0;i<n;i++){
		for(j=0;j<n;j++){
			if(delta[m-1][i]>delta[m-1][j]){
				temp=delta[m-1][i];
				delta[m-1][i]=delta[m-1][j];
				delta[m-1][j]=temp;
			}
		}
	}
*/	
	printf("\n probability of maximum likelihood sequence :\n");
	for(i=0;i<n;i++){
		printf("%f \t",delta[m-1][i]);
		printf("\n");
	}
	printf("maximum likelihood sequence :\n");
	for(i=0;i<n;i++){
		printf("%d \t",si[i]);
	}
	
//BAUM WELCH ALGORITHM

	printf("\n***************************************BAUM WELCH ALGORITHM*************************************************\n");
	//initialisation
	for(i=0;i<n;i++){
		alpha[0][i]=pi[i]*b[i][0];
	}
	//induction
	
	for(i=0;i<n;i++){	
		for(t=1;t<m;t++){
			for(j=0;j<n;j++){
				sum = sum + alpha[t-1][i]*a[i][j];
			}
		}
	}
	//scaling
	
	for(t=1;t<m;t++){
		for(j=0;j<n;j++){
			alpha[t][j] = sum *b[j][t];
		}
	}
	
	//termination
	
	//probability of hmm from given observation
	printf("\n scaled alpha variables: \n");
	for(i=0;i<n;i++){
		probability = probability + alpha[m-1][i];
		printf(" %f \t",alpha[m-1][i]);
	}
	printf("\n");	
	printf("\n scaled forward probability %f", probability);
	//computing backward variables

	
	//initialisation
	float beta[100][100],agg = 0;
	
	for(i=0;i<n;i++){
		beta[m-1][i] = 1;
	}
	printf("\n");
	for(j=0;j<n;j++){
		for(t=m-1;t>=0;t--){
			for(i=0;i<n;i++){
				agg = agg + beta[t][j]*a[i][j];
				//printf("%f",agg);
			}
		}
	}
	//induction
	printf("\n backward variable: \n");
	for(t=m-1;t>=0;t--){
		for(i=0;i<n;i++){
			beta[t-1][i] = agg * b[i][t];
			printf(" %f \t",beta[t-1][i]);
		}
	}printf("\n");

	//computing gamma variables
	
	printf("\n gamma variables\n");
	float gamma[100][100];
	for(t=0;t<m;t++){
		for(i=0;i<n;i++){
			gamma[t][i] = (alpha[t][i] * beta[t][i]) / probability;
			//total = total + gamma[t][i];			
			printf("%f \t",gamma[t][i]);
		}
	}
	
	//computing estimation parameter
	
	printf("\n estimation parameters\n");
	float est[100][100];
	for(i=0;i<n;i++){
		for(j=0;j<n;j++){
			for(t=0;t<m;t++){
				est[i][j] = alpha[t][i]*a[i][j] * b[j][t+1] * beta[t+1][j] / probability;
				//tot = tot + est[i][j]; 
				if(est[i][j]!=0){
					printf("%f \t",est[i][j]);
				}
			}
		}
	}

	//re-estimated initial probability
	printf("\n re-estimated initial probability :\n");
	float newpi[100];
	for(i=0;i<n;i++){
		newpi[i] = alpha[0][i] * beta[0][i] ;
		printf("%f \t ",newpi[i]);
	}
	printf("\n");
	
}
