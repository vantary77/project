#include<bits/stdc++.h>

using namespace std;

double distance(double a,double b,double c,double d)
{
    double x,y,z;
    x=(a-c)*(a-c);
    y=(b-d)*(b-d);
    z=sqrt(x+y);
    return z;
}

double pathloss(double a, double b,double c,double d)
{
     double x,y,z,pl,k,lamda=0.138;
    k=16*(distance(a,b,c,d))*(distance(a,b,c,d))/(lamda*lamda);
    pl=10*(log10(k));
    pl=pl+(20*(log10(distance(a,b,c,d)/10)));
    return pl;
}
int main()
{
    int i,j,n,k=0,l=0,m=0,c,p,bo=0,z=1,emergency[8]={0},in,in1;
    double a[]={0.85,1.05,0.64,0.61,1.41,1.08,0.80,0.93,0.68};           //x_co-ordinates
    double b[]={1.90,1.79,1.58,1.25,1.38,0.86,0.59,0.61,1.25};           //y-co-ordinates
    n=sizeof(a)/sizeof(a[0]);
    int cluster1[n],cluster2[n],cluster3[n];                             //three different levels
    double min=10.0,e;
    cout<<"no. of rounds are "<<endl;                                    //for no. of rounds
    cin>>c;    
    cout<<"energy of nodes at starting are "<<endl;
    cin>>e;
    double energy[8]={e,e,e,e,e,e,e,e};
                                       
    for(i=0;i<n-1;i++)
    {
        for(j=i;j<i+1;j++)
        {
            if(distance(a[i],b[i],a[n-1],b[n-1])<=0.4){
            cluster1[k]=i;
            k++;
            }
            else if(distance(a[i],b[i],a[n-1],b[n-1])<=0.6){
            cluster2[l]=i;
            l++;
            }
            else {
            cluster3[m]=i;
            m++;
            }
        }
    }
    cout<<"cluster1"<< ":"<<" ";
    for(i=0;i<k;i++)
    {
        cout<<cluster1[i]<<" ";
    } 
    cout<<endl<<"cluster2"<<" ";
    for(i=0;i<l;i++)
    {
        cout<<cluster2[i]<<" ";
    } 
    cout<<endl<<"cluster3"<<" ";
    for(i=0;i<m;i++)
    {
        cout<<cluster3[i]<<" ";
    } 
    
    cout<<endl;
    while(c--){
    int pac=10,th1=4000,th2=2000;
    int packet[8];      
    cout<<"at "<<z<<" th round"<<endl;
    cout<<"emergency information at "<<endl;
    for(i=0;i<8;i++)
    {
    int in=rand()%8;  
    packet[i]=in;
    }
    int packet_size[8]={packet[0],packet[1],packet[2],packet[3],packet[4],packet[5],packet[6],packet[7]};
    for(i=0;i<8;i++)
    {
        if(packet[i]>5){
        cout<<i<<"   ";
        emergency[i]=1;
    }
    }
    cout<<endl;                                    
    for(i=0;i<m;i++)
    {
    bo=0;
        for(j=0;j<l;j++)
        {
            if((((distance(a[cluster3[i]],b[cluster3[i]],a[cluster2[j]],b[cluster2[j]]))<min) 
                  && ((energy[cluster2[j]])>th1) && (emergency[cluster3[i]]==0)  && (emergency[cluster2[j]]==0)
                  &&(pathloss(a[cluster3[i]],b[cluster3[i]],a[n-1],b[n-1]))>((pathloss(a[cluster2[j]],b[cluster2[j]],a[n-1],b[n-1]))
                  +pathloss(a[cluster3[i]],b[cluster3[i]],a[cluster2[j]],b[cluster2[j]]))&&(energy[cluster3[i]]>0)&&(packet[cluster3[i]]<6))
             || (((distance(a[cluster3[i]],b[cluster3[i]],a[cluster2[j]],b[cluster2[j]]))<min) 
                  && ((energy[cluster2[j]])>th2) && (emergency[cluster3[i]]==0)  && (emergency[cluster2[j]]==0)
                  &&(pathloss(a[cluster3[i]],b[cluster3[i]],a[n-1],b[n-1]))>((pathloss(a[cluster2[j]],b[cluster2[j]],a[n-1],b[n-1]))
                  +pathloss(a[cluster3[i]],b[cluster3[i]],a[cluster2[j]],b[cluster2[j]]))&&(energy[cluster3[i]]>0)   
                  &&(2<packet[cluster3[i]]<6)))
            {
                min=distance(a[cluster3[i]],b[cluster3[i]],a[cluster2[j]],b[cluster2[j]]);
                p=cluster2[j];
                bo=1;
             }
         }
         if(bo){
         energy[p]=energy[p]-((36.1)*packet_size[p]);
         packet_size[p]=packet_size[p]+packet_size[cluster3[i]];
         min=10.0;
         energy[cluster3[i]]-=((((16.7)*packet_size[cluster3[i]])+((1.97)*(packet_size[cluster3[i]])*(min)*(min))));
         if(energy[cluster3[i]]>0)
         cout<<cluster3[i]<<" has forwarder node of "<<p<<endl;
         else
         cout<<cluster2[i]<<" sensor is died"<<endl;
         }
         else
         {
         if(energy[cluster3[i]]<0)
         cout<<cluster3[i]<<" sensor is dead "<<endl;
         else
         {
         cout<<cluster3[i]<<" directly sends to sink"<<endl;
         double dis=distance(a[cluster3[i]],b[cluster3[i]],a[n-1],b[n-1]);
         energy[cluster3[i]]=(energy[cluster3[i]])-((((16.7)*packet_size[cluster3[i]])+((1.97)*(packet_size[cluster3[i]])*(dis)*(dis))));
         }
         }
    }
    for(i=0;i<l;i++)
    {
    bo=0;
        for(j=0;j<k;j++)
        {
            if((((distance(a[cluster2[i]],b[cluster2[i]],a[cluster1[j]],b[cluster1[j]]))<min)
                    && ((energy[cluster1[j]])>th1) && (emergency[cluster2[i]]==0) && (emergency[cluster1[j]]==0)
                    &&(pathloss(a[cluster2[i]],b[cluster2[i]],a[n-1],b[n-1]))>((pathloss(a[cluster1[j]],b[cluster1[j]],a[n-1],b[n-1]))
                   +pathloss(a[cluster2[i]],b[cluster2[i]],a[cluster1[j]],b[cluster1[j]]))&&(energy[cluster2[i]]>0)&&(packet[cluster2[i]]>5)
                ||  (((distance(a[cluster2[i]],b[cluster2[i]],a[cluster1[j]],b[cluster1[j]]))<min)
                    && ((energy[cluster1[j]])>th2) && (emergency[cluster2[i]]==0) && (emergency[cluster1[j]]==0)
                    &&(pathloss(a[cluster2[i]],b[cluster2[i]],a[n-1],b[n-1]))>((pathloss(a[cluster1[j]],b[cluster1[j]],a[n-1],b[n-1]))
                   +pathloss(a[cluster2[i]],b[cluster2[i]],a[cluster1[j]],b[cluster1[j]])) && (energy[cluster2[i]]>0)
                    &&(2<packet[cluster3[i]]<=5))))
            {
                min=distance(a[cluster2[i]],b[cluster2[i]],a[cluster1[j]],b[cluster1[j]]);
                p=cluster1[j];
                bo=1;
             }
         }
         if(bo){
         energy[p]=energy[p]-(((36.1)*packet_size[p]));
         packet_size[p]=packet_size[p]+packet_size[cluster2[i]];
         min=10.0;
         energy[cluster2[i]]-=((((16.7)*packet_size[cluster2[i]])+((1.97)*(packet_size[cluster2[i]])*(min)*(min))));
         if(energy[cluster2[i]]>0)
         cout<<cluster2[i]<<" has forwarder node of "<<p<<endl;
         else
         cout<<cluster2[i]<<" sensor is died"<<endl;
         }
         else
         {
         if(energy[cluster2[i]]<0)
         cout<<cluster2[i]<<" sensor is dead "<<endl;
         else
         {
         cout<<cluster2[i]<<" directly sends  to sink"<<endl;
         double dis=distance(a[cluster2[i]],b[cluster2[i]],a[n-1],b[n-1]);
         energy[cluster2[i]]=(energy[cluster2[i]])-((((16.7)*packet_size[cluster2[i]])+((1.97)*(packet_size[cluster2[i]])*(dis)*(dis))));
         }
         }
    }
    for(i=0;i<k;i++){
    if(energy[cluster1[i]]<0)
         cout<<cluster1[i]<<" sensor is dead "<<endl;
         else
         {
         cout<<cluster1[i]<<" directly sends to sink"<<endl;
         double dis=distance(a[cluster1[i]],b[cluster1[i]],a[n-1],b[n-1]);
         energy[cluster1[i]]-=((((16.7)*(packet_size[cluster1[i]]))+((1.97)*(packet_size[cluster1[i]])*(dis)*(dis))));
         }
         }
    z++;
    for(i=0;i<=7;i++){
    cout<<"energy of sensor"<<i<<" is "<<energy[i]<<endl;
    cout<<"size of packets are "<<packet_size[i]<<endl;
    packet_size[i]=0;
    emergency[i]=0;
    }
    }
    return 0;
 }        
 

