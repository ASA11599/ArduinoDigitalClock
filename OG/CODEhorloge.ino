#include <LiquidCrystal.h>

LiquidCrystal
lcd(12,11,5,4,3,2);

int heures=11;             // heures
int minutes=02;           // minutes
int secondes=00;         // secondes
int jours;              // compte le nb de jours depuis le depuis du mois
int annees=2018;       // année
String mois;          // noms en 3 lettres du mois
int JOURS=75;        // compte le nb de jours depuis le début de l'année
int SC=0;           // secondes du chronomètre
int MC=0;          // minutes du chronomètre 
int bouton;       // mesure une valeur qui permet de savoir quel bouton est enclenché
int compteur=1;  // compte le nombre de fois que l'on appuie sur un bouton pour permuter entre les fonctionnalités
int SM;         // secondes du minuteur
int MM;        // minutes du minuteur

void setup()
{
  lcd.begin(16,2);
  Serial.begin(9600);
  pinMode(10,OUTPUT);
  digitalWrite(10, HIGH);
}

void loop() 
{
  Serial.println(analogRead(A5));
 
  // POUR L'HEURE
  
  lcd.setCursor(0,0);     
  secondes++;
  lcd.print("TEMPS:");
  if (heures<=9)
  {
  lcd.print("0");
   }      
  lcd.print(heures);
  lcd.print(":");
  if (minutes<=9)
  {
  lcd.print("0");
   }  
  lcd.print(minutes);                                 
  lcd.print(":");
  if (secondes<=9)
  {
  lcd.print("0");
   }  
  lcd.print(secondes);

  delay(988.481675);
  lcd.clear();
  if (secondes==60)    
  {
    secondes=0;              // remet les secondes à 0 à la fin d'une minute
    minutes++;              // ajoute une minute
  }
  if (minutes==60)
  {
    minutes=0;              // remet les minutes à 0 à la fin d'une heure 
    heures++;              // ajoute une heure 
    tone(7,500,100);      // émet un son
  }

//POUR LA DATE 
 
if (heures==24)
{
  JOURS++;
  heures=0;                // remet les heures à 0 à la fin d'un jour
}
if (JOURS<=31)
{
  mois="JAN";
  jours=JOURS;
}
if (JOURS>31 && JOURS<=59)
{
  mois="FEV";
  jours=JOURS-31;
}
if (JOURS>59 && JOURS<=90)
{
  mois="MAR";
  jours=JOURS-59;
}
if (JOURS>90 && JOURS<=120)
{
  mois="AVR";
  jours=JOURS-90;
}
if (JOURS>120 && JOURS<=151)
{
  mois="MAI";
  jours=JOURS-120;
}
if (JOURS>151 && JOURS<=181)
{
  mois="JUN";
  jours=JOURS-151;
}
if (JOURS>181 && JOURS<=212)
{
  mois="JUI";
  jours=JOURS-181;
}
if (JOURS>212 && JOURS<=243)
{
  mois="AOU";
  jours=JOURS-212;
}
if (JOURS>243 && JOURS<=273)
{
  mois="SEP";
  jours=JOURS-243;
}
if (JOURS>273 && JOURS<=304)
{
  mois="OCT";
  jours=JOURS-273;
}
if (JOURS>304 && JOURS<=334)
{
  mois="NOV";
  jours=JOURS-304;
}
if (JOURS>334 && JOURS<=365)
{
  mois="DEC";
  jours=JOURS-334;
}
if (JOURS==366)
  {
    annees++;
    JOURS=0;
  }
  
//POUR LES BOUTONS

bouton=analogRead(A5);
if (bouton>=1010 && bouton<=1030)
    {
      heures++;                          // le premier bouton ajoute une heure
    }
else if (bouton>=990 && bouton<=1000)
    {
      minutes++;                         // le deuxième bouton ajoute une minute
    }
else if (bouton>=945 && bouton<=960)
    {
      minutes--;                         // le troisième bouton soustrait une minute
        if (minutes<0)
         {
            minutes=60+minutes;
         }
    }
else if (bouton>= 785  && bouton<=791)   // le cinquième bouton règle le minuteur à 5 minutes ET remet le chronomètre à zéro ET avance jour par jour dans l'année
{if (compteur==3)
 {MM=5;                              
 SM=0;}
 if (compteur==1)
 {MC=0;
 SC=0;}
 if (compteur==2)
 {JOURS++;}
}
else if (bouton>=507  && bouton<=512)   // le sixième bouton règle le minuteur à 10 minutes ET soustrait une année
{if (compteur==3)
 {MM=10;                              
 SM=0;}
 if (compteur==2)
 {annees--;}
}
else if (bouton>=288  && bouton<=292)  // le septième bouton règle le minuteur à 15 minutes ET  ajoute une année
{if(compteur==3)
 {MM=15;
 SM=0;}
 if (compteur==2)
 {annees++;} 
}

// POUR LE COMPTEUR

if (bouton>=885 && bouton<=890)       // le quatrième bouton compte de 1 à 3 afin d'associer une fonctionnalité à un chiffre et de permuter entre elles
  {
    compteur++;
  } 
if (compteur==4) 
{
compteur=1;
}

 // POUR LE MINUTEUR                // un décompte de 15, 10 ou 5 minutes
 
if (compteur==3)
{if (not (MM==0 && SM==0))
{
SM--;
}}
if (SM<0)
{
  SM=59;
 }
 if (SM==59) 
 {
  MM--;
 }
 if (MM==0 && SM==0)
{if (compteur==3)
 {tone(7,500,2000);}
}
if (MM<0)
{
MM=0;
}

//POUR CHOISIR LES FONCTIONNALITÉS
 
if (compteur==1)
  {
    lcd.setCursor(0,1);
    lcd.print("CHRONO:");
    lcd.print("m:");
    if (MC<10) 
    {
      lcd.print("0");
    }
    lcd.print(MC);
    lcd.print(" s:");
    if (SC<10)
    {
      lcd.print("0");
    }
    lcd.print(SC);
    SC++;
    if (SC==60) 
    {
      MC++;
      SC=0;
    }
} 
else if (compteur==2)
  {
    lcd.setCursor(0,1);
    lcd.print("DATE:");
    lcd.print(jours);
    lcd.print("|");
    lcd.print(mois);
    lcd.print("|");
    lcd.print(annees);
    SC=0;
    MC=0;
  }
 else if (compteur==3)
  {
    lcd.setCursor(0,1);
    lcd.print("MINUTEUR:");
    if (MM<10) 
    {
      lcd.print("0");
    }
    lcd.print(MM);
    lcd.print(":");
    if (SM<10) 
    {
      lcd.print("0");
    }
    lcd.print(SM);
    SC=0;
    MC=0; 
  }
}
