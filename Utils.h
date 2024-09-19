//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <iostream.h>
#include <fstream.h>
#include <ExtCtrls.hpp>
#include <jpeg.hpp>
#include <Graphics.hpp>




#ifndef UtilsH
#define UtilsH


String getUntil(const String s, const String c);
String getAfter(const String s, const String c);
String replace(String s, const String oldChar, const String newChar);
__int16 calcBrightness(int Brightness, const String s);
double calcContrast(double Contrast, const String s);
void RestartLog(String data);
void Log(const String data);
String removeTags(String s);


void setLoggingOn(bool b);
void setLogDir(String s);
float MyStrToFloat(String s);
String GetFromIniFile(const String Chapter, const String Part, const String Default, const String Filename);
void PutInIniFile(const String Chapter, const String Part, const String Value, const String Filename);

String GetLanguageString(const String Part, const String Default);
String expandPicutureFileName(String s);
bool allNumbers(const String s);
int getLeadingNumber(String s);
String NextPrevSong(String s, bool increase);
void LogThisDay(String s);


//---------------------------------------------------------------------------
#endif
