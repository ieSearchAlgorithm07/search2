#include<stdio.h>
#include<math.h>
#include<stdlib.h>

#define LAYER	3 /* レイヤー数（入力・中間・出力層） */
#define INPUT	2 /* 入力層のニューロン（入力信号）数 */
#define HIDDEN	1 /* 中間層のニューロン数 */
#define OUTPUT	1 /* 出力層のニューロン数 */
#define CTG	4 /* 学習事例数 */

#define ITERATIONS	1000 /* 学習回数（終了条件1） */

#define ETA	1.50   /* 学習係数(0以上の実数) */
#define ALPHA	0.90   /* 慣性項(0〜1の実数) */
#define WD	2.00   /* 重み初期化用 */
#define MIN_ERR	0.0001 /* 最少誤差（終了条件2） */

#define ON		0.9
#define OFF		0.1
#define SMAX	15
#define SMIN	-15
#define MAX		0.99995
#define MIN		0.00005

#ifdef	_Cdecl
#define	drand() ((double)(random()+1)/RAND_MAX-0.5)
#else
#define	drand() ((double)(random()+1)/RAND_MAX-0.5)
#endif

#define sq(x) (x)*(x)

double 	i_lay[CTG][INPUT+1],
		h_lay[HIDDEN+1],
		o_lay[OUTPUT],
		teach[CTG][OUTPUT];
		
double	ih_w[INPUT+1][HIDDEN],
		ho_w[HIDDEN+1][OUTPUT];
		
double	h_del[HIDDEN+1],
		o_del[OUTPUT];

double	ih_dw[INPUT+1][HIDDEN],
		ho_dw[HIDDEN+1][OUTPUT];
		
double sigmoid();
void usage();


int main(argc,argv)
	int	argc;
	char **argv;
{
  int	i,j,ite,ctg;
  double err,sum;
  int seed;
  
  if( argc != 2 ){
    usage();
  }else{
    seed = atoi(argv[1]);
    srandom((int)seed);
  }
  
  /* OR Problem */
  i_lay[0][0]=OFF; i_lay[0][1]=OFF; i_lay[0][2]=ON; teach[0][0]=OFF;
  i_lay[1][0]=ON;  i_lay[1][1]=OFF; i_lay[1][2]=ON; teach[1][0]=ON;
  i_lay[2][0]=OFF; i_lay[2][1]=ON;  i_lay[2][2]=ON; teach[2][0]=ON;
  i_lay[3][0]=ON; i_lay[3][1]=ON;  i_lay[3][2]=ON; teach[3][0]=ON;

  h_lay[HIDDEN]=ON;
	
  for(j=0;j<HIDDEN;j++)
    for(i=0;i<=INPUT;i++){
      ih_w[i][j]=WD*drand();
      ih_dw[i][j]=0.;
    }
  for(j=0;j<OUTPUT;j++)
    for(i=0;i<=HIDDEN;i++){
      ho_w[i][j]=WD*drand();
      ho_dw[i][j]=0.;
    }
  for(ite=0;ite<=ITERATIONS; ite++){
    for(ctg=0,err=0.;ctg<CTG;ctg++){
      for(j=0;j<HIDDEN;j++){
	for(i=0,sum=0.;i<=INPUT;i++)
	  sum += i_lay[ctg][i]*ih_w[i][j];
	h_lay[j]=sigmoid(sum);
      }
      for(j=0;j<OUTPUT;j++){
	for(i=0,sum=0.;i<=HIDDEN;i++)
	  sum+=h_lay[i]*ho_w[i][j];
	o_lay[j]=sigmoid(sum);
      }
      for(i=0;i<OUTPUT;i++){
	err+=sq(teach[ctg][i]-o_lay[i])/2./(double)CTG;
	o_del[i]=(teach[ctg][i]-o_lay[i])*o_lay[i]*(1.-o_lay[i]);			}
      for(j=0;j<=HIDDEN;j++){
	h_del[j]=0.;
	for(i=0;i<OUTPUT;i++)
	  h_del[j]+=o_del[i]*ho_w[j][i];
	h_del[j]*=h_lay[j]*(1.-h_lay[j]);
      }
      
      for(j=0;j<=HIDDEN;j++)
	for(i=0;i<OUTPUT;i++){
	  ho_dw[j][i]=ETA*o_del[i]*h_lay[j]+ALPHA*ho_dw[j][i];
	  ho_w[j][i]+=ho_dw[j][i];
	}
      for(j=0;j<=INPUT;j++)
	for(i=0;i<HIDDEN;i++){
	  ih_dw[j][i]=ETA*h_del[i]*i_lay[ctg][j]+ALPHA*ih_dw[j][i];
	  ih_w[j][i]+=ih_dw[j][i];
	}
    }
    fprintf(stdout,"%4d %.10f\n",ite,err);
    if((err<MIN_ERR)||(ite==ITERATIONS)){
      for(ctg=0;ctg<CTG;ctg++){
	for(j=0;j<HIDDEN;j++){
	  for(i=0,sum=0.;i<=INPUT;i++)
	    sum+=i_lay[ctg][i]*ih_w[i][j];
	  h_lay[j]=sigmoid(sum);
	}
	for(j=0;j<OUTPUT;j++){
	  for(i=0,sum=0.;i<=HIDDEN;i++)
	    sum+=h_lay[i]*ho_w[i][j];
	  o_lay[j]=sigmoid(sum);
	}
      }
      break;
    }
  }

  return 0;
}

double sigmoid(s)
	double s;
{
	double sm;
	
	sm=s;
	if(sm>SMAX)			return(MAX);
	else if(sm<SMIN)	return(MIN);
	else				return(1./(1.+exp(-sm)));
}


void usage(){
  fprintf(stderr," Usage: prompt> ./a.out random-seed\n");
  exit(0);
}
