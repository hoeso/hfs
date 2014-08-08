<?php
unset($arr);
$arr[0]=0;// hier Feld 0 rein = Projekt
$arr[1]=1;// hier Feld 1 rein = Beschreibung
$dim=count($arr);
gibFelderArray( $MySQLDb, "SELECT Projekt, Beschreibung FROM EDV WHERE ID={$_REQUEST['ID']}", $arr );
if( false == habWas( $arr, 0, 1 ) )
{
  mysql_close( $lkid );
  echo "kein Zugriff auf Elemente Relation <b>EDV</b>";
  $_E['wZu']="anbietendKnopfZurueck";
  include("forkZu.inc");
}
dtUmlaute2Tex( $arr[1] );
entwertenSonderzeichenTex( $arr[1] );

$datei=$BERICHT_ROOT . "hoermann{$_REQUEST['ID']}.tex";

anhaengenAnDatei( $datei, "\documentclass[a4paper,9pt]{scrreprt}\n" );
anhaengenAnDatei( $datei, "\usepackage[latin9]{inputenc}\n" );
anhaengenAnDatei( $datei, "\usepackage{graphicx}\n" );
anhaengenAnDatei( $datei, "\usepackage{color}\n" );
anhaengenAnDatei( $datei, "\usepackage[right]{eurosym}\n" );
anhaengenAnDatei( $datei, "\usepackage{ngerman}\n" );
//anhaengenAnDatei( $datei, "\usepackage{chngcntr}\n" );
$datum = date("d.m.Y");
anhaengenAnDatei( $datei, "\date{" );
anhaengenAnDatei( $datei, "$datum}\n" );
anhaengenAnDatei( $datei, "\author{H\"ormann Solutions}\n" );
anhaengenAnDatei( $datei, "\pagestyle{empty}\n" );
dtUmlaute2Tex( $arr[0] );
entwertenSonderzeichenTex( $arr[0] );
anhaengenAnDatei( $datei, "\\title{Angebot zum EDV-Projekt Nummer {$_REQUEST['ID']}: $arr[0]}\n" );
anhaengenAnDatei( $datei, "\begin{document}\n" );
anhaengenAnDatei( $datei, "\maketitle\n" );
//anhaengenAnDatei( $datei, "\\tableofcontents\n" );
anhaengenAnDatei( $datei, "\setcounter{chapter}{" );
anhaengenAnDatei( $datei, "{$_REQUEST['ID']}}\n" );
anhaengenAnDatei( $datei, "\chapter*{" );
anhaengenAnDatei( $datei, "$arr[0]}\n" );
anhaengenAnDatei( $datei, "$arr[1]\n" );

$arrA[0]=0;// hier Feld 0 rein = Section
$arrA[1]=1;// hier Feld 1 rein = Details
$arrA[2]=2;// hier Feld 2 rein = realisierungsStunden
$arrA[3]=3;// hier Feld 3 rein = ID
$arrA[4]=4;// hier Feld 4 rein = Festpreis
$arrA[5]=5;// hier Feld 5 rein = Spende
$dim=count($arrA);
gibFelderArray( $MySQLDb, "SELECT Section, Details, realisierungsStunden, ID, Festpreis, Spende FROM Angebot WHERE EDVID={$_REQUEST['ID']} ORDER BY Position", $arrA );
if( false == habWas( $arrA, 0, $dim ) )
{
  anhaengenAnDatei( $datei, "\end{document}\n" );
  $_E['wZu']="anbietendKnopfZurueck";
  include("forkZu.inc");
}
//anhaengenAnDatei( $datei, "\newcounter{section}[chapter]\n" );

for( $i=0; $i<count($arrA); $i += $dim )
{
  $i1 = $i+1;
  $i2 = $i+2;
  $i3 = $i+3;
  $i4 = $i+4;
  $i5 = $i+5;
  dtUmlaute2Tex( $arrA[$i] );
  dtUmlaute2Tex( $arrA[$i1] );
  entwertenSonderzeichenTex( $arrA[$i] );
  entwertenSonderzeichenTex( $arrA[$i1] );
  anhaengenAnDatei( $datei, "\section{" );
  anhaengenAnDatei( $datei, "$arrA[$i]}\n" );
  anhaengenAnDatei( $datei, "$arrA[$i1]\n" );
  unset($arrB);
  gibFeldArray( $MySQLDb, "SELECT Beistellung FROM Beistellung WHERE AngebotID=$arrA[$i3] AND 'nein' = erfolgt", 0, $arrB );
  if( !count( $arrB ) )
  {
    if( $arrA[$i2] )
    {
      anhaengenAnDatei( $datei, "\paragraph{Aufwand in Stunden:}" );
      anhaengenAnDatei( $datei, " $arrA[$i2]\n" );
    }
    else if( 0 < $arrA[$i4] )
    {
      anhaengenAnDatei( $datei, "\paragraph{Festpreis:}" );
      $a = explode(".", $arrA[$i4]);
      anhaengenAnDatei( $datei, " $a[0],- Euro\n" );
    }
    else if( 0 < $arrA[$i5] )
    {
      anhaengenAnDatei( $datei, "\paragraph{Spende:}" );
      $a = explode(".", $arrA[$i5]);
      anhaengenAnDatei( $datei, " $a[0],- Euro\n" );
    }
  }
  else
  {
    for( $c=0; $c<count($arrB); $c++ )
    {
      anhaengenAnDatei( $datei, "\subsection{Beistellung}" );
      anhaengenAnDatei( $datei, "\\textcolor{red}{" );
      dtUmlaute2Tex( $arrB[$c] );
      anhaengenAnDatei( $datei, "$arrB[$c]}\n" );
    }
  }
}

anhaengenAnDatei( $datei, "\section{Zusammenfassung}" );
$section=1;
$h=0;
$fBeistellung=false;
for( $i=0; $i<count($arrA); $i += $dim )
{
  $i1 = $i+1;
  $i2 = $i+2;
  $i3 = $i+3;
  $f=gibFeld( $MySQLDb, "SELECT Beistellung FROM Beistellung WHERE AngebotID=$arrA[$i3] AND 'nein' = erfolgt", 0 );
  if( $f )
  {
    anhaengenAnDatei( $datei, "Absatz {$_REQUEST['ID']}.$section : Beistellung erforderlich\\\\\n" );
    $fBeistellung=true;
  }
  else if( $arrA[$i2] )
  {
    $str = sprintf( "%02d", $arrA[$i2] );
    dtUmlaute2Tex( $str );
    entwertenSonderzeichenTex( $str );
    $section = sprintf( "%02d", $section );
    anhaengenAnDatei( $datei, "Absatz {$_REQUEST['ID']}.$section : $str Stunden\\\\\n" );
    $h += $arrA[$i2];
  }
  ++$section;
}

$section=1;
$f=0;
$fBeistellung=false;

for( $i=0; $i<count($arrA); $i += $dim )
{
  $i1 = $i+1;
  $i2 = $i+2;
  $i3 = $i+3;
  $i4 = $i+4;
  $f=gibFeld( $MySQLDb, "SELECT Beistellung FROM Beistellung WHERE AngebotID=$arrA[$i3] AND 'nein' = erfolgt", 0 );
  if( $f )
  {
    $section = sprintf( "%02d", $section );
    anhaengenAnDatei( $datei, "Absatz {$_REQUEST['ID']}.$section : Beistellung erforderlich\\\\\n" );
    $fBeistellung=true;
  }
  else if( 0 < $arrA[$i4] )
  {
    $a = explode(".", $arrA[$i4]);
    anhaengenAnDatei( $datei, "Absatz {$_REQUEST['ID']}.$section : $a[0],- Festpreis\\\\\n" );
    $f += $arrA[$i4];
  }
  ++$section;
}
$section=1;
$s=0;

for( $i=0; $i<count($arrA); $i += $dim )
{
  $i1 = $i+1;
  $i2 = $i+2;
  $i3 = $i+3;
  $i4 = $i+4;
  $i5 = $i+5;
  if( 0 < $arrA[$i5] )
  {
    $a = explode(".", $arrA[$i5]);
    anhaengenAnDatei( $datei, "Absatz {$_REQUEST['ID']}.$section : $a[0],- Open Source Spende\\\\\n" );
    $s += $arrA[$i5];
  }
  ++$section;
}

anhaengenAnDatei( $datei, "\section{Angebotspreis}" );
if( true == $fBeistellung )
  anhaengenAnDatei( $datei, "Ein Angebot kann erst nach dem Erbringen der Beistellungen abgegeben werden\\\\\n" );
else
{
  anhaengenAnDatei( $datei, "Realisierungsaufwand : $h Stunden\\\\\n" );
  $euro=gibFeld( $MySQLDb, "SELECT Stundensatz FROM EDV, Zeitstempel, Stundensatz WHERE EDV.ID={$_REQUEST['ID']} AND versandtAm >= Zeitstempel.Datum AND Zeitstempel.ID=Stundensatz.ZeitstempelID ORDER BY Datum DESC", 0 );
  $euro = $euro * $h;
  $sum=number_format($euro,'2',',','.');
  anhaengenAnDatei( $datei, "\\\\Angebot : $sum \euro\ netto zzgl. gesetzlicher MWSt.\\\\\n" );
  $sum=number_format($s,'2',',','.');
  anhaengenAnDatei( $datei, "\\\\Spende Open Source: $sum \euro\\\\\n" );
}
anhaengenAnDatei( $datei, "\end{document}\n" );
?>
