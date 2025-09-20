#include "stdafx.h"
#include<conio.h>
#include "string.h"
#include <string>
#include <iostream>
#include "stdio.h"
#include<stdlib.h>
#include<cstdlib>
#include<time.h>
#include<math.h>
#include<windows.h>
#pragma comment(lib,"Winmm.lib")
using namespace std;

#define fs 320
#define sc 30
#define P 12
#define pii 22.0/7.0
#define size 60000
double tw[]={0.0,1.0, 3.0, 7.0, 13.0, 19.0, 22.0, 25.0, 33.0, 42.0, 50.0, 56.0, 61.0};
double arr[size][P+1];
double cb[33][P+1];
int us=0;
#define ep 0.03
#define deltaa 0.00001

#define rs 1000
#define N 5
#define M 32
long double a[rs][N+1];
long double b[rs][N+1];
long double g[rs][N+1];
long double dl[rs][N+1];
long double zai[rs][N+1][N+1];
int shai[rs][N+1];
int _q[rs];
long double A[N+1][N+1];
long double B[N+1][M+1];
long double PI[N+1];
long double _A[N+1][N+1];
long double _B[N+1][M+1];
long double _PI[N+1];
int O[rs];
int T;

string words[] = {"hello", "My", "Name", "Tapish", "Student", "This", "Teacher", "Temple", "University", "Book", "Brave", "Dog"};
//string hindi[]={"नमस्ते", "मेरा", "नाम", "तपिश", "विद्यार्थी", "यह", "अध्यापक", "मंदिर", "विश्वविद्यालय", "किताब", "बहादुर", "कुत्ता"};
short int waveIn[16025 * 2];


long double avgEnergy(int l, int r,long double arr[])
{
	long double energy = 0;
	for(int i = l; i<=r; i++)
		energy += arr[i]*arr[i];
	return energy/(r-l+1);
}


void writeCodebook()
{
	FILE *fptr;
	fptr=fopen("./Output_Training/cb.txt","w");
	for(int i=1;i<=32;i++)
	{
		for(int j=1;j<=P;j++)
		{
			fprintf(fptr,"%Lf  ",cb[i][j]);
		}
		fprintf(fptr,"\n");
	}
	fclose(fptr);
}

void iniCodebook(int k)
{
	int i,j;
	for(i=1;i<=k;i++)
	{
		for(j=1;j<=P;j++)
			cb[i][j]=0;
	}
}

double t_dist(int i,int j)
{
	double d=0;
	for(int k1=1;k1<=P;k1++)
	{
		d+=tw[k1]*pow((arr[i][k1]-cb[j][k1]),2);
	}
	return d;
}


double distortion(int k)
{
	double dis=0,min_dis=INT_MAX,total_dis=0;
	int index=0;
	for(int i=1;i<=us;i++)
	{
		min_dis=INT_MAX;
		for(int j=1;j<=k;j++)
		{
			dis=t_dist(i,j);
			if(dis<min_dis)
			{
				min_dis=dis;
				index=j;
			}
		}
		arr[i][0]=index; 
		total_dis+=min_dis;
	}
	return total_dis/us;
}





double abs(double x,double y)
{
	if(x>y)
		return x-y;
	return y-x;
}

void updateCodebook(int k)
{
	double temp[P+1];
	int temp_count=0; 
	for(int i=1;i<=P;i++)
		temp[i]=0;
	for(int i=1;i<=k;i++)
	{
		temp_count=0;
		for(int j=1;j<=us;j++)
		{
			if(arr[j][0]==i)
			{
				for(int k1=1;k1<=P;k1++)
				{
					temp[k1]+=arr[j][k1];
				}
				temp_count++;
			}
		}
		for(int j=1;j<=P;j++)
		{
			cb[i][j]=temp[j]/temp_count;
			temp[j]=0;
		}
	}
}


void kmeans(int k)
{
	double distor1,distor2,diff;
	int step_count=0;
	distor1=distortion(k);
	diff=1;
	while(diff>deltaa)
	{
		distor2=distor1;
		updateCodebook(k);
		distor1=distortion(k);
		diff=abs(distor1,distor2);
		step_count++;
	}
}


void lbg()
{
	int d;
	double temp;
	for(int k=1;k<=32;k=k*2)
	{
		printf("genrating codebook of size: %d\n",k);
		kmeans(k);
		if(k<32)
		{
			for(int i=1;i<=P;i++)
			{
				d=k+1;
				for(int j=1;j<=k;j++)
				{
					temp=cb[j][i];
					cb[j][i]=temp*(1+ep);
					cb[d][i]=temp*(1-ep);
					d++;
				}
			}
		}
	}
}


void arrayInput(FILE *fp)
{
	int i,j,result;
	double num;
	for(i=1;i<size;i++)
	{
		for(j=1;j<=P;j++)
		{
			result=fscanf(fp,"%Lf[^,]",&num);
			if(result==-1)
				return;
			else if(result==0)
			{
				result=fscanf(fp,"%*c");
				fscanf(fp,"%Lf[,]",&num);
				arr[i][j]=num;
			}	
			else
				arr[i][j]=num;
		}
		us++;
	}
}


void createCodebook()
{
	FILE *fp;
	fp=fopen("./Output_Training/universe.csv","r");
	if(fp==NULL)
		printf("Can't open file\n");
	int k=32;
	arrayInput(fp);
	fclose(fp);
	iniCodebook(k);
	lbg();
	writeCodebook();
	printf("Codebook genrated and saved");
}

int maxx(int x,int y)
{
	if(x>y)
	return x;
	return y;
}

void dc_shift(long double arr[])
{
	long double avg,count=0;
	int n=sizeof(arr);
	for(int i=0;i<n;i++)
		count+=arr[i];
	avg=count/n;
	for(int i=0;i<n;i++)
		arr[i]=arr[i]-avg;
}

void normalize(long double arr[])
{
	long double max_val=0,min_val=0;
	int n=sizeof(arr);
	for(int i=0;i<n;i++)
	{
		if(arr[i]>max_val)
		max_val=arr[i];
		if(arr[i]<min_val)
		min_val=arr[i];
	}
	max_val=maxx(max_val,0-min_val);
	for(int i=0;i<n;i++)
	arr[i]=(arr[i]*5000)/max_val;
}

void computeRis(long double arr[],long double R[])
{
	for(int i=0;i<=P;i++)
	{
		long double temp=0;
		for(int j=0;j<fs-i;j++)
			temp+=arr[j]*arr[j+i];
		R[i]=temp;
	}
}

void computeAis(long double R[],long double A[])
{
	long double E[P+1],k[P+1],a[P+1][P+1];
	E[0]=R[0];
	long double summation;
	for(int i=1;i<=P;i++)
	{
		summation=0;
		for(int j=1;j<=i-1;j++)
			summation+=a[j][i-1]*R[i-j];
		k[i]=(R[i]-summation)/E[i-1];
		a[i][i]=k[i];
		for(int j=1;j<=i-1;j++)
		a[j][i]=a[j][i-1]-k[i]*a[i-j][i-1];
		E[i]=(1-(k[i]*k[i]))*E[i-1];
	}
	for(int i=1;i<=12;i++)
		A[i]=a[i][P];
}

void computeCis(long double R[],long double A[],long double C[])
{
	C[0]=log(R[0]*R[0]);
	long double summation;
	for(int i=1;i<=12;i++)
	{
		summation=0;
		for(int k=1;k<=i-1;k++)
			summation+=(k*C[k]*A[i-k])/i;
		C[i]=A[i]+summation;
	}
}

void hamming(long double arr[])
{
	long double w;
	for(int i=0;i<fs;i++)
	{
		w=0.54-(0.46*cos((2*pii*i)/(fs-1)));
		arr[i]=arr[i]*w;
	}
}

void raisedSine(long double arr[])
{
	long double w;
	for(int i=1;i<=P;i++)
	{
		w=1+((P/2)*sin(pii*i/P));
		arr[i]=w*arr[i];
	}
}

long double Energy(long double arr[])
{
	long double e=0;
	for(int i=0;i<sizeof(arr);i++)
		e+=arr[i]*arr[i];
	return e;
}




void loadCodebook()
{
	FILE *fp;
	fp=fopen("./Output_Training/cb.txt","r");
	for(int i=1;i<=32;i++)
	{
		for(int j=1;j<=P;j++)
		{
			fscanf(fp,"%Lf ",&cb[i][j]);
		}
	}
}


int t_distIndx(long double C[])
{
	long double min_dis=INT_MAX,dis;
	int index=1;
	for(int i=1;i<=32;i++)
	{
		dis=0;
		for(int j=1;j<=P;j++)
		dis+=tw[j]*pow((C[j]-cb[i][j]),2);
		if(dis<min_dis)
		{
			min_dis=dis;
			index=i;
		}
	}
	return index;
}


long double fwd()
{
	for(int i=1;i<=N;i++)
		a[1][i]=PI[i]*B[i][O[1]];
	for(int t=1;t<=T-1;t++)
	{
		for(int j=1;j<=N;j++)
		{
			long double temp=0;
			for(int i=1;i<=N;i++)
				temp+=a[t][i]*A[i][j];
			a[t+1][j]=temp*B[j][O[t+1]];
		}
	}
	long double probability=0;
	for(int i=1;i<=N;i++)
		probability+=a[T][i];
	return probability;
}


void bwd()
{
	for(int i=1;i<=N;i++)
		b[T][i]=1;
	for(int t=T-1;t>=1;t--)
	{
		for(int i=1;i<=N;i++)
		{
			long double temp=0;
			for(int j=1;j<=N;j++)
			{
				temp+=A[i][j]*B[j][O[t+1]]*b[t+1][j];
			}
			b[t][i]=temp;
		}
	}
}


void plb2()
{
	for(int i=1;i<=N;i++)
	{
		for(int t=1;t<=T;t++)
		{
			long double temp=0;
			for(int j=1;j<=N;j++)
			{
				temp+=a[t][j]*b[t][j];
			}
			g[t][i]=(a[t][i]*b[t][i])/temp;
		}
	}
}


long double viterbi()
{
	for(int i=1;i<=N;i++)
	{
		dl[1][i]=PI[i]*B[i][O[1]];
		shai[1][i]=0;
	}
	long double max,arg_max,temp;
	int state=-1;
	for(int t=2;t<=T;t++)
	{
		for(int j=1;j<=N;j++)
		{
			max=0;
			arg_max=0;
			for(int i=1;i<=N;i++)
			{
				temp=dl[t-1][i]*A[i][j];
				if(temp>arg_max)
				{
					arg_max=temp;
					state=i;
				}
				temp*=B[j][O[t]];
				if(temp>max)
					max=temp;
			}
			dl[t][j]=max;
			shai[t][j]=state;
		}
	}

	long double Pstar;
	max=0,arg_max=0;
	for(int i=1;i<=N;i++)
	{
		if(dl[T][i]>max)
			max=dl[T][i];
		if(dl[T][i]>arg_max)
		{
			arg_max=dl[T][i];
			state=i;
		}
	}
	Pstar=max;
	_q[T]=state;
	return Pstar;
}


void rest()
{
	long double nm,dm;
	for(int i=1;i<=N;i++)
	{
		PI[i]=g[1][i];
	}
	for(int i=1;i<=N;i++)
	{
		for(int j=1;j<=N;j++)
		{
			nm=0,dm=0;
			for(int t=1;t<=T-1;t++)
			{
				nm+=zai[t][i][j];
				dm+=g[t][i];
			}
			A[i][j]=nm/dm;
		}
	}
	for(int j=1;j<=N;j++)
	{
		dm=0;
		for(int t=1;t<=T;t++)
		{
			dm+=g[t][j];
		}
		for(int k=1;k<=M;k++)
		{
			nm=0;
			for(int t=1;t<=T;t++)
			{
				if(O[t]==k)
					nm+=g[t][j];
			}
			B[j][k]=nm/dm;
		}
	}
}


void check()
{
	long double row_sum=0,max=0;
	int index;
	for(int i=1;i<=N;i++)
	{
		if(PI[i]>max)
		{
			max=PI[i];
			index=i;
		}
		row_sum+=PI[i];
	}
	if(row_sum<1)
		PI[index]+=1-row_sum;
	else if(row_sum>1)
		PI[index]-=row_sum-1;
	for(int i=1;i<=N;i++)
	{
		row_sum=0,max=0;
		for(int j=1;j<=N;j++)
		{
			if(A[i][j]>max)
			{
				max=A[i][j];
				index=j;
			}
			row_sum+=A[i][j];		
		}
		if(row_sum<1)
			A[i][index]+=1-row_sum;
		else if(row_sum>1)
			A[i][index]-=row_sum-1;
	}
	for(int i=1;i<=N;i++)
	{
		row_sum=0,max=0;
		for(int j=1;j<=M;j++)
		{
			if(B[i][j]<(1e-30))
				B[i][j]=1e-30;
			if(B[i][j]>max)
			{
				max=B[i][j];
				index=j;
			}
			row_sum+=B[i][j];		
		}
		if(row_sum<1)
			B[i][index]+=1-row_sum;
		else if(row_sum>1)
			B[i][index]-=row_sum-1;
	}
}

void plb3()
{
	long double nm,dm;
	for(int t=1;t<=T-1;t++)
	{
		for(int i=1;i<=N;i++)
		{
			for(int j=1;j<=N;j++)
			{
				nm=a[t][i]*A[i][j]*B[j][O[t+1]]*b[t+1][j];
				dm=0;
				for(int x=1;x<=N;x++)
				{
					for(int y=1;y<=N;y++)
					{
						dm+=a[t][x]*A[x][y]*B[y][O[t+1]]*b[t+1][y];
					}
				}
				zai[t][i][j]=nm/dm;
			}
		}
	}
	rest(); 
	check();
}


void initializeModel()
{
	for(int i=1;i<=N;i++)
	{
		if(i==1)
			PI[i]=1.0;
		else
			PI[i]=0.0;
	}
	for(int i=1;i<=N;i++)
	{
		for(int j=1;j<=N;j++)
		{
			if(j==i && j+1<=N)
			{
				A[i][j]=0.8;
				A[i][j+1]=0.2;
			}
			else if(j==i && j+1>N)
				A[i][j]=1;
		}
	}
	for(int i=1;i<=N;i++)
	{
		for(int j=1;j<=M;j++)
		{
			B[i][j]=1.0/32;
		}
	}
}


void initializeModel_comp()
{
	for(int i=1;i<=N;i++)
		_PI[i]=0;
	for(int i=1;i<=N;i++)
	{
		for(int j=1;j<=N;j++)
		{
			_A[i][j]=0;
		}
	}
	for(int i=1;i<=N;i++)
	{
		for(int j=1;j<=M;j++)
		{
			_B[i][j]=0;
		}
	}
}


void readModel(int digit)
{
	FILE *fpt;
	char ch[1000];
	sprintf(ch,"Trained_Model/%s_PI.txt",words[digit].c_str());
	fpt=fopen(ch,"r");
	for(int i=1;i<=N;i++)
		fscanf(fpt,"%lf",&PI[i]);
	fclose(fpt);
	sprintf(ch,"Trained_Model/%s_A.txt",words[digit].c_str());
	fpt=fopen(ch,"r");
	for(int i=1;i<=N;i++)
	{
		for(int j=1;j<=N;j++)
			fscanf(fpt,"%lf",&A[i][j]);
	}
	fclose(fpt);
	sprintf(ch,"Trained_Model/%s_B.txt",words[digit].c_str());
	fpt=fopen(ch,"r");
	for(int i=1;i<=N;i++)
	{
		for(int j=1;j<=M;j++)
			fscanf(fpt,"%lf",&B[i][j]);
	}
	fclose(fpt);
}


void BM(int train_count,int digit)
{

	initializeModel();
	long double pp,cp=10;
	int countt=0;
	do
	{
		countt++;
		pp=cp;
		fwd();	
		bwd();
		plb2();
		cp=viterbi();
		plb3();
	}while(countt!=1000 && pp<cp);
}

void collectModel()
{
	for(int i=1;i<=N;i++)
		_PI[i]+=g[1][i];
	for(int i=1;i<=N;i++)
	{
		for(int j=1;j<=N;j++)
		{
			_A[i][j]+=A[i][j];
		}
	}
	for(int i=1;i<=N;i++)
	{
		for(int j=1;j<=M;j++)
		{
			_B[i][j]+=B[i][j];
		}
	}
}

void avgModel(int digit)
{
	for(int i=1;i<=N;i++)
		_PI[i]/=sc;
	for(int i=1;i<=N;i++)
	{
		for(int j=1;j<=N;j++)
			_A[i][j]/=sc;
	}
	for(int i=1;i<=N;i++)
	{
		for(int j=1;j<=M;j++)
			_B[i][j]/=sc;
	}
	FILE *fpp;
	char ch[1000];
	sprintf(ch,"Trained_Model/%s_PI.txt",words[digit].c_str());
	fpp=fopen(ch,"w");
	for(int i=1;i<=N;i++)
		fprintf(fpp,"%e ",_PI[i]);
	fclose(fpp);
	sprintf(ch,"Trained_Model/%s_A.txt",words[digit].c_str());
	fpp=fopen(ch,"w");
	for(int i=1;i<=N;i++)
	{
		for(int j=1;j<=N;j++)
		{
			fprintf(fpp,"%e ",_A[i][j]);
		}
		fprintf(fpp,"\n");
	}
	fclose(fpp);
	sprintf(ch,"Trained_Model/%s_B.txt",words[digit].c_str());
	fpp=fopen(ch,"w");
	for(int i=1;i<=N;i++)
	{
		for(int j=1;j<=M;j++)
		{
			fprintf(fpp,"%e ",_B[i][j]);
		}
		fprintf(fpp,"\n");
	}
	fclose(fpp);
}



int getDigit()
{
	long double probability=0,calc_probability=0;
	int index=0;
	for(int i=0;i<=11;i++)
	{
		readModel(i);
		calc_probability=fwd();
		if(calc_probability>probability)
		{
			probability=calc_probability;
			index=i;
		}
	}
	return index;
}

void PlayRecord()
{
 const int NUMPTS = 16025 * 3;   // 3 seconds
 int sampleRate = 16025;  
 // 'short int' is a 16-bit type; I request 16-bit samples below
    // for 8-bit capture, you'd    use 'unsigned char' or 'BYTE' 8-bit types
 HWAVEIN  hWaveIn;
 WAVEFORMATEX pFormat;
 pFormat.wFormatTag=WAVE_FORMAT_PCM;     // simple, uncompressed format
 pFormat.nChannels=1;                    //  1=mono, 2=stereo
 pFormat.nSamplesPerSec=sampleRate;      // 44100
 pFormat.nAvgBytesPerSec=sampleRate*2;   // = nSamplesPerSec * n.Channels * wBitsPerSample/8
 pFormat.nBlockAlign=2;                  // = n.Channels * wBitsPerSample/8
 pFormat.wBitsPerSample=16;              //  16 for high quality, 8 for telephone-grade
 pFormat.cbSize=0;
 // Specify recording parameters
 waveInOpen(&hWaveIn, WAVE_MAPPER,&pFormat, 0L, 0L, WAVE_FORMAT_DIRECT);
 WAVEHDR      WaveInHdr;
 // Set up and prepare header for input
 WaveInHdr.lpData = (LPSTR)waveIn;
 WaveInHdr.dwBufferLength = NUMPTS*2;
 WaveInHdr.dwBytesRecorded=0;
 WaveInHdr.dwUser = 0L;
 WaveInHdr.dwFlags = 0L;
 WaveInHdr.dwLoops = 0L;
 waveInPrepareHeader(hWaveIn, &WaveInHdr, sizeof(WAVEHDR));
 HWAVEOUT hWaveOut;
 printf("\nPlaying...\n");
 waveOutOpen(&hWaveOut, WAVE_MAPPER, &pFormat, 0, 0, WAVE_FORMAT_DIRECT);
 waveOutWrite(hWaveOut, &WaveInHdr, sizeof(WaveInHdr)); // Playing the data
 Sleep(3 * 1000); //Sleep for as long as there was recorded
 waveInClose(hWaveIn);
 waveOutClose(hWaveOut);
}

void StartRecord()
{
 const int NUMPTS = 16025 * 3;   // 3 seconds
 int sampleRate = 16025;  
 // 'short int' is a 16-bit type; I request 16-bit samples below
 // for 8-bit capture, you'd use 'unsigned char' or 'BYTE' 8-bit     types
 HWAVEIN      hWaveIn;
 MMRESULT result;
 WAVEFORMATEX pFormat;
 pFormat.wFormatTag=WAVE_FORMAT_PCM;     // simple, uncompressed format
 pFormat.nChannels=1;                    //  1=mono, 2=stereo
 pFormat.nSamplesPerSec=sampleRate;      // 8.0 kHz, 11.025 kHz, 22.05 kHz, and 44.1 kHz
 pFormat.nAvgBytesPerSec=sampleRate*2;   // =  nSamplesPerSec × nBlockAlign
 pFormat.nBlockAlign=2;                  // = (nChannels × wBitsPerSample) / 8
 pFormat.wBitsPerSample=16;              //  16 for high quality, 8 for telephone-grade
 pFormat.cbSize=0;
 // Specify recording parameters
 result = waveInOpen(&hWaveIn, WAVE_MAPPER,&pFormat, 0L, 0L, WAVE_FORMAT_DIRECT);
 WAVEHDR      WaveInHdr;
 // Set up and prepare header for input
 WaveInHdr.lpData = (LPSTR)waveIn;
 WaveInHdr.dwBufferLength = NUMPTS*2;
 WaveInHdr.dwBytesRecorded=0;
 WaveInHdr.dwUser = 0L;
 WaveInHdr.dwFlags = 0L;
 WaveInHdr.dwLoops = 0L;
 waveInPrepareHeader(hWaveIn, &WaveInHdr, sizeof(WAVEHDR));
 // Insert a wave input buffer
 result = waveInAddBuffer(hWaveIn, &WaveInHdr, sizeof(WAVEHDR));
 // Commence sampling input
 result = waveInStart(hWaveIn);
 printf("\nRecording...\n");
 Sleep(3 * 1000);
 // Wait until finished recording
 waveInClose(hWaveIn);
 PlayRecord();
}



void predictDigit()
{
	char ch[1000];
	long double arr[60000],frame_arr[fs+1];
	int index,framecount=0,predicted_digit;
	long double count;
	long double R[P+1],A[P+1],C[P+1];
	loadCodebook();
	
	int k=0;
	for(int i=0;i<16025*2;i++)
		arr[k++]=waveIn[i];

	dc_shift(arr);
	normalize(arr);
	framecount=0;
	
	for(int x=0;x+fs<k;x+=280)
	{
		
		index=0;
		for(int y=x;y<x+fs;y++)
		{
			frame_arr[index]=arr[y];
			index++;
		}
		hamming(frame_arr);
		computeRis(frame_arr,R);
		computeAis(R,A);
		computeCis(R,A,C);
		raisedSine(C);
		framecount++;
		O[framecount]=t_distIndx(C);
	}
	T=framecount;
	predicted_digit=getDigit();
	printf("\nEnglish Translation of Spoken word is: %s\n",words[predicted_digit].c_str());
}


void liveTest()
{
	StartRecord();
	predictDigit();
}

int indx=-1;

int digitTesting(int digit)
{
	long double probability=0,calc_probability=0;
	int index=-1;
	for(int i=0;i<=11;i++)
	{
		readModel(i);
		calc_probability=fwd();
		if(calc_probability>probability)
		{
			probability=calc_probability;
			index=i;
		}
	}
	indx=index;
	if(index==digit)
		return 1;
	return 0;
}


void testing()
{
	char ch[1000];
	long double arr[60000],frame_arr[fs+1];
	int index,framecount;
	long double count;
	long double R[P+1],A[P+1],C[P+1];
	loadCodebook();
	int accuracy_count=0,overall_accuracy_count=0;
	for(int i=0;i<=11;i++)
	{
		accuracy_count=0;
		for(int j=31;j<=40;j++)
		{
			sprintf(ch,"./Hindi recording/%s_%d.txt",words[i].c_str(),j);
			FILE *fp=fopen(ch,"r");
			if(fp==NULL)
			{
				printf("Cannot open file\n");
				return;
			}
			int k=0;
			while(fscanf(fp,"%Lf",&arr[k])!=EOF)
				k++;
			fclose(fp);
			dc_shift(arr);
			normalize(arr);
			framecount=0;
			for(int x=0;x+fs<k;x+=280)
			{
				index=0;
				for(int y=x;y<x+fs;y++)
				{
					frame_arr[index]=arr[y];
					index++;
				}
				hamming(frame_arr);
				computeRis(frame_arr,R);
				computeAis(R,A);
				computeCis(R,A,C);
				raisedSine(C);
				framecount++;
				O[framecount]=t_distIndx(C);
			}
			T=framecount;
			accuracy_count+=digitTesting(i);
			printf("Predicted English translation for file : %s --> %s\n",ch,words[indx].c_str());
		}
		printf("\nAccuracy of %s is: %d\n\n",words[i].c_str(),accuracy_count*10);
		overall_accuracy_count+=accuracy_count;
	}
	printf("Total Model Accuracy : %f%% \n",double(overall_accuracy_count/1.2));
}


void training()
{
	char ch[1000];
	long double arr[60000],frame_arr[fs+1];
	int index,framecount;
	long double count;
	long double R[P+1],A[P+1],C[P+1];
	loadCodebook();

	for(int i=0;i<=11;i++)
	{
		initializeModel_comp();
		for(int j=1;j<=sc;j++)
		{
			sprintf(ch,"./Hindi recording/%s_%d.txt",words[i].c_str(),j);
			FILE *fp=fopen(ch,"r");
			if(fp==NULL)
			{
				printf("Cannot Open File\n");
				return;
			}

			int k=0;

			char c[100];
			for(int i=0;i<10;i++)
			{
				fscanf(fp,"%s",c);
			}

			while(fscanf(fp,"%Lf",&arr[k])!=EOF)
				k++;
			fclose(fp);
			dc_shift(arr);
			normalize(arr);
			framecount=0;
			for(int x=0;x+fs<k;x+=280)
			{
				index=0;
				for(int y=x;y<x+fs;y++)
				{
					frame_arr[index]=arr[y];
					index++;
				}
				hamming(frame_arr);
				computeRis(frame_arr,R);
				computeAis(R,A);
				computeCis(R,A,C);
				raisedSine(C);
				framecount++;
				O[framecount]=t_distIndx(C);
			}
			
			T=framecount;
			BM(1,i);
			collectModel();
		}
		avgModel(i);
	}
}


void uniCreation()
{
	char ch[1000];
	long double arr[60000],frame_arr[fs+1];
	int index,z;
	long double count;
	long double R[P+1],A[P+1],C[P+1];
	FILE* fptr=fopen("./Output_Training/universe.csv","w");

	if(fptr==NULL)
	{
		printf("Cannot Open File");
		return;
	}

	for(int i=0;i<=11;i++)
	{
		printf("Processing ci's for %s\n",words[i].c_str());
		for(int j=1;j<=sc;j++)
		{
			sprintf(ch,"./Hindi recording/%s_%d.txt",words[i].c_str(),j);
			FILE *fp=fopen(ch,"r");
			if(fp==NULL)
			{
				printf("Cannot Open File\n");
				return;
			}
			int k=0;
			while(fscanf(fp,"%Lf",&arr[k])!=EOF)
				k++;
			fclose(fp);
			dc_shift(arr);
			normalize(arr);
			for(int x=0;x+fs<k;x+=280)
			{
				index=0;
				for(int y=x;y<x+fs;y++)
				{
					frame_arr[index]=arr[y];
					index++;
				}
				hamming(frame_arr);
				computeRis(frame_arr,R);
				computeAis(R,A);
				computeCis(R,A,C);
				raisedSine(C);
				for(z=1;z<=P;z++)
					fprintf(fptr,"%Lf,",C[z]);
				fprintf(fptr,"\n");
			}
		}
	}
	fclose(fptr);
}


int _tmain(int argc, _TCHAR* argv[])
{
	int ch=0;
	while(ch!=4)
	{
		printf("\n-------------------------------------------------");
		printf("\nChoices : \n1.Training Samples \n2.Testing Recorded Samples \n3.Live Testing \n4.Exit\n");
		printf("-------------------------------------------------\n");
		printf("Enter Choice : ");
		scanf("%d",&ch);
		printf("\n-------------------------------------------------\n");
		switch(ch)
		{
			case 1:
				printf("\n-------------------------------------------------\n");
				printf("\nTraining in Progress   Please Wait....");
				printf("\n-------------------------------------------------\n");
				printf("Genrating Universe\n\n");
				uniCreation();
				printf("\nGenrating Codebook\n");
				createCodebook();
				printf("\n\nTraining Started\n");
				training();
				printf("Training Completed\n");
				break;
			case 2:
				testing();
				break;
			case 3:
				liveTest();
				break;
			default:
				break;
		}
	}
	return 0;
}
