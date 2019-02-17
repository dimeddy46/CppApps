#include <iostream>
#include <time.h>
#include <windows.h>
#include <fstream>
#include <conio.h>
#include <stdlib.h>
#include <sstream>
#include <math.h>
#include <string.h>
using namespace std;

#define nameNum 39
#define surNum 45
#define echipe 22

#define x_nume 8
#define x_prenume 21
#define x_vst 35
#define x_val 45
#define x_rol 55

// --------------------------------- JUCATOR BUY -> 26 - 40 = > 14 juc------

char Names[50][15] = {"Gigel","Costel","Emil","Silviu","Nicu","George","Traian","Claudiu","Cristian",
"Petru","Robert","Mitica","Razvan","Serban","Ghita","Stefan","Andrei","Marius","Cornel","Dorel","Alexandru","Ioan","Gabriel",
"Rares","Bogdan","Eduard","Teodor","George","Axinte","Mihai","Ovidiu","Alex","Pavel","Sebastian","Niculae","Titel","Codrin","Patrick",
"Constantin","Justin"};
char Surnames[50][15] = {"Stoica","Grecu","Iancu","Andreescu","Enache","Popescu","Ionescu","Pintea",
"Tudor","Plesu","Diaconescu","Banciu","Florescu","Moldovan","Pop","Stefaniu","Antonescu","Muresan","Tomescu","Maxim","Ciutacu","Cilinca",
"Mititelu","Georgescu","Creanga","Stancu","Chiriac","Parvulescu","Anton","Pristanda","Minculescu","Minulescu","Stoiescu","Pop","Staicu",
"Frone","Costin","Avram","Mustata","Pelin","Baciu","Nicolae","Pohoata","Lupescu","Ekong","Mitrea","Lipan"};

const string Teams[30] = {"AC Milan","FC Barcelona","FC Steaua Bucuresti","FC Dinamo Bucuresti","CFR Cluj","FC Juventus","AS Roma",
"CF Real Madrid","FC Astra Giurgiu","FC Liverpool","FC Chelsea","FC Borrusia Dortmund","FC Bayern Munich","FC Rapid Bucuresti","FC Napoli"
"FC Paris SG","FC Internazionale","FC Atletico Madrid","FC Viitorul Constanta","Galatasaray S.K","FC Pandurii Tg. Jiu","FC Villareal","Concordia"};

char Rol[11][4] = {"GK","LB","CB","CB","RB","LMF","CMF","CMF","RMF","ST","ST"};
string ecpNume, ecpAdv;
int juc,wins,lost,efc,numBonus,cmp,meciDay,depl; // cmp = daca a cumparat jucator azi
float bani,medVal,baniChelt,baniCtg;
long sec;
struct tm * now;
time_t rawtime;

struct player {
char nume[15],prenume[15];
int vst,rang,rol;
float val;}ecp[43];

void gotoxy( int column, int line ){
  COORD coord;
  coord.X = column;
  coord.Y = line;
  SetConsoleCursorPosition(GetStdHandle( STD_OUTPUT_HANDLE ),coord);
}

 int getX(){
  CONSOLE_SCREEN_BUFFER_INFO csbi;
  if (!GetConsoleScreenBufferInfo(GetStdHandle( STD_OUTPUT_HANDLE ),&csbi)) return -1;
  return csbi.dwCursorPosition.X;
}

int getY(){
  CONSOLE_SCREEN_BUFFER_INFO csbi;
  if (!GetConsoleScreenBufferInfo(GetStdHandle( STD_OUTPUT_HANDLE ),&csbi)) return -1;
  return csbi.dwCursorPosition.Y;
}
void csxy(int col,int lin,const char s[70]){ // ---------Afiseaza cuvinte la x,y
gotoxy(col,lin);
cout<<s;}
void cixy(int col,int lin,const long s){// ------------Afiseaza numere la x,y
gotoxy(col,lin);
cout<<s;}



void salvare_date(){
ofstream f("ecp.txt");
int i;
f<<ecpNume<<endl<<juc<<" "<<wins<<" "<<lost<<" "<<efc<<" "<<bani<<" "<<numBonus<<" "<<baniChelt<<" "<<baniCtg<<endl;
for(i = 1;i<=juc;i++){
    f<<ecp[i].nume<<" ";
    f<<ecp[i].prenume<<" ";
    f<<ecp[i].vst<<" ";
    f<<ecp[i].val<<" ";
    f<<ecp[i].rol<<" ";
    f<<endl;}f.close();
}
void citire_date(){int i;
    ifstream f("ecp.txt");
    getline(f,ecpNume);//getline(f,ecpAdv);
    f>>juc>>wins>>lost>>efc>>bani>>numBonus>>baniChelt>>baniCtg;
for(i = 1;i<=juc;i++){
    f>>ecp[i].nume;
    f>>ecp[i].prenume;
    f>>ecp[i].vst;
    f>>ecp[i].val;
    f>>ecp[i].rol;
 }f.close();

    ifstream f2("urmMeci.txt");
    f2>>i>>depl>>meciDay;
    f2.close();
    ecpAdv = Teams[i];
}
string af_valoare(float val,bool a = 0){
string str;
ostringstream strs;
if(a == 0){ // --------- afisare valoare jucator ------------
    strs << val;str = strs.str();
    if(val >= 1)str.append("M");
    else {str.erase(0,2);if(str.length() == 1)str.append("00");
    else if(str.length() == 2) str.append("0");
    str.append("K");}
}
else {      // -------------- afisare bani -----------
     strs << val;str = strs.str();
     if(val >= 1 && a == 1){if(str.length() > 5)str.erase(5,6);
     str.append(" milioane $");}
     else if(val < 1 && a == 1) {str.erase(0,2);str.erase(3,4);str.append(" mii $");}
}
return str;
}

/*void meci(){int minut = 0,scor1 = 0,scor2 = 0;
cin.get(ecpNume,25);system("cls");gotoxy(0,2);
cout<<setw(23)<<ecpNume;
cixy(30,2,scor1);
csxy(37,2,"VS.");
cixy(44,2,scor2);
csxy(51,2,"Nume echp. adversa");
gotoxy(0,4);cout<<setw(39)<<minut;
csxy(39,4,"'");
csxy(17,10,"Pentru a incepe meciul,apasa orice tasta.");
getch();
csxy(17,10,"                                         ");
csxy(11,10,"Pentru a trece peste meci apasa tasta ENTER.");
while(minut != 45){Sleep(1000);
cout<<setw(39)<<minut;gotoxy(0,4);minut++;
    if(kbhit()){int ch;
        ch = getch();
        if(ch == 13){csxy(1,1,"Meciul s-a terminat");break;}}
                }
}*/

void Semn_x(int &y,int dir,int a = 0){ // ----------- dir = 2 se duce jos // -------dir = -2 se duce sus
    int z = a == 3?59 : 66;
    if(((y+dir >= 2 && a!= 3)||(y+dir >=6 && a == 3)) && y+dir != 24 && y+dir <= juc*2+2) { // ----- DACA SE AFLA INTRE TOP SI REZERVE
            if(y+dir == 2)gotoxy(0,0);
                csxy(4,y,"   ");            // ----------- Stergere [X] DE sus stg
                csxy(4,y+dir,"[X]");        // ----------- Afisare [X] Nou
                csxy(z,y,"   ");
                csxy(z,y+dir,"[X]");
                y+=dir;}
    else if((y+dir == 24 && a != 3)&& (dir == 2 || dir == -2)){ // - daca urmatoarea alegere e bara cu rezerve -> creste/scade doua unitati
            csxy(4,y+dir*2,"[X]");csxy(4,y,"   ");
            csxy(66,y+dir*2,"[X]");csxy(66,y,"   ");y +=dir*2;}
}

void eficienta_ecp(){
        efc = 0;
        for(int i = 1;i<=11;i++){      // ---------- calc. eficienta echipei,
            if(strcmp(Rol[ecp[i].rol],Rol[i-1]) == 0)efc += 9;}
        csxy(18,0,"  ");
        cixy(18,0,efc);
    }
void valMedieEcp(){
    medVal = 0;
    for(int i = 1;i<=11;i++)
    medVal+=ecp[i].val;
    medVal /= 11.0;
    csxy(60,0,"               ");gotoxy(60,0);
    cout<<af_valoare(medVal,1);
}

void Schb_propriu(int alg1,int alg2){
    swap(ecp[alg1].nume,ecp[alg2].nume);
    swap(ecp[alg1].prenume,ecp[alg2].prenume);
    swap(ecp[alg1].rang,ecp[alg2].rang);
    swap(ecp[alg1].rol,ecp[alg2].rol);
    swap(ecp[alg1].val,ecp[alg2].val);
    swap(ecp[alg1].vst,ecp[alg2].vst);
}


void Schimbare_jucatori(int a = 0){
    int x = 2,alg1 = 0,alg2,var1 =0,var2,g;
    x = a == 3?6 : 2;
    var1 = a == 3 ? 59 : 66;
        csxy(4,x,"[X]");
        csxy(var1,x,"[X]");
        if(a != 3)gotoxy(0,0);
while(g != -1){
    g = getch();
            if(g == 27){system("cls");break;}
           if(g == 13){ // ---------- PRIMA SELECTARE PT SCHIMBARE --------
    if(alg1 == 0){csxy(3,x,"X");csxy(69,x,"X");
        if(x <= 22 && a != 3)alg1 = x/2;
        else if(a != 3)alg1 = x/2-1;
        else if(a == 3)alg1 = (x-4)/2+25;
        var1 = x; // --------------------- legatura afisaj - cod
        if(a == 1){system("cls");//   ---------------------- VINDERE JUCATOR ---------------------------------
            if(juc-1 < 18){
            cout<<"Nu poti ramane cu mai putin de 16 jucatori."; goto Z;}

            cout<<"Esti sigur ca vrei sa-l vinzi pe: "<<ecp[alg1].nume<<" "<<ecp[alg1].prenume<<" ?"<<endl;
            cout<<"Jucatorul are "<<ecp[alg1].vst<<" ani, ocupa rolul "<<Rol[ecp[alg1].rol]
                <<" si momentan valoreaza $"<<af_valoare(ecp[alg1].val)<<endl;
            cout<<endl<<"Apasa ENTER pentru a vinde jucatorul sau ESC pentru a renunta la vanzare.";
            X:
            g = getch();
                    if(g == 13){
                                bani+=ecp[alg1].val;gotoxy(7,6);
                                cout<<"Felicitari! Jucatorul a fost vandut! Ai primit $"<<af_valoare(ecp[alg1].val)<<
                                endl<<"        Apasa orice tasta pentru a reveni la meniu.";
                                Schb_propriu(juc,alg1);juc--;baniCtg += ecp[alg1].val;salvare_date();}
                    else if(g != 27)goto X; //        ---------------- apasare orice tasta in afara de ESC | ENTER-----------
                    else goto Z2;// menu
                goto Z;// -------------- ESC || SUCCES ----------
                      } // --------------------- SFARSIT VINDERE JUCATOR ------------------------------------

         if(a == 3){  // ---------------------------- CUMPARARE JUCATOR --------------------------------
            system("cls");
            float pr1,pr2;
            cout<<"Esti sigur ca vrei sa-l cumperi pe: "<<ecp[alg1].nume<<" "<<ecp[alg1].prenume<<" ?"<<endl;
            cout<<"Jucatorul are "<<ecp[alg1].vst<<" ani, ocupa rolul "<<Rol[ecp[alg1].rol]
                <<" si momentan valoreaza $"<<af_valoare(ecp[alg1].val)<<endl<<endl<<"     Ai "<<af_valoare(bani,1)<<".";
                pr1 = ecp[alg1].val;                      // -------  acc valoare in bani
                pr2 = pr1 + (pr1*3)/10;  // ----- 30 % in plus
               // pr2 = pr2 * 1000;
               // var2 = pr2 /10;    pr2 = var2 / 100.0;
               // cout<<var2<<" "<<(float)pr2;
            cout<<endl<<"     Vei plati "<<af_valoare(pr2,1)<<" pentru transfer.(30% in plus)";
            cout<<endl<<endl<<"Apasa ENTER pentru a cumpara jucatorul sau ESC pentru a reveni la meniu.";
            Y:
            g = getch();
                    if(g == 13){
                            if(bani < pr2){
                                system("cls");
                                cout<<"Nu ai destui bani ca sa cumperi acest jucator!"<<endl
                                    <<"       Bani: $"<<af_valoare(bani,1)<<"."<<endl
                                    <<"       Pret jucator: $"<<af_valoare(pr2,1)<<endl
                                    <<"Apasa orice tasta pentru a te intoarce la meniu."; goto Z; }
                        gotoxy(8,8);bani-=pr2;
                        cout<<"Felicitari! Jucatorul a fost cumparat!"<<endl<<"    Ai platit $"<<af_valoare(pr2,1)<<"."<<endl<<
                        "    Mai ai $"<<af_valoare(bani,1)<<endl<<"        Apasa orice tasta pentru a te intoarce la meniu.";
                        juc++;Schb_propriu(alg1,juc);cmp = 1; ofstream f("juc.txt"); f<<1; f.close();baniChelt +=pr2;salvare_date();}
                        else if(g != 27)goto Y;
                        else goto Z2;//   ---------------- apasare orice tasta in afara de ESC | ENTER-----------
                   Z: getch();
                   Z2: system("cls");break;
                    }  // ---------------------------- SFARSIT CUMPARARE JUCATOR --------------------------------
                }
    else { //------------ A 2-A SELECTARE PT SCHB ------------
            if(x <= 22)alg2 = x/2;else alg2 = x/2-1; var2 = x; // -------- legatura afisaj - cod
        // -------- alg1,alg2 = pozitia in vector | var1,var2 = pozitia in afisare(linie)  | x = cursor pt determinare linie

    Schb_propriu(alg1,alg2);

    csxy(3,var1,"                                                           ");
    csxy(3,var2,"                                                           ");
                    // ----------- AFISARE PRIMA SCHIMBARE
    csxy(x_nume,var1,ecp[alg1].nume);
    csxy(x_prenume,var1,ecp[alg1].prenume);
    cixy(x_vst,var1,ecp[alg1].vst);
    csxy(x_val,var1,af_valoare(ecp[alg1].val).c_str());
    csxy(x_rol,var1,Rol[ecp[alg1].rol]);
                    // ----------- AFISARE A 2-A SCHIMBARE
    csxy(x_nume,var2,ecp[alg2].nume);
    csxy(x_prenume,var2,ecp[alg2].prenume);
    cixy(x_vst,var2,ecp[alg2].vst);
    csxy(x_val,var2,af_valoare(ecp[alg2].val).c_str());
    csxy(x_rol,var2,Rol[ecp[alg2].rol]);
    if((alg1 <= 11 || alg2 <= 11) && strcmp(Rol[ecp[alg1].rol],Rol[ecp[alg2].rol]) != 0)
    eficienta_ecp();
    valMedieEcp();
    alg1= 0; //x = var2; csxy(4,var2,"[X]");csxy(69,var1," ");csxy(66,var2,"[X]");
    x = 2; csxy(69,var1," ");csxy(66,var2,"     ");csxy(4,x,"[X]");csxy(66,x,"[X]");gotoxy(0,0);
    salvare_date();
       }
} // ------- END IF g == 13
            if(g == 224){g = getch();
                if(g == 72)Semn_x(x,-2,a); // ------ sageata jos
                else if(g == 80)Semn_x(x,2,a);}// -------- sageata sus
        } // --- END WHILE (g != 2 )
}

void afsEcp(int a = 0){     // -------- a == 0 -> afs normala | a == 1 -> vindere juc |
                            //--------- a == 2 -> schimbare jucatori  |  a == 3 -> cumparare juc
int i,s,z = 1,memjuc = juc;
  if(a != 3)
      csxy(0,1,"        NUME        PRENUME      VARSTA   VALOARE($)   ROL    POST");
  else {
      csxy(0,0,"                           CUMPARARE JUCATORI");
      csxy(0,1,"   - Cumparand un jucator vei plati 30% in plus fata de valoarea sa.");
      csxy(0,2,"   - Ofertele se schimba in fiecare zi.");
      csxy(0,3,"   - Pot aparea jucatori legendari (prob. 1 / 1500). Acestia costa dublu.");
      csxy(0,4,"   - Poti cumpara un singur jucator pe zi.");
      csxy(0,5,"        NUME        PRENUME      VARSTA   VALOARE($)   ROL");}
s = getY()+1;
if(a != 3){
    csxy(0,0,"Eficienta echipa:   %");
    csxy(45,0,"Valoare medie:");
    eficienta_ecp();
    valMedieEcp();}
else {z = 26;juc = 34;}
for(i = z;i<=juc;i++){
    csxy(x_nume,s,ecp[i].nume);
    csxy(x_prenume,s,ecp[i].prenume);
    cixy(x_vst,s,ecp[i].vst);
    csxy(x_val,s,af_valoare(ecp[i].val).c_str());
    csxy(x_rol,s,Rol[ecp[i].rol]);
    if(i <= 11 && a != 3)
    csxy(63,s,Rol[i-1]); // ----------------------------- AFISARE POST(COL DREAPTA) --------------------
    if(a != 3)
    csxy(2,s+1,"----------------------------------------------------------------------");
    else csxy(2,s+1,"--------------------------------------------------------------");
    if(i == 11 && a != 3){
            csxy(3,s+2,"******************************REZERVE*********************************");
            csxy(3,s+3,"                                                                  ");}
    s = getY()+1;}juc = memjuc;z = 1;
    if(a == 1 || a == 2 || a == 3) // ----------- Vindere jucator || schimbare juc || cumparare juc
    Schimbare_jucatori(a);
}
void generare_echipa(int a = 0){ // ----------- a == 0 -> generare echipa normala | a == 1 -> generare jucatori pt buy
    int i= 0,x,y,z,t = 0,jucBuy = 0,jucAdv = juc;
    float rar;
    srand(time(NULL));
    if(a == 1){jucBuy = 25;juc = 9;} // ------------------- SMECHERIE combinare cumparare cu ecp.
  for(i = 1;i<=juc;i++){
    strcpy(ecp[i+jucBuy].nume,Names[rand()%35]);
    strcpy(ecp[i+jucBuy].prenume,Surnames[rand()%43]);
    ecp[i+jucBuy].vst = rand()% 16 +18;
    if(i <= 11 && a == 0) // --------------- Asigurare exista minim un jucator pt fiecare post ------------
        ecp[i+jucBuy].rol = i-1;
    else ecp[i+jucBuy].rol = (rand()% 121) / 11;
    // --------------------------------------- GENERATOR VALOARE ----------------------------------
        x = rand()%100+1;y = rand()%100+1;z = rand()%100+1; // 10000 = 10KK , 1000 = 1KK , 100 = 100K , 10 = 10K
    if(x >= y && x <= z && abs(x-z) <= 3 && abs(x-y)<= 3 && t == 0) // ---------------- LEGEND(10m~20m)
        {rar = rand()%10;rar = rar/10+(rand()%10+10);t = 1;}
    else if(x > y && x < z && abs(x-z) <= 10 && abs(x-y) <= 10) // ----------------- EPIC(1m~10m)
        {rar = rand()%10;rar = rar/10+(rand()%9+1);}
    else if(x > y && abs(x-z) <= 35) // ----------------- RARE(600k~1m)
        rar = (rand()%500+500)/1000.0;
    else // ------------------ PRAF(100~600k)
        rar = (rand()%400+100)/1000.0;
    ecp[i+jucBuy].val = rar;
              }
        juc = jucAdv;
            if(a == 0)
                for(i = 1;i<=14;i++){x = rand()%juc+1;y = rand()%juc+1;
                Schb_propriu(x,y);} // ----------------- SCHIMBURI RANDOM PT EFICIENTA SCAZUTA------------------
}
void vindere_juc(){afsEcp(1);}
void schmb_juc_meniu(){afsEcp(2);}
void cumparare_juc(){int i,x,y,z;
    ifstream g("cumparare.txt");ifstream s("time.txt");s>>x>>y>>z>>i;s.close();
    if(!g || i != now->tm_yday){
        ofstream f("time.txt");
        f<<x<<" "<<y<<" "<<z<<" "<<now->tm_yday;
        f.close();
        ofstream g2("cumparare.txt");
        generare_echipa(1);g2<<0<<endl;cmp = 0;
            for(i = 26;i<=34;i++){
                g2<<ecp[i].nume<<" ";
                g2<<ecp[i].prenume<<" ";
                g2<<ecp[i].vst<<" ";
                g2<<ecp[i].val<<" ";
                g2<<ecp[i].rol<<" ";
                g2<<endl;}g2.close();
    }
    else {g>>cmp;
        if(cmp == 0)
        for(int i = 26;i<=34;i++){
            g>>ecp[i].nume;
            g>>ecp[i].prenume;
            g>>ecp[i].vst;
            g>>ecp[i].val;
            g>>ecp[i].rol;}}
    if(cmp == 1){
            cout<<"       Deja ai cumparat un jucator astazi. Mai incearca maine."<<endl
                <<"          Apasa orice tasta pentru a te intoarce la meniu."; getch(); system("cls");}
    else afsEcp(3);
}

void bonus(){int x,y;
time(&rawtime);now = localtime(&rawtime);
csxy(0,0,"Secunde de asteptat pentru a primi bonusul: ");gotoxy(0,1);
cout<<"Ai primit bonusul de "<<numBonus<<" ori.";
x = now->tm_hour*3600+now->tm_min*60+now->tm_sec;
    while(!kbhit()){
        y = 600 - abs(sec-x);
            if(y <= 0){system("cls");
                cout<<"Felicitari, ai primit un bonus de 150K !Apasa orice tasta.";bani+=0.150;y = 600;getch();
                sec = now->tm_hour * 3600 + now->tm_min *60+now->tm_sec; numBonus++;baniCtg+=0.150;
                ofstream f3("time.txt");f3<<now->tm_hour<<" "<<now->tm_min<<" "<<now->tm_sec<<" "<<now->tm_yday;
                csxy(0,0,"                                                                ");
                csxy(0,0,"Secunde de asteptat pentru a primi bonusul: ");gotoxy(0,1);
                cout<<"Ai primit bonusul de "<<numBonus<<" ori.";f3.close();}

        cixy(44,0,y);
        Sleep(1000);
        csxy(44,0,"            ");
        x++;}

        system("cls");
}
void istoric(){string s;system("cls");
csxy(25,0,"ISTORIC MECIURI");
int i =2;
ifstream f("meciuri.txt");
if(!f)csxy(20,4,"Echipa ta nu a jucat nici un meci pana acum.");
else {
    while(getline(f,s)){gotoxy(20,i);
    cout<<s;i+=2;}
}
getch();system("cls");}
void statistici(){
    csxy(30,0,"STATISTICI ECHIPA");
    gotoxy(23,4);cout<<"Bani: "<<af_valoare(bani,1);
    gotoxy(23,6);cout<<"Meciuri castigate: "<<wins;
    gotoxy(23,8);cout<<"Meciuri pierdute: "<<lost;
    gotoxy(23,10);
    if(baniCtg == 0)
    cout<<"Bani castigati: 0";
    else cout<<"Bani castigati: "<<af_valoare(baniChelt);
    gotoxy(23,12);
    if(baniChelt == 0)
    cout<<"Bani cheltuiti / pierduti: 0";
    else cout<<"Bani cheltuiti / pierduti: "<<af_valoare(baniChelt);
    gotoxy(23,14);cout<<"Numar total de jucatori: "<<juc;
    getch();system("cls");
}
void nextGame(int a = 0){
    if(a == 1){time(&rawtime);now = localtime(&rawtime);
        meciDay = now->tm_yday;}
    else meciDay++;
srand(time(NULL));
ofstream f("urmMeci.txt");
int z= rand()%echipe,depl = rand()%10+1;

f<<z<<" "<<depl<<" "<<meciDay;
ecpAdv = Teams[z];
f.close();
}
void meci(){srand(time(NULL));
        time(&rawtime);
        now = localtime(&rawtime);
        if(now->tm_yday == meciDay){
    ofstream f;
    valMedieEcp();eficienta_ecp();
    f.open("meciuri.txt",ios_base::app);
    int x1 = 0,x2 = 0,noroc1 = ((rand() % 100)*2)/10,noroc2 = ((rand() % 100)*2)/10,efc2 = ((rand() % 60+40)*4)/10,efc1 = (efc*4)/10;
    float medValAdv = medVal;
    if(rand()% 10 < 6) medValAdv -=medVal*0.5;
    else medValAdv += medVal*0.5;
    if(medVal > 1) medValAdv = (medValAdv * 100* 4)/10;
    else medValAdv = (medValAdv * 1000*4)/10;
    x1 = medVal + noroc1+ efc1;
    x2 = medValAdv + noroc2 +efc2;
    if(x1 > x2){   // -- win
       if(rand()%5 != 2){x1 = rand()%4+2;x2 = rand()%2;}
       else {x1 = 1;x2 = 0;}
        wins++;bani+=0.5; baniCtg +=0.5;}
    if(x1 < x2){   // -- lost
        if(rand()%5 != 2){x1 = rand()%2;x2 = rand()%4+2;}
        else {x2 = 1;x1 = 0;}
        lost++;bani-=0.2;baniChelt+= 0.2;}

    csxy(25,3,"Meciul s-a terminat.");
    gotoxy(18,5);
    if(depl <= 5){
            cout<<ecpNume<<"     "<<x1<<"-"<<x2<<"     "<<ecpAdv;
            f<<ecpNume<<" "<<x1<<"-"<<x2<<" "<<ecpAdv<<endl;}
    else {
            f<<ecpAdv<<" "<<x2<<"-"<<x1<<" "<<ecpNume<<endl;
            cout<<ecpAdv<<"     "<<x2<<"-"<<x1<<"     "<<ecpNume;}
    f.close();
    nextGame();
    salvare_date();}
    else csxy(15,3,"Azi nu se joaca nici un meci. Incearca maine.");
    getch();
    system("cls");
}
void meniu(){L:
    int x = 1,g = 1 ,varCol = 5,varLin = 1;csxy(5,1,"[X]");
    gotoxy(9,1);if(depl <= 5)cout<<"1. Urmatorul meci [Deplasare] contra [ "<<ecpAdv<<" ]";
    else cout<<"1. Urmatorul meci [Acasa] contra ["<<ecpAdv<<" ]";
    gotoxy(14,4);cout<<"2. Statistici / finante [ "<<ecpNume<<" ]";
    csxy(19,7,"3. Schimbare pozitionare echipa");
    csxy(24,10,"4. Cumparare jucator");
    csxy(29,13,"5. Vanzare jucator");
    csxy(34,16,"6. Obtinere bonus");
    csxy(39,19,"7. Istoric meciuri");
    while(g != -1){
    g = getch();
    if(g == 13){system("cls");
        if(x == 1){meci();}
        if(x == 2){statistici();}
        if(x == 3){afsEcp(2);}
        if(x == 4){cumparare_juc();}
        if(x == 5){vindere_juc();}
        if(x == 6){bonus();}
        if(x == 7){istoric();}
        goto L;
    }
      if(g == 224){g = getch();
                if(g == 72 && x != 1){csxy(varCol,varLin,"   ");varCol-=5;varLin-=3;csxy(varCol,varLin,"[X]");x--;}
                else if(g == 80 && x != 7){csxy(varCol,varLin,"   ");varCol+=5;varLin+=3;csxy(varCol,varLin,"[X]");x++;}
        }
    }
}


void citire_timp(){
ifstream f2("time.txt");
        time(&rawtime);
        now = localtime(&rawtime);
    if(f2){
        int x,y,z;
        f2>>x>>y>>z;sec = x * 3600 + y*60+z;
        }
    else {
        ofstream f3("time.txt");
        f3<<now->tm_hour<<" "<<now->tm_min<<" "<<now->tm_sec<<" "<<now->tm_yday;
        sec = now->tm_hour * 3600 + now->tm_min *60+now->tm_sec;
        f3.close();}
        f2.close();
}


void intro(){
csxy(4,3,"Bun venit in Manager Simulator 2016.");
csxy(6,4,"Introduceti un nume pentru echipa: ");
getline(cin,ecpNume);
system("cls");juc = 20;
generare_echipa();gotoxy(5,5);bani+=3.0;
cout<<"      Echipa ta a fost generata! Ai primit 3 milioane $. "<<endl<<endl<<
      "    Jucatorii sunt clasati in functie de valoare: "<<endl<<
      "        - COMMON (100K - 499K)"<<endl<<
      "        - RARE (500K - 999K)"<<endl<<
      "        - EPIC (1MLN - 9.9MLN)"<<endl<<
      "        - LEGEND (10MLN - 20MLN)"<<endl<<endl<<
      "   Selectiile se fac din sageti(sus,jos), ESC si ENTER"<<endl<<endl<<
      "   In joc se poate obtine un bonus la fiecare 10 minute(timp real)."<<endl<<endl<<
      "   Meciurile se joaca in fiecare zi impotriva unor echipe random."<<endl<<endl<<
      "   Win = +500K / Lose = -200K "<<endl<<endl<<
      "                 MULT NOROC!!   ";
      nextGame(1);
      getch();system("cls");
}

int main()
{
    ifstream f("ecp.txt");
if(!f){
intro();salvare_date();}
else {f.close();citire_date();}
citire_timp();
meniu();


    return 0;
}
