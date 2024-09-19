/*
Open source not for commercial deployment
*/
//---------------------------------------------------------------------------


#pragma hdrstop

#include "Utils.h"

bool loggingOn;
String LogDir;

void setLoggingOn(bool b)
{
     loggingOn = b;
}

void setLogDir(String s)
{
     LogDir = s;
}

String getUntil(const String s, const String c)
{
       int pos = s.UpperCase().Pos(c.UpperCase());
       if (pos>0) return s.SubString(1,pos-1);
       else return s;
}

String getAfter(const String s, const String c)
{
       int pos = s.UpperCase().Pos(c.UpperCase());
       if (pos>0) return s.SubString(pos+c.Length(),s.Length());
       else return "";
}

String replace(String s, const String oldStr, const String newStr)
{
       if (oldStr.Length()==0) return  s;
       while (s.UpperCase().Pos(oldStr.UpperCase())>0)
       {
             int oldPos = s.UpperCase().Pos(oldStr.UpperCase());
             s = s.SubString(0,oldPos-1) + newStr + s.SubString(oldPos+oldStr.Length(),s.Length());
       }
       return s;
}

String removeTags(String s)
{
       while (s.Pos("<")>0)
       {
             String rest = getAfter(s,"<");
             s = getUntil(s,"<");
             if (rest.Pos(">")>0)
                s += getAfter(rest,">");
             else
                return s+rest;
       }
       return s;
}



__int16 calcBrightness(int Brightness, const String s)
{
     if (s.Pos("Inc_")==1)       Brightness+=  StrToInt( getAfter(s,"_") );
     else if (s.Pos("Dec_")==1)  Brightness-=  StrToInt( getAfter(s,"_") );
     else if (s.Pos("Reset")==1) Brightness= 0;

     if (Brightness>256)         Brightness = 256;
     if (Brightness<-256)        Brightness = -256;

     return Brightness;
}

double calcContrast(double Contrast, const String s)
{
     if (s.Pos("Reset")==1)       Contrast= 1;
     else                         Contrast*=  MyStrToFloat( s );

     if (Contrast>33)             Contrast = 33;
     if (Contrast<0.03)           Contrast = 0.03;

     return Contrast;
}
//---------------------------------------------------------------------------

void Log(const String data)
{
    if (!loggingOn) return;
    if (data.Length()==0) return;
    ofstream logFile ((LogDir + "log.txt").c_str(), ios::app);
    String logData = DateToStr(Date()) + " " + TimeToStr(Time()) + " " + data + "\n";
    logFile.write(logData.c_str(), logData.Length());
    logFile.close();
};
//---------------------------------------------------------------------------

void RestartLog(String data)
{
    if (data.Length()==0) return;
    ofstream logFile ((LogDir + "log.txt").c_str(), ios::out | ios::trunc);
    String logData = DateToStr(Date()) + " " + TimeToStr(Time()) + " " + data + "\n";
    logFile.write(logData.c_str(), logData.Length());
    logFile.close();
};
//---------------------------------------------------------------------------


float MyStrToFloat(String s)
{
      DecimalSeparator = '.';
      replace(s, ",", ".");
      return StrToFloat(s);
}
//---------------------------------------------------------------------------

String GetFromIniFile(const String Chapter, const String Part, const String Default, const String Filename)
{
	char * rVal_a = new char [1024];
        GetPrivateProfileStringA(Chapter.c_str(), Part.c_str(), Default.c_str(), rVal_a, 1024, Filename.c_str());
        String retval = rVal_a;
        delete rVal_a;
        return retval;
}

void PutInIniFile(const String Chapter, const String Part, const String Value, const String Filename)
{
        WritePrivateProfileStringA(Chapter.c_str(), Part.c_str(), Value.c_str() , Filename.c_str());
}


String GetLanguageString(const String Part, const String Default)
{
   return GetFromIniFile("Translation", Part, Default, LogDir+"lanuage.ini");
}

String expandPicutureFileName(String s)
{
     s = s.UpperCase();
     if (s.Pos(":")==0)
          s = LogDir + "data\\background\\" + s;

     if ((s.Pos(".JPG")<s.Length()-3) && (s.Pos(".BMP")<s.Length()-3))
          s += ".jpg";     // if no extension add .jpg
     return s;
}

// check if the string consist of all numbers
bool allNumbers(const String s)
{
     for (int i=1;i<=s.Length();i++)
     {
         if (s[i]<'0') return false;
         if (s[i]>'9') return false;
     }
     return true;
}


int getLeadingNumber(String s)
{
     String numberString;
     int i=1;
     while ((s.Length()>i) && (s[i]>='0') && (s[i]<='9'))
     {
           numberString += s[i];
           i++;
     }
     if (numberString.Length()==0) return 0;
     return StrToInt(numberString.c_str());
}


String NextPrevSong(String s, bool increase)
{
   s= getUntil(s,",");
   s= getUntil(s,":");
   s= replace(s," ","");

   //find begin of trailing number
   int i=s.Length();
   while ((s[i]>='0') && (s[i]<='9')) i--;

   String endNumberString= s.SubString(i+1,s.Length());
   String leadingBookString= s.SubString(1,i);
   if (endNumberString.Length()==0) return "";

   if (increase)   return leadingBookString + IntToStr(StrToInt(endNumberString)+1);
   else            return leadingBookString + IntToStr(StrToInt(endNumberString)-1);

}


void LogThisDay(String data)
{
    if (data.Length()==0) return;
    String  DayString[] ={"","Sun","Mon","Tue","Wed","Thu","Fri","Sat"};

    TDateTime now = Now();

    String logData =  DateTimeToStr(now) + "," + data + "\n";
    ofstream logFile ((LogDir + "LOG\\"+ DayString[now.DayOfWeek()] + DateToStr(Date()) +".log").c_str(), ios::app);

    logFile.write(logData.c_str(), logData.Length());
    logFile.close();
}

#pragma package(smart_init)
