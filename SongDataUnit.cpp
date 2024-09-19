/*
Open source not for commercial deployment
*/
//---------------------------------------------------------------------------


#pragma hdrstop

#include "SongDataUnit.h"
#include "GlobalUnit.h"
#include "OutputScreenUnit.h"




String SongBaseDir;

SongData::SongData()
{
    copyRightText="";
    ToneHeightText="";
    fileName="";
    TitleText="";
    songLength=0;
    previewSong=false;
    doDecrypt=false;
    protectedSong=false;
    Tones ="D___Eb__E___F___F#__G___G#__A___Bb__B___C___C#__D___Dis_E___F___Fis_G___Gis_A___Ais_B___C___Cis_D___D#__E___F___Ges_G___Aes_A___A#__B___C___Des_D___Ees_E___F___Gb__G___Ab__A___Bes_B___C___Db__D___Ees_";
}

int SongData::getSongLength()
{
    return songLength;
}

void  SongData::setSongLength(int i)
{
    songLength = i;
    SendToSlaves();
}

bool SongData::LoadSong(String s)     // return true if new, different text is loaded.
{
    if (s.Length()==0) return false;
    if (s[1]=='|')
    {
      SetText(getAfter(s,"|"));
      shortFileNameAndVers = s;
      return true;
    }
    if (s.Pos("ViewFile_")==1)
    {
      String smallFilename = getAfter(s,"ViewFile_");
      smallFilename = getAfter(s,"_");
      while (smallFilename.Pos("\\")>0) smallFilename = getAfter(smallFilename,"\\");
      smallFilename = getUntil(smallFilename,".");
      text[0] = smallFilename+"                                           [command ·" + s + "]";
      songLength = 1;
      shortFileNameAndVers = s;
      return true;
    }
    s=getUntil(s, "_");  // remove _LineNr_n  , other sub commands.

    //if (shortFileNameAndVers == s) return true; // text already loaded to speed up do not reload.
    String newShortFileName = s;

    String verses;
    String book;

    //split up book and verses
    book=getUntil(s,":");
    //remove spaces from book
    book = replace(book, " ", "");
    verses=getAfter(s,":");

    String newFileName = getFileName(book);
    char buffer[1024];
    ifstream songFile (newFileName.c_str());

    if (! songFile.is_open())
       return false;

    fileName = newFileName;


    int index = 0;
    bool allTextRead= false;
    bool inTextArea = false;
    bool inCopyRightArea = false;

    int textTagPos;
    songLength = 0;

    ToneHeightText = "";
    TitleText = "";
    copyRightText ="";
    if (book.Length()<2)return false;

    shortFileNameAndVers = newShortFileName;  // file found store the current loaded file
    doDecrypt=false;

    while (! allTextRead )
    {
        songFile.getline (buffer,1024);
        String lineBuffer = buffer;

        lineBuffer = Decrypt(lineBuffer);

        //remove tabs from the lineBuffer
        lineBuffer =  replace(lineBuffer, "\t", " ");

        //remove spaces at the end of the line buffer
        if (lineBuffer != NULL)
            if (lineBuffer.Length()>0)
        {
            bool spacesFound = (lineBuffer[lineBuffer.Length()] == ' ');
            while (spacesFound)
            {
                lineBuffer = lineBuffer.SubString(0, lineBuffer.Length() -1 );
                if (lineBuffer.Length()>0)
                {
                    spacesFound = lineBuffer[lineBuffer.Length()] == ' ';
                }
                else
                {
                    spacesFound = false;
                }
            }
        }

        textTagPos = lineBuffer.Pos("<tekst>");
        if (textTagPos != 0)
        {
            lineBuffer=lineBuffer.SubString(textTagPos + 7, lineBuffer.Length());
            text[index]=lineBuffer;
            inTextArea=true;
        }
        int textTagPos = lineBuffer.Pos("</tekst>");
        if (textTagPos != 0)
        {
            lineBuffer=lineBuffer.SubString(0,textTagPos-1);
            text[index]=lineBuffer;
            inTextArea=false;
            index++;
        }
        if (inTextArea)
        {
            if (index < MAX_SONG_LENGTH)
            {
                text[index]=lineBuffer;
                index++;
            }
        }

           textTagPos = lineBuffer.Pos("<oorsprong>");
           if (textTagPos != 0)
           {
                lineBuffer=lineBuffer.SubString(textTagPos + 11, lineBuffer.Length());
           }
           textTagPos = lineBuffer.Pos("</oorsprong>");
           if (textTagPos != 0)
           {
                lineBuffer=lineBuffer.SubString(0,textTagPos-1);
                if (lineBuffer.Length()>1)
                {
                   copyRightText = "Oorsprong: " + lineBuffer + " ";
                }
           }

           textTagPos = lineBuffer.Pos("<copyrights>");
           if (textTagPos != 0)
           {
                lineBuffer=lineBuffer.SubString(textTagPos + 12, lineBuffer.Length());
                inCopyRightArea=true;
           }
           textTagPos = lineBuffer.Pos("</copyrights>");
           if (textTagPos != 0)
           {
              lineBuffer=lineBuffer.SubString(0,textTagPos-1);
              copyRightText =  lineBuffer + " " + copyRightText;
              inCopyRightArea=false;
           }
           if (inCopyRightArea)
           {
              copyRightText =  copyRightText + lineBuffer;
           }

           textTagPos = lineBuffer.Pos("<toonsoort1>");
           if (textTagPos != 0)
           {
              lineBuffer=lineBuffer.SubString(textTagPos + 12, lineBuffer.Length());
           }
           textTagPos = lineBuffer.Pos("</toonsoort1>");
           if (textTagPos != 0)
           {
              lineBuffer=lineBuffer.SubString(0,textTagPos-1);
              ToneHeightText = lineBuffer;
           }

           textTagPos = lineBuffer.Pos("<titel>");
           if (textTagPos != 0)
           {
              lineBuffer=lineBuffer.SubString(textTagPos + 7, lineBuffer.Length());
           }
           textTagPos = lineBuffer.Pos("</titel>");
           if (textTagPos != 0)
           {
              lineBuffer=lineBuffer.SubString(0,textTagPos-1);
              TitleText = lineBuffer;
           }


        if (songFile.eof()) allTextRead=true;
    }
    songFile.close();

    if (inTextArea==true)
    {
       index = 0; // </text> not found something corrupt or not correct decrypted.
    }
    songLength = index;

    getSpecificVerses(verses);
    
    //remove empty lines at the end of the song.
    while ((songLength>0) &&( text[songLength-1].Length() == 0))
    {
        songLength--;
    }

     SendToSlaves();
    if (!previewSong) OutputScreen->calcMarginTextReduction = true;

    return true;
};

void SongData::SetBaseDir(String pBaseDir)
{
        SongBaseDir=pBaseDir+"Data\\";
};

String SongData::getFileName(String book)
{
        if (book.Length()<2) return "";
        if ((book.operator [](2) >= '0') &&
            (book.operator [](2) <= '9'))
        {
            while (book.Length()<4)
            {
                String tmp = book.SubString(0,1);
                tmp =  book.SubString(2,book.Length());

                book = book.SubString(0,1)+ "0" + book.SubString(2,book.Length());
            }
            return SongBaseDir + book.SubString(0,1)+"\\L"+book.SubString(2,book.Length())+".txt";
        }
        return SongBaseDir + "bible\\" + book + ".txt";
}


String SongData::Decrypt(String lineBuffer)
{
        if (lineBuffer.Pos("</encrypted>")>0)
        {
                doDecrypt=false;
                lineBuffer = lineBuffer.SubString(lineBuffer.Pos("</encrypted>")+12, lineBuffer.Length());
        }
        if (doDecrypt)lineBuffer = DecryptString(lineBuffer);
        if (lineBuffer.Pos("<encrypted>")>0)
        {
                doDecrypt=true;
                protectedSong=true;
                initPseudoRandom();
                DecryptString(lineBuffer[lineBuffer.Pos("<encrypted>")+11] );
                lineBuffer =
                        lineBuffer.SubString(1,lineBuffer.Pos("<encrypted>")-1) +
                        DecryptString(lineBuffer.SubString(lineBuffer.Pos("<encrypted>")+12, lineBuffer.Length()));
        }
        return lineBuffer;
}


void SongData::getSpecificVerses(String verses)
{
          if (verses.Length()==0)
                return;

          songLengthCopy=0;
          String versNr="";
          String versSeparator="";
          String startVers="";
          int index =1;

          //remove leading spaces.
          while (verses.SubString(1,1)==" ")
                verses = verses.SubString(2,verses.Length());

          //process verses
          while (index <= verses.Length())
          {
                if ((verses[index]=='-') || (verses[index]==' '))
                {
                        if (startVers.Length()>0)
                        {
                                copySongText( startVers, versNr, versSeparator);
                                if (versSeparator=='-') startVers = "";
                                else startVers = versNr;
                        }
                        else
                        {
                                startVers = versNr;
                        }
                        versNr="";
                        versSeparator = verses[index];
                }
                else
                {
                        versNr = versNr + verses[index];
                }
                index++;
          }
          if (startVers.Length()>0)
             copySongText( startVers, versNr, versSeparator);
          if (versSeparator!="-")
             copySongText(versNr, versNr, versSeparator);
             
          for (int i=0; i<songLengthCopy; i++)
          {
                text[i]=textCopy[i];
          }
          songLength = songLengthCopy;

}

// copy part of text to textCopy
void SongData::copySongText(String startVers, String endVers, String versSeparator)
{
        if (startVers.Length() == 0) startVers="0";
        if (endVers.Length() ==0) endVers="1000";
        int start = StrToInt(startVers);
        int end = StrToInt(endVers);
        if (versSeparator==" ") end=start;
        start = FindCoupletLinenr(start, false);
        end = FindCoupletLinenr(end + 1, true);
        for (int i=start; i<end; i++)
        {
                textCopy[songLengthCopy]=text[i];
                songLengthCopy++;
        }
}

int SongData::FindCoupletLinenr(String CoupletNumber, bool untilVerse)
{
    int coupletToFind = StrToInt(CoupletNumber);
    int prevCoupletNrPos = 0;
    bool coupletFound = false;
    int newSongStartLine = 0;
    while (!coupletFound)
    {
        String tempSongLine =  text[newSongStartLine];
        bool done=false;
        if (tempSongLine.Length()>0)
        do  // remove leading stuff
        {
                char firstChar = tempSongLine[1];
                switch (firstChar)
                {
                        case '<' :
                                tempSongLine = getAfter(tempSongLine,">");
                                break;
                        case ' ' :
                        case '\t':
                                tempSongLine = tempSongLine.SubString(2,tempSongLine.Length()-1);
                                break;
                        default : done=true;
                }
                if (tempSongLine.Length()==0) done=true;
        }
        while (!done);

        int curCouplet = getLeadingNumber(tempSongLine);

        if (curCouplet ==0) ; // do nothing
        else if (curCouplet < coupletToFind)  prevCoupletNrPos = newSongStartLine;
        else if (curCouplet == coupletToFind) return newSongStartLine;
        else
        {
          if (untilVerse) return newSongStartLine;
          else return prevCoupletNrPos;
        }

        newSongStartLine++;
        if (newSongStartLine > songLength) return songLength;
    }
    return newSongStartLine;
}


String SongData::getBeginOfText()
{
    String retval="";
    int index = 0;

    for (int i=0; i< songLength; i++)
    {
       if (text[i].Pos("<acc>")>0)
       {
          retval += " º";
          break;
       }
    }

    while ((retval.Length()<60) && (index <songLength))
    {
          if (text[index].Pos("<acc>")==0)
               retval += " " + removeTags(text[index]);
          index++;
    }
    return retval.SubString(0,60);
}

//---------------------------------------------------------------------------
void SongData::SendToSlaves()
{
     if (previewSong) return;

     String s ="<SongText>";
     s += "<titel>"+ TitleText +"</titel>\n";
     for (int i=0; i<songLength; i++)
          s += "<tekst>" +text[i] + "</tekst>\n";;
     s += "<copyrights>"+copyRightText+"</copyrights>\n";
     s += "<toonsoort1>"+ToneHeightText+"</toonsoort1>\n";
     s += "<shortFileNameAndVers>"+shortFileNameAndVers+"</shortFileNameAndVers>\n";
     s += "\n</SongText>\n";
     MainForm->SendDataToSlaves(s);
}
//---------------------------------------------------------------------------

void SongData::ReceiveAsSlave(String s)
{
     if (s.Pos("<titel>")==1) TitleText = getUntil(getAfter(s,">"),"<");
     s = getAfter(s,"</titel>\n");
     songLength = 0;
     while (s.Pos("<tekst>")==1)
     {
           text[songLength] = getUntil(getAfter(s,">"),"<");
           s = getAfter(s,"</tekst>\n");
           songLength++;
     }
     if (s.Pos("<copyrights>")==1) copyRightText = getUntil(getAfter(s,">"),"<");
     s = getAfter(s,"</copyrights>\n");
     if (s.Pos("<toonsoort1>")==1) ToneHeightText = getUntil(getAfter(s,">"),"<");
     s = getAfter(s,"</toonsoort1>\n");
     if (s.Pos("<shortFileNameAndVers>")==1) shortFileNameAndVers = getUntil(getAfter(s,">"),"<");
     s = getAfter(s,"</shortFileNameAndVers>\n");
}


void SongData::SetText(String s)
{
     s = getUntil(s,"|");
     songLength =0;
     copyRightText="";
     TitleText="";
     ToneHeightText="";
     fileName = "";
     shortFileNameAndVers = "";

     while (s.Length()>0)
     {
        text[songLength] = getUntil(s,"_");
        s = getAfter(s,"_");
        songLength ++;
     }
     SendToSlaves();
}

void SongData::Transpose(String s)
{
    LoadSong(shortFileNameAndVers);
    int transNr = StrToInt(s);
    if (transNr==0) return;
    for ( int i=0; i<songLength; i++)
     if(text[i].Pos("<acc>")==1)
     {
        String TransposedText="";
        int DoneIndex=1;
        int LengthMismatch=0;
        for (int j=6; j<= text[i].Length(); )
        {
           if (text[i][j] == ' ')
           {
              j++;
              while (LengthMismatch<0)
              {
                 TransposedText += text[i].SubString(DoneIndex, j-DoneIndex);
                 TransposedText += " ";
                 DoneIndex = j;
                 LengthMismatch++;
              }
              if (LengthMismatch>0)
              {
                 TransposedText += text[i].SubString(DoneIndex, j-DoneIndex-1);
                 DoneIndex = j;
                 LengthMismatch--;
              }
           }
           else
           {
              int foundLength=1;
              int foundTone=-1;
              for (int k=1; k<4; k++)
              {
                 String textTone = "_" + text[i].SubString(j,k) + "_";
                 int tempPos = Tones.Pos(textTone)+1;
                 
                 if (tempPos==1)
                      break;

                 foundLength = k;
                 foundTone = tempPos;
              }
              if (foundTone>-1)
              {
                TransposedText += text[i].SubString(DoneIndex, j-DoneIndex);

                int t = (foundTone + (transNr*4)+48 )%48;
                String newTone = replace(Tones.SubString(t,3),"_","");
                LengthMismatch +=  newTone.Length() - foundLength;
                TransposedText += newTone;
                DoneIndex = j+foundLength;
              }
              j+=foundLength;
            }
         }
         String tmp2 =   TransposedText + text[i].SubString(DoneIndex, text[i].Length()-DoneIndex+1);
         text[i]=  tmp2;
      }

}

void SongData::TextToNotepad()
{
    //save to the file.
    String tempFileName = SongBaseDir + "\\notepad_tmp.wri";
    ofstream editFile(tempFileName.c_str());
    if(protectedSong)
    {
               editFile.write("Text can not be changed    \n",28);
               editFile.write("send the change request to:\n",28);
               editFile.write(" j.baartse@gmail.com       \n",28);
    }
    else
    {
       for ( int i=0; i<songLength; i++)
       {
           String curLine = replace(text[i],"<acc>","");
           curLine =  replace(curLine,"<--->","");
           editFile.write(curLine.c_str(), curLine.Length());
           editFile.write("\n",1);
       }
       editFile.write("\n",1);
       editFile.write(copyRightText.c_str(), copyRightText.Length());
    }
    editFile.close();
    ShellExecuteA(this, "open", tempFileName.c_str(), NULL, NULL, SW_NORMAL);

}

#pragma package(smart_init)
