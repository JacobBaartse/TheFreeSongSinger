/*
Open source not for commercial deployment
*/
//---------------------------------------------------------------------------


#pragma hdrstop

#include "Search.h"
#include "GlobalUnit.h"


//---------------------------------------------------------------------------
String programDir="";
char * searchStrings[MAX_SEARCH_WORDS];
int searchStringsStart[MAX_SEARCH_WORDS];
SongData curSong;
String fistSongPart;
String prevSearchString;

char replaceArray  [256] =
  {
  //nul soh stx etx eot enq ack bel bs  tab lf  vt  ff  cr  so  si  dle dc1 dc2 dc3 dc4 nak syn etb can em  sub esc fs  gs  rs  us
    ' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',

  // !   "   #   $   %   &   '   (   )   *   +   ,   -   .   /   0   1   2   3   4   5   6   7   8   9   :   ;   <   =   >   ?
    ' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',

  // @   A   B   C   D   E   F   G   H   I   J   K   L   M   N   O   P   Q   R   S   T   U   V   W   X   Y   Z   [   \   ]   ^   _
    ' ','A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z',' ',' ',' ',' ',' ',

  // '   a   b   c   d   e   f   g   h   i   j   k   l   m   n   o   p   q   r   s   t   u   v   w   x   y   Z   {   |   }   ~
    ' ','A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z',' ',' ',' ',' ',' ',

  // €      ‚   ƒ   "   …   †   ‡   ˆ   ‰   Š   ‹   Œ      Ž          '   '   "   "   o   -   -   ˜   ™   š   ›   œ      ž   Ÿ
    'E',' ',' ','F',' ',' ',' ',' ',' ',' ','S',' ',' ',' ','Z',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','S',' ',' ',' ','Z','Y',

  //     ¡   ¢   £   ¤   ¥   ¦   §   ¨   ©   ª   "       ­   ®   ¯   °   ±   ²   ³   ´   µ      ·   ¸   ¹   º   "   ¼   ½   ¾   ¿
    ' ','I','C','L',' ','Y',' ','S',' ','C','A',' ',' ',' ','R',' ',' ',' ',' ',' ',' ','U',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',

  // À   Á   Â   Ã   Ä   Å   Æ   Ç   È   É   Ê   Ë   Ì   Í   Î   Ï   Ð   Ñ   Ò   Ó   Ô   Õ   Ö   ×   Ø   Ù   Ú   Û   Ü   Ý   Þ   ß
    'A','A','A','A','A','A',' ','C','E','E','E','E','I','I','I','I','D','N','O','O','O','O','O','X','O','U','U','U','U','Y',' ',' ',

  // à   á   â   ã   ä   å   æ   ç   è   é   ê   ë   ì   í   î   ï   ð   ñ   ò   ó   ô   õ   ö   ÷   ø   ù   ú   û   ü   ý   þ   ÿ
    'A','A','A','A','A','A',' ','C','E','E','E','E','I','I','I','I','O','N','O','O','O','O','O',' ','O','U','U','U','U','Y',' ','Y',
   };



void findText(String searchString)
{
    if (searchString.Pos("?")==1)
       searchString = prevSearchString  + " " +  getAfter(searchString,"?");

    if (searchString.Length()>250)
    {
         MessageDlg("Search string too long max 256 characters are supported.", mtInformation, TMsgDlgButtons()<<mbOK , 0);
         return;
    }

    prevSearchString = searchString;

    // convert the search string to uppercase and skipp special characters.
    char caSearchString[256];
    char previousChar=' ';
    caSearchString[0]=' ';
    int j=1;
    for (int i=0; i< searchString.Length(); i++)
    {
        char currChar=(char)searchString[i+1];
        if ((replaceArray[currChar] == ' ') && (previousChar==' '))
        {
        }
        else
        {
          caSearchString[j]= replaceArray[currChar];
          previousChar = replaceArray[currChar];
          j++;
        }
    }
    caSearchString[j]=' ';
    j++;
    caSearchString[j] = '\0';

    const int MaxSearchResult = 20;
    if (searchString.Length() == 0)  return;

    // find for all songs where the searchString occures
    char buffer[32*1024];  // max song size 32 kb

    //reserve memory to store tempory results
    int hitRates[MaxSearchResult];
    String firstLine[MaxSearchResult];
    for (int i=0; i<MaxSearchResult; i++)   hitRates[i]=0;
    for (int i=0; i<MaxSearchResult; i++)   firstLine[i]="";
    int numberOfWords=0;

    ifstream searchIndexFile2( (programDir + "searchindex.txt").c_str() );
    if (searchIndexFile2.is_open())
    {
        //split search string
        String tempSearchString =  caSearchString;
        // remove leading spaces
        while (tempSearchString.Length()>0 && tempSearchString[1]==' ')
             tempSearchString = tempSearchString.SubString(2,tempSearchString.Length());

        while ((numberOfWords< MAX_SEARCH_WORDS) && (tempSearchString.Length()>1))
        {
           int spacePos =  tempSearchString.Pos(" ");
           if (numberOfWords==0)
           {
                strcpy(searchStrings[numberOfWords],((String)" " + tempSearchString.SubString(0,spacePos)).c_str());
           }
           else
           {
                strcpy(searchStrings[numberOfWords],((String)searchStrings[numberOfWords-1] + tempSearchString.SubString(0,spacePos)).c_str());
           }
           searchStringsStart[numberOfWords+1] = strlen(searchStrings[numberOfWords])-1;

           tempSearchString = tempSearchString.SubString(spacePos,tempSearchString.Length());
           numberOfWords++;
           // remove leading spaces
           while (tempSearchString.Length()>0 && tempSearchString[1]==' ')
                tempSearchString = tempSearchString.SubString(2,tempSearchString.Length());
        }

        int hitRate;
        int hitLevel = 1;

        //declare all variables out of the loop to speed up.
        searchIndexFile2.getline(buffer,32*1024);
        char * tempSubStrPtr;
        char * subStrPtr;
        char * prevSubStrPnt;
        char * lastHit;
        int temp;
        int i,j,badMatch;
        while (!searchIndexFile2.eof())
        {

           if (buffer[1]=='t')
           {
             hitRate=0;
             i=0;
             j=0;
             prevSubStrPnt = buffer;
             lastHit=buffer;

             while (i<  numberOfWords)
             {
               subStrPtr = strstr(buffer, searchStrings[i] + searchStringsStart[j]);

               if (subStrPtr!=NULL)  // found good text
               {
                       if (prevSubStrPnt!=buffer)  // find the new string in the prev search result
                               tempSubStrPtr = strstr(prevSubStrPnt, searchStrings[i] + searchStringsStart[j]);
                       else tempSubStrPtr = subStrPtr;

                       if (tempSubStrPtr!=NULL)
                       {
                               temp = tempSubStrPtr - prevSubStrPnt;

                               if (temp>0)
                               {
                                        temp = 5000 / (temp+5);
                                        hitRate+= temp;
                               }
                               lastHit = tempSubStrPtr;
                       }
                       else lastHit = subStrPtr;

                       hitRate+= (strlen(searchStrings[i] + searchStringsStart[j]) *
                                  strlen(searchStrings[i] + searchStringsStart[j])   )* 10;
                       i++;  //search on one word more.
               }
               else
               {
                       prevSubStrPnt=lastHit;
                       j++; //search on one word less
                       if (j>i) i=j; //to the next word
               }
             }

             if (hitRate> hitLevel)
             {
               // find bad match in the list to be replaced.
               badMatch=0;
               for (j=0; j<MaxSearchResult; j++)
               {
                  if (hitRates[j] < hitRates[badMatch]) badMatch=j;
               }
               if (hitRates[badMatch]>0)
                   hitLevel =  hitRates[badMatch];

               hitRates[badMatch]= hitRate;

               while ((buffer[1] !='n') &&  (!searchIndexFile2.eof()) )
               {
                   searchIndexFile2.getline(buffer,32*1024);
               }
               //show the found song in the result.
               String fileSongName = buffer;
               fileSongName =  fileSongName.SubString(5,100);
               while ((buffer[1] !='t') &&  (!searchIndexFile2.eof()) )
               {
                   searchIndexFile2.getline(buffer,32*1024);
                   if (buffer[1] !='t')
                   {
                           String moreSongText = buffer;
                           fileSongName += ("\n" + moreSongText.SubString(5,100));
                   }
               }
               firstLine[badMatch] = fileSongName;
             }
             else
             {
               while ((buffer[1] !='n') &&  (!searchIndexFile2.eof()) )
               {
                   searchIndexFile2.getline(buffer,32*1024);
               }
               while ((buffer[1] !='t') &&  (!searchIndexFile2.eof()) )
               {
                   searchIndexFile2.getline(buffer,32*1024);
               }
             }
           }// not <t>
           else
           {
              searchIndexFile2.getline(buffer,32*1024);
           }

       }


        //sort the search result
        bool toggled=true;
        while (toggled)
        {
          toggled = false;
          for (int i=1; i<MaxSearchResult; i++)
          {
                if (hitRates[i] > hitRates[i-1])
                {
                        int tempI =  hitRates[i-1];
                        String tempS = firstLine[i-1];
                        hitRates[i-1] = hitRates[i];
                        firstLine[i-1] = firstLine[i];
                        hitRates[i] = tempI;
                        firstLine[i] = tempS;
                        toggled=true;
                }
          }
        }

        MainForm->SearchResult->Clear();
        for (int j=0; j<MaxSearchResult; j++)
        {
          if  (hitRates[j]>(hitRates[0]/5))//(hitRates[j]>0)
          {
            MainForm->SearchResult->Items->Add(firstLine[j].c_str());
//            " ( " + IntToStr(hitRates[j]).c_str() + " )"
          }
        }
        MainForm->SearchResult->ItemIndex=0;
        MainForm->LastUsed = "SearchResult";
    }
    else
    {       //no search index available
            MessageDlg("No search index found, (re)create the search index.", mtInformation, TMsgDlgButtons()<<mbOK , 0);
    }

}



void searchInit(String s)
{
    programDir = s;
    for (int i=0; i<MAX_SEARCH_WORDS; i++)
        searchStrings[i]= new char[256];
}


void createSearchIndex()
{
    String tempProgressMessage = MainForm->IndexProgress->Caption;
    MainForm->IndexProgress->Caption = GetLanguageString("creatIndexWait","Creating search index please wait ....");
    MainForm->IndexProgress->Refresh();

    WIN32_FIND_DATA      finddata;
    HANDLE               hFind;

    String songText;
    String fistSongPart;


    String indexFileName = String(programDir + "searchindex.txt");
    ofstream searchIndexFile(indexFileName.c_str());

    for (char i='A'; i<='Z'; i++)
    {
        AnsiString filePatern = programDir + "DATA\\" + i + "\\L*.txt";

        hFind = FindFirstFile(filePatern.c_str(), &finddata);
        if (hFind != INVALID_HANDLE_VALUE)
        {
            do
            {
                // Do Something with found file...

                String songName = finddata.cFileName;
                songName = getAfter(songName.UpperCase() , "L");
                songName = getUntil(songName, ".TXT");
                while ((songName.Pos("0")==1) && songName.Length()>1)
                       songName= songName.SubString(2,songName.Length());
                //copy the song to the search index.
                if (curSong.LoadSong((String)i+songName))
                {
                    // write the songnumber and first line to the index file.
                    fistSongPart = "<n> " + curSong.shortFileNameAndVers + ",'";
                    songText = "<t> ";

                    for (int i=0; i< curSong.getSongLength(); i++)
                    {
                        if (curSong.text[i].Pos("<acc>")>0)
                        {
                           fistSongPart += " º ";
                           break;
                        }
                    }

                    for (int i=0; i< curSong.getSongLength(); i++)
                    {
                        if (curSong.text[i].Pos("<acc>")>0)
                           curSong.text[i] = "";
                           
                        curSong.text[i] = removeTags(curSong.text[i]);
                        if (fistSongPart.Length()<80)
                              fistSongPart+= replace(curSong.text[i],"'","") +" ";

                        curSong.text[i] = converToUpperOnly(curSong.text[i]);
                        songText += curSong.text[i] + " ";
                    }
                    songText += "\n";
                    songText = replace(songText, "  ", " ");
                    fistSongPart += "'\n";
                    searchIndexFile.write(songText.c_str(), songText.Length());
                    searchIndexFile.write(fistSongPart.c_str(), fistSongPart.Length());
                }
            }
            while (FindNextFile(hFind, &finddata));
        }
        FindClose(hFind);
    }
    searchIndexFile.close();
    MainForm->IndexProgress->Caption = tempProgressMessage;
}

String converToUpperOnly(String s)
{
    char * caSearchString;
    caSearchString = new char [s.Length() +1];
    char previousChar=' ';
    int j=0;
    for (int i=1; i <=s.Length(); i++)
    {
        char currChar=(char)s[i];
        if ((replaceArray[currChar] == ' ') && (previousChar==' '))
        {
        }
        else
        {
          caSearchString[j]= replaceArray[currChar];
          previousChar = replaceArray[currChar];
          j++;
        }
    }
    caSearchString[j] = '\0';
    s =  caSearchString;
    delete caSearchString;

    return s;
}
#pragma package(smart_init)
