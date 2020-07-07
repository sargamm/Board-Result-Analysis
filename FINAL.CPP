#include<fstream.h>
#include<conio.h>
#include<stdio.h>
#include<process.h>
#include<string.h>
#include<dos.h>


struct subject
{
   int mks;
   int code;
   char nm[30];
   char g[3];   };

struct details
{  char topper[20];
   int pass,fail;
   float avg;
};

class student
{ subject x[6];
  char name[20];
  float cent;
  int adno;
  char rno[10];

  public:

  char* get_name()
  { return name;}

  void feed_mks(int i,int n)
  { x[i].mks=n; }

  float get_mks(int i)
  { return x[i].mks; }

  void show();

  float calculate();

  void feed_rno(char f[20])
  { strcpy(rno,f); }

  void feed_name(char h[20])
  { strcpy(name,h); }

  char* get_sub(int i)
  { return x[i].nm; }

  void feed_adno(int l)
  { adno=l; }

  float get_cent()
  { float a;
   a=calculate();
    return a; }

  char* get_grade(int i)
 {return grade(i);}

  student();


  char* grade(int i);
  };


 student::student()
 {   strcpy(name," ");
     adno=0;
     strcpy(rno," ");
     cent=0.0;
     for(int i=0;i<6;i++)
    { x[i].mks=0.0;
     strcpy(x[i].g," ");
     }
     strcpy(x[0].nm,"English Core");
     strcpy(x[1].nm,"Physics");
     strcpy(x[2].nm,"Chemistry");
     strcpy(x[3].nm,"Maths");
     strcpy(x[4].nm,"Biology");
     x[0].code=301;
     x[1].code=42;
     x[2].code=43;
     x[3].code=41;
     x[4].code=46;
     }


 char* student::grade(int i)
   { if(x[i].mks>90)
     strcpy(x[i].g,"A1");
     else if(x[i].mks>80)
     strcpy(x[i].g,"A2");
     else if(x[i].mks>70)
     strcpy(x[i].g,"B1");
     else if(x[i].mks>60)
     strcpy(x[i].g,"B2");
     else if(x[i].mks>50)
     strcpy(x[i].g,"C");
     else if(x[i].mks>40)
     strcpy(x[i].g,"D");
     else
     strcpy(x[i].g,"E");
     return x[i].g;
     }


 void student::show()
 {
  cout<<"roll no.: "<<rno<<'\n'<<"admn. no.: "<<adno<<'\n'<<"name: "<<name;
  for(int i=0;i<5;i++)
    {cout<<'\n'<<x[i].nm;
    cout<<"---code: "<<x[i].code<<"---marks: "<<x[i].mks<<"---grade: ";
   cout<<grade(i);
    cout<<'\n';}
  cout<<'\n'<<"percentage : "<<calculate();
  getch();cout<<"\n\n";
 }

 float student::calculate()
 {
   float t=0.0;
   for(int i=0;i<5;i++)
   t=t+x[i].mks;
   cent=t/5;
   return cent;
 }

void title()
{ clrscr();
  gotoxy(22,9);
  cout<<"*************************************\n";
  gotoxy(22,10);
  cout<<"        BOARD RESULT ANALYSIS        \n";
  gotoxy(22,11);
  cout<<"*************************************\n";
  gotoxy(30,20);
  cout<<"****************\n";
  gotoxy(30,21);
  cout<<"  DEVELOPED BY  \n";
  gotoxy(30,22);
  cout<<"  SARGAM MONGA  \n";
  gotoxy(30,23);
  cout<<"****************\n";
  getch();
}

void display(char xyz[25])
{ clrscr();
  ifstream mf(xyz,ios::binary);
  if(!mf)
  { cout<<"error";exit(0); }
  student s;
  mf.read((char*)&s,sizeof(s));

  while(mf)
  {
   s.show();
   mf.read((char*)&s,sizeof(s));
  }
  mf.close();
}




void parse()
  {
    ofstream bin("NEW.dat", ios::binary);
    ifstream mf("STUDENT.TEX");

    if(!bin ||!mf)
    { cout<<"Error in stream";
      getch();
      exit(0);
    }
    char w[20];
    int z;
    student s;
    mf>>w;

    while(mf)
    { s.feed_rno(w);
      mf.getline(w,20);
      s.feed_name(w);
      mf>>z;
      s.feed_adno(z);
      for(int i=0;i<5;i++)
      { mf>>z;
      s.feed_mks(i,z);
      }
      bin.write((char*)&s,sizeof(s));
      mf>>w;
    }
    mf.close();
    bin.close();
  }




  void all_A1()
  {
    ifstream a("NEW.dat",ios::binary);
    ofstream b("allA1.dat",ios::binary);
    if(!a || !b)
    { cout<<"error";
      getch();
      exit(0);
    }

    student s;
    int i,n;
    a.read((char*)&s,sizeof(s));
    while(a)
    { n=0;
      for(i=0;i<5;i++)
      {
	if(strcmpi(s.get_grade(i),"A1")==0)
	n++;
	 }
      if(n==5)
      b.write((char*)&s,sizeof(s));
      a.read((char*)&s,sizeof(s));
    }
   a.close();
   b.close();
   display("allA1.dat");
   getch();
   }

  void pass_fail(int i,int &p,int &f)
  { p=0;f=0;
    student s;
    ifstream q("NEW.dat",ios::binary);
    if(!q)
    { cout<<"error";
      getch();
      exit(0);
    }
    q.read((char*)&s,sizeof(s));
    while(q)
    { if(s.get_mks(i)<33)
	 f++;
      else p++;
      q.read((char*)&s,sizeof(s));
    }
    q.close();
    }

    float avg_mks(int i)
  {
    student s;
    ifstream q("NEW.dat",ios::binary);
    if(!q)
    { cout<<"error";
      getch();
      exit(0);
    }
    float t=0.0;
    int n=0;
    q.read((char*)&s,sizeof(s));
    while(q)
    { t=t+s.get_mks(i);n++;
      q.read((char*)&s,sizeof(s));
    }
    t=t/n;
    q.close();

    return t;
    }

    void top(int i,char y[20])
  { float max=0.0;
    student s;
    ifstream q("NEW.dat",ios::binary);
    if(!q)
    { cout<<"error";
      getch();
      exit(0);
    }

    q.read((char*)&s,sizeof(s));
    while(q)
    {
    if(s.get_mks(i)>max)
      {
       max=s.get_mks(i);
	strcpy(y,s.get_name());

      }

      q.read((char*)&s,sizeof(s));
    }
    q.close();

    }

    void showdata()
    {
      ifstream mf("subject.dat",ios::binary);
     if(!mf)
     { cout<<"error";
       getch();
       exit(0);
     }
     details D;
     int i=0;
     mf.read((char*)&D,sizeof(D));
     while(mf)
     { clrscr();
       cout<<"\n\n";
       switch(i)
       {
	 case 0 : cout<<"ENGLISH CORE";
		  break;
	 case 1 : cout<<"PHYSICS";
		  break;
	 case 2 : cout<<"CHEMISTRY";
		  break;
	 case 3 : cout<<"MATHEMATICS";
		  break;
	 case 4 : cout<<"BIOLOGY";
		  break;
       }
       cout<<"\npass: "<<D.pass<<'\n'<<"fail: "<<D.fail<<'\n';
       cout<<"Topper : ";
       cout<<D.topper<<'\t';
       cout<<"average marks : "<<D.avg;
       getch();
       mf.read((char*)&D,sizeof(D));
       i++;
     }
     mf.close();
     }


   void sub_create()
   { ofstream mf("subject.dat",ios::binary);
     if(!mf)
     { cout<<"error";
       getch();
       exit(0);
     }
     details D;
     int p,f;
     for(int i=0;i<5;i++)
     { pass_fail(i,p,f);
       D.pass=p;
       D.fail=f;
       D.avg=avg_mks(i);
       top(i,D.topper);
       mf.write((char*)&D,sizeof(D));
     }
     mf.close();
     showdata();

    }


  void school_top()
  { student A[20];
    ifstream mf("NEW.dat",ios::binary);
    ofstream nf("topper.dat",ios::binary);
    if(!mf)
    {cout<<"ERROR";
     getch();
     exit(0);
     }


    student s,t;
    int n=0;
    mf.read((char*)&s,sizeof(s));
    while(mf)
    {
      A[n]=s;
      n++;
      mf.read((char*)&s,sizeof(s));
    }
    mf.close();
    for(int i=0;i<n-1;i++)
    for(int j=i+1;j<n;j++)
	if(A[i].get_cent()<A[j].get_cent())
	  { t=A[j];
	    A[j]=A[i];
	    A[i]=t;
	  }
   for(int h=0;h<3;h++)
   nf.write((char*)&A[h],sizeof(A[h]));
   nf.close();
  display("topper.dat");
    }


  void main()
  { title();
    parse();
    int op;
    char ch;
    do{
	clrscr();
	gotoxy(22,9);
	cout<<"|~~~~~~~~~~~~~~MAIN MENU~~~~~~~~~~~~~~|\n";gotoxy(22,10);
	cout<<"|         1.DISPLAY ALL RECORDS       |\n";gotoxy(22,11);
	cout<<"|         2.STUDENTS SECURING ALL A1s |\n";gotoxy(22,12);
	cout<<"|         3.SUBJECT DETAILS           |\n";gotoxy(22,13);
	cout<<"|         4.SCHOOL TOPPERS            |\n";gotoxy(22,14);
	cout<<" ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~";gotoxy(22,15);
	cout<<"\n\n\n\n\nEnter Choice";
	cin>>op;

	switch(op)

    {
	case 1 : display("NEW.dat");
		 break;
	case 2 : all_A1();
		 break;
	case 3 : sub_create();
		 break;
	case 4 : school_top();
		 break;
	default: cout<<"INVALID CHOICE";
     }
     clrscr();
     gotoxy(22,9);
     cout<<"Back to Main Menu?y/n";
     cin>>ch;

     } while(ch=='Y'||ch=='y');
   getch();
  }