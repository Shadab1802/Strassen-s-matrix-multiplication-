#include<iostream>
#include<cmath>
using namespace std;

int** stracess(int **arr1,int **arr2,int istrt1,int iend1,int jstrt1,int jend1,int istrt2,int iend2,int jstrt2,int jend2);
// "multi" take two matrix as arrgument along with its strts and end of colom and parameter 
//  checkes if of order 2 than multiply else calls strcess func for further cutting
int** multi(int **arr1,int **arr2,int istrt1,int iend1,int jstrt1,int jend1,int istrt2,int iend2,int jstrt2,int jend2){
    if(iend1-istrt1 <= 1){
        int A=arr1[istrt1][jstrt1];
        int B=arr1[istrt1][jend1];
        int C=arr1[iend1][jstrt1];
        int D=arr1[iend1][jend1];

        int E=arr2[istrt2][jstrt2];
        int F=arr2[istrt2][jend2];
        int G=arr2[iend2][jstrt2];
        int H=arr2[iend2][jend2];

        int P1=A*(F-H);
        int P2=(B+A)*H;
        int P3=(C+D)*E;
        int P4=D*(G-E);
        int P5=(A+D)*(E+H);
        int P6=(B-D)*(G+H);
        int P7=(A-C)*(E+F);

        int **Z=new int*[2];
        for(int i=0;i<2;i++){
            Z[i]=new int[2];
        }

        Z[0][0]=P6+P5+P4-P2;
        Z[0][1]=P1+P2;
        Z[1][0]=P3+P4;
        Z[1][1]=P1-P3+P5-P7;

        return Z;
    }
    else{
        return stracess(arr1,arr2,istrt1,iend1,jstrt1,jend1,istrt2,iend2,jstrt2,jend2);
    }
    
}

//adds two matrix by just taking end of row and coloum as any matrix passed to it will be a ref of new created mat not of users
//returns by creating new matrix
int **add(int **arr1,int **arr2,int iend2,int jend2){
    int **copy=arr1;
    for(int i=0;i<=iend2;i++){
        for(int j=0;j<=jend2;j++){
            copy[i][j]+=arr2[i][j];
        }
    }
    return copy;
}

//displays matrix by takeing starting and end point of row and coloum
void disp(int **arr,int istrt,int iend,int jstrt,int jend){
    
    for(int i=istrt;i<=iend;i++){
        for(int j=jstrt;j<=jend;j++){
            //cout<<"(i,j)="<<i<<j<<endl;
            cout<<arr[i][j]<<"\t";
        }
        cout<<endl;
    }
}

//it control all other function , divides if mat is not of 2 and then pass for futher operation to fun multi and sum.. 
// it is bascically the master of other
int** stracess(int **arr1,int **arr2,int istrt1,int iend1,int jstrt1,int jend1,int istrt2,int iend2,int jstrt2,int jend2){

    if((iend1-istrt1)==1){
        return multi(arr1,arr2,istrt1,iend1,jstrt1,jend1,istrt2,iend2,jstrt2,jend2);
    }
    else if((iend1-istrt1)>1){              
           
        int **A11=add(multi(arr1,arr2,istrt1,iend1/2,jstrt1,jend1/2,   istrt2,iend2/2,jstrt2,jend2/2),multi(arr1,arr2,istrt1,iend1/2,jend1/2 +1,jend1,     iend2/2 +1,iend2,jstrt2,jend2/2),iend1/2-istrt1,jend1/2-jstrt1);
        int **A12=add(multi(arr1,arr2,istrt1,iend1/2,jstrt1,jend1/2,   istrt2,iend2/2,jend2/2 +1,jend2),multi(arr1,arr2,istrt1,iend1/2,jend1/2 +1,jend1,   iend2/2 +1,iend2,jend2/2 +1,jend2),iend1/2-istrt1,jend1/2-jstrt1);
        int **A21=add(multi(arr1,arr2,iend1/2 +1,iend1,jstrt1,jend1/2, istrt2,iend2/2,jstrt2,jend2/2),multi(arr1,arr2,iend1/2 +1,iend1,jend1/2 +1,jend1,   iend2/2 +1,iend2,jstrt2,jend2/2),iend1/2-istrt1,jend1/2-jstrt1);
        int **A22=add(multi(arr1,arr2,iend1/2 +1,iend1,jstrt1,jend1/2, istrt2,iend2/2,jend2/2 +1,jend2),multi(arr1,arr2,iend1/2 +1,iend1,jend1/2 +1,jend1, iend2/2 +1,iend2,jend2/2 +1,jend2),iend1/2-istrt1,jend1/2-jstrt1);
        
        int **result=new int*[iend1-istrt1+1];
                for(int i=0;i<=(iend1-istrt1+1);i++){
                    result[i]=new int[jend1-jstrt1+1];
                }
        int r=0,c=0;
        
        for(int i=0;i<=(iend1/2-istrt1);i++){
            for(int j=0;j<=(jend1/2-jstrt1);j++){
                result[r][c]=A11[i][j];
                
                c++;
            }
            r++,c=0;  
        }

        c=jend1/2+1,r=0;

        for(int i=0;i<=iend1/2-istrt1;i++){
            for(int j=0;j<=(jend1/2-jstrt1);j++){
                result[r][c]=A12[i][j];
                c++;
            }
            c=jend1/2+1,r++;
        }

        r=iend1/2+1,c=0;
        for(int i=0;i<=(iend1/2-istrt1);i++){
            for(int j=0;j<=(jend1/2-jstrt1);j++){
                result[r][c]=A21[i][j];
                c++;
            }
            c=0,r++;
        }

        r=iend1/2+1,c=jend1/2+1;
        for(int i=0;i<=(iend1/2-istrt1);i++){
            for(int j=0;j<=(jend1/2-jstrt1);j++){
                result[r][c]=A22[i][j];
                c++;
            }
            c=jend1/2+1,r++;
            
        } 
        return result;       
    }
}

int main(){
    int n;
    cout<<"Enter Order: ";
    cin>>n;
    cout<<"Enter Element: ";
    
    if(!(n && !(n & (n - 1)))){
        
        int copy=n;
        double logValue = log2(n);

        int roundedLog = ceil(logValue);
    
        n= pow(2, roundedLog);
    
        int **arr=new int*[n];
        
        for (int i=0;i<n;++i) {
            arr[i]=new int[n];
        }
        
        for(int i=0;i<n;i++){
            for(int j=0;j<n;j++){
                
                if(i<(n-copy)||j<(n-copy)){
                    
                    arr[i][j]=0;
                }
                else{
                    cin>>arr[i][j];
                }
            }
        }

        int **result=stracess(arr,arr,0,n-1,0,n-1,0,n-1,0,n-1);
        
        disp(result,(n-copy),n-1,(n-copy),n-1);
    }
    else{
        int **arr=new int*[n];

        for (int i=0;i<n;++i) {
            arr[i]=new int[n];
        }

        for(int i=0;i<n;i++){
            for(int j=0;j<n;j++){
                cin>>arr[i][j];
            }
        }
       
        int **result=stracess(arr,arr,0,n-1,0,n-1,0,n-1,0,n-1);
        
        disp(result,0,n-1,0,n-1);
        
    }
    return 0;
}