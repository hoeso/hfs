<?php
include ("dateiRoutinen.inc");
include ("anzeigeRoutinen.inc");
include ("dbRoutines.inc");
include ("zeitRoutinen.inc");
include ("anzeigenTabelle.inc");// contains the Select-Stmt-Array $Select
include "entitySQLAbbrev.prj";

function fuellen( $wert, $len, $fuellZ )
{
   $c = $len - strlen( $wert );
   for( ; $c>0; $c-- )
			if( !isset($str) )
        $str = "$fuellZ";//Nullen voranstellen
			else
        $str .= "$fuellZ";//Nullen voranstellen
	 if( isset($str) )
     $str .= $wert;
	 else
     $str = $wert;
   return $str;
}

// wenn Inhalt ungleich dem Index, dann wurde gefuellt
function habWas( $arr, $start, $ende )
{
  if( $ende <= $start )
  {
    ?>Du stehst wohl auf Endlos-Schleifen, wa?!<br><?php
    exit;
  }
  for( $i=$start; $i<=$ende; $i++ )
  {
    if( !isset($arr[$i]) )
      break;
    if( $arr[$i] != $i )
      return true;
  }
  return false;
}

function istForeignKeyName( $feld )
{
	$len = strlen($feld) - 2;
	$str = substr($feld, $len, 2); 
	if( strstr($str, "ID" ) )
	    return true;
	return false;
}
function gibCent2stellig( &$betrag )
{
	$pos = strrpos($betrag,'.');
	if( !$pos )
	    $betrag .=".00";
	else
	{
		$len = strlen($betrag);
		if( $len - $pos == 2 )
			    $betrag .="0";
	}
}
function cent2stelligMachen( $betrag )
{
   $arr=explode(".",$betrag);
   $nachkomma=$arr[1][0];
   $ch=$arr[1][2];
   if( $ch < 5 )
      $nachkomma.=$arr[1][1];
   else
      $nachkomma.=$arr[1][1]+1;
   $betrag="$arr[0].$nachkomma";
}
function gibWert( $row, $arrSpalte, $Spalte, &$attribut )
{
	$i=0;
	foreach( $row as $elem )
	{
		if( $Spalte == $arrSpalte[$i] )
		{
		    $attribut = $elem;
		    break;
		}
		$i++;
	}
}
function abschneidenID( $string )
{
	$len = strlen($string) - 2;
	$str = substr($string, $len, 2); 

	if( strstr($str, "ID" ) )
		return str_replace( "ID", "", $string );
	return "";
}
function wertErhoehen( $row, $arrSpalte, $Spalte, &$sum )
{
	$i=0;
	foreach( $row as $elem )
	{
		if( $Spalte == $arrSpalte[$i] )
		{
		    $sum += $elem;
		    break;
		}
		$i++;
	}
}
function dtUmlaute2Tex( &$strUmlaut )
{
  $strUmlaut=str_replace( "ä", "\"a", $strUmlaut );
  $strUmlaut=str_replace( "Ä", "\"A", $strUmlaut );
  $strUmlaut=str_replace( "ö", "\"o", $strUmlaut );
  $strUmlaut=str_replace( "Ö", "\"O", $strUmlaut );
  $strUmlaut=str_replace( "ü", "\"u", $strUmlaut );
  $strUmlaut=str_replace( "Ü", "\"U", $strUmlaut );
  $strUmlaut=str_replace( "ß", "\"s", $strUmlaut );
// Gaensefuesschen auch noch gleich:
}
function entwertenSonderzeichenTex( &$strSonderzeichen )
{
  $strSonderzeichen=str_replace( "_", "\\_", $strSonderzeichen );
  $strSonderzeichen=str_replace( "$", "\\$", $strSonderzeichen );
  $strSonderzeichen=str_replace( "%", "\\%", $strSonderzeichen );
  $strSonderzeichen=str_replace( "&", "\\&", $strSonderzeichen );
}
/*** diese Funktion stammt von:
 *** https://www.tutorials.de/threads/timestamp-aus-kw-wochentag-und-jahr-bilden.297102/
 ***/
function kalenderwoche($kw, $year) {
    $time = strtotime("4 January " . $year);
    if (date('w', $time) != 1)
        $time = strtotime("last Monday", $time);
    $time = strtotime("+" . ($kw - 1) . " weeks", $time);
   
    return $time;
}
/*** Ausdruecke fuer strtotime():
 ***/
$cfsWochentag = array
( // Index korrespondiert mit Entitaet 'Tag'
  "",
  /*1*/"monday",
  /*2*/"tuesday",
  /*3*/"wednesday",
  /*4*/"thursday",
  /*5*/"friday",
  /*6*/"saturday",
  /*7*/"sunday"
);

function gibDokumentenVerzeichnis( $sf, $rootDir, &$rootSubD, &$childSubD )
{
  if( isset( $sf[ 6 ] ) )
  {
    $rootSubD = "{$sf[0]}{$sf[1]}{$sf[2]}{$sf[3]}/";
    $childSubD = intval("{$sf[4]}{$sf[5]}{$sf[6]}");
  }
  else if( isset( $sf[ 5 ] ) )
  {
    $rootSubD = "{$sf[0]}{$sf[1]}{$sf[2]}/";
    $childSubD = intval("{$sf[3]}{$sf[4]}{$sf[5]}");
  }
  else if( isset( $sf[ 4 ] ) )
  {
    $rootSubD = "{$sf[0]}{$sf[1]}/";
    $childSubD = intval("{$sf[2]}{$sf[3]}{$sf[4]}");
  }
  else if( isset( $sf[ 3 ] ) )
  { // 1000 - 9999
    $rootSubD = "{$sf[0]}/";
    $childSubD = intval("{$sf[1]}{$sf[2]}{$sf[3]}");
  }
  else if( isset( $sf[ 2 ] ) )
  { // 100 - 999
    $rootSubD = "0/";
    $childSubD = intval("{$sf[0]}{$sf[1]}{$sf[2]}");
  } // 10 - 99
  else if( isset( $sf[ 1 ] ) )
  {
    $rootSubD = "0/";
    $childSubD = intval("{$sf[0]}{$sf[1]}");
  }
  else if( isset( $sf[ 0 ] ) )
  { // 0 - 9
    $rootSubD = "0/";
    $childSubD = "{$sf[0]}{$sf[1]}";
  }
  if( !is_dir( $rootDir . $rootSubD ) )
    mkdir( $rootDir . $rootSubD );
  if( !is_dir( $rootDir . $rootSubD . $childSubD ) )
    mkdir( $rootDir . $rootSubD . $childSubD );
}
?>
